#include <gtest/gtest.h>

#include "TeaFiles/os/FileIO.h"
using namespace teatime;

TEST(FileIOTest, WriteReadRoundTrip)
{	  
  remove("test.tea");
  {
    {
      FileIO f;
      f.Create("test.tea");
      EXPECT_EQ(0, f.GetFilePosition());
      EXPECT_EQ(0, f.FileSize());
      f.Flush();
      
      uint64 value = 0x0102030405060708;
      f.Write((byte*)&value, 8);
      EXPECT_EQ(8, f.GetFilePosition());
      EXPECT_EQ(8, f.FileSize());
      f.Flush();

      uint32 value2 = 0x01020304;
      f.Write((byte*)&value2, 4);
      EXPECT_EQ(12, f.GetFilePosition());
      EXPECT_EQ(12, f.FileSize());
      f.Flush();
    }
    {
      FileIO f;
      f.OpenRead("test.tea");
      EXPECT_EQ(12, f.FileSize());
      EXPECT_EQ(0, f.GetFilePosition());

      uint64 value = 0xffffffffffffffff;
      f.Read(&value, 8);
      EXPECT_EQ(0x0102030405060708, value);
      EXPECT_EQ(8, f.GetFilePosition());

      uint32 value2 = 0xffffffff;
      f.Read(&value2, 4);
      EXPECT_EQ(0x01020304, value2);
      EXPECT_EQ(12, f.GetFilePosition());
    }
  }
}

TEST(FileIOTest, WriteAndReadBytes)
{	
  remove("test.tea");
  {
    {
      FileIO f;
      f.Create("test.tea");
      uint8 bytes[] = {8, 4, 1, 1, 33};
      f.Write(bytes, 5);
    }
    {
      FileIO f;
      f.OpenRead("test.tea");
      uint8 bytes[5];
      f.Read(&bytes, 5);
      EXPECT_EQ(8, bytes[0]);
      EXPECT_EQ(4, bytes[1]);
      EXPECT_EQ(1, bytes[2]);
      EXPECT_EQ(1, bytes[3]);
      EXPECT_EQ(33, bytes[4]);
    }
  }
}

//TEST(FileIOTest, WriteIntoReadOnlyFile)
//{	
//  remove("test.tea");
//  {
//    {
//      FileIO f;
//      f.Create("test.tea");
//      uint8 bytes[] = {8, 4, 1, 1, 33};
//      f.Write(bytes, 5);
//    }
//    {
//      FileIO f;
//      f.OpenRead("test.tea");
//      uint8 bytes[] = {8, 4, 1, 1, 33};
//      ASSERT_THROW(f.Write(bytes, 5), std::exception);      
//    }
//  }
//}

TEST(FileIOTest, WriteFile)
{	
  remove("test.tea");
  {
    {
      FileIO f;
      f.Create("test.tea");
      uint8 bytes[] = {8, 4, 1, 1, 33};
      EXPECT_EQ(0, f.FileSize());
      f.Write(bytes, 5);
      EXPECT_EQ(5, f.FileSize());
    }
    {
      FileIO f;
      f.OpenReadWrite("test.tea");
      EXPECT_EQ(5, f.FileSize());
      uint8 bytes[] = { 7, 5, 4, 22 };
      EXPECT_EQ(5, f.FileSize());
      f.SetFilePosition(0);
      f.Write(bytes, 4); // update only the first 4 bytes
    }
     {
      FileIO f;
      f.OpenRead("test.tea");
      EXPECT_EQ(5, f.FileSize());
      uint8 bytes[5];
      f.Read(&bytes, 5);
      EXPECT_EQ(7, bytes[0]);
      EXPECT_EQ(5, bytes[1]);
      EXPECT_EQ(4, bytes[2]);
      EXPECT_EQ(22, bytes[3]);
      EXPECT_EQ(33, bytes[4]); // the last byte still has the value from thefirst version
    }
  }
}
