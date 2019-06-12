//---------------------------------------------------------------------------

#ifndef TimingDeviceH
#define TimingDeviceH
#include <vcl.h>
#include <vector>
#include "UltraSki.h"
#include "Racer.h"
#include "Competition.h"
#include "RaceViews.h"

extern TIniFile *IniUltraTimeKeeping;//ini file
///extern Races *rcs;
using namespace std;

enum timemachinelines{FISemulation=0,startline=1,inter1=2,inter2=3,inter3=4,inter4=5,finishline=9};
class TimeKeeping{
private:
	struct Timing{
		int icurrpulseNumber;
		AnsiString TimeOfDay;
		AnsiString electroLine;
	};
	vector < Timing > TimingList;

	struct TimeMachine{
		String model;
		String Number;
	};

	struct _viewTK{
		TPanel *ptk;
		TLabel *lAS,*lAt1,*lAt2,*lAt3,*lAt4,*lAF;
		TLabel *lBS,*lBt1,*lBt2,*lBt3,*lBt4,*lBF;


		TPanel *p1;
		TLabel *lSN,*lSNb;//seq number
		TLabel *lLine,*lbLine;//pulse line 0-correction according to FIS rules, 1-start, 2-8 intermediate, 9-finish physical
		TEdit *eTime;//electronic time
		TEdit *emTime;//emulated time
		TEdit *emBTime;//backup time

		_viewTK(TPanel*p,int i,Timing *tm1,Timing *tm2,TLabel *lbl){//constructor
			AnsiString str,aline="",aSN="",aTOD="",bline="",bSN="",bTOD="";
			if(tm1!=NULL){
				aSN=tm1->icurrpulseNumber;
				aline=tm1->electroLine;
				aTOD=tm1->TimeOfDay;
			}
			if(tm2!=NULL){
				bSN=tm2->icurrpulseNumber;
				bline=tm2->electroLine;
				bTOD=tm2->TimeOfDay;
			}


			p1=dynamic_cast<TPanel*> (p->FindComponent("Panel"+IntToStr(i)));
			if(!p1){
				p1=new TPanel(p);
				p1->Parent = p;
				p1->Name="Panel"+IntToStr(i);
				p1->DoubleBuffered=true;
				p1->Top=i*18;
                p1->ShowCaption=false;
			}
			lSN=dynamic_cast<TLabel*> (p1->FindComponent("tmlSN"));
			if(lSN==NULL){
				lSN=new TLabel(p1);
				lSN->Parent = p1;
				lSN->Name="tmlSN";
				lSN->AutoSize=false;
				lSN->Transparent=false;
				lSN->Tag=i;
				lSN->Color=clWhite;
				lSN->Font->Size=10;
				lSN->Width=40;
				lSN->Height=18;
				lSN->Top=0;
				lSN->Left=1;
				lSN->Alignment=taCenter;
			}
			lSN->Caption=aSN;

			lLine=dynamic_cast<TLabel*> (p1->FindComponent("tmlLine"));
			if(lLine==NULL){
				lLine=new TLabel(p1);
				lLine->Parent = p1;
				lLine->Name="tmlLine";
				lLine->AutoSize=false;
				lLine->Transparent=false;
				lLine->Tag=lSN->Tag;
				lLine->Color=lSN->Color;
				lLine->Font->Size=lSN->Font->Size;
				lLine->Width=30;
				lLine->Height=lSN->Height;
				lLine->Top=lSN->Top;
				lLine->Left=lSN->Left+lSN->Width+1;
				lLine->Alignment=taCenter;
			}
			lLine->Caption=aline;
			eTime=dynamic_cast<TEdit*> (p1->FindComponent("tmeTime"));
			if(eTime==NULL){
				eTime=new TEdit(p1);
				eTime->Name="tmeTime";
				eTime->Parent = p1;
				eTime->AutoSize=false;
				eTime->Tag=lSN->Tag;
				eTime->Font->Size=lSN->Font->Size;
				eTime->Width=90;
				eTime->Height=lSN->Height;
				eTime->Top=lSN->Top;
				eTime->Left=lLine->Left+lLine->Width;
				eTime->Alignment=taLeftJustify;
			}
			eTime->Text=aTOD;

			emTime=dynamic_cast<TEdit*> (p1->FindComponent("tmemTime"));
			if(emTime==NULL){
				emTime=new TEdit(p1);
				emTime->Name="tmemTime";
				emTime->Parent = p1;
				emTime->AutoSize=false;
				emTime->Tag=lSN->Tag;
				emTime->Font->Size=lSN->Font->Size;
				emTime->Width=eTime->Width;
				emTime->Height=lSN->Height;
				emTime->Top=lSN->Top;
				emTime->Left=eTime->Left+eTime->Width;
				emTime->Alignment=taLeftJustify;
			}
			emTime->Text="";

			lSNb=dynamic_cast<TLabel*> (p1->FindComponent("tmlSNb"));
			if(lSNb==NULL){
				lSNb=new TLabel(p1);
				lSNb->Parent = p1;
				lSNb->Name="tmlSNb";
				lSNb->AutoSize=false;
				lSNb->Transparent=false;
				lSNb->Tag=i;
				lSNb->Color=clWhite;
				lSNb->Font->Size=10;
				lSNb->Width=lSN->Width;
				lSNb->Height=18;
				lSNb->Top=0;
				lSNb->Left=emTime->Left+emTime->Width+5;
				lSNb->Alignment=taCenter;
			}
			lSNb->Caption=bSN;

			lbLine=dynamic_cast<TLabel*> (p1->FindComponent("tmlbLine"));
			if(lbLine==NULL){
				lbLine=new TLabel(p1);
				lbLine->Parent = p1;
				lbLine->Name="tmlbLine";
				lbLine->AutoSize=false;
				lbLine->Transparent=false;
				lbLine->Tag=lSN->Tag;
				lbLine->Color=lSN->Color;
				lbLine->Font->Size=lSN->Font->Size;
				lbLine->Width=lLine->Width;
				lbLine->Height=lSN->Height;
				lbLine->Top=lSN->Top;
				lbLine->Left=lSNb->Left+lSNb->Width+1;
				lbLine->Alignment=taCenter;
			}
			lbLine->Caption=bline;



			emBTime=dynamic_cast<TEdit*> (p1->FindComponent("tmembTime"));
			if(emBTime==NULL){
				emBTime=new TEdit(p1);
				emBTime->Name="tmembTime";
				emBTime->Parent = p1;
				emBTime->AutoSize=false;
				emBTime->Tag=lSN->Tag;
				emBTime->Font->Size=lSN->Font->Size;
				emBTime->Width=eTime->Width;
				emBTime->Height=lSN->Height;
				emBTime->Top=lSN->Top;
				emBTime->Left=lbLine->Left+lbLine->Width+1;
				emBTime->Alignment=taLeftJustify;
			}
			emBTime->Text=bTOD;
			p1->Width=emBTime->Left+emBTime->Width+5;
///			str="";
///			emTime->Text=str;
//			emTime->OnKeyDown = lSN->OnMouseDown;
		}
		~_viewTK(){
		}
	};
	vector < _viewTK > viewTK;
	TForm *pTMViews;
	TTimer *TKtimer;
	TLabel *lsynch;
	TMaskEdit *eAsynch,*eBsynch;
	TLabel *l0pulse,*lpulse,*lBpulse;

