#ifndef TEATIME_TEAFILE_BASE_ENUMS
#define TEATIME_TEAFILE_BASE_ENUMS

namespace teatime {

class Enumeration
{
public:  
  Enumeration(int v) : value_(v) {}
  operator int() const  {return this->value_;}
protected:
  int value_;
};

class FileMode : public Enumeration
{
public:

  static const int Create = 2;
  static const int CreateNew = 1;
  static const int Open = 3;

  FileMode(int value) : Enumeration(value) {}  
  
  const char *ToString()
  {
    switch(value_) 
    {
    case Create:    return "FileMode::Create";
    case CreateNew: return "FileMode::CreateNew";
    case Open:      return "FileMode::Open";
    default:        return "Invalid Value";
    }
  }
};

class FileAccess : public Enumeration
{
public:

  static const int Read = 1;
  static const int ReadWrite = 3;

  FileAccess(int value) : Enumeration(value) {}
};

class NameValueKind : public Enumeration
{
public:

  static const int Int = 1;
  static const int Double = 2;
  static const int Text = 3;
  static const int UUID = 4;
  
  NameValueKind(int value) : Enumeration(value) {}

  const char *ToString()
  {
    switch(value_) 
    {
    case Int:     return "int";
    case Double:  return "double";
    case Text:    return "text";
    case UUID:    return "uuid";
    default:      return "invalid";
    }
  }
};

} // namespace teatime

#endif // TEATIME_TEAFILE_BASE_ENUMS
