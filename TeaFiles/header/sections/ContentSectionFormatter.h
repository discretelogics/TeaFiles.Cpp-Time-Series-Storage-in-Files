#ifndef TEATIME_TEAFILE_CONTENTSECTIONFORMATTER
#define TEATIME_TEAFILE_CONTENTSECTIONFORMATTER

#include "../SectionFormatter.h"

namespace teatime {

class ReadContext;
class WriteContext;

class ContentSectionFormatter : public SectionFormatter
{
public:

  ContentSectionFormatter() : SectionFormatter(0x80) {}

  void Read(ReadContext*);
  void Write(WriteContext*);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ContentSectionFormatter);
};

} // namespace teatime

#endif // TEATIME_TEAFILE_CONTENTSECTIONFORMATTER
