#ifndef TEATIME_TEAFILE_HEADER_SECTIONFORMATTER
#define TEATIME_TEAFILE_HEADER_SECTIONFORMATTER

#include "../base/Common.h"

namespace teatime {

class ReadContext;
class WriteContext;

class SectionFormatter
{ 
public:

  SectionFormatter(int sectionID) : id_(sectionID)
  {
  }

  virtual int32 Id() { return id_; }
  virtual void Read(ReadContext*) = 0;
  virtual void Write(WriteContext*) = 0;

private:

  int id_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_HEADER_SECTIONFORMATTER
