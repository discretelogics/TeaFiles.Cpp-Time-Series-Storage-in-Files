#ifndef TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION_IPP
#define TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION_IPP

#include "ItemCollection.h"
#include "../core/TeaFileCore.h"

namespace teatime {

template<typename T>
InputIterator<T>::InputIterator(TeaFileCore *core, int64 itemPosition) :
    core_(core)
{
  if(this->core_ == 0) return; // end iterator

  this->currentPosition_ = -1;
  this->itemCount_ = this->core_->ItemCount();  
  
  if(itemPosition > 0) 
  {
    this->currentPosition_ = itemPosition;
    this->core_->SetFilePointerToItem(itemPosition);
  }

  this->fetchNext_ = this->currentPosition_ < this->itemCount_;
}

template<typename T>
InputIterator<T>& InputIterator<T>::operator=(const InputIterator<T>& other)
{
  if(this == &other)
  {
    return(*this);
  }
  this->core_ = other.core_;
  this->current_ = other.current_ ;
  this->itemPosition_ = other.itemPosition_;
  
  return(*this);
}

template<typename T>
InputIterator<T>& InputIterator<T>::operator++() 
{    
  this->fetchNext_ = true;  
  return( *this ) ;
}
  
template<typename T>
InputIterator<T> InputIterator<T>::operator++(int)
{
  InputIterator InputIteratorCopy(*this);
  ++(*this);
  return InputIteratorCopy;
}

template<typename T>
bool InputIterator<T>::operator==(const InputIterator<T>& other)
{
  if(other.core_ == 0) // other iterator is end marker
  {
    return this->currentPosition_ == this->itemCount_ - 1;
  }
  else
  {
    return this->currentPosition_ == other.currentPosition_;
  }
}
  
template<typename T>
bool InputIterator<T>::operator!=( const InputIterator<T>& other )
{
  return !((*this) == other);
}

template<typename T>
T& InputIterator<T>::operator*()
{
  if(this->fetchNext_)
  {
    this->core_->Read((byte*)&this->current_, sizeof(T));
    this->currentPosition_++;
    this->fetchNext_ = false;
  }
  return current_;
}

template<typename T>
T& InputIterator<T>::operator->()
{
  return(*(*this));
}

// ItemCollection ////////////////////////////////////////////////////////////////

template<typename T>
void ItemCollection<T>::Initialized(TeaFileCore *core)  
{
  core_ = core;
}

template<typename T>
bool ItemCollection<T>::IsEmpty()
{
  return this->core_->ItemAreaStart() == this->core_->ItemAreaEnd();
}

template<typename T>
int64 ItemCollection<T>::Count()
{
  return (this->core_->ItemAreaEnd() - this->core_->ItemAreaStart()) / sizeof(T);
}

template<typename T>
InputIterator<T> ItemCollection<T>::begin(int64 startItemIndex)
{
  this->core_->SetFilePointerToItem(startItemIndex);
  return InputIterator<T>(this->core_, 0);
}

template<typename T>
InputIterator<T> ItemCollection<T>::end()
{
  return InputIterator<T>();
}

} // namespace teatime

#endif // TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION_IPP
