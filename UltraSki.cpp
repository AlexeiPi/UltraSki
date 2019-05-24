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
//_______________________________________________________________________________
String FISstartLIST(String sCODEX,String sPASSWORD,String sRun,string filename){

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
	str=FISstartLIST("9872","08101957","2","C:\\test\\RPT_Start_911.csv");
	LiveFIS->IOHandler->WriteLn(str);
	str="";
 ////	str= LiveFIS->IOHandler->ReadLn();
	lMessage1Response->Caption=str;
}
//---------------------------------------------------------------------------

