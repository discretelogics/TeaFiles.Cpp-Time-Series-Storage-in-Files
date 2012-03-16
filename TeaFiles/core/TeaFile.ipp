#ifndef TEATIME_TEAFILE_CORE_TEAFILEIPP
#define TEATIME_TEAFILE_CORE_TEAFILEIPP

#include "TeaFile.h"
#include "TeaFileCore.h"
#include "../access/ItemCollection.ipp"
#include "../description/TeaFileDescription.h"
#include "../base/Pointer.h"
#include "../base/Exceptions.h"

namespace teatime {

template<typename T, typename D>
shared_ptr<TeaFile<T,D>> TeaFile<T,D>::OpenRead(const char *filename)
{
  auto tf = shared(new TeaFile());
  tf->core_ = unique(new TeaFileCore(sizeof(T)));
  tf->core_->OpenRead(filename);  
  tf->items_.Initialized(tf->core_.get());
  return tf;
}

template<typename T, typename D>
shared_ptr<TeaFile<T,D>> TeaFile<T,D>::Create(const char *filename, string contentDescription, shared_ptr<NameValueCollection> nvc)
{
  try
  {
    auto tf = shared(new TeaFile());
    tf->core_ = unique(new TeaFileCore(sizeof(T)));
    tf->items_.Initialized(tf->core_.get());
    
    shared_ptr<TeaFileDescription> tfd(new TeaFileDescription());
    tfd->Item(shared(new D()));
    tfd->Content(contentDescription);
    tfd->NameValues(nvc);
    tfd->Scale(TimeScale::Master());

    tf->core_->Create(filename, tfd);
    return tf;
  }
  catch(...) // todo
  { 
    throw;
  }
}

template<typename T, typename D>
void TeaFile<T,D>::Write(const T value)
{
  this->core_->Write((byte*)&value, sizeof(T));
}

template<typename T, typename D>
bool TeaFile<T,D>::Read(T* value)
{
  return this->core_->Read((byte*)value, sizeof(T));
}

template<typename T, typename D>
shared_ptr<const TeaFileDescription> TeaFile<T,D>::Description() const
{
  return this->core_->Description();
}

template<typename T, typename D>
int64 TeaFile<T,D>::ItemAreaStart()
{
  return this->core_->ItemAreaStart();
}

template<typename T, typename D>
int64 TeaFile<T,D>::ItemAreaEnd()
{
  return this->core_->ItemAreaEnd();
}

template<typename T, typename D>
int64 TeaFile<T,D>::ItemCount()
{
  return this->core_->ItemCount();
}

template<typename T, typename D>
ItemCollection<T>& TeaFile<T,D>::Items()
{
  return this->items_;
}

template<typename T, typename D>
shared_ptr<FileMapping<T>> TeaFile<T,D>::OpenReadableMapping()
{
  FileMappingRaw *raw = this->core_->OpenReadableMapping();
  return shared(new FileMapping<T>(raw));
}

} // namespace teatime

#endif // TEATIME_TEAFILE_CORE_TEAFILEIPP
