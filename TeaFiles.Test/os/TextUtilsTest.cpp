// #include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TeaFiles/os/TextUtils.h"
#include "TeaFiles/base/Common.h"
using namespace teatime;

TEST(TextUtilsTest, ConvertASCII)
{	
  string s = TextUtils::ConvertToUTF8("abc");  
  EXPECT_EQ("abc", s);
}

TEST(TextUtilsTest, Convert3ByteSymbol)
{	
  string s = TextUtils::ConvertToUTF8("€");
  EXPECT_EQ((byte)0xe2, (byte)s[0]);
  EXPECT_EQ((byte)0x82, (byte)s[1]);
  EXPECT_EQ((byte)0xac, (byte)s[2]);
}

TEST(TextUtilsTest, ConvertRoundTrip)
{	
  string utf8 = TextUtils::ConvertToUTF8("€");
  string s = TextUtils::ConvertFromUTF8(utf8);
  EXPECT_EQ("€", s);
}
