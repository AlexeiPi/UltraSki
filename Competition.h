//---------------------------------------------------------------------------
#ifndef CompetitionH
#define CompetitionH
#include "UltraSki.h"
#include <vector>
#include <vcl.h>

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include <Xml.XMLDoc.hpp>
#include "IniFiles.hpp"

TIniFile *IniUltraAlpSki;//ini file



using namespace std;
class RaceList;
class RaceResults;
enum {SNHeight=18,SNWidth=30,CodexWidth=90};
//---------------------------------------------------------------------------
class Races{
	private:
		int number_Of_competitions;
//=============================================================================
		struct _viewRL{
			TLabel *SN;
			TLabel *RCodex;
			_viewRL(TPanel*p,int i,Races *r,TLabel *lbl){//constructor
				AnsiString str;
				SN=new TLabel(p);
				SN->Name="SN"+AnsiString(i);
				SN->Parent = p;
				SN->AutoSize=false;
				SN->Alignment=taCenter;
				SN->Transparent=false;
				SN->Tag=i;
				SN->Color=clWhite;
				SN->Font->Size=10;
				SN->Width=SNWidth;
				SN->Height=SNHeight;
				SN->Top=i*SNHeight;
				SN->Left=1;
				str=i+1;
				SN->Caption=str;
				SN->OnMouseDown = lbl->OnMouseDown;
				SN->OnDblClick = lbl->OnDblClick;

				RCodex=new TLabel(p);
				RCodex->Name="FC"+AnsiString(i);
				RCodex->Parent = p;
				RCodex->AutoSize=false;
				RCodex->Transparent=false;
				RCodex->Tag=SN->Tag;
				RCodex->Color=SN->Color;
				RCodex->Font->Size=SN->Font->Size;
				RCodex->Width=CodexWidth;
				RCodex->Height=SNHeight;
				RCodex->Top=SN->Top;
				RCodex->Left=SN->Left+SN->Width;
				RCodex->Alignment=taLeftJustify;
				str=r->getRace(i).Codex;
				RCodex->Caption=str;
				RCodex->OnMouseDown = SN->OnMouseDown;
				RCodex->OnDblClick = SN->OnDblClick;

			}
		};
		vector < _viewRL > viewSL;
		TForm *pRaceViews,*pRaceInfo,*pRaceStartList;
		TEdit *eCompetition;
///        String sLastRegistered;


		TPanel *panel1,*panel2,*panel3;
		TLabel *lbl;
		TLabel *lFISCodex,*lDate,*lSLiportN,*lSLiport,*lID,*lInfoName;
		TEdit *eFISCodex,*eDate,*eInfoName;
		TOpenDialog *StartListFileDialog;
        TRadioButton *rb1,*rb2,*rb3,*rb4,*rb5,*rb6,*rb7;


