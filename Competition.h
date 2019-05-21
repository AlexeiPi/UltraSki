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
/*
class Competition{
	private:
		vector <vector <string> > Racers;
		String CODEX;
		RaceResults *Run1Results;
		RaceResults *Run2Results;
	public:
		RaceList(){}
		RaceList(String codex):CODEX(codex){}
		~RaceList(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename);
		int getRacersN(){return Racers.size();};
		string getRacer(int i,int j){return Racers[i][j];};
		void setRacer(int i,int j,string sval){Racers[i][j].assign(sval);};
		void setCODEX(String codex){CODEX=codex;};
		String getCODEX(){return CODEX;};
		bool Compare(RaceList *rl){return Racers==rl->Racers;};
};
*/
//______________________________________________________________________________
class RaceList{
	private:
		vector <vector <string> > Racers;
		String CODEX;
		RaceResults *Run1Results;
		RaceResults *Run2Results;
	public:
		RaceList(){}
		RaceList(String codex):CODEX(codex){}
		~RaceList(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename);
		int getRacersN(){return Racers.size();};
		string getRacer(int i,int j){return Racers[i][j];};
		void setRacer(int i,int j,string sval){Racers[i][j].assign(sval);};
		void setCODEX(String codex){CODEX=codex;};
		String getCODEX(){return CODEX;};
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

