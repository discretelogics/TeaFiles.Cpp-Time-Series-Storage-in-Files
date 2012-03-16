#ifndef TEATIME_TIME
#define TEATIME_TIME

#include "../base/Common.h"

namespace boost {
namespace posix_time { class ptime; class time_duration; }
namespace gregorian { class date; }
}

namespace teatime {

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::gregorian::date;
class TimeScale;

// value type
class Time
{ 
public:

  Time() : ticks_(0) {};
  explicit Time(int64 ticks);
  Time(ptime);

  // boost interface
  ptime         ToPosixTime() const;
  ptime         ToPosixTime(TimeScale&) const;
  time_duration TimeOfDay() const;

  //  operations
  Time          Date() const;  
  Time          AddDays(int numberOfDays);

  // time part access. all these methods use TimeScale::Master()
  int Year() const;
  int Month() const;
  int Day() const;
  int Hour() const;
  int Minute() const;
  int Second() const;

  //  access the underlying ticks value
  int64 Ticks() const { return ticks_; }

  // operators
  bool operator==(const Time& other) const;
  bool operator!=(const Time& other) const;
  bool operator> (const Time& other) const;
  bool operator>=(const Time& other) const;
  bool operator< (const Time& other) const;
  bool operator<=(const Time& other) const;  

private:
  int64 ticks_;
};

} // namespace teatime

#endif // TEATIME_TIME
