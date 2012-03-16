//#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace testing;

#include <TeaFiles/File.h>
#include <TeaFiles/IO.h>
#include <TeaFiles/access/MemoryAccess.h>

using namespace teatime;

#include <iostream>
using std::cout;
using std::endl;

struct Tick
{
  int64 A; 
  int64 B; 
  int64 C; 
};

namespace teatime {

template<>
class Description<Tick> : public DefaultDescription<Tick>
{
public:
  Description()
  {    
    this->AddField(&Tick::A, "A");
    this->AddField(&Tick::B, "B");
    this->AddField(&Tick::C, "C");
  }
};

}

TEST(TeaFileTest, OpenReadableMapping)
{
  remove("test.tea");
  {
    auto tf = TeaFile<Tick>::Create("test.tea");
    for(int i=1; i <= 7; i++)
    {
      Tick t;
      t.A = i;
      t.B = i * 2;
      t.C = i * 3;
      tf->Write(t);
    }  
  }
  auto tf = TeaFile<Tick>::OpenRead("test.tea");
  auto mapping = tf->OpenReadableMapping();
  int n=1;
  for(Tick *p = mapping->begin(); p != mapping->end(); ++p)
  {
     EXPECT_EQ(n,   p->A);
     EXPECT_EQ(n*2, p->B);
     EXPECT_EQ(n*3, p->C);
     n++;
  }
  EXPECT_EQ(8, n);

  cout << mapping->begin() << endl;
  cout << mapping->end() << endl;
  cout << tf->Description() << endl;
}

TEST(TeaFileTest, TimeScaleIsSetInNewFile)
{
  remove("test.tea");
  auto tf = TeaFile<Tick>::Create("test.tea");
  EXPECT_EQ(719162, tf->Description()->Scale().Epoch());
}

#if 0 // creating a 4GB file takes a long time. change 0 to 1 and recompile to include this test
TEST(TeaFileTest, CreateAndManipulateFileLargerThan4GB)
{  
  int N = 178956970 + 1000; // 2^32 / 24 + 1000  
  
  remove("test4plusGB.tea");
  {
    auto tf = TeaFile<Tick>::Create("test4plusGB.tea");
    for(int i=0; i < N; i++)
    {
      Tick t;
      t.A = i;
      t.B = i * 2;
      t.C = i * 3;
      tf->Write(t);
    }
  }

  auto tf = TeaFile<Tick>::OpenRead("test4plusGB.tea");
  auto mapping = tf->OpenReadableMapping();
  int n=0;
  Tick* start= mapping->Start();
  Tick* end = mapping->End();  
  for(Tick *p = start; p != end; ++p)
  {
      ASSERT_EQ(n,   p->A);
      ASSERT_EQ(n*2, p->B);
      ASSERT_EQ(n*3, p->C);
      n++;
  }
  EXPECT_EQ(N, n);

  cout << mapping->Start() << endl;
  cout << mapping->End() << endl;
  cout << tf->Description() << endl;
}
#endif