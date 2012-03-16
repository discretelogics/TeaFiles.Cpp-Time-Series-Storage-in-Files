#ifndef TEATIME_TEAFILE_BASE_COMMON
#define TEATIME_TEAFILE_BASE_COMMON

#ifdef _MSC_VER
#pragma warning ( disable : 4996 4514 4820 ) // ?, unreferenced inlines, added padding
#else
#include <stdint.h>
#endif

namespace teatime {

#ifdef _MSC_VER
typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#else
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
#endif

typedef uint8 byte;

} // namespace teatime

namespace boost { namespace uuids {
struct uuid;
}}
using boost::uuids::uuid;

// macro borrowed from google
#undef GOOGLE_DISALLOW_EVIL_CONSTRUCTORS
#define GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                           \
  void operator=(const TypeName&)

#endif // TEATIME_TEAFILE_BASE_COMMON
