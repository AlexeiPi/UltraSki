//---------------------------------------------------------------------------

#ifndef CompetitionH
#define CompetitionH
#include <vector>
using namespace std;
class RaceList{
	private:
		TPanel *panel;
		vector <vector <string>> Racers;
	public:
		RaceList(){}
		~RaceList(){}
		void __fastcall Locations(TForm* form);
		//std::vector <Racers*> RacersList;
		void LoadFromExcel(AnsiString filename);
		void saveXML(AnsiString filename);
};
//---------------------------------------------------------------------------
#endif



//---------------------------------------------------------------------------

