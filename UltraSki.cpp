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
#include <Vcl.Imaging.GIFImg.hpp>
TfUltraSki *fUltraSki;
extern TIdTCPClient *LiveFIS;
AnsiString toLatin(AnsiString &srussian);
//extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
Races *rcs;

__fastcall TfUltraSki::TfUltraSki(TComponent* Owner): TForm(Owner){
	rcs=new Races;
    TGIFImage *GIF = dynamic_cast<TGIFImage*>(Image2->Picture->Graphic);

if (GIF != NULL)
	GIF->Animate = true;

/*
AnsiString astr;
Races *rcs=NULL;

	if (rcs==NULL) {
		rcs=new Races;
	}
	rcs->showRaces();
	rcs->showInfo();
*/
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
	if( LiveFIS!=NULL && LiveFIS->Connected() ){
		String str;
		str=rcs->getCodex();
		str="Нажмите для публикации на странице живого хронометража FIS для гонки с кодексом "+str;
		pINFO->Caption=str;
		pINFO->Visible=true;
		emessage2FIS->Visible=true;
	}

	else{
		pINFO->Visible=false;
		emessage2FIS->Visible=false;
	}

	fUltraSki->Caption="ULTRASKI "+Now().FormatString("dd.mm.yyyy hh:mm:ss");
}//end of proc
//---------------------------------------------------------------------------
/*struct RaceInfo{
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
 */
//______________________________________________________________________________
//_______________________________________________________________________________

void __fastcall TfUltraSki::Image2Click(TObject *Sender){
	rcs->showRaces();
	int iN=rcs->getNumberOfRaces();
	if(iN>0){
		iN=rcs->getCurrRace();
		rcs->showInfo();
		rcs->setCurrRace(iN);
		iN=rcs->getCurrRace();
		rcs->setCurRacersColor();
		iN=rcs->getCurrRace();
		rcs->SetFocus();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfUltraSki::pINFOClick(TObject *Sender){
	if( LiveFIS->Connected() ){
	String Str;
	Str=rcs->getCodex();
	pINFO->Caption="Нажмите для публикации на странице живого хронометража FIS для гонки с кодексом "+Str;
		Str=rcs->LiveFISRacemessage(emessage2FIS->Text);

		LiveFIS->IOHandler->WriteLn(Str);
		String Str1="";
		Str1= LiveFIS->IOHandler->ReadLn();
	}

}
//---------------------------------------------------------------------------


