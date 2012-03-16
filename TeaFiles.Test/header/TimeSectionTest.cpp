#if 0

//#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace testing;

#include "description/ItemDescription.h"
#include "header/sections/ItemSectionPayload.h"
#include "base/Common.h"
#include "base/google/Common.h"
using namespace teatime;

#include <iostream>
using std::cout;
using std::endl;

TEST(PayloadTest, Write)
{	
  ItemDescription id(20, "Tick");
  ItemSectionPayload payload(&id);

  remove("mock.bin");
  {
    NiceMock<FileIO> f("mock.bin");
    NiceMock<WriteContext> c(&f);
  
    EXPECT_EQ(20, payload.GetSize(&c));
    payload.Write(&c);
  }
}

#endif