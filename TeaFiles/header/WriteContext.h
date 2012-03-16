#ifndef TEATIME_HEADER_WRITECONTEXT
#define TEATIME_HEADER_WRITECONTEXT

#include "../base/Common.h"
#include "../base/FieldType.h"
#include "../base/Pointer.h"
#include <sstream>
using std::stringstream;

namespace teatime {

class FormattedWriter;
class TeaFileDescription;

class WriteContext
{
public:

  WriteContext(FormattedWriter *w, const TeaFileDescription *d);

  FormattedWriter *Writer();
  void Writer(FormattedWriter*);
  
  const TeaFileDescription *Description();

  int64 ItemAreaStart() const;
  void  ItemAreaStart(int64 value);

  int64 SectionCount() const;
  void  IncrementSectionCount();

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(WriteContext);

  FormattedWriter *writer_;
  const TeaFileDescription *description_;
  int64 itemAreaStart_;
  int64 sectionCount_;
};

} // namespace teatime

#endif // TEATIME_HEADER_WRITECONTEXT
