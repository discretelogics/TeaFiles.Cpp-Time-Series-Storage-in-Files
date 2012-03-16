#ifndef TEATIME_BASE_FIELDTYPE
#define TEATIME_BASE_FIELDTYPE

#include "Enums.h"
#include "Common.h"
#include "Exceptions.h"

namespace teatime {

class FieldType : public Enumeration
{
public:

  static const uint32 Unknown = 0;
  
  static const int32 Int8  = 1;
  static const int32 Int16 = 2;
  static const int32 Int32 = 3;
  static const int32 Int64 = 4;

  static const int32 UInt8  = 5;
  static const int32 UInt16 = 6;
  static const int32 UInt32 = 7;
  static const int32 UInt64 = 8;
  
  static const int32 Float  = 9;
  static const int32 Double = 10;

  // platform specific
  static const int32 NetDecimal = 0x200;
  static const int32 JavaBigDecimal = 0x201;

  // private extensions must have identifiers above 0x1000.
  static const int32 Custom = 0x1000;

  FieldType() : Enumeration(Unknown) {}
  FieldType(int value) : Enumeration(value) {}

  const char* ToString() const;
};

//bool operator==(const FieldType& lhs, const FieldType& rhs);

template<class F>
struct FieldTypeTraits
{
  static void    GetMagicValue() {throw Exception("Unavailable FieldType.");}
  static FieldType GetFieldType()  {throw Exception("Unavailable FieldType.");}
};

template<>
struct FieldTypeTraits<int8>
{
  static int8    GetMagicValue() {return 0x36; }
  static FieldType GetFieldType()  {return FieldType::Int8;}
};

template<>
struct FieldTypeTraits<int16>
{
  static int16   GetMagicValue() {return 0x0102; }
  static FieldType GetFieldType()  {return FieldType::Int16;}
};

template<>
struct FieldTypeTraits<int32>
{
  static int32   GetMagicValue() {return 11223344;}
  static FieldType GetFieldType()  {return FieldType::Int32;}  
};

template<>
struct FieldTypeTraits<int64>
{
  static int64   GetMagicValue() {return 0x0102030405060708;}
  static FieldType GetFieldType()  {return FieldType::Int64;}  
};

template<>
struct FieldTypeTraits<uint8>
{
  static uint8   GetMagicValue() {return 0x21; }
  static FieldType GetFieldType()  {return FieldType::UInt8;}
};

template<>
struct FieldTypeTraits<uint16>
{
  static uint16  GetMagicValue() {return 0x0807; }
  static FieldType GetFieldType()  {return FieldType::UInt16;}
};

template<>
struct FieldTypeTraits<uint32>
{
  static uint32  GetMagicValue() {return 3485;}
  static FieldType GetFieldType()  {return FieldType::UInt32;}  
};

template<>
struct FieldTypeTraits<uint64>
{
  static uint64  GetMagicValue() {return 0x0807060504020301;}
  static FieldType GetFieldType()  {return FieldType::UInt64;}  
};

template<>
struct FieldTypeTraits<double>
{
  static double  GetMagicValue() {return 1234.5678;}
  static FieldType GetFieldType()  {return FieldType::Double;}
};

} // namespace teatime

#endif // TEATIME_BASE_FIELDTYPE