		int icurrRace=1,ilastcurrRace=-1;
		int iTopLine=1,iBottomLine;
		int iActiveLine=1;

//=============================================================================
		struct RacePack{
			String Codex;
			String path;
		};
		vector < RacePack > RacesList;
		String DefaultPath;
		String ApplicationPath;
//-----------------------------------------------------------------------------
	public:
		Races(){
			String str="";
				DefaultPath=ExtractFilePath(Application->ExeName);
				pRaceViews=new TForm(Application);
				pRaceViews->Caption="";
				pRaceViews->KeyPreview=true;
				pRaceInfo=new TForm(Application);
				pRaceInfo->Caption="";
				pRaceInfo->KeyPreview=true;
				pRaceStartList=new TForm(Application);
				pRaceStartList->Caption="";
				pRaceStartList->KeyPreview=true;

				StartListFileDialog=new TOpenDialog(pRaceStartList);

				eCompetition=NULL;
				lbl=NULL;
				lInfoName=NULL;lID=NULL;lSLiport=NULL;lSLiportN=NULL;
				panel3=NULL;panel2=NULL;panel1=NULL;
				ApplicationPath=Application->ExeName;
				ApplicationPath=StringReplace(ApplicationPath,".\\","",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
				ApplicationPath=ChangeFileExt( ApplicationPath, ".INI" );
		};
		~Races(){delete pRaceViews;};
		void LoadFromPath(String path);
		int getRacesN(){return RacesList.size();};
//------------------------------------------------------------------------------
		void setDefaultPath(String path){DefaultPath=path;};
		String getDefaultPath(void){return DefaultPath;};

		RacePack getRace(int i){return RacesList[i];};

		void __fastcall showView();
		void __fastcall showInfo();
		void __fastcall showStartList();

		void __fastcall Locations(TForm* form);
		void __fastcall LocationsInfo(TForm* form);
		void __fastcall LocationsStartList(TForm* form);

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_key_down_startlist(TObject *Sender, WORD &Key, TShiftState Shift);


		void __fastcall form_resize(TObject *Sender);
		void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall radio_click(TObject *Sender);
		void __fastcall mouse_DblClick(TObject *Sender);

		int __fastcall checkLines(void);
		void __fastcall setRacersColor(_viewRL vsl);
		void __fastcall FillRaceDescription(void);
		void __fastcall SaveInfo2INI(void);
};
//______________________________________________________________________________
#if 1
class Race;
class Race{
	private:
		String LiveFISpassword;
		String Gender;//[M]en,[L]adies,[A] Mixed
		//Season-Codex-Nation-Discipline-Category-Type-Training
		//Speedcodex-Eventname-Place-Racedate
		//Tempunit-Longunit-Speedunit-Windunit
		int Season;// 2012 for Juni 2011 - May 2012 integer
		int Codex;
		String Nation;
		String Discipline;
		String Category;
		String Type;   //Type of content Startlist Partial Unofficial Official
		String Training;
		int Speedcodex;
		String Eventname;
		String Place;
		String Slope;
		TDate Racedate;
		String Tempunit;
		String Longunit;
		String Speedunit;
		String Windunit;
		String Usedfislist;
		float Appliedpenalty;
		int Fvalue;
		String Timingby;
		String Dataprocessingby;
		String Softwarecompany;
		String Softwarename;
		String Softwareversion;
		struct Jury{
			String Lastname;
			String Firstname;
			String Nation;
			String Email;
			String Phonenbr;
		};
		struct Course{
			String Name;
			String Homologation;
			int Length;
			int Gates;
			int Turninggates;
			int Startlelev;
			int Finishelev;
		};
		struct Coursesetter{
			String Lastname;
			String Firstname;
			String Nation;
		};
		struct Forerunner{
			String Lastname;
			String Firstname;
			String Nation;
		};
		String IntermediateDistance;
		struct Weather{
			String Time;
			String Place;
			String Weather;
			String Snow;
			float Temperatureair;
			float Temperaturesnow;
			int Humiditystart;
			float Windspeed;
		};
//		struct AL_ranked{		Rank 		Order 		Bib 		};
		struct Competitor{
			String Fiscode;
			String Lastname;
			String Firstname;
			String Gender;//M L
			String Nation;
			int Yearofbirth;
			String Clubname;
		};
		struct AL_result{
			String Timerun1;//MM:SS:ZZ
			String Timerun2;//MM:SS:ZZ
			String Timerun3;//MM:SS:ZZ
			String Totaltime;//MM:SS:ZZ
			String Diff;//MM:SS:ZZ
			float Racepoints;
			String Level;//	final smallfinal semifinal quarterfinaleightfinal qualification sixteenfinal thirtytwofinal sixtyfourfinal
		};
/*
Order number of intermediate point
1-98 	= intermediate points
99 		= Finish
*/
		struct Intermediate{
			String Time;
			String Diff;
			int Rank;
			float Speed;
			String Sectortime;
			String Sectordiff;
			String Sectorrank;
		};
		struct AL_notranked{
			int Run;
			String Bib;
			Competitor competitor;
			int Gate;
			AL_result al_result;
//			AL_resultdetail al_resultdetail;
			String Reason;

		};
	public:
		Race():Codex(0){};
		~Race(){};

