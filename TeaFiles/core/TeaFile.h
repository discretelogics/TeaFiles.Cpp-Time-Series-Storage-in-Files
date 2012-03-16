#ifndef TEATIME_CORE_TEAFILE
#define TEATIME_CORE_TEAFILE

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "../description/Description.h"

namespace teatime {

class TeaFileCore;
class TeaFileDescription;
class NameValueCollection;

template<typename T>
class ItemCollection;

template<typename T>
class FileMapping;

template<typename T, typename D=Description<T>>
class TeaFile
{
public:

  // factory methods
  static shared_ptr<TeaFile<T,D>> Create(const char *filename, string contentDescription=string(), shared_ptr<NameValueCollection> nvc=0);
  static shared_ptr<TeaFile<T,D>> OpenRead(const char *filename);
  static shared_ptr<TeaFile<T,D>> OpenReadWrite(const char *filename);

  // description
  shared_ptr<const TeaFileDescription> Description() const;

  //  data
  ItemCollection<T>& Items();

  void    Write(const T);
  bool    Read(T*);
  int64   ItemAreaStart();
  int64   ItemAreaEnd();
  int64   ItemCount();

  // memory mapping.  
  shared_ptr<FileMapping<T>> OpenReadableMapping();
  
  // file pointer access
  void    SetFilePointerToItem(int64 itemIndex);

private:
  TeaFile() {}    // enforce use of factory methods
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TeaFile);

  unique_ptr<TeaFileCore> core_;  // core implementation
  ItemCollection<T> items_;
};

} // namespace teatime

#endif // TEATIME_CORE_TEAFILE
