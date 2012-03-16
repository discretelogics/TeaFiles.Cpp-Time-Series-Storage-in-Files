#include "Field.h"

namespace teatime {

string Field::Name() const
{ 
  return name_; 
}

void Field::Name(string name)
{ 
  name_ = name; 
}

FieldType Field::Type() const
{ 
  return type_;
}

void Field::Type(FieldType type)
{ 
  type_ = type; 
}

uint32 Field::Offset() const
{ 
  return offset_; 
}

void Field::Offset(uint32 offset)
{ 
  offset_ = offset; 
}

bool Field::IsTime() const
{
  return this->isTime_;
}

void Field::IsTime(bool isTime)
{
  this->isTime_ = isTime;
}

bool Field::IsEventTime() const
{
  return this->isEventTime_;
}

void Field::IsEventTime(bool isEventTime)
{
  this->isEventTime_ = isEventTime;
}

}
