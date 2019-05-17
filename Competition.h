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
//______________________________________________________________________________
class RaceResults{
	private:
		vector <vector <string> > Results;
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
class RaceList{
	private:
		vector <vector <string> > Racers;
		RaceResults *Run1Results;
		RaceResults *Run2Results;
	public:
		RaceList(){}
		~RaceList(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename);
		string getRacer(int i,int j){return Racers[i][j]/*.c_str()*/;};
		void setRacer(int i,int j,string sval){Racers[i][j].assign(sval);};
		bool Compare(RaceList *rl){return Racers==rl->Racers;};
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

