#include <Examples/Common.h>

// we analyze the number of ticks per trading session, so we define a class for such session
class TradingSession
{
public:

  typedef vector<shared_ptr<TradingSession>> Container;
  
  teatime::Time  Begin;
  teatime::Time  End;
  int TickCount;

  TradingSession(teatime::Time time) // time is any time within the trading session
  {
      this->Begin = time.Date();
      this->End = this->Begin.AddDays(1);
      this->TickCount = 0;
  }
private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TradingSession);
};

bool CompareByTickCount(TradingSession::Container::value_type &lhs, TradingSession::Container::value_type &rhs)
{
  return lhs->TickCount < rhs->TickCount;
}

ostream& operator<<(ostream& os, const shared_ptr<TradingSession> s)
{
  return os << s->Begin << " " << s->TickCount;
}

int run(const char* filename, bool displayValues);

int main(int ac, const char* av[])
{
  try
  {
    if(ac < 2) throw Exception("Usage: Analyze <filename> <n>times");
    const char* filename = av[1];
    int n =  (ac >= 3) ? boost::lexical_cast<int>(av[2]) : 1;
  
    for(int i=1; i <= n; i++)
    {
      cout << "----------------------------------" << endl;
      cout << i << ". run" << endl;
      Stopwatch sw;
      run(filename, n == 1);
    }  
  }
  catch(Exception &e)
  {
    cout << e.what() << endl;
  }
  return 0;
}

int run(const char* filename, bool displayValues)
{
  try
  {
    {      
      //  open the file
      auto tf = TeaFile<Tick>::OpenRead(filename);

      // check if the file is empty
      if(tf->Items().IsEmpty()) throw Exception("The file is empty");      

      //  map the file into memory
      auto items = tf->OpenReadableMapping();

      //  instantiate a sessions container and add the first session to it
      double minPrice = std::numeric_limits<double>::max();
      double maxPrice = std::numeric_limits<double>::min();
      Tick *first = items->begin();
      auto session = shared(new TradingSession(first->Time));
      TradingSession::Container sessions;
      sessions.push_back(session);

      for(Tick *t = items->begin(); t != items->end(); ++t)
      {
        if (t->Time >= session->End)
        {
            session = shared(new TradingSession(t->Time));
            sessions.push_back(session);
        }
        session->TickCount++;
        minPrice = std::min(t->Price, minPrice);
        maxPrice = std::max(t->Price, maxPrice);
      }      

      int minTicksPerSession = (*std::min_element(sessions.begin(), sessions.end(), CompareByTickCount))->TickCount;
      int maxTicksPerSession = (*std::max_element(sessions.begin(), sessions.end(), CompareByTickCount))->TickCount;

      cout << "min price = " << minPrice << endl;
      cout << "max price = " << maxPrice << endl;
      cout << "min ticks per session = " << minTicksPerSession << endl;
      cout << "max ticks per session = " << maxTicksPerSession << endl;

      vector<int> tickCounts(sessions.size());      
      int i=0;
      foreach(auto s, sessions)
      {
        tickCounts[i++] = s->TickCount;
      }
      std::sort(tickCounts.begin(), tickCounts.end());
      int median = tickCounts[tickCounts.size() / 2];
      cout << "median = " << median << endl;      

      if (displayValues)
      {
          double minimumExpectedTicksPerSession = median / 2.0;
          cout << "First 10 sessions:" << endl;
          int n=0;
          for(auto sit = sessions.begin(); sit != sessions.end() && n < 10; ++sit, ++n)
          {
              auto session = *sit;
              cout << session;
              cout << ((session->TickCount >= minimumExpectedTicksPerSession) ? " OK" : " QUESTIONABLE");
              cout << endl;
          }
      }
    }
  }
  catch(exception &e)
  {
    cout << e.what() << endl;
  }
  return 0;
}

