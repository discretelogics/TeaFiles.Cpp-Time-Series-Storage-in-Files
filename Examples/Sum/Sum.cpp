#include <Examples/Common.h>

int main(int ac, const char* av[])
{
  try
  {
    if(ac != 2) throw Exception("Usage: Sum <filename>");
    const char* filename = av[1];

    Stopwatch sw;
    
    //  open file for reading
    auto tf = TeaFile<Tick>::OpenRead(filename);
    
    //  print its description
    cout << tf->Description() << endl;
    
    //  sum all items
    double sum = 0;
    {            
      //  map the file into memory
      auto itemArea = tf->OpenReadableMapping();
      
      //  the Start() and End() methods should be inlined by the compiler and do just raw pointer access.
      for(Tick *tick = itemArea->begin(); tick != itemArea->end(); ++tick)
      {
        sum += tick->Price;
      }
    }    
    cout << "sum=" << sum << endl;    
  }
  catch(exception &e)
  {
    cout << e.what() << endl;
  }
  return 0;
}
