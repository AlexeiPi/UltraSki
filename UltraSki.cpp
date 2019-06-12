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
#include "TimingDevice.h"


TfUltraSki *fUltraSki;
extern TIdTCPClient *LiveFIS;
AnsiString toLatin(AnsiString &srussian);
//extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
Races *rcs;
TimeKeeping *tk;

__fastcall TfUltraSki::TfUltraSki(TComponent* Owner): TForm(Owner){
	rcs=new Races;
	tk=new TimeKeeping;
	TGIFImage *GIF = dynamic_cast<TGIFImage*>(Image2->Picture->Graphic);
	Application->OnException = MyException;

   int horizontal = 0;
   int vertical = 0;
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;


	Left=0;

	Top=vertical-Height;

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
void __fastcall TfUltraSki::MyException( TObject *Sender, Exception *E )
{
 if( String( E->ClassName() ) == "ESocketError" )
   {
    ShowMessage("Ошибка - ESocketError");
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::Timer1Timer(TObject *Sender){
//auto поw = std::chrono::system_clock::поw();
int iconnection=0;
	if( LiveFIS!=NULL ){
		try{
			if(LiveFIS->Connected()){
				String str;
				str=rcs->getCodex();
				str="Нажмите для публикации на странице живого хронометража FIS для гонки с кодексом "+str;
				pINFO->Caption=str;
				pINFO->Visible=true;
				emessage2FIS->Visible=true;
				iconnection=1;
			}

		}
		catch(...){
//			if(ex==ECONNRESET)
///				ShowMessage(e.Message);
			if( LiveFIS!=NULL ){
				LiveFIS->Disconnect();
				delete LiveFIS;
				LiveFIS=0;

			}
		}
	}
	if(!iconnection){
		if(pINFO->Visible){
			pINFO->Visible=false;
			emessage2FIS->Visible=false;
		}
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

		rcs->setCategory("FIS");
		rcs->setNation("RUS");
		rcs->setPlace("Elizovo");
		AnsiString astr;
		astr=rcs->getEventname();
		astr=toLatin(astr);
		if (astr.Length()==0) {
			astr=" ";
		}
		rcs->setEventname(astr);
		rcs->setSlope("Slope");
//		rcs->setRacetime(TTime("11:47"));
		AnsiString ahour= rcs->getRaceth(),amin= rcs->getRacetm();
		//rcs->setRacetime(TTime("09:05:17"));
		ahour= rcs->getRaceth(),amin= rcs->getRacetm();


		if( LiveFIS->Connected() ){

			String Str=rcs->LiveFISRaceinfo(L"1");//run 1

			LiveFIS->IOHandler->WriteLn(Str);
			String Str1="";
			Str1= LiveFIS->IOHandler->ReadLn();

		}
		if( LiveFIS->Connected() ){

			String Str=rcs->LiveFISRacemeteo(L"1");//run 1

			LiveFIS->IOHandler->WriteLn(Str);
			String Str1="";
			Str1= LiveFIS->IOHandler->ReadLn();

		}

	}
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::Image1Click(TObject *Sender){
AnsiString astr;
	astr.sprintf("https://vimeo.com/offsideexplained/videos/");
    astr.sprintf("http://yandex.ru");
		try {
			astr = IdHTTP1->Get(astr);//////get CHANNELs page
		}
		catch(const EIdOSSLCouldNotLoadSSLLibrary &){
			Memo1->Lines->Add("SSL Error:");
			Memo1->SelStart = Memo1->GetTextLen();
			Memo1->SelText = WhichFailedToLoad();
		}
}
//---------------------------------------------------------------------------
AnsiString __fastcall _getTimeHHSSZZZ(void){
int ih,im,is,ims;
AnsiString astr;
	SYSTEMTIME sys;
	FILETIME lsys;
	GetSystemTime(&sys);
	ih=sys.wHour+3;
	im=sys.wMinute;
	is=sys.wSecond;
	ims=sys.wMilliseconds;
	astr.sprintf("%02d:%02d:%02d.%03d",ih,im,is,ims);
	return astr;
}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::imTimeMachineClick(TObject *Sender){

	Memo1->Lines->Add(_getTimeHHSSZZZ());
	tk->showTimeKeeping();
	tk->SetLeftTop(rcs->GetLeftInfo(),rcs->GetBottomInfo());


	int iN=tk->getPulsesN();
	if(iN>0){
/*
		iN=rcs->getCurrRace();
		rcs->showInfo();
		rcs->setCurrRace(iN);
		iN=rcs->getCurrRace();
		rcs->setCurRacersColor();
		iN=rcs->getCurrRace();
		rcs->SetFocus();
*/
	}

}
//---------------------------------------------------------------------------

