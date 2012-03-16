#ifndef TEATIME_TEAFILE_FILE_STREAM
#define TEATIME_TEAFILE_FILE_STREAM

#include "../base/Common.h"
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

namespace teatime {

class FileIO;

class IStream
{ 
public:
  virtual void Write(const byte*, int32 length) = 0;
};

class FileStream : public IStream
{
public:
  FileStream(FileIO*);
  ~FileStream();
  void Write(const byte*, int32 length);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileStream);
  FileIO *fileIO_;
};

class MemoryStream : public IStream
{
public:
  MemoryStream();
  ~MemoryStream();
  void Write(const byte*, int32 length);
  size_t Size();
  string ToString();

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MemoryStream);
  stringstream stream_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_FILE_STREAM
