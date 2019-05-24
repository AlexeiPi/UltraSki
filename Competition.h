//---------------------------------------------------------------------------
#ifndef CompetitionH
#define CompetitionH
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
using namespace std;
class RaceList;
class RaceResults;

//---------------------------------------------------------------------------
#if 1
class Race;
class Race{
	private:
        string LiveFISpassword;
		string Gender;//[M]en,[L]adies,[A] Mixed
		//Season-Codex-Nation-Discipline-Category-Type-Training
		//Speedcodex-Eventname-Place-Racedate
		//Tempunit-Longunit-Speedunit-Windunit
		int Season;// 2012 for Juni 2011 - May 2012 integer
		int Codex;
		string Nation;
		string Discipline;
		string Category;
		string Type;   //Type of content Startlist Partial Unofficial Official
		string Training;
		int Speedcodex;
		string Eventname;
		string Place;
		string Slope;
		TDate Racedate;
		string Tempunit;
		string Longunit;
		string Speedunit;
		string Windunit;
		string Usedfislist;
		float Appliedpenalty;
		int Fvalue;
		string Timingby;
		string Dataprocessingby;
		string Softwarecompany;
		string Softwarename;
		string Softwareversion;
		struct Jury{
			string Lastname;
			string Firstname;
			string Nation;
			string Email;
			string Phonenbr;
		};
		struct Course{
			string Name;
			string Homologation;
			int Length;
			int Gates;
			int Turninggates;
			int Startlelev;
			int Finishelev;
		};
		struct Coursesetter{
			string Lastname;
			string Firstname;
			string Nation;
		};
		struct Forerunner{
			string Lastname;
			string Firstname;
			string Nation;
		};
		string IntermediateDistance;
		struct Weather{
			string Time;
			string Place;
			string Weather;
			string Snow;
			float Temperatureair;
			float Temperaturesnow;
			int Humiditystart;
			float Windspeed;
		};
//		struct AL_ranked{		Rank 		Order 		Bib 		};
		struct Competitor{
			string Fiscode;
			string Lastname;
			string Firstname;
			string Gender;//M L
			string Nation;
			int Yearofbirth;
			string Clubname;
		};
		struct AL_result{
			string Timerun1;//MM:SS:ZZ
			string Timerun2;//MM:SS:ZZ
			string Timerun3;//MM:SS:ZZ
			string Totaltime;//MM:SS:ZZ
			string Diff;//MM:SS:ZZ
			float Racepoints;
			string Level;//	final smallfinal semifinal quarterfinaleightfinal qualification sixteenfinal thirtytwofinal sixtyfourfinal
		};
/*
Order number of intermediate point
1-98 	= intermediate points
99 		= Finish
*/
		struct Intermediate{
			string Time;
			string Diff;
			int Rank;
			float Speed;
			string Sectortime;
			string Sectordiff;
			string Sectorrank;
		};
		struct AL_notranked{
			int Run;
			string Bib;
			Competitor competitor;
			int Gate;
			AL_result al_result;
//			AL_resultdetail al_resultdetail;
			string Reason;

		};
	public:
		Race():Codex(0){}
		~Race(){}

		void setLiveFISpassword(string liveFISpassword){LiveFISpassword=liveFISpassword;};
		string getLiveFISpassword(){return LiveFISpassword;};
		void setCodex(int icodex){Codex=icodex;};
		int getCodex(){return Codex;};
		void setNation(string nation){Nation=nation;};
		string getNation(){return Nation;};
		void setDiscipline(string discipline){Discipline=discipline;};
		string getDiscipline(){return Discipline;};

		void setGender(string gender){Gender=gender;};
		string getGender(void){return Gender;};
		void setCategory(string category){Category=category;};
		string getCategory(){return Category;};
		void setType(string ttype){Type=ttype;};   //Type of content Startlist Partial Unofficial Official
		string getType(){return Type;};   //Type of content Startlist Partial Unofficial Official
		void setEventname(string eventname){Eventname=eventname;};
		string getEventname(){return Eventname;};
		void setPlace(string place){Place=place;};
		string getPlace(){return Place;};

		void setSlope(string slope){Slope=slope;};
		string getSlope(){return Slope;};


		String getRaceyyyy(){String str;DateTimeToString(str, "yyyy", Racedate);return str;};
		String getRacemm(){String str;DateTimeToString(str, "m", Racedate);return str;};
		String getRacedd(){String str;DateTimeToString(str, "d", Racedate);return str;};
		void setRacedate(TDate racedate){Racedate=racedate;};

		void setTimingby(string timingby){Timingby=timingby;};
		string getTimingby(){return Timingby;};
		void setDataprocessingby(string dataprocessingby){Dataprocessingby=dataprocessingby;};
		string getDataprocessingby(){return Dataprocessingby;};

		void setSoftwarecompany(string softwarecompany){Softwarecompany=softwarecompany;};
		string getSoftwarecompany(){return Softwarecompany;};
		void setSoftwarename(string softwarename){Softwarename=softwarename;};
		string getSoftwarename(){return Softwarename;};
		void setSoftwareversion(string softwareversion){Softwareversion=softwareversion;};
		string getSoftwareversion(){return Softwareversion;};

//______LIVE FIS________________________________________________________________________
		String __fastcall LiveFISRaceclear(void);
		String __fastcall LiveFISRacemeteo(String srun);
		String __fastcall LiveFISRaceinfo(String srun);
		String __fastcall LiveFISRacemessage(String message);
		String __fastcall LiveFISRaceactiverun(String srun);
		String __fastcall LiveFISRacestartLIST(String srun,string filename);


 };
#endif
//______________________________________________________________________________
class RaceList:public Race{
	private:
		vector <vector <string> > Racers;
///		String CODEX;//Codex
		RaceResults *Run1Results;
		RaceResults *Run2Results;
	public:
		RaceList(){}
///		RaceList(String codex):Codex(codex){}
		~RaceList(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename);
		int getRacersN(){return Racers.size();};
		string getRacer(int i,int j){return Racers[i][j];};
		void setRacer(int i,int j,string sval){Racers[i][j].assign(sval);};
///		void setCODEX(String codex){CODEX=codex;};
///		String getCODEX(){return Codex;};
		bool Compare(RaceList *rl){return Racers==rl->Racers;};
};
//______________________________________________________________________________
class RaceResults{
	private:
		vector <vector <string> > Results;
		RaceList *RL;
	public:
		RaceResults(){}
		~RaceResults(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename){};
		string getResult(int i,int j){return Results[i][j];};
		void setResult(int i,int j,string sval){Results[i][j].assign(sval);};
		bool Compare(RaceResults *rl){return Results==rl->Results;};
};
//______________________________________________________________________________
#endif
//---------------------------------------------------------------------------

