//---------------------------------------------------------------------------
#ifndef RaceViewsH
#define RaceViewsH

#include <vcl.h>
//#include<algorithm>

#include "UltraSki.h"

//#include "TimingDevice.h"
//#include "Racer.h"
#include "Competition.h"

extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
class RaceStartListView:public RaceList{
	private:

//------------------------------------------------------------------------------
//______________________________________________________________________________
	struct _viewSL{
		TLabel *SN;
		TLabel *FC;
		TLabel *FIO;
		TLabel *T1;
		TLabel *T2;

		_viewSL(TPanel*p,int i,RaceList *rL,TLabel *lbl){//constructor
			AnsiString str;

			SN=dynamic_cast<TLabel*> (p->FindComponent("SN"+AnsiString(i)));
			if(SN==NULL){
				SN=new TLabel(p);
				SN->Parent = p;
				SN->Name="SN"+AnsiString(i);
				SN->AutoSize=false;
				SN->Transparent=false;
				SN->Tag=i;
				SN->Color=i>0?clWhite:clAqua;
				SN->Font->Size=10;
				SN->Width=30;
				SN->Height=18;
//				SN->Top=(i>0?i-1:1)*SN->Height;
				SN->Top=(i>0?i-1:2)*SN->Height;
				SN->Left=1;
				SN->Alignment=taCenter;
				str=i>0?rL->getRacer(i,0):"№";
				SN->Caption=str;
				SN->OnMouseDown = lbl->OnMouseDown;
				SN->OnDblClick = lbl->OnDblClick;
			}

			FC=dynamic_cast<TLabel*> (p->FindComponent("FC"+AnsiString(i)));
			if(FC==NULL){
				FC=new TLabel(p);
				FC->Name="FC"+AnsiString(i);
				FC->Parent = p;
				FC->AutoSize=false;
				FC->Transparent=false;
				FC->Tag=SN->Tag;
				FC->Color=SN->Color;
				FC->Font->Size=SN->Font->Size;
				FC->Width=60;
				FC->Height=SN->Height;
				FC->Top=SN->Top;
				FC->Left=SN->Left+SN->Width;
				FC->Alignment=taCenter;
				if(i>0){
					str=rL->getRacer(i,1);
				}
				else{
					str="код";
				}
				FC->Caption=str;
				FC->OnMouseDown = SN->OnMouseDown;
				FC->OnDblClick = lbl->OnDblClick;
			}

			FIO=dynamic_cast<TLabel*> (p->FindComponent("FIO"+AnsiString(i)));
			if(FIO==NULL){
				FIO=new TLabel(p);
				FIO->Name="FIO"+AnsiString(i);
				FIO->Parent = p;
				FIO->AutoSize=false;
				FIO->Transparent=SN->Transparent;
				FIO->Tag=SN->Tag;
				FIO->Color=SN->Color;
				FIO->Font->Size=SN->Font->Size-(i>0?1:0);
				FIO->Width=210;
				FIO->Height=SN->Height;
				FIO->Top=SN->Top;
				FIO->Left=FC->Left+FC->Width;
				FIO->Alignment=taLeftJustify;
				str=i>0?rL->getRacer(i,2):" Фамилия, Имя";

				FIO->Caption=str;
				FIO->OnMouseDown = SN->OnMouseDown;
				FIO->OnDblClick = lbl->OnDblClick;
			}

			T1=dynamic_cast<TLabel*> (p->FindComponent("T1"+AnsiString(i)));
			if(T1==NULL){
				T1=new TLabel(p);
				T1->Name="T1"+AnsiString(i);
				T1->Parent = p;
				T1->AutoSize=false;
				T1->Transparent=SN->Transparent;
				T1->Tag=SN->Tag;
				T1->Color=SN->Color;
				T1->Font->Size=SN->Font->Size-(i>0?1:0);
				T1->Width=80;
				T1->Height=SN->Height;
				T1->Top=SN->Top;
				T1->Left=FIO->Left+FIO->Width;
				T1->Alignment=taCenter;
				str=i>0?"1:22.33"/*rL->getRacer(i,2)*/:"T1";

				T1->Caption=str;
				T1->OnMouseDown = SN->OnMouseDown;
				T1->OnDblClick = lbl->OnDblClick;
			}
			T2=dynamic_cast<TLabel*> (p->FindComponent("T2"+AnsiString(i)));
			if(T2==NULL){
				T2=new TLabel(p);
				T2->Name="T2"+AnsiString(i);
				T2->Parent = p;
				T2->AutoSize=false;
				T2->Transparent=SN->Transparent;
				T2->Tag=SN->Tag;
				T2->Color=SN->Color;
				T2->Font->Size=SN->Font->Size-(i>0?1:0);
				T2->Width=T1->Width;
				T2->Height=SN->Height;
				T2->Top=SN->Top;
				T2->Left=T1->Left+T1->Width;
				T2->Alignment=T1->Alignment;
				str=i>0?/*rL->getRacer(i,2)*/"1:22.33":"T2";

				T2->Caption=str;
				T2->OnMouseDown = SN->OnMouseDown;
				T2->OnDblClick = lbl->OnDblClick;
			}
		}
		~_viewSL(){
		}
	};
//______________________________________________________________________________
		vector < _viewSL > viewSL;
		TForm *pRaceSLViews;
		TPanel *panel1,*panel2,*panel3;
		TLabel *l2live;
		TImage *image;

