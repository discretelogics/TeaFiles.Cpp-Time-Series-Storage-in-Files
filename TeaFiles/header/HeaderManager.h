#ifndef TEATIME_TEAFILE_HEADER_HEADERMANAGER
#define TEATIME_TEAFILE_HEADER_HEADERMANAGER

#include "../base/Common.h"
#include "../base/Pointer.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

namespace teatime {

class WriteContext;
class ReadContext;
class FormattedReader;
class FormattedWriter;
class TeaFileDescription;
class Section;
class SectionFormatter;

class HeaderManager
{
public:

  void WriteHeader(FormattedWriter*, const TeaFileDescription* const);
  shared_ptr<ReadContext> ReadHeader(FormattedReader*);

  static HeaderManager &Instance();

private:
  HeaderManager(); // singleton ctor
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(HeaderManager);

  vector<unique_ptr<SectionFormatter>> formatters_;
  SectionFormatter *GetFormatter(int sectionId);
  string CreateSections(WriteContext* context);
};

} // namespace teatime

#endif // TEATIME_TEAFILE_HEADER_HEADERMANAGER
