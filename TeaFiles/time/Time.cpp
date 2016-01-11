#include "Time.h"
#include "TimeScale.h"

#include <boost/date_time/posix_time/posix_time.hpp>
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::gregorian::date;
using boost::gregorian::days;

namespace teatime {

const int64 Epoch1400 = 510974; // number of days between 1.1.1 and 1.1.1400
const int64 Epoch1970 = 719162; // number of days between 1.1.1 and 1.1.1970

Time::Time(int64 ticks)
{
  this->ticks_ = ticks;
}

Time::Time(ptime t)
{
  auto datePart = t.date();
  auto timePart = t.time_of_day();

  TimeScale timeScale = TimeScale::Master();

  // consider date part only
  auto d = datePart - date(1970, 1, 1);
  int offsetFromEpochDays = d.days();  
  this->ticks_ = timeScale.TicksPerDay() * offsetFromEpochDays;
    
  // add ticks for time of day
  if(time_duration::ticks_per_second() > timeScale.TicksPerSecond()) // since the following computations are integer calculcations, we distinguish here
  {
    int64 conversionRate = time_duration::ticks_per_second() / timeScale.TicksPerSecond();
    this->ticks_ += timePart.ticks() / conversionRate;
  }
  else
  {
    int64 conversionRate = timeScale.TicksPerSecond() / time_duration::ticks_per_second();
    this->ticks_ += timePart.ticks() * conversionRate;
  }  
}

ptime Time::ToPosixTime() const
{
  return this->ToPosixTime(TimeScale::Master());
}

ptime Time::ToPosixTime(TimeScale& timeScale) const
{
  auto ticks = this->ticks_;

  //  adjust ticks for epoch 1970
  int64 epochDelta = Epoch1970 - timeScale.Epoch();
  ticks -= epochDelta * timeScale.TicksPerDay(); // now the ticks are epoch'd 1970, so we use 1970,1,1 below
  
  // create time duration considering resolution.
  if(time_duration::ticks_per_second() > timeScale.TicksPerSecond()) // since the following computations are integer calculcations, we distinguish here
  {
    int64 conversionRate = time_duration::ticks_per_second() / timeScale.TicksPerSecond();
    ticks = conversionRate * ticks;
  }
  else
  {
    int64 conversionRate = timeScale.TicksPerSecond() / time_duration::ticks_per_second();
    ticks = ticks / conversionRate;
  }
  
  // date(1970) + ptime ticks since (1970)
  time_duration durationSinceEpoch(0, 0, 0, ticks);
  ptime pt(date(1970, 1, 1), durationSinceEpoch);
  return pt;
}

Time Time::AddDays(int numberOfDays)
{
    return Time(this->ticks_ + numberOfDays * TimeScale::Master().TicksPerDay());
}

Time Time::Date() const
{
  return Time(this->ticks_ - this->ticks_ % TimeScale::Master().TicksPerDay());
}

int Time::Year() const
{
  return this->ToPosixTime().date().year();
}

int Time::Month() const
{
  return this->ToPosixTime().date().month();
}

int Time::Day() const
{
  return this->ToPosixTime().date().day();
}

time_duration Time::TimeOfDay() const
{
  return this->ToPosixTime().time_of_day();
}

int Time::Hour() const
{
  return this->TimeOfDay().hours();
}

int Time::Minute() const
{
  return this->TimeOfDay().minutes();
}

int Time::Second() const
{
  return this->TimeOfDay().seconds();
}

bool Time::operator> (const Time& other) const
{
  return this->ticks_ > other.ticks_;
}

bool Time::operator>=(const Time& other) const
{
  return this->ticks_ >= other.ticks_;
}

bool Time::operator< (const Time& other) const
{
  return this->ticks_ < other.ticks_;
}

bool Time::operator<=(const Time& other) const
{
  return this->ticks_ <= other.ticks_;
}

bool Time::operator== (const Time& other) const
{
  return this->ticks_ == other.ticks_;
}

bool Time::operator!=(const Time& other) const
{
  return this->ticks_ != other.ticks_;
}

} // namespace teatime