        TImage *imageFIS;


		int icurrRacer=-1,ilastcurrRacer=-1;
		int iTopLine=1,iBottomLine;
		int iActiveLine=1;
		AnsiString XMLpath;

//______________________________________________________________________________
	public:
		void __fastcall ClearXMLpath(void){XMLpath="";}
		  void __fastcall  setXMLpath(AnsiString apath){XMLpath=apath;}
		  AnsiString  __fastcall getXMLpath(void){return XMLpath;};

		RaceStartListView(){
			if(pRaceSLViews==NULL){
				panel3=NULL;
				panel2=NULL;
				panel1=NULL;
				l2live=NULL;
                imageFIS=NULL;

				pRaceSLViews=new TForm(Application);
				pRaceSLViews->Caption="Стартовый список";
				pRaceSLViews->Name="RaceStartListViewForm";
				pRaceSLViews->Font->Style = pRaceSLViews->Font->Style << fsBold;
				pRaceSLViews->DoubleBuffered=true;
				pRaceSLViews->KeyPreview=true;
				pRaceSLViews->OnKeyDown=form_key_down;
				pRaceSLViews->OnMouseWheel=formmousewheel;
	//---------------------------------------------------------------------------


				TBorderIcons tempBI;
				tempBI = pRaceSLViews->BorderIcons;
				tempBI >> biSystemMenu;
				tempBI >> biMinimize;
				tempBI >> biMaximize;
				tempBI >> biHelp;
				pRaceSLViews->BorderIcons = tempBI;


				panel1= new TPanel(pRaceSLViews);
				panel1->Parent = pRaceSLViews;
				panel1->Name="P1SL";
				panel1->Font->Size=12;
				panel1->Alignment=taLeftJustify;
				panel1->VerticalAlignment=taAlignTop;
				panel1->Top=3;
				panel1->Left=3;
				panel1->Visible=true;
				int ccodex=this->getCodex();
				//str.sprintf(L"RaceList%d",this->getCodex());
				panel1->Caption="";//str;

#if 1
				l2live= new TLabel(panel1);
				l2live->Parent=panel1;
				l2live->Font->Size=10;
				l2live->Top=0;
				l2live->Left=3;
				l2live->Height=18;
				l2live->Width=1;
				l2live->Top=0;
				l2live->Name="SL2FIS";
				l2live->Caption="";//"Нажмите для записи в LiveTiming FIS";
				l2live->Transparent=false;
				l2live->Color=clLime;
				l2live->OnMouseDown=mouse_down;
				l2live->OnDblClick=mouse_DblClick;
//#else

				imageFIS=new TImage(panel1);
				imageFIS->Parent = panel1;
				imageFIS->Stretch=true;
				imageFIS->Height=2*18;
				imageFIS->Width=imageFIS->Height;
				imageFIS->Top=0;
				imageFIS->Left=l2live->Left+l2live->Width;
				imageFIS->Picture=fUltraSki->Image1->Picture;

#endif



				panel2= new TPanel(panel1);
				panel2->Parent = panel1;
				panel2->Name="P2SL";
				panel2->Font->Size=12;
				panel2->Alignment=taLeftJustify;
				panel2->VerticalAlignment=taAlignTop;
				panel2->Top=18*3;
				panel2->Left=3;
				panel2->Visible=true;
				panel2->Caption="";

				panel3= new TPanel(panel2);
				panel3->Parent = panel2;
				panel3->Name="P3SL";
				panel3->Font->Size=12;
				panel3->Alignment=taLeftJustify;
				panel3->VerticalAlignment=taAlignTop;
				panel3->Top=0;
				panel3->Left=3;
				panel3->Visible=true;
				panel3->Caption="";
			}

		}
		~RaceStartListView(){
			DeleteAll();
		}

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
		void DeleteAll(void){
///			std::for_each(viewSL.begin(),viewSL.end(),freevcls);
			for(auto i:viewSL)
				freevcls(i);
/*			if(pRaceSLViews!=NULL)
				delete pRaceSLViews,pRaceSLViews=NULL;
*/
		};

