#include "Examples/Common.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

teatime::Time clockTime;
boost::random::mt19937 gen;

Tick GetRandomTick()
{
  boost::random::uniform_int_distribution<> dist(1, 10000);
  clockTime = clockTime.AddDays(1);

  Tick t;
  t.Time = clockTime;
  t.Price = dist(gen) / 100.0;
  t.Volume = dist(gen);
  return t;
}

int main(int ac, const char* av[])
{
  try
  {
    if(ac != 3) throw Exception("Usage: CreateTicks <filename> <number of ticks>");
    const char* filename = av[1];
    int n = boost::lexical_cast<int>(av[2]);

    //  create sample ticks
    clockTime = boost::posix_time::second_clock::local_time();
    auto tf = TeaFile<Tick>::Create(filename);
    cout << tf->Description() << endl;
    for(int i=0; i < n; i++)
    {
      tf->Write(GetRandomTick());
    }
    cout << "added " << n << " Ticks" << endl;
  }
  catch(exception &e)
  {
    cout << e.what() << endl;
    return -1;
  }
  catch(...)
  {
    cout << "unspecified error" << endl;
    return -1;
  }
  return 0;
}
