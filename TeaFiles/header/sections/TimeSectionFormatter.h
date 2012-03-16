#ifndef TEATIME_TEAFILE_TIMESECTIONFORMATTER
#define TEATIME_TEAFILE_TIMESECTIONFORMATTER

#include "../SectionFormatter.h"

namespace teatime {

class ReadContext;
class WriteContext;

class TimeSectionFormatter : public SectionFormatter
{
public:

  TimeSectionFormatter() : SectionFormatter(0x40) {}

  void Read(ReadContext*);
  void Write(WriteContext*);

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TimeSectionFormatter);
};

} // namespace teatime

#endif // TEATIME_TEAFILE_TIMESECTIONFORMATTER