		void __fastcall form_key_down(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall form_resize(TObject *Sender);
		void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall mouse_DblClick(TObject *Sender);
		void __fastcall showView(int itop,int ileft,int iheight);
		void __fastcall Locations(TForm* form);
		void __fastcall setRacersColor(_viewSL vsl);
		void  __fastcall setCurRacersColor(){
				std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
		}
		void  __fastcall setCurRacersColor(int icurr){
				icurrRacer=icurr;
				setCurRacersColor();
		}

		int  __fastcall checkLines(void);
		void __fastcall CleaSLForm(void){pRaceSLViews->Hide();};
		void __fastcall formmousewheel(TObject *Sender, TShiftState Shift, int WheelDelta,
						 const TPoint &MousePos, bool &Handled){//OnMouseWheel
						 int wheeldelta=WheelDelta;
						 int itop=0,iheight=0;
						 Handled=true;
						 iheight=panel3->Height;
						 itop=panel3->Top;
						 if(WheelDelta<0){
							if(itop>-iheight+pRaceSLViews->Height-5*18){
								panel3->Top-=18;
							}
						 }
						 else {
							if(itop<0)
								panel3->Top+=18;
							else
								panel3->Top=0;
						 }
		}
        void __fastcall SetCurRacer(int irc);



};
//---------------------------------------------------------------------------
class RaceResults;
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
		AnsiString sCurrentXMLfilename;
//=============================================================================
		struct _viewRL{
			TLabel *SN;
			TLabel *RCodex;
			_viewRL(TPanel*p,int i,Races *r,TLabel *lbl){//constructor
				AnsiString str;

				SN=dynamic_cast<TLabel*> (p->FindComponent("SN"+AnsiString(i)));
				if(SN==NULL){
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
				}
				RCodex=dynamic_cast<TLabel*> (p->FindComponent("RCodex"+AnsiString(i)));
				if(RCodex==NULL){
					RCodex=new TLabel(p);
					RCodex->Name="RCodex"+AnsiString(i);
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

			}
		};
		vector < _viewRL > viewSL;
		TForm *pRaceViews,*pRaceInfo,*pRaceStartList;
		//TMaskEdit *eCompetition;
		TEdit *eCompetition;
///        String sLastRegistered;


		TPanel *panel1,*panel2,*panel3;
		TLabel *lplus,*lCompetition,*lminus;
		TLabel *lFISCodex,*lDate,*lSLimportN,*lSLimport,*lID,*lInfoName;
		TEdit *eInfoName;
		TMaskEdit *eFISCodex;
		TImage *imageFIS;
		TMaskEdit *eDate,*eTime;
		TOpenDialog *StartListFileDialog;
		TRadioButton *rb1,*rb2,*rb3,*rb4,*rb5,*rb6,*rb7,*rb8,*rb9,*rb10;
		TRadioGroup *grpGender,*grpDiscipline;

		int icurrRace=-1,ilastcurrRace=-1;
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

