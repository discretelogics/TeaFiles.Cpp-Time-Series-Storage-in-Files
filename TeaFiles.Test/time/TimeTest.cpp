#include <gtest/gtest.h>

#include "TeaFiles/time/Time.h"
using teatime::Time;
#include "TeaFiles/time/TimeScale.h"
using teatime::TimeScale;

#include <boost/date_time/posix_time/posix_time.hpp>
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::gregorian::date;

TEST(Time, JavaTimeScale)
{
  Time t(0);
  EXPECT_EQ(0, t.Ticks());
  
  EXPECT_EQ(1970, t.Year());
  EXPECT_EQ(1, t.Month());
  EXPECT_EQ(1, t.Day());
  EXPECT_EQ(0, t.Hour());
  EXPECT_EQ(0, t.Minute());
  EXPECT_EQ(0, t.Second());
}

TEST(Time, NetTimeScale)
{	
  Time t(630822816000000000); // these are the ticks of a .Net System.DateTime at 1.1.2000 00:00:00
  
  ptime pt = t.ToPosixTime(TimeScale::Net());
  time_duration timeOfDay = pt.time_of_day();
  date day = pt.date();
  
  EXPECT_EQ(630822816000000000, t.Ticks());
  
  EXPECT_EQ(2000, day.year());
  EXPECT_EQ(1, day.month());
  EXPECT_EQ(1, day.day());
  EXPECT_EQ(0, timeOfDay.hours());
  EXPECT_EQ(0, timeOfDay.minutes());
  EXPECT_EQ(0, timeOfDay.seconds());
}

TEST(Time, PosixConversionRoundTrip)
{	
  Time t(10 * 1000); // 10 seconds past 1.1.1970 at java time scale
  ptime pt = t.ToPosixTime(TimeScale::Java());  
  Time t2 = pt;
  EXPECT_EQ(t, t2);
}

TEST(Time, PosixConversionRoundTrip2)
{	
  Time t(1000 * 86400 * 5 + 1000 * 60 * 20); // 5.1.1970 00:20
  ptime pt = t.ToPosixTime(TimeScale::Java());  
  Time t2 = pt;  
  EXPECT_EQ(t, t2);
}

TEST(Time, PosixConversionRoundTrip3)
{	
  Time t(0);
  ptime pt = t.ToPosixTime(TimeScale::Java());  
  Time t2 = pt;  
  EXPECT_EQ(t, t2);
}
