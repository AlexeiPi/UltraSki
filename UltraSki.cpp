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
#include "System.Zip.hpp"

//------------------------------------------------------------------------------
void __fastcall UnZIP(AnsiString afiledir,AnsiString afilename);
//------------------------------------------------------------------------------
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
int idirs;
/*
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
*/

	if( FISftp->Connected() ) FISftp->Disconnect();
	FISftp->Host = "ftp.fis-ski.com";
	FISftp->Port = 21;
	FISftp->Password ="anonymous@example.com";
	FISftp->Username ="anonymous";
	FISftp->Passive = true;
	FISftp->AutoLogin = true;
	try	{
		FISftp->Connect();
	}
	catch(...){
		ShowMessage( "Сервер не отвечает" );
		if( FISftp->Connected() ) FISftp->Disconnect();
		return;
	}
   unsigned short iyear,imonth,iday;
   Now().DecodeDate(&iyear, &imonth, &iday);
   AnsiString ayear(iyear);

	FISftp->ChangeDir("/Software/Files/Competitors/");
	FISftp->List(NULL, "*.zip",false);
   idirs =  FISftp->DirectoryListing->Count;
   Memo1->Lines->Add("Competitors-----------");
   for(int j=0,i = 0; i < idirs; ++i){
		TIdFTPListItem *Item = FISftp->DirectoryListing->Items[i];
		astr=Item->FileName;
		if(astr.Pos(ayear))
			Memo1->Lines->Add(AnsiString(++j)+" "+astr);
	}

	TIdFTPListItems* Files = FISftp->DirectoryListing;
	idirs = Files->Count;
	FISftp->ChangeDir("/Software/Files/Fislist/");


	FISftp->List(NULL, "ALFP*F.zip",false);
///	FISftp->ExtListDir(NULL, "ALFP*F.zip");// bad try

	idirs=-1;
   idirs =  FISftp->DirectoryListing->Count;
   Memo1->Lines->Add("Fislist------------");

   int isize,i,ipos,ilargestid=0;
   TDateTime adate,youngest(NULL),bestdate;
   AnsiString id,ayoungestfilename="",largestid="",bestid;
   for(i = 0; i < idirs; ++i){
		TIdFTPListItem *Item = FISftp->DirectoryListing->Items[i];
////		adate=Item->ModifiedDate;    // bad try
		astr=Item->FileName;
		id=astr.SubString(5,astr.Length()-4);
		ipos=id.Pos("F.zip");
		if(ipos>0){
			id=id.SubString(1,ipos-1);
			if(TryStrToInt(id,ipos)){
				if(ilargestid<ipos){
					adate=FISftp->FileDate(astr,true);
					ilargestid=ipos;
					largestid=id;
					bestid=astr;
					bestdate=adate;
					Memo1->Lines->Add(AnsiString(i+1)+" "+astr+" "+DateToStr(adate));
				}
			}
		}
	}
	Memo1->Lines->Add("Loading the latest file ...");
	Memo1->Lines->Add(bestid+" "+DateToStr(bestdate));
	astr=rcs->getDefaultPath()+bestid;
	if(FileExists(astr)){
		Memo1->Lines->Add("No need for downloading!!!");
		Memo1->Lines->Add("Can be found as ");
		Memo1->Lines->Add(astr);
	}
	else{
		FISftp->Get(bestid, astr, True);
		///UnZIP(rcs->getDefaultPath(),bestid);
	}
	Memo1->Lines->Add("...Done!");

	UnZIP(rcs->getDefaultPath(),bestid);
/*
	FISftp->Get("ALFP1219F.zip", "d://ALFP1219F.zip", True);
	FISftp->Get("ALFP1919F.zip", "d://ALFP1919F.zip", True);
*/
	////  ftp://ftp.fis-ski.com/Software/Files/Calendar/
}
//---------------------------------------------------------------------------
AnsiString __fastcall _getTimeHHSSZZZ(void){
int ih,im,is,ims;
AnsiString astr;
	SYSTEMTIME sys;
	FILETIME lsys;
	GetSystemTime(&sys);
	ih=(sys.wHour+3)%24;
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
void __fastcall UnZIP(AnsiString afiledir,AnsiString afilename){
 TZipFile *zip=new TZipFile;
 AnsiString astr;
	zip->Open(afiledir+afilename,zmRead);
	astr=afilename.SubString(1,afilename.Pos(".zip")-1);
	astr=afiledir+astr+"\\";
	fUltraSki->Memo1->Lines->Add("Starting unzip to");
	fUltraSki->Memo1->Lines->Add(astr+" ...");

	zip->ExtractAll(astr);
	fUltraSki->Memo1->Lines->Add("...Done!");
	zip->Close();
	delete zip;
}
