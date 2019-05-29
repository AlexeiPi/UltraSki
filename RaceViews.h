//---------------------------------------------------------------------------

#ifndef RaceViewsH
#define RaceViewsH
#include <vcl.h>

#include "UltraSki.h"
#include "Racer.h"
#include "Competition.h"
//---------------------------------------------------------------------------

class RaceStartListView:public RaceList{
	private:

//------------------------------------------------------------------------------
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
			str=i>0?rL->getRacer(i,0):"¹";
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
			str=i>0?rL->getRacer(i,1):"êîä ÔÈÑ";
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
			str=i>0?rL->getRacer(i,2):"ÔÀÌÈËÈß, Èìÿ";

			FIO->Caption=str;
			FIO->OnMouseDown = SN->OnMouseDown;
		}
	};
//______________________________________________________________________________
		vector < _viewSL > viewSL;
		TForm *pRaceSLViews;
		TPanel *panel1,*panel2,*panel3;
		TLabel *lbl;
		TImage *image;


		int icurrRacer=1,ilastcurrRacer=-1;
		int iTopLine=1,iBottomLine;
		int iActiveLine=1;
		AnsiString XMLpath;

//______________________________________________________________________________
	public:
		void __fastcall ClearXMLpath(void){XMLpath="";}
		  void __fastcall  setXMLpath(AnsiString apath){XMLpath=apath;}
		  AnsiString  __fastcall getXMLpath(void){return XMLpath;};

		RaceStartListView():pRaceSLViews(NULL){}
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
			if(pRaceSLViews!=NULL){
				delete pRaceSLViews;pRaceSLViews=NULL;
			}

		};

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_resize(TObject *Sender);
		void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall showView(int itop,int ileft,int iheight);
		void __fastcall Locations(TForm* form);
		void __fastcall setRacersColor(_viewSL vsl);
		int  __fastcall checkLines(void);
		void __fastcall CleaSLForm(void){
			if(pRaceSLViews!=NULL){
				delete pRaceSLViews;
				pRaceSLViews=NULL;
			}
		};


};
//---------------------------------------------------------------------------
class RaceResultsView:public RaceList{
	private:
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

class Races:public RaceStartListView{
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
		TLabel *lFISCodex,*lDate,*lSLimportN,*lSLimport,*lID,*lInfoName;
		TEdit *eFISCodex,*eInfoName;
		TMaskEdit *eDate;
		TOpenDialog *StartListFileDialog;
		TRadioButton *rb1,*rb2,*rb3,*rb4,*rb5,*rb6,*rb7,*rb8,*rb9,*rb10;
		TRadioGroup *grpGender,*grpDiscipline;

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
		String ImportedFileName;

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
				rb1=rb2=rb3=rb4=rb5=rb6=rb7=rb8=rb9=rb10=NULL;
				grpDiscipline=grpGender=NULL;
				lInfoName=NULL;lID=NULL;lSLimport=NULL;lSLimportN=NULL;
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

		int getCodexInRAM(){
			try{
				int icodex=StrToInt(eFISCodex->Text);
				return   icodex;
			}
			catch(...){}
			return 0;
		}

		void setImportedFileName(String path){ImportedFileName=path;};
		String getImportedFileName(void){return ImportedFileName;};

		RacePack getRace(int i){return RacesList[i];};

		void __fastcall showRaces();
		void __fastcall showInfo();
		void __fastcall showStartList();

		void __fastcall Locations(TForm* form);
		void __fastcall LocationsInfo(TForm* form);
		void __fastcall LocationsStartList(TForm* form);

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_key_down_startlist(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall edit_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall maskedit_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift);


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




#endif
