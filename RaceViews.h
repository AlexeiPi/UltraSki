//---------------------------------------------------------------------------

#ifndef RaceViewsH
#define RaceViewsH
#include <vcl.h>
#include "Racer.h"
#include "Competition.h"
//---------------------------------------------------------------------------
struct _viewSL{
	TLabel *SN;
	TLabel *FC;
	TLabel *FIO;
};

class RaceStartListView{
	private:
		RaceList *RL;
		vector < _viewSL > viewSL;
		TForm *pRaceViews;
		int icurrRacer=1,ilastcurrRacer=-1;
		int iTopLine=1,iBottomLine;
	public:
		RaceStartListView():pRaceViews(NULL){}
		RaceStartListView(RaceList *rl):pRaceViews(NULL){RL=rl;}
		~RaceStartListView(){};

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall form_resize(TObject *Sender);
		void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall showView();
		void __fastcall Locations(TForm* form);
		void __fastcall setRacersColor(_viewSL vsl);
        void __fastcall checkLines(void);
};
//---------------------------------------------------------------------------
class RaceResultsView{
	private:
	///	TfUltraSki *fRaceResultsView;
		RaceResults *RR;
	public:
		RaceResultsView(){}
		~RaceResultsView(){}
		void LoadFromCSV(string filename);
		void saveXML(string filename);
		void loadXML(string filename){};

//		string getResult(int i,int j){return Results[i][j];};
//		void setResult(int i,int j,string sval){Results[i][j].assign(sval);};
};
//---------------------------------------------------------------------------
#endif
