#include "FieldType.h"

#include "Exceptions.h"

namespace teatime {

bool operator==(const FieldType& lhs, const FieldType& rhs) 
{
  return (uint32)lhs == (uint32)rhs;
}

const char* FieldType::ToString() const
{
  switch(this->value_)
  {
    case FieldType::Unknown: return "unknown";
    case FieldType::Int8  : return "Int8";
    case FieldType::Int16 : return "Int16";
    case FieldType::Int32 : return "Int32";
    case FieldType::Int64 : return "Int64";
    case FieldType::UInt8 : return "UInt8";
    case FieldType::UInt16: return "UInt16";
    case FieldType::UInt32: return "UInt32";
    case FieldType::UInt64: return "UInt64";
    case FieldType::Float : return "Float";
    case FieldType::Double: return "Double";
  }
  throw Exception("Invalid FieldType");
}

} // namespace teatime
