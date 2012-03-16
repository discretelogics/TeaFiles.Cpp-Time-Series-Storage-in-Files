#ifndef TEATIME_HEADER_READCONTEXT
#define TEATIME_HEADER_READCONTEXT

#include "../base/Common.h"
#include "../base/FieldType.h"
#include "../base/Pointer.h"

namespace teatime {

class FormattedReader;
class TeaFileDescription;

class ReadContext
{
public:

  ReadContext(FormattedReader *r);

  FormattedReader* Reader();
  shared_ptr<TeaFileDescription> Description();

  int64 ItemAreaStart();
  void  ItemAreaStart(int64 value);

  int64 ItemAreaEnd();
  void  ItemAreaEnd(int64 value);

  int64 SectionCount();
  void  SectionCount(int64 value);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ReadContext);

  FormattedReader* reader_;
  shared_ptr<TeaFileDescription> description_;
  int64 itemAreaStart_;
  int64 itemAreaEnd_;
  int64 sectionCount_;
};

} // namespace teatime

#endif // TEATIME_HEADER_READCONTEXT
