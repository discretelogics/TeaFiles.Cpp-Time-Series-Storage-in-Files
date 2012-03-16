#ifndef TEATIME_TEAFILE_ACCESS_MEMORYACCESS
#define TEATIME_TEAFILE_ACCESS_MEMORYACCESS

#include "../base/Common.h"
#include "../base/Pointer.h"

namespace teatime {

class FileMappingRaw
{
public:
  
  FileMappingRaw(const char* filename, int64 itemAreaStart, int64 itemAreaSize);
  ~FileMappingRaw();

  inline byte* begin() { return begin_; }
  
  //  like stl iterators, this pointer marks the position past the last item
  inline byte* end()   { return end_; }

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileMappingRaw);
  
  byte *begin_;
  byte *end_;

  class State;
  State *state_;
};

template<typename T>
class FileMapping
{
public:

  FileMapping(FileMappingRaw *raw) : raw_(raw) {}
  
  inline T* begin() { return (T*)raw_->begin(); }
  inline T* end()   { return (T*)raw_->end(); }

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileMapping);
  unique_ptr<FileMappingRaw> raw_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_ACCESS_MEMORYACCESS
