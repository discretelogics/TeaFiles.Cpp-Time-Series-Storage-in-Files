#include "TimeScale.h"

namespace teatime {

const int64 SecondsPerDay = 60 * 60 * 24; // = 86400
const int64 MillisecondsPerDay = SecondsPerDay * 1000;
const int64 MicrosecondsPerDay = MillisecondsPerDay * 1000;

TimeScale& TimeScale::Master()
{
  return TimeScale::Java(); // default time scale. change if needed
}

TimeScale& TimeScale::Java()
{
  static TimeScale instance(719162, MillisecondsPerDay); 
  
  return instance;
}

TimeScale& TimeScale::Net()
{
  static TimeScale instance(0, MicrosecondsPerDay * 10); 
  
  return instance;
}

TimeScale::TimeScale(int64 epoch, int64 ticksPerDay)
{
  this->epoch_ = epoch;
  this->ticksPerDay_ = ticksPerDay;
}
  
int64 TimeScale::Epoch() const
{
  return this->epoch_;
}

int64 TimeScale::TicksPerDay() const
{
  return this->ticksPerDay_;
}

int64 TimeScale::TicksPerSecond() const
{
  return this->TicksPerDay() / 86400;
}

int64 TimeScale::TicksSinceEpoch() const
{
  return this->epoch_ * this->TicksPerDay();
}

bool TimeScale::operator==(const TimeScale& other) const
{
  return (this->ticksPerDay_ == other.ticksPerDay_) &&
         (this->epoch_ == other.epoch_);
}

bool TimeScale::operator!=(const TimeScale& other) const
{
  return !this->operator==(other);
}

} // namespace teatime
