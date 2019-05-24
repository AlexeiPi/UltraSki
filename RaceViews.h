//---------------------------------------------------------------------------

#ifndef RaceViewsH
#define RaceViewsH
#include <vcl.h>

#include "UltraSki.h"
#include "Racer.h"
#include "Competition.h"


#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

//TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------

class RaceStartListView:public RaceList{
	private:
//______________________________________________________________________________
	struct _viewSL{
		TLabel *SN;
		TLabel *FC;
		TLabel *FIO;

		_viewSL(TPanel*p,int i,RaceList *rL,TLabel *lbl){//constructor
			AnsiString str;
			SN=new TLabel(p);
			SN->Name="SN"+AnsiString(i);
			SN->Parent = p;
			SN->AutoSize=false;
			SN->Transparent=false;
			SN->Tag=i;
			SN->Color=i>0?clWhite:clAqua;
			SN->Font->Size=10;
			SN->Width=30;
			SN->Height=18;
			SN->Top=(i>0?i-1:1)*SN->Height;
			SN->Left=1;
			SN->Alignment=taCenter;
			str=i>0?rL->getRacer(i,0).c_str():"¹";
			SN->Caption=str;
			SN->OnMouseDown = lbl->OnMouseDown;

			FC=new TLabel(p);
			FC->Name="FC"+AnsiString(i);
			FC->Parent = p;
			FC->AutoSize=false;
			FC->Transparent=false;
			FC->Tag=SN->Tag;
			FC->Color=SN->Color;
			FC->Font->Size=SN->Font->Size;
			FC->Width=70;
			FC->Height=SN->Height;
			FC->Top=SN->Top;
			FC->Left=SN->Left+SN->Width;
			FC->Alignment=taLeftJustify;
			str=i>0?rL->getRacer(i,1).c_str():"êîä ÔÈÑ";
			FC->Caption=str;
			FC->OnMouseDown = SN->OnMouseDown;

			FIO=new TLabel(p);
			FIO->Name="FIO"+AnsiString(i);
			FIO->Parent = p;
			FIO->AutoSize=false;
			FIO->Transparent=SN->Transparent;
			FIO->Tag=SN->Tag;
			FIO->Color=SN->Color;
			FIO->Font->Size=SN->Font->Size;
			FIO->Width=210;
			FIO->Height=SN->Height;
			FIO->Top=SN->Top;
			FIO->Left=FC->Left+FC->Width;
			FIO->Alignment=taLeftJustify;
			str=i>0?rL->getRacer(i,2).c_str():"ÔÀÌÈËÈß, Èìÿ";

			FIO->Caption=str;
			FIO->OnMouseDown = SN->OnMouseDown;
		}
	};
//______________________________________________________________________________
	   ///	RaceList *RL;
		vector < _viewSL > viewSL;
		TForm *pRaceViews;
		TPanel *panel1,*panel2,*panel3;
		TLabel *lbl;

		TIdTCPClient *TcpClient1;

		int icurrRacer=1,ilastcurrRacer=-1;
		int iTopLine=1,iBottomLine;
		int iActiveLine=1;
//______________________________________________________________________________
	public:
		RaceStartListView():pRaceViews(NULL){}
/*		RaceStartListView(RaceList *rl):pRaceViews(NULL){
			RL=rl;
		}
*/
		void __fastcall freevcls(_viewSL vsl){
			if(vsl.SN!=NULL){
				delete vsl.SN;vsl.SN=NULL;
			}
			if(vsl.FC!=NULL){
				delete vsl.FC;vsl.FC=NULL;
			}
			if(vsl.FIO!=NULL){
				delete vsl.FIO;vsl.FIO=NULL;
			}
		}
		~RaceStartListView(){
			std::for_each(viewSL.begin(),viewSL.end(),freevcls);
			if(panel3!=NULL){
				delete panel3;panel3=NULL;
			}
			if(panel2!=NULL){
				delete panel2;panel2=NULL;
			}
			if(panel1!=NULL){
				delete panel1;panel1=NULL;
			}
			if(lbl!=NULL){
				delete lbl;lbl=NULL;
			}
			if(TcpClient1!=NULL)
				delete TcpClient1;
			if(pRaceViews!=NULL){
				delete pRaceViews;pRaceViews=NULL;
			}

		};

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_resize(TObject *Sender);
		void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall showView();
		void __fastcall Locations(TForm* form);
		void __fastcall setRacersColor(_viewSL vsl);
		int  __fastcall checkLines(void);


		void __fastcall FISconnect();
		void __fastcall OnConnected(TObject *Sender);
		void __fastcall OnWork(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount);
		void __fastcall WorkBegin(TObject *ASender, TWorkMode AWorkMode,__int64 AWorkCountMax);
		void __fastcall Status(TObject *ASender, const TIdStatus AStatus,const UnicodeString AStatusText);
};
//---------------------------------------------------------------------------
class RaceResultsView:public RaceList{
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
