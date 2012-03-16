#include "IO.h"

#include "../description/Field.h"
#include "../description/TeaFileDescription.h"
#include "../description/ItemDescriptionInternals.h"
#include "../time/TimeScale.h"
#include "../time/Time.h"
#include "../base/NameValue.h"

#include <boost/date_time/posix_time/posix_time.hpp>
using boost::posix_time::ptime;

using std::endl;

namespace teatime {

ostream& operator<<(ostream& os, const FieldType& ft)
{
  return os << ft.ToString();
}

ostream& operator<<(ostream& os, const NameValueCollection &nvc)
{
  for(auto it = nvc.begin(); it != nvc.end(); ++it)
  {
    os << (*it)->Name() << ": " << (*it)->ValueText() << " (" << (*it)->Kind().ToString() << ")" << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const TimeScale &scale)
{
  os << scale.Epoch() << endl
     << scale.TicksPerDay() << endl;
  if(scale == TimeScale::Java())
  {
    os << "Wellknown scale: Java" << endl;
  }
  else if(scale == TimeScale::Net())
  {
    os << "Wellknown scale: Net" << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const Field &f)
{
  return os << f.Name() << "\t" << f.Offset() << "\t" << f.Type() << "\t" << f.IsTime() << "\t" << f.IsEventTime();
}

ostream& operator<<(ostream& os, const ItemDescription &id)
{
  os << id.ItemName() << endl;
  os << id.ItemSize() << endl;
  int n = id.FieldCount();
  for(int i=0; i<n; i++)
  {
    auto f = id.GetField(i);
    os << f << endl;
  }  
  return os;
}

ostream& operator<<(ostream& os, const TeaFileDescription &tfd)
{
  auto id = tfd.Item();
  if(id != 0)
  {
    os << "ItemDescription" << endl << id << endl;
  }
  auto cd = tfd.Content();
  if(!cd.empty())
  {
    os << "ContentDescription" << endl << tfd.Content() << endl << endl;
  }
  auto nvc = tfd.NameValues();
  if(nvc != 0)
  {
    os << "NameValueDescription" << endl << nvc << endl;
  }
  os << "TimeScale:" << endl;
  os << tfd.Scale() << endl;
  return os;
}

class Time;
ostream& operator<<(ostream& os, const Time &time)
{
  return os << time.ToPosixTime();
}

} // namespace teatime
