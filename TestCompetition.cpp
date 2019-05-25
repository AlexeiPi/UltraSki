#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include "TestCompetition.h"

//-------------------------------------------------------------------------------
Race r;
RaceResults rrcl,rrcl1;
RaceList rcl,rcl1;
extern String udiag;
String str;
TIdTCPClient *LiveFIS;

//-------------------------------------------------------------------------------
class TTestRace : public TTestCase
{
public:
  __fastcall virtual TTestRace(System::String name) : TTestCase(name) {}
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
/*  void __fastcall LoadFromCSV();
  void __fastcall saveXML();
  void __fastcall loadXML();
*/
	void __fastcall setgetRaceData();
//________________________________

	void __fastcall LiveFISRaceclear();
    void __fastcall LiveFISRacemeteo();
	void __fastcall LiveFISRaceinfo();
	void __fastcall LiveFISRaceactiverun();
	void __fastcall LiveFISRacemessage();
	void __fastcall LiveFISRacestartLIST();
};
//______________________________________________________________________________
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
void __fastcall TTestRace::SetUp(){
	if (LiveFIS!=NULL){
		if(LiveFIS->Connected())
			LiveFIS->Disconnect();
		delete LiveFIS;
		LiveFIS=NULL;
	}
	if (LiveFIS==NULL) {
		LiveFIS=new TIdTCPClient;
		LiveFIS->Name="LiveFIS";
		LiveFIS->Port=1550;
		LiveFIS->Host="live.fisski.com";
		LiveFIS->Connect();
	}

}
void __fastcall TTestRace::TearDown(){}
//_____________________________________________________________________________
//_____________________________________________________________________________
void __fastcall TTestRace::LiveFISRaceclear(){
String Str,Str1;
int  iCodex=9872;
	r.setCodex(iCodex);
	r.setLiveFISpassword("08101957");

	if( LiveFIS->Connected() ){
		Str=r.LiveFISRaceclear();
		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();
	}
	udiag="Несовпадение кодексов гонок";
	Check(true,udiag);
}
//------------------------------------------------------------------------------
void __fastcall TTestRace::LiveFISRacemeteo(){
String Str,Str1;
int  iCodex=9872;
	r.setCodex(iCodex);
	r.setLiveFISpassword("08101957");
	Str=r.LiveFISRacemeteo("1");


	LiveFIS->IOHandler->WriteLn(Str);
	Str1="";
	Str1= LiveFIS->IOHandler->ReadLn();
	udiag="Несовпадение метео";
	Check(true,udiag);
}
//------------------------------------------------------------------------------
void __fastcall TTestRace::LiveFISRaceinfo(){
int  iCodex=9872;
String Str,Str1;
String  sDiscipline="DH";
String  sCategory="UNI";
	r.setCodex(iCodex);
	r.setDiscipline(sDiscipline);
	r.setCategory(sCategory);
	r.setLiveFISpassword("08101957");
	r.setGender("L");
	r.setNation("RUS");
	r.setPlace("Elizovo");
	r.setEventname("Eventname");
	r.setSlope("Slope");
	r.setRacedate(TDate("23.05.2019"));
	Str=r.getRaceyyyy();
	Str=r.getRacemm();
	Str=r.getRacedd();



	if( LiveFIS->Connected() ){

		Str=r.LiveFISRaceinfo(L"1");

		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();

/*		Str=r.LiveFISRaceactiverun("1");
		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();
*/
	}
	udiag="Несовпадение кодексов гонок";
	Check(true,udiag);
}
//------------------------------------------------------------------------------
void __fastcall TTestRace::LiveFISRaceactiverun(){
String Str,Str1;
int  iCodex=9872;
	r.setCodex(iCodex);
	r.setLiveFISpassword("08101957");

	if( LiveFIS->Connected() ){
		Str=r.LiveFISRaceactiverun("1");
		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();
	}
	udiag="Несовпадение кодексов гонок";
	Check(true,udiag);
}
//------------------------------------------------------------------------------
void __fastcall TTestRace::LiveFISRacemessage(){
String Str,Str1,strTIME;
int  iCodex=9872;
	r.setCodex(iCodex);
	r.setLiveFISpassword("08101957");
	DateTimeToString(strTIME, "h:mm:ss", Now());

	if( LiveFIS->Connected() ){
		Str=r.LiveFISRacemessage("new message "+strTIME);
		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();
	}
	udiag="Несовпадение кодексов гонок";
	Check(true,udiag);
}
//------------------------------------------------------------------------------
void __fastcall TTestRace::LiveFISRacestartLIST(){
String Str,Str1,strTIME;
int  iCodex=9872;
	rcl.setCodex(iCodex);
	rcl.setLiveFISpassword("08101957");
	DateTimeToString(strTIME, "h:mm:ss", Now());

	if( LiveFIS->Connected() ){
		Str=rcl.LiveFISRacestartLIST(1,"C:\\test\\RPT_Start_911");

		LiveFIS->IOHandler->WriteLn(Str);
		Str1="";
		////Str1= LiveFIS->IOHandler->ReadLn();
	}
	udiag="Несовпадение списков гонок";
	Check(true,udiag);
}


//------------------------------------------------------------------------------
void __fastcall TTestRace::setgetRaceData(){
int  iCodex=9872,iCodex1;
String  sNation="RUS",sNation1;
String  sDiscipline="Moscow Cup",sDiscipline1;
String  sCategory="Moscow Cup",sCategory1;
String  sPlace="Moscow",sPlace1;
String  sType="Moscow Cup",sType1;
String  sEventname="Moscow Cup",sEventname1;

	r.setCodex(iCodex);
	iCodex1=r.getCodex();

	r.setNation(sNation);
	sNation1=r.getNation();

	r.setDiscipline(sDiscipline);
	sDiscipline1=r.getDiscipline();

	r.setCategory(sCategory);
	sCategory1=r.getCategory();

	r.setPlace(sPlace);
	sPlace1=r.getPlace();

	r.setType(sType);
	sType1=r.getType();

	r.setEventname(sEventname);
	sEventname1=r.getEventname();

	udiag="Несовпадение кодексов гонок";
	Check(iCodex==iCodex1,udiag);
}
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
String Str,Str1,Str2,Str3;
	rcl.LoadFromCSV("C:\\test\\RPT_Start_910.csv");
	rcl.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.loadXML("C:\\test\\RPT_Start_910_1.xml");
	Str=rcl.getRacer(1,2);
	Str1=rcl1.getRacer(1,1);
	Str2=rcl1.getRacer(1,2);

	for (int i = 1; i < 10; i++) {
		Str3=rcl.getRacer(i,8);
		Str2=rcl1.getRacer(i,8);

	}


	rcl1.setRacer(1,2,"Пивоваров Алексей");
	rcl1.saveXML("C:\\test\\RPT_Start_910_1.xml");
	rcl1.setRacer(1,2,Str);
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
	Testframework::RegisterTest(TTestRace::Suite());
	Testframework::RegisterTest(TTestRaceList::Suite());
	Testframework::RegisterTest(TTestRaceResults::Suite());
}
#pragma startup registerTests 33
