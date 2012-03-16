#include "TimeSectionFormatter.h"

#include "../ReadContext.h"
#include "../WriteContext.h"
#include "../../base/Exceptions.h"
#include "../../base/Pointer.h"
#include "../../file/FormattedReader.h"
#include "../../file/FormattedWriter.h"
#include "../../description/Field.h"
#include "../../description/TeaFileDescription.h"
#include "../../description/ItemDescription.h"
#include "../../time/TimeScale.h"
#include "../../time/Time.h"

#include <sstream>
using std::ostringstream;
#include <algorithm>
using std::copy_if;
#include <functional>
using std::mem_fun;
#include <boost/foreach.hpp>

namespace teatime {

void TimeSectionFormatter::Read(ReadContext *rc)
{
  // time scale
  auto r = rc->Reader();
  auto epoch  = r->ReadInt64();
  auto ticksPerDay = r->ReadInt64();

  TimeScale scale(epoch, ticksPerDay);
  rc->Description()->Scale(scale);

  if(scale != TimeScale::Master())
  {
    throw TimeScaleMismatchException(); // API limitation: Only TeaFiles that have the scale of TimeScale::Master() can be read!
  }

  auto id = rc->Description()->Item();

  // time fields
  bool isFirstTimeField = true;
  int32 timeFieldsCount = r->ReadInt32();
  while(timeFieldsCount--)
  {
    int32 offset = r->ReadInt32();
    if (id != 0)
    {
      auto f = id->GetFieldByOffset(offset);
      f->IsTime(true);
      f->IsEventTime(isFirstTimeField);
      isFirstTimeField = false;
    }
  };
}

void TimeSectionFormatter::Write(WriteContext *wc)
{
  if (wc->Description() == 0) return;
  if (wc->Description()->Item() == 0) return;

  auto id = wc->Description()->Item();
  int n = wc->Description()->Item()->FieldCount();
  vector<shared_ptr<const Field>> timeFields;
  for(int i=0; i < n; i++)
  {
    auto f = id->GetField(i);
    if(f->IsTime())
    {
      timeFields.push_back(f);
    }
  }
  if(timeFields.empty()) return; // do not write time section if no time field exists

  // time format
  wc->Writer()->WriteInt64(TimeScale::Master().Epoch());
  wc->Writer()->WriteInt64(TimeScale::Master().TicksPerDay());

  // time fields
  wc->Writer()->WriteInt32(static_cast<int32>(timeFields.size())); // cast:this number is in the range of 0 ... 1, 2.
  BOOST_FOREACH(shared_ptr<const Field> f, timeFields)
  {
    wc->Writer()->WriteInt32(f->Offset());
  }
}

}