	TLabel *l0pulseValue,*l0pulseValue1,*l0pulseValue2,*l0pulseValue3,*l0pulseValue4,*l0pulseValue5,*l0pulseValue6;
	TLabel *lpulseValue,*lpulseValue1,*lpulseValue2,*lpulseValue3,*lpulseValue4,*lpulseValue5,*lpulseValue6;
	TLabel *lBpulseValue,*lBpulseValue1,*lBpulseValue2,*lBpulseValue3,*lBpulseValue4,*lBpulseValue5,*lBpulseValue6;
	TPanel *panel3,*panel2,*panel1;


	AnsiString ApplicationPath,DefaultPath;
	TStringList* Sections;
	TStringList* Values;

public:
	TimeKeeping(){
	AnsiString astr;
		pTMViews=new TForm(Application);
		pTMViews->DoubleBuffered=true;
		pTMViews->OnResize=form_resize;
		TKtimer=new TTimer(pTMViews);
		TKtimer->Interval=10;
		TKtimer->Name="TKtimer";
		TKtimer->OnTimer=OnTKtimer;

		panel3=NULL;panel2=NULL;panel1=NULL;
		lsynch=NULL;
		eAsynch=eBsynch=NULL;
		l0pulse=NULL;l0pulseValue=NULL;l0pulseValue1=NULL;l0pulseValue2=NULL;l0pulseValue3=NULL;l0pulseValue4=NULL;l0pulseValue5=NULL;l0pulseValue6=NULL;
		lpulse=NULL;lpulseValue=NULL;lpulseValue1=NULL;lpulseValue2=NULL;lpulseValue3=NULL;lpulseValue4=NULL;lpulseValue5=NULL;lpulseValue6=NULL;
		lBpulse=NULL;lBpulseValue=NULL;lBpulseValue1=NULL;lBpulseValue2=NULL;lBpulseValue3=NULL;lBpulseValue4=NULL;lBpulseValue5=NULL;lBpulseValue6=NULL;


		ApplicationPath=Application->ExeName;
		ApplicationPath=StringReplace(ApplicationPath,".\\","",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
		DefaultPath=ExtractFilePath(ApplicationPath);
		ApplicationPath=ChangeFileExt( ApplicationPath, ".INI" );
		ApplicationPath=DefaultPath+"TimeKeeping.INI";
		astr=ApplicationPath;

		IniUltraTimeKeeping=new TIniFile(ApplicationPath);
		Sections = new TStringList;
		Values = new TStringList;

	};
	~TimeKeeping(){

		if(TKtimer!=NULL){delete TKtimer;TKtimer=NULL;}
		if(lsynch!=NULL){delete lsynch;lsynch=NULL;}
		if(eAsynch!=NULL){delete eAsynch;eAsynch=NULL;}
		if(eBsynch!=NULL){delete eBsynch;eBsynch=NULL;}

		if(l0pulse!=NULL){delete l0pulse;l0pulse=NULL;}
		if(l0pulseValue!=NULL){delete l0pulseValue;l0pulseValue=NULL;}
		if(l0pulseValue1!=NULL){delete l0pulseValue1;l0pulseValue1=NULL;}
		if(l0pulseValue2!=NULL){delete l0pulseValue2;l0pulseValue2=NULL;}
		if(l0pulseValue3!=NULL){delete l0pulseValue3;l0pulseValue3=NULL;}
		if(l0pulseValue4!=NULL){delete l0pulseValue4;l0pulseValue4=NULL;}
		if(l0pulseValue5!=NULL){delete l0pulseValue5;l0pulseValue5=NULL;}
		if(l0pulseValue6!=NULL){delete l0pulseValue6;l0pulseValue6=NULL;}
		if(lpulse!=NULL){delete lpulse;lpulse=NULL;}
		if(lpulseValue!=NULL){delete lpulseValue;lpulseValue=NULL;}
		if(lpulseValue1!=NULL){delete lpulseValue1;lpulseValue1=NULL;}
		if(lpulseValue2!=NULL){delete lpulseValue2;lpulseValue2=NULL;}
		if(lpulseValue3!=NULL){delete lpulseValue3;lpulseValue3=NULL;}
		if(lpulseValue4!=NULL){delete lpulseValue4;lpulseValue4=NULL;}
		if(lpulseValue5!=NULL){delete lpulseValue5;lpulseValue5=NULL;}
		if(lpulseValue6!=NULL){delete lpulseValue6;lpulseValue6=NULL;}
		if(lBpulse!=NULL){delete lBpulse;lBpulse=NULL;}
		if(lBpulseValue!=NULL){delete lBpulseValue;lBpulseValue=NULL;}
		if(lBpulseValue1!=NULL){delete lBpulseValue1;lBpulseValue1=NULL;}
		if(lBpulseValue2!=NULL){delete lBpulseValue2;lBpulseValue2=NULL;}
		if(lBpulseValue3!=NULL){delete lBpulseValue3;lBpulseValue3=NULL;}
		if(lBpulseValue4!=NULL){delete lBpulseValue4;lBpulseValue4=NULL;}
		if(lBpulseValue5!=NULL){delete lBpulseValue5;lBpulseValue5=NULL;}
		if(lBpulseValue6!=NULL){delete lBpulseValue6;lBpulseValue6=NULL;}
		if (pTMViews!=NULL){delete pTMViews;pTMViews=NULL;}

	};
	int getPulsesN(){return TimingList.size();};
	void __fastcall TimeKeepingLocations(TForm* form);
	void __fastcall showTimeKeeping(void);
	void __fastcall mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall OnTKtimer(TObject *Sender);
	void __fastcall SetLeftTop(int ileft,int itop){pTMViews->Left=ileft;pTMViews->Top=itop;};
	void __fastcall form_resize(TObject *Sender);
	void __fastcall show_viewTK(void);
	void __fastcall TimePut(AnsiString atype,AnsiString aname,AnsiString atime);
};
#endif
//---------------------------------------------------------------------------

