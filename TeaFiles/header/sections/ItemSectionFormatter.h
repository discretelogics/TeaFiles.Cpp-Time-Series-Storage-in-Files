#ifndef TEATIME_TEAFILE_ITEMSECTIONFORMATTER
#define TEATIME_TEAFILE_ITEMSECTIONFORMATTER

#include "../SectionFormatter.h"

namespace teatime
{

class ReadContext;
class WriteContext;

class ItemSectionFormatter : public SectionFormatter
{
public:

  ItemSectionFormatter() : SectionFormatter(10) {}

  void Read(ReadContext*);
  void Write(WriteContext*);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ItemSectionFormatter);
};

} // namespace teatime

#endif // TEATIME_TEAFILE_ITEMSECTIONFORMATTER
