#ifndef EXAMPLES_ITEMS
#define EXAMPLES_ITEMS

#include <TeaFiles/Description.h>
#include <TeaFiles/IO.h>

namespace teatime {

struct Tick
{    
  teatime::Time Time;
  double Price;
  int Volume;
};

}

using teatime::Tick;

ostream& operator<<(ostream& os, const Tick& v)
{
  return os << v.Time << " " << v.Price << " " << v.Volume;
}

#endif // EXAMPLES_ITEMS