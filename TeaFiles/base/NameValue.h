#ifndef TEATIME_NAMEVALUE
#define TEATIME_NAMEVALUE

#include "Common.h"
#include "Enums.h"
#include "Pointer.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning ( disable : 4996 )
#endif
#include <boost/uuid/uuid.hpp>
using boost::uuids::uuid;
#ifdef _MSC_VER
#pragma warning ( pop )
#endif

namespace teatime {

// This class has reference semantics.
class NameValue
{ 
public:
  explicit NameValue(string name);
  virtual ~NameValue();
  string Name() const;

  virtual NameValueKind Kind() const = 0;
  virtual string ValueText() const = 0;

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(NameValue);
  string name_;
};

template<typename T>
class NameValueBase : public NameValue
{
public:

  NameValueBase(string name, T value) : 
    NameValue(name),
    value_(value)
  {}
  T Value() const { return value_; }
  
private:
  T value_;
};
  
class NameValueInt : public NameValueBase<int> 
{
public:
  NameValueInt(string name, int value) : NameValueBase(name, value) {}
  virtual NameValueKind Kind() const {return NameValueKind::Int;}
  virtual string ValueText() const;
};

class NameValueDouble : public NameValueBase<double>
{
public:
  NameValueDouble(string name, double value) : NameValueBase(name, value) {}
  virtual NameValueKind Kind() const {return NameValueKind::Double;}
  virtual string ValueText() const;
};

class NameValueText : public NameValueBase<string> 
{
public:
  NameValueText(string name, string value) : NameValueBase(name, value) {}
  virtual NameValueKind Kind() const {return NameValueKind::Text;}
  virtual string ValueText() const;
};

class NameValueUUID : public NameValueBase<uuid>
{
public:
  NameValueUUID(string name, uuid value) : NameValueBase(name, value) {}
  virtual NameValueKind Kind() const {return NameValueKind::UUID;}
  virtual string ValueText() const;
};

class NameValueCollection
{
public:

  typedef vector<shared_ptr<NameValue>> Container;

  int Count() const;
  void Add(const char *name, int value);
  void Add(const char *name, double value);
  void Add(const char *name, string value);
  void Add(const char *name, uuid value);
  void Add(shared_ptr<NameValue>);

  /*template<typename T>
  T GetValue(const char *name);*/

  Container::const_iterator begin() const;
  Container::const_iterator end() const;

private:
  Container nameValues_;
};

} // namespace teatime

#endif // TEATIME_NAMEVALUE
