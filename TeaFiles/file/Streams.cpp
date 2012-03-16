#include "Streams.h"
#include "../os/FileIO.h"

namespace teatime {

FileStream::~FileStream()
{
}

FileStream::FileStream(FileIO *fileIO) : fileIO_(fileIO)
{
}

void FileStream::Write(const byte *bytes, int32 length)
{
  this->fileIO_->Write(bytes, length);
}

MemoryStream::MemoryStream()
{
}

MemoryStream::~MemoryStream()
{
}

void MemoryStream::Write(const byte *bytes, int32 length)
{
  this->stream_.write((char*)bytes, length);
}

size_t MemoryStream::Size()
{
  return this->stream_.str().size();
}

string MemoryStream::ToString()
{
  return this->stream_.str();
}

} // namespace teatime
