#ifndef TEATIME_BASE_POINTER
#define TEATIME_BASE_POINTER

#include <memory>
using std::shared_ptr;
using std::unique_ptr;

template<class T>
shared_ptr<T> shared(T*p)
{
  return shared_ptr<T>(p);
}

template<class T>
unique_ptr<T> unique(T*p)
{
  return unique_ptr<T>(p);
}

#endif // TEATIME_BASE_POINTER
