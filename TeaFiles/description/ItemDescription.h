#ifndef TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTION
#define TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTION

#include "../base/Common.h"
#include "../base/Pointer.h"
#include <string>
using std::string;

namespace teatime {

class Field;

class ItemDescription
{
public:

  ItemDescription();
  ~ItemDescription();
    
  int           FieldCount() const;
  shared_ptr<Field> GetField(int index) const;
  
  int           ItemSize() const;
  void          ItemSize(int value);
  string        ItemName() const;
  void          ItemName(string value);

  // primarily for internal use
  shared_ptr<Field> GetFieldByOffset(uint32 offset) const;
  int GetEventTimeFieldOffset();

protected:
  
  friend class ItemSectionFormatter;
  void AddField(shared_ptr<Field>);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ItemDescription);
 
  class State;
  State* state_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_DESCRIPTION_ITEMDESCRIPTION
