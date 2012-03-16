#include "FormattedReader.h"
#include "../base/Exceptions.h"
#include "../os/TextUtils.h"

#include "../base/Pointer.h"
#include "../os/FileIO.h"

#include <cstring>
using std::memset;

namespace teatime {

FormattedReader::FormattedReader(FileIO* fio)
{
  this->fileIO_ = fio;
}

int32 FormattedReader::ReadInt32()
{
  int32 value;
  this->fileIO_->Read((void*)&value, 4);
  return value;
}

int64 FormattedReader::ReadInt64()
{
  int64 value;
  this->fileIO_->Read((void*)&value, 8);
  return value;
}

double FormattedReader::ReadDouble()
{ 
  double value;
  this->fileIO_->Read((void*)&value, 8);
  return value;
}

string FormattedReader::ReadText()
{
  int32 length = this->ReadInt32();

  unique_ptr<byte> buffer(new byte[length]);
  byte *pBuffer = buffer.get();
  memset(pBuffer, 0, length);

  this->fileIO_->Read(pBuffer, length);
  string utf8((char*)pBuffer, length);
  string s = TextUtils::ConvertFromUTF8(utf8);
  
  return s;
}

uuid FormattedReader::ReadUUID()
{
  byte bytes[16];
  this->fileIO_->Read((void*)&bytes, 16);
  uuid u;
  memcpy(&u, bytes, 16);
  return u;
}

shared_ptr<NameValue> FormattedReader::ReadNameValue()
{
  string name = this->ReadText();
  int kind = this->ReadInt32();
  
  if(kind == NameValueKind::Int)
  {
    int32 value = this->ReadInt32();
    return shared(new NameValueInt(name, value));
  }
  if(kind == NameValueKind::Double)
  {
    double value = this->ReadDouble();
    return shared(new NameValueDouble(name, value));
  }
  if(kind == NameValueKind::Text)
  {
    string value = this->ReadText();
    return shared(new NameValueText(name, value));
  }
  if(kind == NameValueKind::UUID)
  {
    uuid value = this->ReadUUID();
    return shared(new NameValueUUID(name, value));
  }
  throw OperationException("Invalid NameValueKind");
}

int64 FormattedReader::Position()
{
  return this->fileIO_->GetFilePosition();
}

void FormattedReader::SkipBytes(int32 numberOfBytesToSkip)
{  
  while(numberOfBytesToSkip--)
  {
    int8 value;
    this->fileIO_->Read((void*)&value, 1);
  }
}

} // namespace teatime
