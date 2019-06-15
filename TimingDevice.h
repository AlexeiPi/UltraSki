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
	TForm *pTMViews;
	TTimer *TKtimer;
	TLabel *lsynch;
	TMaskEdit *eAsynch,*eBsynch;

	TMaskEdit *eRaceCode,*eBIBonStart;
	TLabel *lRaceCode,*lBIBonStart;



	TLabel *l0pulse,*lpulse,*lBpulse;

	TLabel *l0pulseValue,*l0pulseValue1,*l0pulseValue2,*l0pulseValue3,*l0pulseValue4,*l0pulseValue5,*l0pulseValue6;
	TLabel *lpulseValue,*lpulseValue1,*lpulseValue2,*lpulseValue3,*lpulseValue4,*lpulseValue5,*lpulseValue6;
	TLabel *lBpulseValue,*lBpulseValue1,*lBpulseValue2,*lBpulseValue3,*lBpulseValue4,*lBpulseValue5,*lBpulseValue6;
	TPanel *panel3,*panel2,*panel1;


	struct Timing{
		int icurrpulseNumber;
		AnsiString TimeOfDay;
		AnsiString electroLine;
		AnsiString racecode;
		AnsiString BIB;
		AnsiString DNF;
		AnsiString DSQ;
		Timing(){
			icurrpulseNumber=0;
			TimeOfDay="";
			electroLine="";
			BIB="";
			DNF="";
			DSQ="";
		}

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
        TLabel *lRaceCode;
		TEdit *eBIB;
		TLabel *lDNF,*lDSQ,*lbibLapse;//seq number

		TLabel *lSN,*lSNb;//seq number
		TLabel *lLine,*lbLine;//pulse line 0-correction according to FIS rules, 1-start, 2-8 intermediate, 9-finish physical
		TEdit *eTime;//electronic time
		TLabel *emTime;//emulated time
		TEdit *emBTime;//backup time

		_viewTK(TPanel*p,int ileftoffset,int iwidth,int i,float idiff,Timing *tm1,Timing *tm2,TLabel *lbl){//constructor
			AnsiString str,aline="",aSN="",aBIB="",aDSQ="",aDNF=""
			,aRACECODE="",aBIBLAPSE="",aTOD="",bline="",bSN="",bTOD="",adiff="";
			int isn=0;
			aBIBLAPSE="1:22.33";
			if(tm1!=NULL){
				isn=tm1->icurrpulseNumber;
				aSN=isn;
				aline=tm1->electroLine;
				aTOD=tm1->TimeOfDay;
				aBIB=tm1->BIB;
				aRACECODE=tm1->racecode;
				aDSQ=tm1->DSQ;
				aDNF=tm1->DNF;
			}
			if(tm2!=NULL){
				isn=tm2->icurrpulseNumber;
				bSN=isn;
				bline=tm2->electroLine;
				bTOD=tm2->TimeOfDay;
				if(aDSQ.Length()==0&&aDNF.Length()==0){
					aBIB=tm2->BIB;
					aDSQ=tm2->DSQ;
					aDNF=tm2->DNF;
					aBIB=tm2->BIB;
					aRACECODE=tm2->racecode;
				}
			}
			if((tm1!=NULL)&&(tm2!=NULL))
				adiff.sprintf("%0.4f",idiff);
			else
				adiff="";

			p1=dynamic_cast<TPanel*> (p->FindComponent("Panel"+IntToStr(i)));
			if(!p1){
				p1=new TPanel(p);
				p1->Parent = p;
				p1->Name="Panel"+IntToStr(i);
				p1->DoubleBuffered=true;
				p1->Top=i*18;
				p1->ShowCaption=false;
			}

			lRaceCode=dynamic_cast<TLabel*> (p1->FindComponent("tmlRaceCode"));
			if(lRaceCode==NULL){
				lRaceCode=new TLabel(p1);
				lRaceCode->Parent = p1;
				lRaceCode->Name="tmlRaceCode";
				lRaceCode->AutoSize=false;
				lRaceCode->Transparent=false;
				lRaceCode->Font->Size=8;
				lRaceCode->Width=90;
				lRaceCode->Height=18;
				lRaceCode->Top=0;
				lRaceCode->Left=2;
				lRaceCode->Alignment=taLeftJustify;
				lRaceCode->OnMouseDown=lbl->OnMouseDown;
			}
			lRaceCode->Caption=aRACECODE;


			lDNF=dynamic_cast<TLabel*> (p1->FindComponent("tmlDNF"));
			if(lDNF==NULL){
				lDNF=new TLabel(p1);
				lDNF->Parent = p1;
				lDNF->Name="tmlDNF";
				lDNF->AutoSize=false;
				lDNF->Transparent=false;
				lDNF->Font->Size=8;
				lDNF->Width=10;
				lDNF->Height=18;
				lDNF->Top=0;
				lDNF->Left=ileftoffset-6;
				lDNF->Alignment=taCenter;
				lDNF->Caption="F";
				lDNF->OnMouseDown=lbl->OnMouseDown;
			}
			lDNF->Tag=isn;
			lDNF->Color=aDNF=="F"?clRed:clWhite;
			lDNF->Font->Color=lDNF->Color==clRed?clYellow:clBlack;

			lDSQ=dynamic_cast<TLabel*> (p1->FindComponent("tmlDSQ"));
			if(lDSQ==NULL){
				lDSQ=new TLabel(p1);
				lDSQ->Parent = p1;
				lDSQ->Name="tmlDSQ";
				lDSQ->AutoSize=false;
				lDSQ->Transparent=false;
				lDSQ->Font->Size=lDNF->Font->Size;
				lDSQ->Width=lDNF->Width;
				lDSQ->Height=lDNF->Height;
				lDSQ->Top=lDNF->Top;
				lDSQ->Left=lDNF->Left+lDNF->Width+2;
				lDSQ->Alignment=taCenter;
				lDSQ->Caption="Q";
				lDSQ->OnMouseDown=lbl->OnMouseDown;
			}
			lDSQ->Color=aDSQ=="Q"?clRed:clWhite;
			lDSQ->Font->Color=lDSQ->Color==clRed?clYellow:clBlack;
			lDSQ->Tag=isn;


			eBIB=dynamic_cast<TEdit*> (p1->FindComponent("tmeBIB"));
			if(eBIB==NULL){
				eBIB=new TEdit(p1);
				eBIB->Name="tmeBIB";
				eBIB->Parent = p1;
				eBIB->AutoSize=false;
				eBIB->Tag=i;
				eBIB->Font->Size=lDNF->Font->Size;
				eBIB->Width=25;
				eBIB->Height=18;
				eBIB->Top=0;
				eBIB->Left=lDSQ->Left+lDSQ->Width;
				eBIB->Alignment=taCenter;
			}
			eBIB->Text=aBIB;

			lbibLapse=dynamic_cast<TLabel*> (p1->FindComponent("tmlbibLapse"));
			if(lbibLapse==NULL){
				lbibLapse=new TLabel(p1);
				lbibLapse->Parent = p1;
				lbibLapse->Name="tmlbibLapse";
				lbibLapse->AutoSize=false;
				lbibLapse->Transparent=false;
				lbibLapse->Tag=i;
				lbibLapse->Color=clWhite;
				lbibLapse->Font->Size=8;
				lbibLapse->Width=40;
				lbibLapse->Height=18;
				lbibLapse->Top=0;
				lbibLapse->Left=eBIB->Left+eBIB->Width+2;
				lbibLapse->Alignment=taCenter;
			}
			lbibLapse->Caption=aBIBLAPSE;

			lSN=dynamic_cast<TLabel*> (p1->FindComponent("tmlSN"));
			if(lSN==NULL){
				lSN=new TLabel(p1);
				lSN->Parent = p1;
				lSN->Name="tmlSN";
				lSN->AutoSize=false;
				lSN->Transparent=false;
				lSN->Tag=i;
				lSN->Color=clWhite;
				lSN->Font->Size=8;
				lSN->Width=40;
				lSN->Height=18;
				lSN->Top=0;
				lSN->Left=ileftoffset+iwidth+20;////lpulseValue2->Left;
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
				eTime->Font->Size=10;
				eTime->Width=90;
				eTime->Height=lSN->Height;
				eTime->Top=lSN->Top;
				eTime->Left=ileftoffset+2*iwidth+5;
				eTime->Alignment=taLeftJustify;
			}
			eTime->Text=aTOD;

			emTime=dynamic_cast<TLabel*> (p1->FindComponent("tmemTime"));
			if(emTime==NULL){
				emTime=new TLabel(p1);
				emTime->Name="tmemTime";
				emTime->Parent = p1;
				emTime->AutoSize=false;
				emTime->Tag=lSN->Tag;
				emTime->Font->Size=eTime->Font->Size;
				emTime->Width=eTime->Width-30;
				emTime->Height=lSN->Height;
				emTime->Top=lSN->Top;
				emTime->Left=ileftoffset+3*(iwidth+5);
				emTime->Alignment=taRightJustify;
			}
			emTime->Caption=adiff;

			emBTime=dynamic_cast<TEdit*> (p1->FindComponent("tmembTime"));
			if(emBTime==NULL){
				emBTime=new TEdit(p1);
				emBTime->Name="tmembTime";
				emBTime->Parent = p1;
				emBTime->AutoSize=false;
				emBTime->Tag=lSN->Tag;
				emBTime->Font->Size=eTime->Font->Size;
				emBTime->Width=eTime->Width;
				emBTime->Height=lSN->Height;
				emBTime->Top=lSN->Top;
				emBTime->Left=ileftoffset+4*(iwidth+5)-5;
				emBTime->Alignment=taLeftJustify;
			}
			emBTime->Text=bTOD;

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
				lbLine->Left=emBTime->Left+emBTime->Width+5;
				lbLine->Alignment=taCenter;
			}
			lbLine->Caption=bline;



			lSNb=dynamic_cast<TLabel*> (p1->FindComponent("tmlSNb"));
			if(lSNb==NULL){
				lSNb=new TLabel(p1);
				lSNb->Parent = p1;
				lSNb->Name="tmlSNb";
				lSNb->AutoSize=false;
				lSNb->Transparent=false;
				lSNb->Tag=i;
				lSNb->Color=clWhite;
				lSNb->Font->Size=lSN->Font->Size;
				lSNb->Width=lSN->Width;
				lSNb->Height=18;
				lSNb->Top=0;
				lSNb->Left=lbLine->Left+lbLine->Width+2;
				lSNb->Alignment=taCenter;
			}
			lSNb->Caption=bSN;




			p1->Width=ileftoffset+6*(iwidth+5);
///			str="";
///			emTime->Text=str;
//			emTime->OnKeyDown = lSN->OnMouseDown;
		}
		~_viewTK(){
		}
	};
	vector < _viewTK > viewTK;


	AnsiString ApplicationPath,DefaultPath;
	TStringList* Sections;
	TStringList* Values;
	TDateTime  LastStartTime;

