#ifndef EXAMPLES_COMMON
#define EXAMPLES_COMMON

#if _MSC_VER
#pragma warning (disable : 4996) // iterator checking
#pragma once
#endif

#include "Items.h"

#include <TeaFiles/File.h>
#include <TeaFiles/IO.h>
using teatime::TeaFile;

#include <Examples/Items.h>
using teatime::Tick;

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
using boost::posix_time::ptime;
using boost::gregorian::date;
using boost::gregorian::days;
using boost::posix_time::hours;
using boost::posix_time::milliseconds;
using boost::posix_time::from_time_t;
using boost::posix_time::microsec_clock;

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <iostream>
using std::cout;
using std::endl;
#include <exception>
using std::exception;

using teatime::Exception;

class Stopwatch
{
public:

  Stopwatch()
  {
    this->start_ = microsec_clock::universal_time();
    this->running_ = true;
  }

  ~Stopwatch()
  {
    if(this->running_)
    {
      Stop();
      Print();
    }
  }

  void Stop()
  {
    this->stop_  = microsec_clock::universal_time();
    this->running_ = false;
  }

  void Print()
  {        
    cout << "execution time=" << TotalMilliseconds() << "ms" << endl;    
  }

  teatime::int64 TotalMilliseconds()
  {
    auto elapsedTime = this->stop_ - this->start_;
    return elapsedTime.total_milliseconds();
  }

  ptime start_;
  ptime stop_;
  bool running_;
};

#endif // EXAMPLES_COMMON          