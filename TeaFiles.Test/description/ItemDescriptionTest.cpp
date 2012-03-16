#include <gtest/gtest.h>
//#include <gmock/gmock.h>
using namespace testing;

#include "TeaFiles/description/Description.h"
#include "TeaFiles/base/Common.h"
using namespace teatime;

// define a struct with customized alignment. this demonstrates how we can specify precisely the layout of a type.
#pragma pack (push, 1)
struct CustomAlignedStruct
{
  byte    a; //  field at expected offset 0
  int16   b; //  field at expected offset 1
  byte    c; //  field at expected offset 3
  byte    d; //  field at expected offset 4
  int64   e; //  field at expected offset 5
};
#pragma pack (pop)

namespace teatime {

template<>
class Description<CustomAlignedStruct> : public DefaultDescription<CustomAlignedStruct>
{
public:

  Description()
  {    
    this->AddField(&CustomAlignedStruct::a, "a");
    this->AddField(&CustomAlignedStruct::b, "b");
    this->AddField(&CustomAlignedStruct::c, "c");
    this->AddField(&CustomAlignedStruct::d, "d");
    this->AddField(&CustomAlignedStruct::e, "e");
    this->AddField(&CustomAlignedStruct::e, "e");
  }
};

struct CompilerAlignedStruct
{
  byte    a; //  field at expected offset 0
  int16   b; //  field at expected offset 2 (1 + 1 padding)
  byte    c; //  field at expected offset 4
  int64   d; //  field at expected offset 8 (4+1 + 3padding)
};

template<>
class Description<CompilerAlignedStruct> : public DefaultDescription<CompilerAlignedStruct>
{
public:

  Description()
  {    
    this->AddField(&CompilerAlignedStruct::a, "a");
    this->AddField(&CompilerAlignedStruct::b, "b");
    this->AddField(&CompilerAlignedStruct::c, "c");
    this->AddField(&CompilerAlignedStruct::d, "d");
  }
};

TEST(ItemDescriptionTest, CustomAlignedStruct)
{
  Description<CustomAlignedStruct> d;
  
  EXPECT_EQ(0, d.GetField(0)->Offset());
  EXPECT_EQ(1, d.GetField(1)->Offset());
  EXPECT_EQ(3, d.GetField(2)->Offset());
  EXPECT_EQ(4, d.GetField(3)->Offset());
  EXPECT_EQ(5, d.GetField(4)->Offset());
}

TEST(ItemDescriptionTest, CompilerAlignedStruct)
{
  Description<CompilerAlignedStruct> d;
  
  EXPECT_EQ(0, d.GetField(0)->Offset());
  EXPECT_EQ(2, d.GetField(1)->Offset());
  EXPECT_EQ(4, d.GetField(2)->Offset());
  EXPECT_EQ(8, d.GetField(3)->Offset());
}

}