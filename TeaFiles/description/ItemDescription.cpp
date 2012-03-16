#include "ItemDescriptionInternals.h"

#include "Field.h"

#include "../file/FormattedReader.h"
#include "../file/FormattedWriter.h"
#include "../base/Exceptions.h"
#include <sstream>
using std::ostringstream;

namespace teatime {

ItemDescription::ItemDescription() : state_(new State()) 
{
}

ItemDescription::~ItemDescription()
{
  delete this->state_;
}
    
int ItemDescription::FieldCount() const
{
  return static_cast<int>(this->state_->fields_.size());
}

shared_ptr<Field> ItemDescription::GetField(int index) const
{
  return this->state_->fields_.at(index);
}

shared_ptr<Field> ItemDescription::GetFieldByOffset(uint32 offset) const
{
  for(auto it = this->state_->fields_.begin(); it != this->state_->fields_.end(); ++it)
  {
    if((*it)->Offset() == offset) return (*it);
  }
  ostringstream os;
  os << "Field expected at offset " << offset << " but no such field exists.";
  throw FileFormatException(os.str().c_str());
}

int ItemDescription::ItemSize() const
{
  return state_->itemSize_;
}

void ItemDescription::ItemSize(int value)
{
  state_->itemSize_ = value;
}

string ItemDescription::ItemName() const
{ 
  return state_->itemName_; 
}

void ItemDescription::ItemName(string value)
{
  state_->itemName_ = value;
}

void ItemDescription::AddField(shared_ptr<Field> f)
{
  this->state_->fields_.push_back(f);
}

int ItemDescription::GetEventTimeFieldOffset()
{
  for(auto it = this->state_->fields_.begin(); it != this->state_->fields_.end(); ++it)
  {
    if((*it)->IsEventTime()) return (*it)->Offset();
  }
  return -1;
}

} // namespace teatime
