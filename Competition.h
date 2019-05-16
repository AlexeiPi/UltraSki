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
class RaceList{
	private:
		vector <vector <string> > Racers;
	public:
		RaceList(){}
		~RaceList(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename);
		String getRacer(int i,int j){return Racers[i][j].c_str();};
		void setRacer(int i,int j,string sval){
			Racers[i][j].assign(sval);
		};
		bool Compare(RaceList *rl){return Racers==rl->Racers;};
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