public:
	TimeKeeping(){
	AnsiString astr;
	    randomize();
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
		eRaceCode=eBIBonStart=NULL;
		lRaceCode=lBIBonStart=NULL;
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
		if(eRaceCode!=NULL){delete eRaceCode;eRaceCode=NULL;}
		if(eBIBonStart!=NULL){delete eBIBonStart;eBIBonStart=NULL;}
		if(lRaceCode!=NULL){delete lRaceCode;lRaceCode=NULL;}
		if(lBIBonStart!=NULL){delete lBIBonStart;lBIBonStart=NULL;}


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
	void __fastcall SetRaceCode(AnsiString aRaceCode){if(lRaceCode->Color==clLime){eRaceCode->Text=aRaceCode;lRaceCode->Color=clRed;lRaceCode->Font->Color=clYellow;}};
	void __fastcall SetBIBonStart(AnsiString abibonstart){if(lBIBonStart->Color==clLime){eBIBonStart->Text=abibonstart;lBIBonStart->Color=clRed;lBIBonStart->Font->Color=clYellow;}};
	void __fastcall Set_DSQ_DNF(TLabel *lblmoused);
	void __fastcall Set_Red_Lime_Color(TLabel *lblmoused);
	void __fastcall SetLastStartTime(TDateTime lastdatetime){LastStartTime=lastdatetime;};
	AnsiString __fastcall Secs2MSS(int isecs){AnsiString atime;int imin;imin=isecs/60;isecs=isecs%60;atime.sprintf("%0d:%02d",imin,isecs);return atime;};
	AnsiString __fastcall mSecs2MSSHH(int imsecs){
										AnsiString atime,aminsec,amsecs;
										int isecs;
										isecs=imsecs/1000;imsecs%=1000;
										amsecs.sprintf("%03d",imsecs);
										amsecs.SubString(1,2);
										aminsec=Secs2MSS(isecs);
										atime.sprintf("%s.%s",aminsec.c_str(),amsecs.c_str());return atime;
	};
	AnsiString __fastcall uSecs2MSSHH(int iusecs){
										AnsiString atime,aminsec,ausecs;
										int isecs;
										isecs=iusecs/10000;iusecs%=10000;
										ausecs.sprintf("%03d",iusecs);
										ausecs.SubString(1,2);
										aminsec=Secs2MSS(isecs);
										atime.sprintf("%s.%s",aminsec.c_str(),ausecs.c_str());return atime;
	};
	void __fastcall ProcessINI(int iN,AnsiString &atod,AnsiString &atype,AnsiString &arace,AnsiString &abib,AnsiString &adnf,AnsiString &adsq);
};
#endif
//---------------------------------------------------------------------------