		void setLiveFISpassword(String liveFISpassword){LiveFISpassword=liveFISpassword;};
		String getLiveFISpassword(){return LiveFISpassword;};

		void setCodex(int icodex){Codex=icodex;};
		int getCodex(){return Codex;};
		void setNation(String nation){Nation=nation;};
		String getNation(){return Nation;};
		void setDiscipline(String discipline){Discipline=discipline;};
		String getDiscipline(){return Discipline;};

		void setGender(String gender){Gender=gender;};
		String getGender(void){return Gender;};
		void setCategory(String category){Category=category;};
		String getCategory(){return Category;};
		void setType(String ttype){Type=ttype;};   //Type of content Startlist Partial Unofficial Official
		String getType(){return Type;};   //Type of content Startlist Partial Unofficial Official
		void setEventname(String eventname){Eventname=eventname;};
		String getEventname(){return Eventname;};
		void setPlace(String place){Place=place;};
		String getPlace(){return Place;};

		void setSlope(String slope){Slope=slope;};
		String getSlope(){return Slope;};


		String getRaceyyyy(){String str;DateTimeToString(str, "yyyy", Racedate);return str;};
		String getRacemm(){String str;DateTimeToString(str, "m", Racedate);return str;};
		String getRacedd(){String str;DateTimeToString(str, "d", Racedate);return str;};
		void setRacedate(TDate racedate){Racedate=racedate;};

		void setTimingby(String timingby){Timingby=timingby;};
		String getTimingby(){return Timingby;};
		void setDataprocessingby(String dataprocessingby){Dataprocessingby=dataprocessingby;};
		String getDataprocessingby(){return Dataprocessingby;};

		void setSoftwarecompany(String softwarecompany){Softwarecompany=softwarecompany;};
		String getSoftwarecompany(){return Softwarecompany;};
		void setSoftwarename(String softwarename){Softwarename=softwarename;};
		String getSoftwarename(){return Softwarename;};
		void setSoftwareversion(String softwareversion){Softwareversion=softwareversion;};
		String getSoftwareversion(){return Softwareversion;};

//______LIVE FIS________________________________________________________________________
		String __fastcall LiveFISRaceclear(void);
		String __fastcall LiveFISRacemeteo(String srun);
		String __fastcall LiveFISRaceinfo(String srun);
		String __fastcall LiveFISRacemessage(String message);
		String __fastcall LiveFISRaceactiverun(String srun);


 };
#endif
//______________________________________________________________________________
class RaceList:public Race{
	private:
		vector <vector <String> > Racers;
///		String CODEX;//Codex
		RaceResults *Run1Results;
		RaceResults *Run2Results;
	public:
		RaceList(){};
		~RaceList(){};
		void LoadFromCSV(String filename);
		void saveXML(String filename);
		void loadXML(String filename);
		int getRacersN(){return Racers.size();};
		String getRacer(int i,int j){return Racers[i][j];};
		void setRacer(int i,int j,String sval){Racers[i][j]=sval;};
		bool Compare(RaceList *rl){return Racers==rl->Racers;};
//______LIVE FIS________________________________________________________________________
	   String __fastcall LiveFISRacestartLIST(int srun,String filename);
};
//______________________________________________________________________________
class RaceResults{
	private:
		vector <vector <String> > Results;
		RaceList *RL;
	public:
		RaceResults(){};
		~RaceResults(){};
		void saveXML(String filename);
		void loadXML(String filename){};
		String getResult(int i,int j){return Results[i][j];};
		void setResult(int i,int j,String sval){Results[i][j]=sval;};
		bool Compare(RaceResults *rl){return Results==rl->Results;};
};
//______________________________________________________________________________
#endif


//---------------------------------------------------------------------------

