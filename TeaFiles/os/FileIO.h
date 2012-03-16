#ifndef TEATIME_OS_FILEIO
#define TEATIME_OS_FILEIO

#include "../base/Common.h"
#include <stddef.h> // size_t on *nix

namespace teatime {

class FileIO
{
public:

  FileIO();
  ~FileIO();

  void Create(const char *filename);
  void OpenRead(const char *filename);
  void OpenReadWrite(const char *filename);
  void Close();
  void Flush(); // problematic to implement

  int64 GetFilePosition();
  void  SetFilePosition(int64 postionToMove);

  int64 FileSize();

  void  Write(const void*, size_t size);
  bool  Read(void*, size_t size);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileIO);  

  class State;
  State *state_;
};

} // namespace teatime

#endif // TEATIME_OS_FILEIO
