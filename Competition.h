//---------------------------------------------------------------------------

#ifndef CompetitionH
#define CompetitionH
#include "UltraSki.h"
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

void __fastcall SetClipBoard(AnsiString aboard);
extern TIniFile *IniUltraAlpSki;//ini file

enum _COMPETITION_ENUMS_{SNHeight=18,SNWidth=30,CodexWidth=90};


using namespace std;
class Race;
class RaceList;
class RaceStartListView;
class RaceResults;

//---------------------------------------------------------------------------
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
		String Nation="RUS";
		String Discipline;
		String Category;
		String Type;   //Type of content Startlist Partial Unofficial Official
		String Training;
		int Speedcodex;//in Alpine Combine
		String Eventname;
		String Place;
		String Slope;
		TDate Racedate;
		TTime Racetime;
		String Tempunit="C";
		String Longunit="m";
		String Speedunit="kmh";
		String Windunit;
		String Usedfislist;
		float Appliedpenalty;
		int Fvalue;
		String Timingby;
		String Dataprocessingby;
		String Softwarecompany;
		String Softwarename="UltraSki";
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
			String Gender;//M L T
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
/* Order number of intermediate point 1-98	= intermediate points      99 = Finish */
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

		void setCodex(int icodex){
			Codex=icodex;
			SetClipBoard("http://live.fis-ski.com/lv-al"+AnsiString(icodex)+".htm#/startlist");
		};
		int getCodex(){
			return Codex;
		};
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
		String getRacemm(){String str;DateTimeToString(str, "M", Racedate);return str;};
		String getRacedd(){String str;DateTimeToString(str, "d", Racedate);return str;};
		String getRaceth(){String str;str=Racetime.FormatString(L"hh");;return str;};
		String getRacetm(){String str;
			str=Racetime.FormatString(L"nn");
			return str;
		};
		void setRacedate(TDate racedate){
			Racedate=racedate;};
		void setRacetime(TTime racetime){
			Racetime=racetime;};

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