		TStringList* Sections;
		TStringList* Values;

//-----------------------------------------------------------------------------
	public:
		Races(){
			TBorderIcons tempBI;
			String str="";
				number_Of_competitions=0;
				DefaultPath=ExtractFilePath(Application->ExeName);
				if(pRaceViews==NULL){
					pRaceViews=new TForm(Application);
					pRaceViews->Caption="Регистрация";
					pRaceViews->Name="RaceViewsForm";
					pRaceViews->DoubleBuffered=true;
					pRaceViews->KeyPreview=true;
					pRaceViews->Font->Style = pRaceViews->Font->Style << fsBold;
					pRaceViews->OnHide=FormHide;
					pRaceViews->OnKeyDown=form_key_down;
					pRaceViews->OnResize=form_resize;
				}
				panel3=NULL;panel2=NULL;panel1=NULL;
				lplus=lCompetition=lminus=NULL;
				eCompetition=NULL;

				if(pRaceInfo==NULL){
					pRaceInfo=new TForm(Application);
					pRaceInfo->Caption="Описание соревнования";
					pRaceInfo->Name="RaceInfoForm";
					pRaceInfo->Font->Style = pRaceInfo->Font->Style << fsBold;

					pRaceInfo->DoubleBuffered=true;
					pRaceInfo->KeyPreview=true;
					pRaceInfo->OnHide=FormHide;
					pRaceInfo->OnDestroy=FormDestroy;
					tempBI = pRaceInfo->BorderIcons;
					tempBI >> biSystemMenu;
					tempBI >> biMinimize;
					tempBI >> biMaximize;
					tempBI >> biHelp;
					pRaceInfo->BorderIcons = tempBI;

					StartListFileDialog=new TOpenDialog(pRaceInfo);
				}

				rb1=rb2=rb3=rb4=rb5=rb6=rb7=rb8=rb9=rb10=NULL;
				grpDiscipline=grpGender=NULL;
				lInfoName=NULL;lID=NULL;lSLimport=NULL;lSLimportN=NULL;

				ApplicationPath=Application->ExeName;
				ApplicationPath=StringReplace(ApplicationPath,".\\","",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
				ApplicationPath=ChangeFileExt( ApplicationPath, ".INI" );
				DefaultPath=ExtractFilePath(ApplicationPath);

				IniUltraAlpSki=new TIniFile(ApplicationPath);
				Sections = new TStringList;
				Values = new TStringList;
		};
		~Races(){
			delete Sections;Sections=NULL;
			delete Values;Values=NULL;
			delete IniUltraAlpSki;Values=NULL;

			if(pRaceInfo!=NULL)
				delete pRaceInfo,pRaceInfo=NULL;
			if(pRaceViews!=NULL)
				delete pRaceViews,pRaceViews=NULL;

		};
		void LoadFromPath(String path);
		int getRacesN(){return RacesList.size();};
//------------------------------------------------------------------------------
		int getNumberOfRaces(void){return RacesList.size();};
		int getCurrRace(void){return icurrRace;};
		void setCurrRace(int icr){icurrRace=icr;ShowRaceInfoAndStartList();};
		void setlastcurrRace(int icr){ilastcurrRace=icr;};
		void __fastcall ShowRaceInfoAndStartList(void);

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
		int __fastcall get_pRaceInfo(){int irc=0;if(pRaceInfo&&pRaceInfo->Visible)irc=pRaceInfo->Width;return irc;};
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
		void __fastcall FormDestroy(TObject *Sender);
		void __fastcall FormHide(TObject *Sender);

		int __fastcall checkLines(void);
		void __fastcall setRacersColor(_viewRL vsl);
		void __fastcall FillRaceDescription(void);
		void __fastcall FillRaceInfo(void);
		void __fastcall FillRaceSL(void);
		void __fastcall SaveInfo2INI(void);
		void __fastcall ReadINIsections(TIniFile *ini);
		int __fastcall LiveFISconnect(void);
		void __fastcall SetFocus(void){pRaceViews->SetFocus();};
		int __fastcall GetLeftInfo(void){return pRaceInfo->Left;}
		int __fastcall GetBottomInfo(void){return pRaceInfo->Top+pRaceInfo->Height;}

};
//______________________________________________________________________________
#endif
