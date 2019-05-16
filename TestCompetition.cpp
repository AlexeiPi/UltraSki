#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include "TestCompetition.h"

//-------------------------------------------------------------------------------
RaceList rcl,rcl1;
extern String udiag;
//-------------------------------------------------------------------------------
class TTestRaceList : public TTestCase
{
public:
  __fastcall virtual TTestRaceList(System::String name) : TTestCase(name) {}
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
  void __fastcall LoadFromCSV();
  void __fastcall saveXML();
  void __fastcall loadXML();
};
//______________________________________________________________________________
//______________________________________________________________________________
void __fastcall TTestRaceList::SetUp(){
}
void __fastcall TTestRaceList::TearDown(){
}
//______________________________________________________________________________
void __fastcall TTestRaceList::LoadFromCSV(){
  // void LoadFromExcel(AnsiString filename)
	rcl.LoadFromCSV("C:\\test\\RPT_Start_910.csv");
	rcl.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	udiag=rcl.getRacer(1,2);
	udiag=rcl1.getRacer(1,1);
	udiag=rcl1.getRacer(1,2);
	rcl1.setRacer(1,2,"ѕивоваров јлексей");
	udiag=rcl1.getRacer(1,2);
	auto i=rcl.Compare(&rcl1);
	udiag="Ќесовпадение векторов списков спортсменов после загрузки из CSV";
	Check(i,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::saveXML(){
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910.xml");
	auto i=rcl.Compare(&rcl1);
	udiag="Ќесовпадение векторов списков спортсменов после сохранени€ XML";
	Check(i,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::loadXML(){
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910.xml");
	auto i=rcl.Compare(&rcl1);
	udiag="Ќесовпадение векторов списков спортсменов после загрузки XML";
	Check(i,udiag);
}
//______________________________________________________________________________
static void registerTests(){
  Testframework::RegisterTest(TTestRaceList::Suite());
}
#pragma startup registerTests 33
