#include "WriteContext.h"

#include "../description/TeaFileDescription.h"
#include "../description/ItemDescriptionInternals.h"

namespace teatime {

WriteContext::WriteContext(FormattedWriter *w, const TeaFileDescription *d) :
    writer_(w),
    description_(d),
    itemAreaStart_(0),
    sectionCount_(0)
  {}

FormattedWriter *WriteContext::Writer()               { return writer_; }
void WriteContext::Writer(FormattedWriter *w)         { writer_ = w; }

const TeaFileDescription *WriteContext::Description()       { return description_; }

int64 WriteContext::ItemAreaStart() const      { return itemAreaStart_; }
void  WriteContext::ItemAreaStart(int64 value) { itemAreaStart_ = value; }

int64 WriteContext::SectionCount() const       { return sectionCount_; }
void  WriteContext::IncrementSectionCount()         { sectionCount_++; }

} // namespace teatime
