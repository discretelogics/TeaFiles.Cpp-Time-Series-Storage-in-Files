#if 0

//  google unit testing
#include <gtest/gtest.h>

#include "header/HeaderManager.h"
#include "header/WriteContext.h"
#include "header/ReadContext.h"
#include "description/TeaFileDescription.h"
#include "description/ItemDescription.h"
using namespace teatime;

#include "base/Common.h"
#include "base/google/Common.h"

#include <iostream>
using std::cout;
using std::endl;

//  sample item
struct Measurement
{
  int SensorId;
  double Value;
};

TEST(HeaderManagerTest, Write)
{	
  int n = 0;
  remove("test.tea");
  {
    //  write the file here
    FileIO file("test.tea");
    
    //  store context while writing the header here
    WriteContext context(&file);
    
    //  write this description
    TeaFileDescription description;
    
    ItemDescription* id = new ItemDescription(sizeof(Measurement), "Measurement");
    description.SetItemDescription(id);
    id->Fields()->push_back(Field::Ptr(new Field("SensorId", TeaType::Int32, 0)));
    id->Fields()->push_back(Field::Ptr(new Field("Value", TeaType::Double, 8)));
    
    //  write
    HeaderManager::WriteHeader(&context, &description);
    n = file.GetCurrentFilePosition();
  }    
  {
    //  write the file here
    FileIO file("test.tea", FileMode::Open, FileAccess::Read);
    
    //  store context while writing the header here
    ReadContext context(&file);
    EXPECT_EQ((int)context.Description(), 0);
    
    HeaderManager::ReadHeader(&context);
    EXPECT_EQ(n, file.GetCurrentFilePosition());
    EXPECT_NE((int)context.Description(), 0);
    EXPECT_NE((int)context.Description()->GetItemDescription(), 0);
    EXPECT_EQ(2, context.Description()->GetItemDescription()->Fields()->size());
    Field *f1 = context.Description()->GetItemDescription()->Fields()->at(0).get();
    EXPECT_EQ(0, f1->Offset());
    EXPECT_EQ(TeaType::Int32, f1->Type());
    EXPECT_EQ("SensorId", f1->Name());
    Field *f2 = context.Description()->GetItemDescription()->Fields()->at(1).get();
    EXPECT_EQ(8, f2->Offset());
    EXPECT_EQ(TeaType::Double, f2->Type());
    EXPECT_EQ("Value", f2->Name());
  }
}

#endif