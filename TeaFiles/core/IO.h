#ifndef TEATIME_TEAFILE_CORE_IO
#define TEATIME_TEAFILE_CORE_IO

#include "../base/Common.h"
#include "../base/Pointer.h"
#include "../base/FieldType.h"
#include <iostream>
using std::ostream;

namespace teatime {

ostream& operator<<(ostream& os, const FieldType& ft);

// allow shared_ptr<T>s be passed directory to ostream<< operators
template<typename T>
ostream& operator<<(ostream& os, const shared_ptr<T>& ptr)
{
  return operator<<(os, *ptr.get());
}

class Field;
ostream& operator<<(ostream& os, const Field &f);

class TimeScale;
ostream& operator<<(ostream& os, const TimeScale &scale);

class NameValueCollection;
ostream& operator<<(ostream& os, const NameValueCollection&);

class ItemDescription;
ostream& operator<<(ostream& os, const ItemDescription&);

class TeaFileDescription;
ostream& operator<<(ostream& os, const TeaFileDescription&);

class Time;
ostream& operator<<(ostream& os, const Time&);

} // namespace teatime

#endif // TEATIME_TEAFILE_CORE_IO
