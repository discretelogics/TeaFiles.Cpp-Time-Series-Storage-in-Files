#include "ReadContext.h"

#include "../description/TeaFileDescription.h"
#include "../description/ItemDescriptionInternals.h"

namespace teatime {

ReadContext::ReadContext(FormattedReader *r) :
    reader_(r),
    description_(new TeaFileDescription()),
    itemAreaStart_(0),	  
    itemAreaEnd_(0),
    sectionCount_(0)
  {}

FormattedReader *ReadContext::Reader() { return reader_; }
shared_ptr<TeaFileDescription> ReadContext::Description() { return description_; }

int64 ReadContext::ItemAreaStart()             { return itemAreaStart_; }
void  ReadContext::ItemAreaStart(int64 value)  { itemAreaStart_ = value; }

int64 ReadContext::ItemAreaEnd()               { return itemAreaEnd_; }
void  ReadContext::ItemAreaEnd(int64 value)    { itemAreaEnd_ = value; }

int64 ReadContext::SectionCount()              { return sectionCount_; }
void  ReadContext::SectionCount(int64 value)   { sectionCount_ = value; }

} // namespace teatime
