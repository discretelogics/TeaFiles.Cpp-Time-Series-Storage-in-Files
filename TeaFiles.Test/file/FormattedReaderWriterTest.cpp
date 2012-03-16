#include <gtest/gtest.h>
//#include <gmock/gmock.h>
using namespace testing;

#include "TeaFiles/os/FileIO.h"
#include "TeaFiles/file/Streams.h"
#include "TeaFiles/file/FormattedReader.h"
#include "TeaFiles/file/FormattedWriter.h"

using namespace teatime;

TEST(FormattedReadWrite, FormattedWriterConstruction)
{	
  remove("test.tea");
  
  FileIO f;
  f.Create("test.tea");
  FileStream s(&f);
  FormattedWriter w(&s);
	
  EXPECT_EQ(0, f.GetFilePosition());
}

TEST(FormattedReadWrite, FormattedWriterReader)
{	
  remove("test.tea");  
  {
    FileIO f;
    f.Create("test.tea");
    FileStream s(&f);
    FormattedWriter w(&s);
  }
  {
    FileIO f;
    f.OpenRead("test.tea");
    FormattedReader r(&f);
  }
}

TEST(FormattedReadWrite, WriteAndReadInt32)
{	
  remove("test.tea");  
  {
    FileIO f;
    f.Create("test.tea");
    FileStream s(&f);
    FormattedWriter w(&s);
    w.WriteInt32(72);
  }
  {
    FileIO f;
    f.OpenRead("test.tea");
    FormattedReader r(&f);
    int32 n = r.ReadInt32();
    EXPECT_EQ(72, n);
  }	
}

TEST(FormattedReadWrite, WriteAndReadInt64)
{	
  remove("test.tea");  
  {
    FileIO f;
    f.Create("test.tea");
    FileStream s(&f);
    FormattedWriter w(&s);
    w.WriteInt64(4412);
  }
  {
    FileIO f;
    f.OpenRead("test.tea");
    FormattedReader r(&f);
    int64 n = r.ReadInt32();
    EXPECT_EQ(4412, n);
  }	  
}

TEST(FormattedReadWrite, WriteAndReadText)
{
  remove("test.tea");  
  {
    FileIO f;
    f.Create("test.tea");
    FileStream s(&f);
    FormattedWriter w(&s);
    w.WriteText("Sunshine");    
    EXPECT_EQ(12, f.GetFilePosition());
  }
 {
    FileIO f;
    f.OpenRead("test.tea");
    FormattedReader r(&f);
    string text = r.ReadText();
    EXPECT_EQ("Sunshine", text);
    EXPECT_EQ(12, f.GetFilePosition());
  }	
}

TEST(FormattedReadWrite, WriteAndReadTextNonASCII)
{
  remove("test.tea");  
  {
    FileIO f;
    f.Create("test.tea");
    FileStream s(&f);
    FormattedWriter w(&s);
    w.WriteText("Some characters are ASCII like $, some are above 127, like €");
  }
  {
    FileIO f;
    f.OpenRead("test.tea");
    FormattedReader r(&f);
    string s = r.ReadText();
    EXPECT_EQ("Some characters are ASCII like $, some are above 127, like €", s);
  }	
}

/*
TEST(FormattedReadWrite, EuroSymbolOccupies3BytesInUTF8)
{	
  remove("test.tea");
  {
    NiceMock<FileIO> fio("test.tea");
    FormattedWriter w(&fio);    
    
    w.WriteText("€");
    
    //EXPECT_EQ(3, n);
  }
}
*/
