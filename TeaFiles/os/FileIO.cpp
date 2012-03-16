#include "FileIO.h"

// FileIO encapsulates all file system differences among platforms:
// 
// For windows, the Win32 Api is used, all other OSes use POSIX or *nix
//
// Other appraoches tried:
//
// C Standard IO library:
// + This library should be available in the C library of every compiler
// + Supports buffering
// - On windows, the library has bugs for files above 4GB
//
// C++ iostreams
// + "The" C++ stream library according to C++ text books
// - Still buggy implementations around
// - Horrible design, focused on text processing
// - Finally ruled out because tell and seek are not willing to return plain numbers as position. Instead the position 
//   is returned as streampos type that one is not allowed to consider as a number. 
// - The text oriented iostreams might not be tested on large files (files larger than 4GB) to the extend the base APIs are tested. Newsgroups 
//   report on problems with large files (http://bytes.com/topic/c/answers/598018-streampos-difficulties-tellg-numeric_limits-unsigned-long-int-max)
//
// POSIX librars on windows
// + With a few defines (eg #define lseek -> _lseeki64) we could be done.
// - On windows we encountered strange errors, like this:
//   {
//      int fd = open("test.tea");
//      close(fd);
//      remove("test.tea"); // fails with access denied. Investigations show that the file is not open anymore.
//   }
//
//  + So finally we use the Win32 API quite for sure has best test coverage and proliferation and that behaved as expected.

#include "../base/Exceptions.h"
#include <assert.h>

#if WIN32

#include "WinUtils.h"
#include <winbase.h>

#else

#define __USE_LARGEFILE64 1
#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#endif

namespace teatime {

#ifdef WIN32
class FileIO::State
{
public:
  State() { this->handle_ = INVALID_HANDLE_VALUE; }
  HANDLE  handle_;
};
#else
class FileIO::State
{
public:
  State() { this->fd_ = -1; }  
  int fd_;
};
#endif

// FileIO
FileIO::FileIO() : state_(new State())
{
}

FileIO::~FileIO()
{
  try
  {
    this->Close();
    delete (this->state_);
  }
  catch(...)
  {
    assert(false);
  }
}

void FileIO::Create(const char *filename)
{
#ifdef WIN32
  HANDLE h = ::CreateFile(filename, GENERIC_ALL, FILE_SHARE_READ, 0, CREATE_NEW, 0, 0);  
  if(h == INVALID_HANDLE_VALUE) throw Exception(WinUtils::GetWindowsErrorMessage());
  this->state_->handle_ = h;
#else
  this->state_->fd_ = open(filename, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if(this->state_->fd_ == -1) throw Exception(strerror(errno));
#endif
}

void FileIO::OpenRead(const char *filename)
{
#ifdef WIN32
  HANDLE h = ::CreateFile(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  if(h == INVALID_HANDLE_VALUE) 
  {
    throw Exception(WinUtils::GetWindowsErrorMessage());
  }
  this->state_->handle_ = h;
#else
  this->state_->fd_ = open(filename, O_RDONLY);
  if(this->state_->fd_ == -1) throw Exception(strerror(errno));
#endif
}

void FileIO::OpenReadWrite(const char *filename)
{
#ifdef WIN32
  HANDLE h = ::CreateFile(filename, GENERIC_ALL, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
  if(h == INVALID_HANDLE_VALUE) throw Exception(WinUtils::GetWindowsErrorMessage());
  this->state_->handle_ = h;  
#else
  this->state_->fd_ = open(filename, O_RDWR);
  if(this->state_->fd_ == -1) throw Exception(strerror(errno));
#endif
}

void FileIO::Write(const void *value, size_t size)
{
#if WIN32
  if(size > UINT_MAX) throw Exception("Cannot write values that are larger than 32bit."); // a single write (item) can not exceed 32bit. This should never ever be the case.
  static CheckException ce("Error writing file.");
  static unsigned long n;
  ce = ::WriteFile(this->state_->handle_, value, (unsigned int)size, &n, 0);  
#else
  ssize_t n = write(this->state_->fd_, value, size);
  if(n == -1) throw Exception(strerror(errno));
  if(n != (ssize_t)size) throw Exception("Write wrote less bytes than expected.");  
#endif
}

bool FileIO::Read(void* value, size_t size)
{
#ifdef WIN32
  if(size > UINT_MAX) throw Exception("Cannot read values that are larger than 32bit."); // a single read (item) can not exceed 32bit. This should never ever be the case.
  static CheckException ce("Error reading file");
  DWORD n;
  ce = ::ReadFile(this->state_->handle_, value, (unsigned int)size, &n, 0);
  return n != size;
#else
  ssize_t n = ::read(this->state_->fd_, value, size);
  if(n == -1) throw Exception(strerror(errno));
  return n != (ssize_t)size;
#endif
}

void FileIO::Close()
{
#ifdef WIN32
  if(this->state_->handle_ != INVALID_HANDLE_VALUE)
  {
    static CheckException ce("Closing file failed.");
    ce = ::CloseHandle(this->state_->handle_);
    this->state_->handle_ = INVALID_HANDLE_VALUE;
  }
#else
  if(this->state_->fd_ == -1) return;
  if(close(this->state_->fd_) != 0) throw Exception(strerror(errno));
  this->state_->fd_ = -1;
#endif
}

void FileIO::Flush()
{
#ifdef WIN32
  static CheckException ce("Flushing file failed.");
  ce = ::FlushFileBuffers(this->state_->handle_);
#else
  if(fsync(this->state_->fd_) != 0) throw Exception(strerror(errno));
#endif  
}

int64 FileIO::GetFilePosition()
{
#ifdef WIN32
    return ::SetFilePointer(this->state_->handle_, 0, 0, FILE_CURRENT);
#else
  int64 pos = lseek64(this->state_->fd_, 0, SEEK_CUR);
  if(pos == -1) throw Exception(strerror(errno));
  return pos;
#endif  
}

void FileIO::SetFilePosition(int64 distanceToMove)
{
#ifdef WIN32
  LARGE_INTEGER distance;
  distance.QuadPart = distanceToMove;
  ::SetFilePointer(this->state_->handle_, distance.LowPart, &distance.HighPart, FILE_CURRENT);
#else
  if(lseek64(this->state_->fd_, distanceToMove, SEEK_SET) == -1) throw Exception(strerror(errno));
#endif  
}

int64 FileIO::FileSize()
{
#ifdef WIN32
  LARGE_INTEGER size;
  ::GetFileSizeEx(this->state_->handle_, &size);
  return size.QuadPart;
#else
  int64 p = GetFilePosition();
  if(lseek64(this->state_->fd_, 0, SEEK_END) == -1) throw Exception(strerror(errno));
  int64 filesize = GetFilePosition();
  SetFilePosition(p);
  return filesize;
#endif
}

} // namespace teatime
