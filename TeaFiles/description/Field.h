#ifndef TEATIME_TEAFILE_DESCRIPTION_FIELD
#define TEATIME_TEAFILE_DESCRIPTION_FIELD

#include "../base/Common.h"
#include "../base/Enums.h"
#include "../base/FieldType.h"
#include "../base/Pointer.h"

#include <string>
using std::string;

namespace teatime {

class Field
{
public:

  Field() : 
    type_(FieldType::Unknown),
    offset_(0),
    isTime_(false),
    isEventTime_(false)
    {
    }

  Field(const char *name) :
    name_(name),
    type_(FieldType::Unknown),
    offset_(0),
    isTime_(false),
    isEventTime_(false)
    {
    }

  string      Name() const;
  void        Name(string name);

  FieldType   Type() const;
  void        Type(FieldType type);

  uint32	    Offset() const;
  void        Offset(uint32	offset);

  bool        IsTime() const;
  void        IsTime(bool);

  bool        IsEventTime() const;
  void        IsEventTime(bool);

protected:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(Field);

  string      name_;
  FieldType   type_;
  int         offset_;  
  bool        isTime_;
  bool        isEventTime_;
};

template<class T, class F>
class TypedField : public Field
{
public:

  // Construct with member field pointer and the name of the field
  TypedField(F T::* field, const char *name) :
    Field(name),
    field_(field)
    {}

  virtual void SetValue(void* item, void *fieldValue)
  {
    (*(T*)item).*field_ = *(F*)fieldValue;
  }

  virtual void GetValue(void* item, void *fieldValue)
  {
    *(F*)fieldValue = (*(T*)item).*field_;
  }

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypedField);
  F T::* field_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_DESCRIPTION_FIELD
