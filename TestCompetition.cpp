#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include "TestCompetition.h"

//-------------------------------------------------------------------------------
RaceResults rrcl,rrcl1;
RaceList rcl,rcl1;
extern String udiag;
string str;
//-------------------------------------------------------------------------------
class TTestRaceResults : public TTestCase
{
public:
  __fastcall virtual TTestRaceResults(System::String name) : TTestCase(name) {}
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
  void __fastcall LoadFromCSV();
  void __fastcall saveXML();
  void __fastcall loadXML();
  void  __fastcall getResult();
  void  __fastcall setResult();

};
//______________________________________________________________________________
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
  void  __fastcall getRacer();
  void  __fastcall setRacer();

};
//______________________________________________________________________________
//______________________________________________________________________________
void __fastcall TTestRaceResults::SetUp(){
}
void __fastcall TTestRaceResults::TearDown(){
}
//______________________________________________________________________________
void __fastcall TTestRaceResults::saveXML(){
int ii=0;
	udiag="Несовпадение векторов списков результатов после сохранения в XML";
	Check(ii,udiag);
};
//______________________________________________________________________________
void __fastcall TTestRaceResults::loadXML(){
int ii=0;
	udiag="Несовпадение векторов списков результатов после загрузки из XML";
	Check(ii,udiag);
};
//______________________________________________________________________________
void __fastcall TTestRaceResults::LoadFromCSV(){
  // void LoadFromExcel(AnsiString filename)
	rrcl.LoadFromCSV("C:\\test\\Results.csv");
	rrcl.saveXML("C:\\test\\Results.xml");
/*	rrcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	str=rrcl.getResult(1,2);
	str=rrcl1.getResult(1,1);
	str=rrcl1.getResult(1,2);
	rrcl1.setResult(1,2,"Пивоваров Алексей");
	rrcl1.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rrcl1.setRacer(1,2,str.c_str());
	str=rrcl1.getResult(1,2);
	int ii=rrcl.Compare(&rcl1);
*/
int ii=0;
	udiag="Несовпадение векторов списков результатов после загрузки из CSV";
	Check(ii,udiag);
}
//______________________________________________________________________________
void  __fastcall  TTestRaceResults::getResult(){
int ii=0;
	udiag="Несовпадение векторов результатов спортсменов";
	Check(ii,udiag);
}
//______________________________________________________________________________
void  __fastcall  TTestRaceResults::setResult(){
int ii=0;
	udiag="Несовпадение векторов результатов спортсменов";
	Check(ii,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::SetUp(){
}
void __fastcall TTestRaceList::TearDown(){
}
//______________________________________________________________________________
void  __fastcall  TTestRaceList::getRacer(){
	rcl.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	str=rcl1.getRacer(1,2);
	rcl1.setRacer(1,2,"Пивоваров Алексей");
	rcl1.setRacer(1,2,str.c_str());
	str=rcl1.getRacer(1,2);

	bool ii=rcl.Compare(&rcl1);
	udiag="Несовпадение векторов списков спортсменов";
	Check(ii,udiag);
}
//______________________________________________________________________________
void  __fastcall TTestRaceList::setRacer(){
	rcl.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	str=rcl.getRacer(1,2);
	rcl1.setRacer(1,2,"Пивоваров Алексей");
	rcl1.setRacer(1,2,str.c_str());
	str=rcl1.getRacer(1,2);

	int ii=rcl.Compare(&rcl1);
	udiag="Несовпадение векторов списков спортсменов";
	Check(ii,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::LoadFromCSV(){
  // void LoadFromExcel(AnsiString filename)
	rcl.LoadFromCSV("C:\\test\\RPT_Start_910.csv");
	rcl.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	str=rcl.getRacer(1,2);
	str=rcl1.getRacer(1,1);
	str=rcl1.getRacer(1,2);
	rcl1.setRacer(1,2,"Пивоваров Алексей");
	rcl1.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.setRacer(1,2,str.c_str());
	str=rcl1.getRacer(1,2);
	int ii=rcl.Compare(&rcl1);
	udiag="Несовпадение векторов списков спортсменов после загрузки из CSV";
	Check(ii,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::saveXML(){
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910.xml");
	auto i=rcl.Compare(&rcl1);
	udiag="Несовпадение векторов списков спортсменов после сохранения XML";
	Check(i,udiag);
}
//______________________________________________________________________________
void __fastcall TTestRaceList::loadXML(){
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910.xml");
	auto i=rcl.Compare(&rcl1);
	udiag="Несовпадение векторов списков спортсменов после загрузки XML";
	Check(i,udiag);
}
//______________________________________________________________________________
static void registerTests(){
  Testframework::RegisterTest(TTestRaceList::Suite());
  Testframework::RegisterTest(TTestRaceResults::Suite());
}
#pragma startup registerTests 33
