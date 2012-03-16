#ifndef TEATIME_NAMEVALUESECTIONFORMATTER
#define TEATIME_NAMEVALUESECTIONFORMATTER

#include "../SectionFormatter.h"

namespace teatime {

class ReadContext;
class WriteContext;

class NameValueSectionFormatter : public SectionFormatter
{
public:

  NameValueSectionFormatter() : SectionFormatter(0x81) {}

  void Read(ReadContext*);
  void Write(WriteContext*);

private:

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(NameValueSectionFormatter);
};

} // namespace teatime

#endif // TEATIME_NAMEVALUESECTIONFORMATTER
