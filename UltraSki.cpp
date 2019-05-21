//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UltraSki.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Racer.h"
#include "Competition.h"
#include "RaceViews.h"
TfUltraSki *fUltraSki;
//extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
__fastcall TfUltraSki::TfUltraSki(TComponent* Owner)
	: TForm(Owner){
AnsiString astr;
/*	Person p1("Иван","Иванович","Иванов","Ivan","Ivanovich","Ivanov","08.10.1957");
	Racer *r1=new Racer;

	r1->setFIScode("123456");
	r1->setPerson(&p1);
	astr=r1->getFIScode();

///	Racer r1("123456","Иван","Иванович","Иванов","Ivan","Ivanovich","Ivanov","08.10.1957");

	astr=r1->getFIO(0)+" возраст "+r1->getAge();
	astr=r1->getFIO(1)+" age "+r1->getAge();
	astr=r1->getIOF(0)+" возраст "+r1->getAge();
	astr=r1->getFio(0)+" возраст "+r1->getAge();
	astr=r1->getioF(0)+" возраст "+r1->getAge();
	astr=r1->getIOF(1)+" age "+r1->getAge();
	astr=r1->getFio(1)+" age "+r1->getAge();
	astr=r1->getioF(1)+" age "+r1->getAge();

	RaceList rcl;
	rcl.LoadFromCSV("C:\\test\\RPT_Start_910.csv");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");

	RaceStartListView rsl;
	rsl.showView();
*/
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::Timer1Timer(TObject *Sender){
//auto поw = std::chrono::system_clock::поw();
	fUltraSki->Caption="ULTRASKI "+Now().FormatString("dd.mm.yyyy hh:mm:ss");
}//end of proc
//---------------------------------------------------------------------------


void __fastcall TfUltraSki::LiveFISStatus(TObject *ASender, const TIdStatus AStatus,
		  const UnicodeString AStatusText)
{
int i=0;
}
//---------------------------------------------------------------------------

void __fastcall TfUltraSki::LiveFISWorkBegin(TObject *ASender, TWorkMode AWorkMode,
		  __int64 AWorkCountMax)
{
int i=0;

}
//---------------------------------------------------------------------------
struct RaceInfo{
	String sCODEX;
	String sPASSWORD;
	String sSEQUENCE;
	String sEVENTname;
	String sEVENTslopeName;
	String sDISCIPLINE;
	String sGENDER;
	String sCATEGORY;
	String sRUNNO;
	String sPLACE;
	String sY,sM,sD;
	String sHH,sMM;
	String sINTER;
} raceinfo;
//______________________________________________________________________________
String __fastcall LiveFISRaceInfo(RaceInfo *ri){

String str,strTIME;
	String sCODEX=ri->sCODEX;
	String sPASSWORD=ri->sPASSWORD;
	String sSEQUENCE=ri->sSEQUENCE;
	DateTimeToString(strTIME, "hh:mm:ss", Now());
	String sEVENTname=ri->sEVENTname;
	String sEVENTslopeName=ri->sEVENTslopeName;
	String sDISCIPLINE=ri->sDISCIPLINE;
	String sGENDER=ri->sGENDER;
	String sCATEGORY=ri->sCATEGORY;
	String sRUNNO=ri->sRUNNO;
	String sPLACE=ri->sPLACE;
	String sY=ri->sY,sM=ri->sM,sD=ri->sD;
	String sHH=ri->sHH,sMM=ri->sMM;
	String sINTER=ri->sINTER;
String sHeader="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
#if 0
String sLivetiming="<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+strTIME+"\">";
#else
String sLivetiming="<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+strTIME+"\">";
#endif
String sRaceinfo="<raceinfo><event>"+sEVENTname+"</event>";
String sName="<name>"+sEVENTslopeName+"</name><slope />";
////String sSlope="<slope>"+sEVENTslopeName+"</slope>";
String sDiscipline="<discipline>"+sDISCIPLINE+"</discipline>";
String sGender="<gender>"+sGENDER+"</gender>";
String sCategory="<category>"+sCATEGORY+"</category>";
String sPlace="<place>"+sPLACE+"</place>";
String sTemperature="<tempunit>C</tempunit><longunit>m</longunit><speedunit>kmh</speedunit>";
String SRunno="<run no=\""+sRUNNO+"\"><discipline>"+sDISCIPLINE+"</discipline><start /><finish /><height /><length /><gates /><turninggates />";
String sYMD="<year>"+sY+"</year><month>"+sM+"</month><day>"+sD+"</day>";
String sHHMM="<hour>"+sHH+"</hour><minute>"+sMM+"</minute>";
String SRacedef="<racedef><inter i=\""+sINTER+"\" />";
String SEnding="</racedef></run></raceinfo></livetiming>";

str=sHeader+sLivetiming+sRaceinfo+sName+sDiscipline+sGender+sCategory+sPlace+sTemperature+SRunno+sYMD+sHHMM+SRacedef+SEnding;
return str;
}
//_______________________________________________________________________________
void __fastcall TfUltraSki::lRaceInfoClick(TObject *Sender){
String str,strtime;
DateTimeToString(strtime, "hh:mm:ss", Now());

	raceinfo.sCODEX="9872";
	raceinfo.sPASSWORD="08101957";
	raceinfo.sSEQUENCE="00001";
	raceinfo.sEVENTname="FORERUNNERS";
	raceinfo.sEVENTslopeName="SLOPE name";
	raceinfo.sDISCIPLINE="SL";
	raceinfo.sGENDER="L";
	raceinfo.sCATEGORY="UNI";
	raceinfo.sRUNNO="1";
	raceinfo.sPLACE="Juzhno-Sakhalinsk";
	raceinfo.sY="2019";raceinfo.sM="5";raceinfo.sD="22";
	raceinfo.sHH="19",raceinfo.sMM="6";
	raceinfo.sINTER="1";


str=LiveFISRaceInfo(&raceinfo);

/*		if( !LiveFIS->Connected() )
			LiveFIS->Connect();
		if( LiveFIS->Connected() ){
		}
*/
			LiveFIS->IOHandler->WriteLn(str);
			str="";
////			str= LiveFIS->IOHandler->ReadLn();

			lRaceInfoResponse->Caption=str+" "+strtime;
}
//---------------------------------------------------------------------------
String FISstartLIST(String sCODEX,String sPASSWORD,String sSEQUENCE,string filename){

String str,strtime;
RaceList rcl;
	rcl.LoadFromCSV(filename);
	rcl.setCODEX(sCODEX);
	int rSize=rcl.getRacersN();

	AnsiString work="";
	std::string fa,im,fc,fio,yob;
	string  TOTAL,item,i1,i2,i3,i4,i5,i6,i7,i8;
	DateTimeToString(strtime, "hh:mm:ss", Now());
	 i1="<?xml version=\"1.0\" encoding=\"UTF-8\"?><livetiming codex=\"";
	 std::string i22(AnsiString(sCODEX).c_str());
	 i3="\" passwd=\"";
	 std::string i23(AnsiString(sPASSWORD).c_str());
	 #if 0
	 i4="\" sequence=\"";
	 std::string i24(AnsiString(sSEQUENCE).c_str());
	 #else
	 #endif
	 i5="\" timestamp=\"";
	 std::string i25(AnsiString(strtime).c_str());
	 i6="\"><startlist runno=\"1\">";

	 #if 0
	TOTAL=i1+i22+i3+i23+i4+i24+i5+i25+i6;//sCODEX;//+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">";
	 #else
	TOTAL=i1+i22+i3+i23+i5+i25+i6;//sCODEX;//+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">";
	 #endif
	for (auto iirs = 1;iirs<rSize;++iirs){
		fc=rcl.getRacer(iirs,1);
		std::string str1 =rcl.getRacer(iirs,8);
		std::size_t pos = str1.find(" ");
		 std::string str2 = str1.substr (0,pos);
		 std::string str3 = str1.substr (pos+1);
		 i1="<racer order=\"";
		 i2= std::to_string(iirs);
		 i3="\"><bib>";
		 i4="</bib><lastname>";
		 i5=str2.c_str();
		 i6="</lastname><firstname>";
		 i7=str3.c_str();
		 i8="</firstname><nat>ITA</nat><fiscode>"+fc+"</fiscode></racer>";
///		str=+work+"\"><bib>"+work+"</bib><lastname>" + str2.c_str() + "</lastname><firstname>" + str3.c_str() + "</firstname><nat>RUS</nat><fiscode"+fc+"</fiscode></racer>";
		im=im;
		item=i1+i2+i3+i2+i4+i5+i6+i7+i8;
		TOTAL+=item;
	}
	i1="</startlist></livetiming>";
	TOTAL+=i1;


/*
DateTimeToString(strtime, "hh:mm:ss", Now());
	DateTimeToString(strtime, "hh:mm:ss", Now());
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">\
<message><text>"+strtime+"</text></message></livetiming>";
*/
	str=TOTAL.c_str();
return str;
}
//---------------------------------------------------------------------------
String __fastcall LiveFISclear(String sCODEX,String sPASSWORD,String sSEQUENCE){
String str,strtime;

			DateTimeToString(strtime, "hh:mm:ss", Now());
#if 0
			str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\"9872\" passwd=\"08101957\" sequence=\"00001\" timestamp=\""+strtime+"\">\
<command><clear /></command></livetiming>";
#else
			str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\"9872\" passwd=\"08101957\" timestamp=\""+strtime+"\">\
<command><clear /></command></livetiming>";

#endif
	return str;
}

void __fastcall TfUltraSki::lClearClick(TObject *Sender){
/*
		if( !LiveFIS->Connected() )
			LiveFIS->Connect();
		if( LiveFIS->Connected() ){
		}
*/
String str,strtime;
 /*
	raceinfo.sCODEX="9872";
	raceinfo.sPASSWORD="08101957";
	raceinfo.sSEQUENCE="00001";
	raceinfo.sEVENTname="111222";
	raceinfo.sEVENTslopeName="";
	raceinfo.sDISCIPLINE="SL";
	raceinfo.sGENDER="L";
	raceinfo.sCATEGORY="UNI";
	raceinfo.sRUNNO="1";
	raceinfo.sPLACE="Moscow";
	raceinfo.sY="2019";raceinfo.sM="05";raceinfo.sD="22";
	raceinfo.sHH="19",raceinfo.sMM="06";
	raceinfo.sINTER="1";
	str=LiveFISRaceInfo(&raceinfo);
	LiveFIS->IOHandler->WriteLn(str);
	str="";
	str= LiveFIS->IOHandler->ReadLn();

*/

	DateTimeToString(strtime, "hh:mm:ss", Now());
	str=LiveFISclear("9872","08101957","00001");
	LiveFIS->IOHandler->WriteLn(str);
	str="";
///	str= LiveFIS->IOHandler->ReadLn();

	lClearResponse->Caption=str+" "+strtime;



}
//---------------------------------------------------------------------------
String __fastcall LiveFISmessage(String sCODEX="9872",String sPASSWORD="08101957",String sSEQUENCE="00001"){
String str,strtime;
	DateTimeToString(strtime, "hh:mm:ss", Now());
   #if 0
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">\
<message><text>"+strtime+"</text></message></livetiming>";
#else
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+strtime+"\">\
<message><text>"+strtime+"</text></message></livetiming>";
#endif
return str;
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::lMessageClick(TObject *Sender){
String str,strtime;
	str=LiveFISmessage("9872","08101957","00001");
	LiveFIS->IOHandler->WriteLn(str);
	str="";
////	str= LiveFIS->IOHandler->ReadLn();

	str=FISstartLIST("9872","08101957","00001","C:\\test\\RPT_Start_910.csv");
	LiveFIS->IOHandler->WriteLn(str);
	str="";
////	str= LiveFIS->IOHandler->ReadLn();
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::lActiveRunClick(TObject *Sender){
String sCODEX="9872";
String sPASSWORD="08101957";
String sRUN="1";

String str,strtime;
DateTimeToString(strtime, "hh:mm:ss", Now());

#if 0
str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\"00002\" timestamp=\""+strtime+"\">\
<command><activerun no=\""+sRUN+"\" /></command></livetiming>";
#else
str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+strtime+"\">\
<command><activerun no=\""+sRUN+"\" /></command></livetiming>";
#endif
	LiveFIS->IOHandler->WriteLn(str);
	str="";
 ///	str= LiveFIS->IOHandler->ReadLn();
 	lActiveRunResponse->Caption=str+" "+strtime;
}
//---------------------------------------------------------------------------

void __fastcall TfUltraSki::FormCreate(TObject *Sender)
{
		if( !LiveFIS->Connected() )
			LiveFIS->Connect();
}
//---------------------------------------------------------------------------

void __fastcall TfUltraSki::lMessage1Click(TObject *Sender)
{
String str;

	str=FISstartLIST("9872","08101957","00001","C:\\test\\RPT_Start_911.csv");
	LiveFIS->IOHandler->WriteLn(str);
	str="";
 ////	str= LiveFIS->IOHandler->ReadLn();
	lMessage1Response->Caption=str;
}
//---------------------------------------------------------------------------


void __fastcall TfUltraSki::lHumidityClick(TObject *Sender)
{
String sCODEX="9872";
String sPASSWORD="08101957";
String sRUN="1";

String str,strtime;
DateTimeToString(strtime, "hh:mm:ss", Now());
#if 0
str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\"00002\" timestamp=\""+strtime+"\">\
<meteo run=\"1\"><weather>sun</weather><temperature>22.0</temperature><wind>no</wind><snowtemperature>6.0</snowtemperature><snowcondition>sft</snowcondition><humidity>5</humidity></meteo></livetiming>";
#else
str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+strtime+"\">\
<meteo run=\"1\"><weather>sun</weather><temperature>22.0</temperature><wind>no</wind><snowtemperature>6.0</snowtemperature><snowcondition>sft</snowcondition><humidity>5</humidity></meteo></livetiming>";
#endif

	LiveFIS->IOHandler->WriteLn(str);
	str="";
 ////	str= LiveFIS->IOHandler->ReadLn();
	lHumidityResponse->Caption=str+" "+strtime;

}
//---------------------------------------------------------------------------

