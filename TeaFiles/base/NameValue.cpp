#include "NameValue.h"

#include <sstream>
using std::stringstream;
#include "boost/uuid/uuid_io.hpp"

namespace teatime {

NameValue::NameValue(string name) : name_(name)
{
}

NameValue::~NameValue()
{
}

string NameValue::Name() const 
{ 
  return this->name_; 
}

string NameValueInt::ValueText() const
{
  stringstream stream;
  stream << this->Value();
  return stream.str();
}

string NameValueDouble::ValueText() const
{
  stringstream stream;
  stream << this->Value();
  return stream.str();
}

string NameValueText::ValueText() const
{
  stringstream stream;
  stream << this->Value();
  return stream.str();
}

string NameValueUUID::ValueText() const
{
  stringstream stream;
  stream << this->Value();
  return stream.str();
}

int NameValueCollection::Count() const
{
  return (int)this->nameValues_.size();
}

void NameValueCollection::Add(const char *name, int value)
{
  this->nameValues_.emplace_back(new NameValueInt(name, value));
}

void NameValueCollection::Add(const char *name, double value)
{
  this->nameValues_.emplace_back(new NameValueDouble(name, value));
}

void NameValueCollection::Add(const char *name, string value)
{
  this->nameValues_.emplace_back(new NameValueText(name, value));
}
  
void NameValueCollection::Add(const char *name, uuid value)
{
  this->nameValues_.emplace_back(new NameValueUUID(name, value));
}
  
void NameValueCollection::Add(shared_ptr<NameValue> nv)
{
  this->nameValues_.push_back(nv);
}

NameValueCollection::Container::const_iterator NameValueCollection::begin() const
{
  return this->nameValues_.begin();
}

NameValueCollection::Container::const_iterator NameValueCollection::end() const
{
  return this->nameValues_.end();
}

}
