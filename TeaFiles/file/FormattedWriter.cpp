#include "FormattedWriter.h"

#include "Streams.h"

#include "../os/TextUtils.h"
#include "../os/FileIO.h"
#include "../base/Exceptions.h"
#include "../base/NameValue.h"

#include <limits>
using std::numeric_limits;
#undef max

namespace teatime {

void FormattedWriter::WriteRaw(const byte* value, int32 length)
{
  this->stream_->Write(value, length);
}  

FormattedWriter::FormattedWriter(IStream *stream)
{
  this->stream_ = stream;
}

void FormattedWriter::WriteInt32(int32 value)
{
  this->WriteRaw((byte*)&value, sizeof(int32));
}

void FormattedWriter::WriteInt64(int64 value)
{
  this->WriteRaw((byte*)&value, sizeof(int64));
}

void FormattedWriter::WriteDouble(double value)
{
  this->WriteRaw((byte*)&value, sizeof(double));
}

void FormattedWriter::WriteUuid(uuid value)
{
  this->WriteRaw((byte*)&value, 16);
}

void FormattedWriter::WriteZeroBytes(int count)
{
  byte b = 0;
  while(count--) this->WriteRaw(&b, 1);
}

void FormattedWriter::WriteBytesLengthPrefixed(const byte* value, int length)
{
  this->WriteInt32(length);
  this->WriteRaw(value, length);
}  

void FormattedWriter::WriteText(string text)
{
  string utf8 = TextUtils::ConvertToUTF8(text);
  this->WriteBytesLengthPrefixed((byte*)utf8.c_str(), static_cast<int>(utf8.size()));
}

void FormattedWriter::WriteNameValue(NameValue *nv)
{
  this->WriteText(nv->Name());
  NameValueKind k = nv->Kind();
  this->WriteInt32(k);
  switch(k)
  {
    case NameValueKind::Int:
      this->WriteInt32(static_cast<NameValueInt*>(nv)->Value());
      break;
    case NameValueKind::Double:
      this->WriteDouble(static_cast<NameValueDouble*>(nv)->Value());
      break;
    case NameValueKind::Text:
      this->WriteText(static_cast<NameValueText*>(nv)->Value());
      break;
    case NameValueKind::UUID:
      this->WriteUuid(static_cast<NameValueUUID*>(nv)->Value());
      break;
    default:
      throw OperationException("invalid NameValueKind");
  }
}

} // namespace teatime
