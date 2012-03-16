#include "TeaFileCore.h"

#include "../base/Exceptions.h"
#include "../os/FileIO.h"
#include "../file/FormattedReader.h"
#include "../file/FormattedWriter.h"
#include "../file/Streams.h"
#include "../access/MemoryAccess.h"
#include "../header/WriteContext.h"
#include "../header/ReadContext.h"
#include "../header/HeaderManager.h"
#include <assert.h>
#include <exception>

namespace teatime {

class TeaFileCore::State
{
public:

  int itemSize_;
  int64 itemAreaStart_;
  int64 itemAreaEnd_;
  shared_ptr<TeaFileDescription> description_;
  FileIO fileIO_;
  string filename_;
};

TeaFileCore::TeaFileCore(int itemSize) : state_(new State())
{
  this->state_->itemSize_ = itemSize;
}

void TeaFileCore::Create(const char *filename, shared_ptr<TeaFileDescription> d)
{
  this->state_->fileIO_.Create(filename);
  this->state_->description_ = d;
  this->state_->filename_ = filename;
  FileStream stream(&this->state_->fileIO_);
  FormattedWriter w(&stream);
  HeaderManager::Instance().WriteHeader(&w, d.get());
}

void TeaFileCore::OpenRead(const char *filename)
{
  this->state_->fileIO_.OpenRead(filename);
  this->state_->filename_ = filename;
  FormattedReader r(&this->state_->fileIO_);
  auto rc = HeaderManager::Instance().ReadHeader(&r);
  state_->description_ = rc->Description();
  this->state_->itemAreaStart_ = rc->ItemAreaStart();
  this->state_->itemAreaEnd_ = rc->ItemAreaEnd();

  assert((this->state_->itemAreaEnd_ == 0) || (this->state_->itemAreaEnd_ >= this->state_->itemAreaStart_));
}

FileMappingRaw *TeaFileCore::OpenReadableMapping()
{
  if(this->ItemAreaSize() == 0)
  {
    throw Exception("ItemArea has length=0");
  }
  FileMappingRaw *raw = new  FileMappingRaw(this->state_->filename_.c_str(), this->ItemAreaStart(), 
    this->ItemAreaEnd()-this->ItemAreaStart());
  return raw;
}

bool TeaFileCore::Read(byte* value, size_t size)
{
  return this->state_->fileIO_.Read(value, size);
}

void TeaFileCore::Write(const byte* value, size_t size)
{
  this->state_->fileIO_.Write(value, size);
}

shared_ptr<const TeaFileDescription> TeaFileCore::Description() const
{
  return this->state_->description_;
}

int64 TeaFileCore::ItemAreaStart() const
{
  return this->state_->itemAreaStart_;
}

int64 TeaFileCore::ItemAreaEnd() const
{
  if(this->state_->itemAreaEnd_ == 0) return this->state_->fileIO_.FileSize();
  return this->state_->itemAreaEnd_;
}

int64 TeaFileCore::ItemAreaSize() const
{  
  return this->ItemAreaEnd() - this->ItemAreaStart();
}

int64 TeaFileCore::ItemCount() const
{
  if(this->state_->itemAreaEnd_ != 0)
  {
    return (this->ItemAreaEnd() - this->ItemAreaStart()) / this->state_->itemSize_;
  }
  else
  {
    return this->ItemAreaSize() / this->state_->itemSize_;
  }
}

void TeaFileCore::SetFilePointerToItem(int64 itemIndex)
{
  this->state_->fileIO_.SetFilePosition(this->state_->itemAreaStart_ + itemIndex * this->state_->itemSize_);
}

} // namespace teatime
