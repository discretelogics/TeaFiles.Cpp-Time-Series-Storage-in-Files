#ifndef TEATIME_TEAFILE_FILE_FORMATTEDREADER
#define TEATIME_TEAFILE_FILE_FORMATTEDREADER

#include "../base/Common.h"
#include "../base/NameValue.h"
#include "../base/Pointer.h"

#include <string>
using std::string;

namespace teatime {

class FileIO;

class FormattedReader
{
public:

  FormattedReader(FileIO*);

  // core read
  int32                 ReadInt32();
  int64                 ReadInt64();
  double                ReadDouble();
  uuid                  ReadUUID();
  string                ReadText();
  shared_ptr<NameValue> ReadNameValue();

  // utils
  int64   Position();
  void    SkipBytes(int32 numberOfBytesToSkip);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FormattedReader);
  FileIO *fileIO_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_FILE_FORMATTEDREADER
