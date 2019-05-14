#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>

class TTestRaceList : public TTestCase
{
public:
  __fastcall virtual TTestRaceList(System::String name) : TTestCase(name) {}
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();
  
__published:
  void __fastcall TestLocations();
  void __fastcall TestLoadFromExcel();
};


void __fastcall TTestRaceList::SetUp()
{
}

void __fastcall TTestRaceList::TearDown()
{
}

void __fastcall TTestRaceList::TestLocations()
{
  // void __fastcall Locations(TForm *form)
}
    
void __fastcall TTestRaceList::TestLoadFromExcel()
{
  // void LoadFromExcel(AnsiString filename)
}
    


static void registerTests()
{
  Testframework::RegisterTest(TTestRaceList::Suite());
}
#pragma startup registerTests 33
