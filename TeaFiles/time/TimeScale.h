#ifndef TEATIME_TEAFILE_TIME_TIMESCALE
#define TEATIME_TEAFILE_TIME_TIMESCALE

#include "../base/Common.h"

namespace teatime {

class Time;

// value type
class TimeScale
{ 
public:

  // if possible, use a single scale for all times in an application. This single scale is then stored
  // in this static variable.
  static TimeScale& Master();
  static TimeScale& Java();
  static TimeScale& Net();

  TimeScale(int64 epoch, int64 ticksPerDay);

  int64 Epoch() const;
  int64 TicksPerDay() const;
  int64 TicksPerSecond() const;
  int64 TicksSinceEpoch() const;

  bool operator==(const TimeScale& other) const;
  bool operator!=(const TimeScale& other) const;
  
private:
  int64 epoch_;
  int64 ticksPerDay_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_TIME_TIMESCALE
