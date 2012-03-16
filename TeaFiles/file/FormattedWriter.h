#ifndef TEATIME_TEAFILE_FILE_FORMATTEDWRITER
#define TEATIME_TEAFILE_FILE_FORMATTEDWRITER

#include "../base/Common.h"
#include <string>
using std::string;

namespace boost { namespace uuids {
struct uuid;
}}
using boost::uuids::uuid;

namespace teatime {

class IStream;
class NameValue;

class FormattedWriter
{
public:

  FormattedWriter(IStream*);

  // core write
  void WriteRaw(const byte*, int32 length);
  void WriteInt32(int32);
  void WriteInt64(int64);	
  void WriteDouble(double);
  void WriteUuid(uuid);
  void WriteText(string text);
  void WriteNameValue(NameValue*);
  
  // utils
  void WriteZeroBytes(int count);
  void WriteBytesLengthPrefixed(const byte* value, int length);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FormattedWriter);
  IStream *stream_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_FILE_FORMATTEDWRITER
