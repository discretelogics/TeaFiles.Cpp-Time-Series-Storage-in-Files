#include "NameValueSectionFormatter.h"
#include "../ReadContext.h"
#include "../WriteContext.h"
#include "../../file/FormattedReader.h"
#include "../../file/FormattedWriter.h"
#include "../../description/ItemDescriptionInternals.h"
#include "../../description/TeaFileDescription.h"

namespace teatime {

void NameValueSectionFormatter::Read(ReadContext *rc)
{
  auto r = rc->Reader();
  int32 n = r->ReadInt32();
  shared_ptr<NameValueCollection> nvc(new NameValueCollection());
  while(n--)
  {
    auto nv = r->ReadNameValue();
    nvc->Add(nv);
  }
  rc->Description()->NameValues(nvc);
}

void NameValueSectionFormatter::Write(WriteContext *wc)
{
  auto nvc = wc->Description()->NameValues();
  if(nvc == 0) return;
  if(nvc->Count() == 0) return;

  auto w = wc->Writer();
  w->WriteInt32(nvc->Count());
  for(auto it=nvc->begin(); it!=nvc->end(); ++it)
  {
    w->WriteNameValue((*it).get());
  }
}

} // namespace teatime
