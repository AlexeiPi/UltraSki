//---------------------------------------------------------------------------

#ifndef CompetitionH
#define CompetitionH
#include <vector>
class RaceList{
	private:
		TPanel *panel;
	public:
		RaceList(){}
		~RaceList(){}
		void __fastcall Locations(TForm* form);
		//std::vector <Racers*> RacersList;
		void LoadFromExcel(AnsiString filename);
};
//---------------------------------------------------------------------------
#endif



//---------------------------------------------------------------------------

