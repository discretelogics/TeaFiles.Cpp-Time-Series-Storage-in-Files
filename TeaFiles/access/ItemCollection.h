#ifndef TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION
#define TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION

#include <iterator>
#include <string>

namespace teatime {

class TeaFileCore;

template<typename T>
class InputIterator : public std::iterator<std::input_iterator_tag, T, int64>
{
public:
  InputIterator(TeaFileCore *core=0, int64 itemPosition=0);
  InputIterator& operator=(const InputIterator&);
  
  InputIterator& operator++();
  InputIterator operator++(int);
  
  bool operator==(const InputIterator&);
  bool operator!=(const InputIterator&);
  
  T& operator*();
  T& operator->();

private:
  TeaFileCore *core_;
  T current_;
  int64 currentPosition_;
  int64 itemCount_;
  bool fetchNext_;
};

template<typename T>
class ItemCollection
{
public:

  typedef InputIterator<T> iterator;
  typedef InputIterator<T> const_iterator;

  ItemCollection() {}

  void Initialized(TeaFileCore*);

  bool  IsEmpty();
  int64 Count();

  InputIterator<T> begin(int64 startItemIndex=0);
  InputIterator<T> end();

private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ItemCollection);
  TeaFileCore *core_;
};

} // namespace teatime

#endif // TEATIME_TEAFILE_ACCESS_ITEMCOLLECTION
