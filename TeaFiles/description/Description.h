#ifndef TEATIME_TEAFILE_DESCRIPTION_DESCRIPTION
#define TEATIME_TEAFILE_DESCRIPTION_DESCRIPTION

#include "ItemDescription.h"

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "Field.h"

#include <string>
using std::string;
#include <boost/algorithm/string.hpp>
using boost::algorithm::replace_all;

namespace teatime {

template<class T>
class DefaultDescription : public ItemDescription
{
public:

  template<typename F>
  void AddField(F T::* mp, const char *name, bool isTime=false, bool isEventTime=false)
  {
    shared_ptr<TypedField<T,F>> f(new TypedField<T,F>(mp, name));
    f->Type(FieldTypeTraits<F>::GetFieldType());
    f->Offset(GetOffsetByAnalysis(f.get()));
    f->IsTime(isTime);
    f->IsEventTime(isEventTime);
    ItemDescription::AddField(f);
  }

  typedef T ItemType;

  DefaultDescription()
  {
    this->ItemSize(sizeof(T));
    //this->pack = __alignof(T);

    string s(typeid(ItemType).name());
    replace_all(s, "struct ", "");
    replace_all(s, "class ", "");
    replace_all(s, "::", ".");
    this->ItemName(s);
  }
  
private:

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DefaultDescription);
  
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wreturn-type"   // g++ bug: does not consider exception before end of function
#endif

  template<typename F>
  uint32 GetOffsetByAnalysis(TypedField<T,F> *f)
  {    
    // analyze
    T tested;
    memset(&tested, 0, sizeof(T));
    F magic = FieldTypeTraits<F>::GetMagicValue();
    f->SetValue(&tested, &magic);
    char* p = (char*)&tested;
    for(uint32 i=0; i <= sizeof(T) - sizeof(F); i++, p++)
    {
      if(*(F*)p == magic) 
      {
        return i;
      }      
    }
    throw Exception("error analyzing field offset: field analysis failed.");
  }  
};

template<typename T>
class Description : public DefaultDescription<T>
{
};

} // namespace teatime

#endif // TEATIME_TEAFILE_DESCRIPTION_DESCRIPTION
