#ifndef TEATIME_TEAFILE_CORE_TEAFILECORE
#define TEATIME_TEAFILE_CORE_TEAFILECORE

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "../base/Enums.h"

namespace teatime {

class TeaFileDescription;
class ItemArea;
class FileMappingRaw;

class TeaFileCore
{
public:

  TeaFileCore(int itemSize);

  // factory methods
  void Create(const char *filename, shared_ptr<TeaFileDescription>);
  void OpenRead(const char *filename);  
  void OpenReadWrite(const char *filename);

  // description
  shared_ptr<const TeaFileDescription> Description() const;

  //  data
  void  Write(const byte* const, size_t);
  bool  Read(byte*, size_t);
  int64 ItemAreaStart() const;
  int64 ItemAreaEnd() const;
  int64 ItemAreaSize() const;
  int64 ItemCount() const;

  //  memory mapping
  FileMappingRaw *OpenReadableMapping();

  // file pointer access
  void    SetFilePointerToItem(int64 itemIndex);
  
private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TeaFileCore);

  class State;
  shared_ptr<State> state_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_CORE_TEAFILECORE
