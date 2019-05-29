//---------------------------------------------------------------------------
#pragma hdrstop
#include "RaceViews.h"
#include "System.SysUtils.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern PACKAGE TfUltraSki *fUltraSki;
AnsiString toLatin(AnsiString &srussian);
TIdTCPClient *LiveFIS;
//_____________________________________________________________________________
void __fastcall RaceStartListView::form_resize(TObject *Sender){
int ichecklines=checkLines(),
//	iracersN=this->getRacersN(),
	iracersN=getRacersN(),
	iformH=pRaceSLViews->Height,
	iracerH=iracersN*18,
	iDelta=panel3->Top+iracerH;
int ipaneltop=panel3->Top;
	if(ipaneltop<0){
		panel3->Top=iformH-iracerH-3*18;
	}
	ipaneltop=panel3->Top;
}
//______________________________________________________________________________
int __fastcall RaceStartListView::checkLines(void){
int iHeight=pRaceSLViews->Height,iN,ih,itop;
	ih=viewSL[0].SN->Height;
	itop=viewSL[0].SN->Top+3*ih;
	iN=(iHeight-itop)/ih;
//	pRaceViews->Caption=iN;
	return iN;
 }
//______________________________________________________________________________
void __fastcall RaceStartListView::setRacersColor(_viewSL vsl){
int i=vsl.SN->Tag;
if (i==0) return;
TColor cl1=clActiveCaption,cl2=clWhite,cl;
	vsl.SN->Color=clActiveCaption;
	cl=(i==icurrRacer)?cl1:cl2;
	vsl.SN->Color=cl;
	vsl.FC->Color=cl;
	vsl.FIO->Color=cl;
}
//______________________________________________________________________________
void __fastcall RaceStartListView::form_key_down(TObject *Sender, WORD &Key, TShiftState Shift){
int ik=Key;
int ichecklines=checkLines(),iracersN=this->getRacersN();
int icurH,icurN,
	iformH=pRaceSLViews->Height,//=icurrRacer*18;
	ipaneltop=panel3->Top;
	icurN=icurrRacer;
	switch(Key){
	   case 35:
			icurrRacer=iracersN-1;
			panel3->Top=(18*(ichecklines-iracersN+1));
	   break;
	   case 36:
			icurrRacer=1;
			panel3->Top=0;
	   break;
	   case 40:
			if(icurrRacer<iracersN-1){
				icurH=(icurN+5)*18;
				if((icurH+ipaneltop)>iformH)
					panel3->Top-=18;

				icurrRacer++;
				icurH=icurrRacer*18;
			}
			else icurrRacer=iracersN-1;
	   break;
	   case 38:
			if(icurrRacer>1){
				icurH=(icurrRacer-2)*18;
				if(icurH+ipaneltop<0)
					panel3->Top+=18;
				icurrRacer--;
				icurN=icurrRacer;
			}
			else{
				icurrRacer=1;
				panel3->Top=0;
			}
	   break;
	}
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::showView(int itop,int ileft,int iheight){
TDateTime tdt=Now();
String astr;
	if(iheight==-1){
		pRaceSLViews->Top=itop;
		pRaceSLViews->Left=ileft;
		return;
	}
	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);
	if(pRaceSLViews!=NULL)
		delete pRaceSLViews;
	pRaceSLViews=new TForm(Application);
	pRaceSLViews->Name="Form"+astr;
	pRaceSLViews->Caption=pRaceSLViews->Name;
	pRaceSLViews->DoubleBuffered=true;
	pRaceSLViews->OnKeyDown=form_key_down;
	pRaceSLViews->OnResize=form_resize;
	Locations(pRaceSLViews);
	pRaceSLViews->Show();
	pRaceSLViews->Top=itop;
	pRaceSLViews->Left=ileft;


}
//_____________________________________________________________________________
void __fastcall RaceStartListView::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
  String sname;
	sname=dynamic_cast<TLabel*>(Sender)->Name;
	if(sname=="SL2FIS"){
		lbl->Color=clRed;
        lbl->Repaint();

		int  iCodex=getCodex();//9872;
/*		setCodex(iCodex);
*/
		if (iCodex>0) {

			if (LiveFIS!=NULL){
				if(LiveFIS->Connected())
					LiveFIS->Disconnect();
				delete LiveFIS;
				LiveFIS=NULL;
			}
			if (LiveFIS==NULL) {
				LiveFIS=new TIdTCPClient;
				LiveFIS->Name="LiveFIS";
				LiveFIS->Port=1550;
				LiveFIS->Host="live.fisski.com";
				LiveFIS->Connect();

				setLiveFISpassword("08101957");

				if( LiveFIS->Connected() ){
					String Str=LiveFISRaceclear();
					LiveFIS->IOHandler->WriteLn(Str);
					String Str1="";
					Str1= LiveFIS->IOHandler->ReadLn();
				}

				setCategory("UNI");
				setNation("RUS");
				setPlace("Elizovo");
				AnsiString astr;
			   ///	setEventname("Eventname");
				astr=getEventname();
				astr=toLatin(astr);
				if (astr.Length()==0) {
					astr=" ";
				}
				setEventname(astr);

////				ShowMessage(astr.c_str());
				setSlope("Slope");
				setRacedate(TDate("23.05.2019"));

				if( LiveFIS->Connected() ){

					String Str=LiveFISRaceinfo(L"1");//run 1

					LiveFIS->IOHandler->WriteLn(Str);
					String Str1="";
					Str1= LiveFIS->IOHandler->ReadLn();

				}

				if( LiveFIS->Connected() ){
					String Str1,Str=LiveFISRacestartLIST(1,XMLpath);//"C:\\test\\RPT_Start_911");

					LiveFIS->IOHandler->WriteLn(Str);
					Str1="";
					////Str1= LiveFIS->IOHandler->ReadLn();
				}








			}
		}
		lbl->Color=clLime;

	}
	else{
		ilastcurrRacer=icurrRacer;
		icurrRacer=dynamic_cast<TLabel*>(Sender)->Tag;

		std::for_each(viewSL.begin(),viewSL.end(),setRacersColor
	/*    ///lambda function sample
			[this] (_viewSL vsl) {
				TColor cl1=clActiveCaption,cl2=clWhite,cl;
				int i=vsl.SN->Tag;
				vsl.SN->Color=clActiveCaption;
				cl=(i==icurrRacer)?cl1:cl2;
				vsl.SN->Color=cl;
				vsl.FC->Color=cl;
				vsl.FIO->Color=cl;
			}
	*/
		);
	}
}//end of proc
//_____________________________________________________________________________
void __fastcall RaceStartListView::Locations(TForm* form){
String str;
_viewSL *vsl;
int iN;

	if(!viewSL.empty()) viewSL.clear();
	iN=this->getRacersN();

	panel1= new TPanel(form);
	panel1->Parent = form;
	panel1->Name="P1"+form->Name;
	panel1->Font->Size=12;
	panel1->Alignment=taLeftJustify;
	panel1->VerticalAlignment=taAlignTop;
	panel1->Top=3;
	panel1->Left=3;
	panel1->Width=form->Width-panel1->Left;
	panel1->Visible=true;
	int ccodex=this->getCodex();
	str.sprintf(L"RaceList%d",this->getCodex());
	panel1->Caption="";//str;

/*	image=new TImage(panel1);
	image->Parent = panel1;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
*/
	lbl= new TLabel(panel1);
	lbl->Parent=panel1;
	lbl->Font->Size=12;
	lbl->Top=0;
	lbl->Left=3;
	lbl->Height=18;
	lbl->Top=0;
	lbl->Name="SL2FIS";
	lbl->Caption="Нажмите для записи в LiveTiming FIS";
	lbl->Transparent=false;
	lbl->Color=clLime;
	lbl->OnMouseDown=mouse_down;



	panel2= new TPanel(panel1);
	panel2->Parent = panel1;
	panel2->Name="P2"+form->Name;
	panel2->Font->Size=12;
	panel2->Alignment=taLeftJustify;
	panel2->VerticalAlignment=taAlignTop;
	panel2->Top=18*2;
	panel2->Left=3;
	panel2->Width=panel1->Width-panel2->Left;
	panel2->Visible=true;
	panel2->Caption="";

	panel3= new TPanel(panel2);
	panel3->Parent = panel2;
	panel3->Name="P3"+form->Name;
	panel3->Font->Size=12;
	panel3->Alignment=taLeftJustify;
	panel3->VerticalAlignment=taAlignTop;
	panel3->Top=0;
	panel3->Left=3;
	panel3->Width=panel2->Width-panel3->Left;
	panel3->Visible=true;
	panel3->Caption="";


	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewSL(i==0?panel1:panel3,i,this,lbl);
		viewSL.push_back(*vsl);
		if(sz!=viewSL.capacity()){
			sz=viewSL.capacity();
		}
	}
	///String *sss=(String*)viewSL.data();
	panel3->Height=(iN-1)*vsl->FIO->Height;
	panel2->Height=panel3->Height;
	panel1->Height=panel2->Height+2;

 /*
	tln = new TShape(stop_panel);
	tln->Parent = stop_panel;
	tln->Top= stop_panel_time_label->Top+stop_panel_time_label->Height;
	tln->Left= 1;
	tln->Height= 1;
	tln->Width= stop_panel->Width;
	tln->Visible=true;


	image=new TImage(stop_panel);
	image->Parent = stop_panel;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
	image->Picture=F366->Image1->Picture;
*/

}//end of proc


//------------------------------------------------------------------------------
void __fastcall Races::showRaces(){
TDateTime tdt=Now();
String astr;

	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);
	pRaceViews->Name="RacesForm"+astr;
	pRaceViews->Caption="";//pRaceViews->Name;
	pRaceViews->DoubleBuffered=true;
	pRaceViews->OnKeyDown=form_key_down;
	pRaceViews->OnResize=form_resize;

	Locations(pRaceViews);
	pRaceViews->Show();
	pRaceViews->Top=0;
	pRaceViews->Left=0;
}
//------------------------------------------------------------------------------
void __fastcall Races::showInfo(){
TDateTime tdt=Now();
String astr;

	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);
	pRaceInfo->Name="RacesINFO"+astr;
	pRaceInfo->Caption=pRaceInfo->Name;
	pRaceInfo->DoubleBuffered=true;
	pRaceInfo->OnKeyDown=form_key_down_info;
	pRaceInfo->OnResize=form_resize;

	LocationsInfo(pRaceInfo);
	pRaceInfo->Show();
	pRaceInfo->Top=pRaceViews->Top;
	pRaceInfo->Left=pRaceViews->Top+pRaceViews->Width;
	int itop,ileft;
	itop=pRaceInfo->Top;
	ileft=pRaceInfo->Left+pRaceInfo->Width;
	showView(itop,ileft,-1);
}
//------------------------------------------------------------------------------
void __fastcall Races::showStartList(){
TDateTime tdt=Now();
String astr;

	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);
	pRaceStartList->Name="RacesSL"+astr;
	pRaceStartList->Caption=pRaceStartList->Name;
	pRaceStartList->DoubleBuffered=true;
	pRaceStartList->OnKeyDown=form_key_down_startlist;
	pRaceStartList->OnResize=form_resize;

	LocationsStartList(pRaceStartList);
	pRaceStartList->Show();
}
//------------------------------------------------------------------------------
void __fastcall Races::Locations(TForm* form){
String str;
_viewRL *vsl;
int iN;

	if(!viewSL.empty()){
		viewSL.clear();

	}
	if(eCompetition!=NULL)	delete eCompetition,eCompetition=NULL;
	if(lbl!=NULL)	delete lbl,lbl=NULL;
	if(panel3!=NULL)	delete panel3,panel3=NULL;
	if(panel2!=NULL)	delete panel2,panel2=NULL;
	if(panel1!=NULL)	delete panel1,panel1=NULL;
	iN=this->getRacesN();

	panel1= new TPanel(form);
	panel1->Parent = form;
	panel1->Name="P1";
	panel1->Font->Size=12;
	panel1->Alignment=taLeftJustify;
	panel1->VerticalAlignment=taAlignTop;
	panel1->Top=3;
	panel1->Left=2;
	panel1->Width=form->Width-panel1->Left;
	panel1->Visible=true;
///	int ccodex=this->getCodex();
	str.sprintf(L"Races");
	panel1->Caption=str;

	panel2= new TPanel(panel1);
	panel2->Parent = panel1;
	panel2->Name="P2";
	panel2->Font->Size=12;
	panel2->Alignment=taLeftJustify;
	panel2->VerticalAlignment=taAlignTop;
	panel2->Top=SNHeight;
	panel2->Left=2;
	panel2->Width=panel1->Width-panel2->Left;
	panel2->Visible=true;
	panel2->Caption="";

	lbl= new TLabel(panel2);
	lbl->Parent = panel2;
	lbl->Name="Label"+form->Name;
	lbl->AutoSize=false;
	lbl->Alignment=taCenter;
	lbl->Transparent=false;
	lbl->Top=SNHeight;
	lbl->Left=3;
	lbl->Width=SNWidth;
	lbl->Visible=true;
	lbl->Caption="+";

	lbl->OnMouseDown=mouse_down;
	lbl->OnDblClick=mouse_DblClick;

	eCompetition=new TEdit(panel2);
	eCompetition->Parent = panel2;
	eCompetition->Name="P2";
	eCompetition->Font->Size=12;
	eCompetition->Top=SNHeight;
	eCompetition->Left=34;
	eCompetition->Width=CodexWidth;
	eCompetition->Visible=true;
	str=Now().FormatString("yyyymmdd01");
	eCompetition->Text=str;


	panel3= new TPanel(panel2);
	panel3->Parent = panel2;
	panel3->Name="P3";
	panel3->Font->Size=12;
	panel3->Alignment=taLeftJustify;
	panel3->VerticalAlignment=taAlignTop;
	panel3->Top=18*2+8;
	panel3->Left=3;
	panel3->Width=panel2->Width-panel3->Left;
	panel3->Visible=true;
	panel3->Caption="";


	IniUltraAlpSki=new TIniFile(ApplicationPath);
	iN=IniUltraAlpSki->ReadInteger("Competitions","Number",0);
	RacePack rp;
	RacesList.clear();
	for (int ii = 1; ii <= iN; ii++) {
		String astr=IniUltraAlpSki->ReadString("Competition "+String(ii),"ID",0);
		rp.path="";
		rp.Codex=astr;
		RacesList.push_back(rp);
	}
	delete  IniUltraAlpSki;IniUltraAlpSki=NULL;

	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewRL(panel3,i,this,lbl);
		viewSL.push_back(*vsl);
		if(sz!=viewSL.capacity()){
			sz=viewSL.capacity();
		}
	}
	panel3->Height=48+(iN+1)*18;
	panel2->Height=panel3->Height;
	panel1->Height=panel2->Height+2;
	panel3->Color=clGradientActiveCaption;
	panel2->Color=clAqua;
	panel1->Color=clLime;
	panel1->ShowCaption=true;panel1->Caption="Регистрация";panel1->Font->Size=10;
	panel2->ShowCaption=true;panel2->Caption="соревнований:";panel2->Font->Size=panel1->Font->Size;
	panel3->ShowCaption=true;panel3->Caption="3333333";panel3->Font->Size=panel1->Font->Size;
	panel3->Width=SNWidth+CodexWidth+3*2;
	panel2->Width=panel3->Width+2*panel3->Left;
	panel1->Width=panel2->Width+2*panel2->Left;
	form->Width=panel1->Width+2*panel1->Left+15;
	form->Height=panel1->Height+40;
	form->Left=0;
	form->Top=0;

	TBorderIcons tempBI = form->BorderIcons;
//	tempBI >> biSystemMenu;
	tempBI >> biMinimize;
	tempBI >> biMaximize;
	tempBI >> biHelp;
	form->BorderIcons = tempBI;

 /*
	tln = new TShape(stop_panel);
	tln->Parent = stop_panel;
	tln->Top= stop_panel_time_label->Top+stop_panel_time_label->Height;
	tln->Left= 1;
	tln->Height= 1;
	tln->Width= stop_panel->Width;
	tln->Visible=true;


	image=new TImage(stop_panel);
	image->Parent = stop_panel;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
	image->Picture=F366->Image1->Picture;
*/

}//end of proc
//------------------------------------------------------------------------------
void __fastcall Races::LocationsInfo(TForm* form){
String str;
_viewRL *vsl;
int iN;
	if(lID==NULL){
		lID=new TLabel(form);
		lID->Parent = form;
		lID->Name="lID";
		lID->Font->Size=10;
		lID->Top=6;
		lID->Left=3;
		lID->Width=CodexWidth;
		lID->Transparent=false;
		lID->Visible=true;
		lID->Caption="ID соревнования";
		lID->OnMouseDown=mouse_down;

		grpGender = new TRadioGroup(form);
		grpGender->Parent = form;
		grpGender->Tag = 2;
		grpGender->Items->Add("Men");
		grpGender->Items->Add("Ladies");
		grpGender->Items->Add("Mixed");
		grpGender->Left = lID->Left+lID->Width+20;
		grpGender->Top = 50;
		grpGender->Height = 40;
		grpGender->Width = 224;
		grpGender->Caption = "Пол участвующих";
		grpGender->Columns=3;
		grpGender->ItemIndex = -1;
		grpGender->OnClick=radio_click;

		grpDiscipline = new TRadioGroup(form);
		grpDiscipline->Parent = form;
		grpDiscipline->Tag = 1;
		grpDiscipline->Items->Add("DH");
		grpDiscipline->Items->Add("SL");
		grpDiscipline->Items->Add("SG");
		grpDiscipline->Items->Add("GS");
		grpDiscipline->Items->Add("AC");
		grpDiscipline->Items->Add("TE");
		grpDiscipline->Items->Add("KOS");
		grpDiscipline->Items->Add("KOG");
		grpDiscipline->Items->Add("PGS");
		grpDiscipline->Items->Add("PSL");
		grpDiscipline->Left = lID->Left+lID->Width+20;
		grpDiscipline->Top = 6;
		grpDiscipline->Height = 40;
		grpDiscipline->Width = 430;
		grpDiscipline->Caption = "Альпийская дисциплина";
		grpDiscipline->Columns=10;
		grpDiscipline->ItemIndex = -1;
		grpDiscipline->OnClick=radio_click;

		lDate= new TLabel(form);
		lDate->Parent = form;
		lDate->Name="LDate"+form->Name;
		lDate->AutoSize=true;
		lDate->Alignment=taCenter;
		lDate->Transparent=false;
		lDate->Top=lID->Top+lID->Height+5;
		lDate->Left=lID->Left;
		lDate->Visible=true;
		lDate->Caption="Дата соревнования";


		eDate=new TMaskEdit(form);
		eDate->EditMask="!99/99/0000;1;_";
		eDate->Parent = form;
		eDate->Name="eDate";
		eDate->Font->Size=10;
		eDate->Top=lDate->Top+lDate->Height+2;
		eDate->Left=lID->Left;
		eDate->Width=70;
		eDate->Visible=true;
		eDate->Text="";
		eDate->OnKeyDown=maskedit_key_down_info;

		lFISCodex= new TLabel(form);
		lFISCodex->Parent = form;
		lFISCodex->Name="LFISCodex"+form->Name;
		lFISCodex->AutoSize=true;
		lFISCodex->Alignment=taCenter;
		lFISCodex->Transparent=false;
		lFISCodex->Top=eDate->Top+eDate->Height+2;
		lFISCodex->Left=lID->Left;
		lFISCodex->Visible=true;
		lFISCodex->Caption="ФИС кодекс";


		eFISCodex=new TEdit(form);
		eFISCodex->Parent = form;
		eFISCodex->Name="eFISCodex";
		eFISCodex->Font->Size=10;
		eFISCodex->Top=lFISCodex->Top+lFISCodex->Height+2;
		eFISCodex->Left=lID->Left;
		eFISCodex->Width=35;
		eFISCodex->Visible=true;
		eFISCodex->Text="";
		eFISCodex->OnKeyDown=edit_key_down_info;

		lInfoName= new TLabel(form);
		lInfoName->Parent = form;
		lInfoName->Name="lInfoName"+form->Name;
		lInfoName->AutoSize=true;
		lInfoName->Alignment=taCenter;
		lInfoName->Transparent=false;
		lInfoName->Top=eFISCodex->Top+eFISCodex->Height+5;
		lInfoName->Left=lID->Left;
		lInfoName->Visible=true;
		lInfoName->Caption="Название соревнования";

		eInfoName=new TEdit(form);
		eInfoName->Parent = form;
		eInfoName->Name="eInfoName"+form->Name;
		eInfoName->Font->Size=10;
		eInfoName->Top=lInfoName->Top+lInfoName->Height+2;
		eInfoName->Left=lID->Left;
		eInfoName->Width=550;
		eInfoName->Visible=true;
		eInfoName->Text="";

		lSLimport=new TLabel(form);
		lSLimport->Parent = form;
		lSLimport->Name="lSLimport";
		lSLimport->AutoSize=true;
		lSLimport->Font->Size=10;
		lSLimport->Top=eInfoName->Top+eInfoName->Height+5;
		lSLimport->Left=eInfoName->Left;
		lSLimport->Transparent=false;
		lSLimport->Color=clLime;
		lSLimport->Visible=true;
		lSLimport->Caption="Импорт стартового списка ";
		lSLimport->OnMouseDown=mouse_down;

		lSLimportN=new TLabel(form);
		lSLimportN->Parent = form;
		lSLimportN->Name="lSLimportN";
		lSLimport->AutoSize=false;
		lSLimportN->Font->Size=10;
		lSLimportN->Top=lSLimport->Top+lSLimport->Height+2;
		lSLimportN->Left=lSLimport->Left;
		lSLimportN->Width=eInfoName->Width;
		lSLimportN->Transparent=false;
		lSLimportN->Visible=true;
		lSLimportN->Caption="";

		form->Width=eInfoName->Left+eInfoName->Width+20;
		form->Height=lSLimportN->Top+lSLimportN->Height+45;

		TBorderIcons tempBI = form->BorderIcons;
	//	tempBI >> biSystemMenu;
		tempBI >> biMinimize;
		tempBI >> biMaximize;
		tempBI >> biHelp;
		form->BorderIcons = tempBI;
	}
	icurrRace=0;
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
	FillRaceDescription();



}//end of proc
//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall Races::LocationsStartList(TForm* form){
String str;
_viewRL *vsl;
int iN;
form->Width=600;
#if 0
	if(!viewSL.empty()){
		viewSL.clear();

	}
	if(eCompetition!=NULL)	delete eCompetition,eCompetition=NULL;
	if(lbl!=NULL)	delete lbl,lbl=NULL;
	if(panel3!=NULL)	delete panel3,panel3=NULL;
	if(panel2!=NULL)	delete panel2,panel2=NULL;
	if(panel1!=NULL)	delete panel1,panel1=NULL;
	iN=this->getRacesN();

	panel1= new TPanel(form);
	panel1->Parent = form;
	panel1->Name="P1"+form->Name;
	panel1->Font->Size=12;
	panel1->Alignment=taLeftJustify;
	panel1->VerticalAlignment=taAlignTop;
	panel1->Top=3;
	panel1->Left=2;
	panel1->Visible=true;

	str.sprintf(L"Races");
	panel1->Caption=str;

	panel2= new TPanel(panel1);
	panel2->Parent = panel1;
	panel2->Name="P2"+form->Name;
	panel2->Font->Size=12;
	panel2->Alignment=taLeftJustify;
	panel2->VerticalAlignment=taAlignTop;
	panel2->Top=SNHeight;
	panel2->Left=2;
	panel2->Visible=true;
	panel2->Caption="";

	lbl= new TLabel(panel2);
	lbl->Parent = panel2;
	lbl->Name="Label"+form->Name;
	lbl->AutoSize=false;
	lbl->Alignment=taCenter;
	lbl->Transparent=false;
	lbl->Top=SNHeight;
	lbl->Left=3;
	lbl->Width=SNWidth;
	lbl->Visible=true;
	lbl->Caption="+";

	lbl->OnMouseDown=mouse_down;
	lbl->OnDblClick=mouse_DblClick;

	eCompetition=new TEdit(panel2);
	eCompetition->Parent = panel2;
	eCompetition->Name="P2"+form->Name;
	eCompetition->Font->Size=12;
	eCompetition->Top=SNHeight;
	eCompetition->Left=34;
	eCompetition->Width=CodexWidth;
	eCompetition->Visible=true;
	str=Now().FormatString("yyyymmdd01");
	eCompetition->Text=str;


	panel3= new TPanel(panel2);
	panel3->Parent = panel2;
	panel3->Name="P3"+form->Name;
	panel3->Font->Size=12;
	panel3->Alignment=taLeftJustify;
	panel3->VerticalAlignment=taAlignTop;
	panel3->Top=18*2+8;
	panel3->Left=3;
	panel3->Width=panel2->Width-panel3->Left;
	panel3->Visible=true;
	panel3->Caption="";


	String astr=Application->ExeName;
	astr=StringReplace(astr,".\\","",TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
	astr=ChangeFileExt( astr, ".INI" );
	IniUltraAlpSki=new TIniFile(astr);
	iN=IniUltraAlpSki->ReadInteger("Competitions","Number",0);
	RacePack rp;
	RacesList.clear();
	for (int ii = 1; ii <= iN; ii++) {
		astr=IniUltraAlpSki->ReadString("Competition "+String(ii),"ID",0);
		rp.path="";
		rp.Codex=astr;
		RacesList.push_back(rp);
	}
	delete  IniUltraAlpSki;

	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewRL(panel3,i,this,lbl);
		viewSL.push_back(*vsl);
		if(sz!=viewSL.capacity()){
			sz=viewSL.capacity();
		}
	}
	panel3->Height=48+(iN+1)*18;
	panel2->Height=panel3->Height;
	panel1->Height=panel2->Height+2;
	panel3->Color=clGradientActiveCaption;
	panel2->Color=clAqua;
	panel1->Color=clLime;
	panel1->ShowCaption=true;panel1->Caption="Регистрация";panel1->Font->Size=10;
	panel2->ShowCaption=true;panel2->Caption="соревнований:";panel2->Font->Size=panel1->Font->Size;
	panel3->ShowCaption=true;panel3->Caption="3333333";panel3->Font->Size=panel1->Font->Size;
	panel3->Width=SNWidth+CodexWidth+3*2;
	panel2->Width=panel3->Width+2*panel3->Left;
	panel1->Width=panel2->Width+2*panel2->Left;
	form->Width=panel1->Width+2*panel1->Left+15;
	form->Height=panel1->Height+40;

	TBorderIcons tempBI = form->BorderIcons;
//	tempBI >> biSystemMenu;
	tempBI >> biMinimize;
	tempBI >> biMaximize;
	tempBI >> biHelp;
	form->BorderIcons = tempBI;

	int itop=pRaceInfo->Top,ileft=pRaceInfo->Left+pRaceInfo->Width;
	form->Top=itop;
	form->Left=ileft;
	form->Height=pRaceInfo->Height;



 /*
	tln = new TShape(stop_panel);
	tln->Parent = stop_panel;
	tln->Top= stop_panel_time_label->Top+stop_panel_time_label->Height;
	tln->Left= 1;
	tln->Height= 1;
	tln->Width= stop_panel->Width;
	tln->Visible=true;


	image=new TImage(stop_panel);
	image->Parent = stop_panel;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
	image->Picture=F366->Image1->Picture;
*/
#endif
}//end of proc
//-----------------------------------------------------------------------------


void __fastcall Races::form_key_down(TObject *Sender, WORD &Key, TShiftState Shift){
int ik=Key,iflag=0;
int ichecklines=checkLines(),iracersN=this->getRacesN();
int icurH,icurN,
	iformH=pRaceViews->Height,
	ipaneltop=panel3->Top;
	icurN=icurrRace;
	switch(Key){
	   case 35:
			icurrRace=iracersN;
			panel3->Top=(18*(ichecklines-iracersN+1));
	   break;
	   case 36://home
			icurrRace=0;
			panel3->Top=18*2+8;
	   break;
	   case 39://right
	   break;
	   case 40://down
			if(icurrRace<iracersN-1){
				icurH=(icurN+5)*18;
				if((icurH+ipaneltop)>iformH)
					panel3->Top-=18;

				icurrRace++;
				icurH=icurrRace*18;
			}
			else icurrRace=iracersN-1;
			Key=0;
	   break;
	   case 38://up
			if(icurrRace>0){
				icurH=icurrRace*18;
				if(icurH+ipaneltop<0)
					panel3->Top+=18;
				icurrRace--;
				icurN=icurrRace;
			}
			Key=0;
	   break;
	   default:
		   iflag=1;
	}
	if(iflag!=1)
		std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
	String sname=viewSL[icurrRace].RCodex->Caption;
	pRaceStartList->Caption="Стартовый список соревнования "+sname;
	pRaceInfo->Caption="Описание соревнования "+sname;

	FillRaceDescription();
}
//------------------------------------------------------------------------------
void __fastcall Races::SaveInfo2INI(void){
	String 	astr,sN,sDateINI,sCodexINI,sEVENT,sSLFile;
	sN=viewSL[icurrRace].SN->Caption;
	sCodexINI=eFISCodex->Text;
	sDateINI=eDate->Text;
	sEVENT=eInfoName->Text;
	sSLFile=lSLimportN->Caption;

	IniUltraAlpSki=new TIniFile(ApplicationPath);
	IniUltraAlpSki->WriteString("Competition "+sN,"DATE",sDateINI);
	IniUltraAlpSki->WriteString("Competition "+sN,"FISCODEX",sCodexINI);
	IniUltraAlpSki->WriteString("Competition "+sN,"EVENT",sEVENT);
	IniUltraAlpSki->WriteString("Competition "+sN,"SLFILE",sSLFile);
	IniUltraAlpSki->WriteString("Competition "+sN,"DISCIPLINE",getDiscipline());
	IniUltraAlpSki->WriteString("Competition "+sN,"GENDER",getGender());

	delete  IniUltraAlpSki;IniUltraAlpSki=NULL;
	lID->Color=clLime;
}
//----------------------------------------------------------------------------
void __fastcall Races::FillRaceDescription(void){
	String 	astr,sDateINI,sCodexINI,sEVENT,sSLFile,
			sname=viewSL[icurrRace].RCodex->Caption,
			sN=viewSL[icurrRace].SN->Caption;
	lID->Caption=sname;
	lID->Color=clLime;

	IniUltraAlpSki=new TIniFile(ApplicationPath);
	astr=IniUltraAlpSki->ReadString("Competition "+sN,"ID","");
	sDateINI=IniUltraAlpSki->ReadString("Competition "+sN,"DATE","");
	sCodexINI=IniUltraAlpSki->ReadString("Competition "+sN,"FISCODEX","");

	try{
		int icodex=StrToInt(sCodexINI);
		setCodex(icodex);
	}
	catch(...){
	}

	sEVENT=IniUltraAlpSki->ReadString("Competition "+sN,"EVENT","");
	setEventname(sEVENT);
	sSLFile=IniUltraAlpSki->ReadString("Competition "+sN,"SLFILE","");
	astr=IniUltraAlpSki->ReadString("Competition "+sN,"DISCIPLINE","");
	setDiscipline(astr);
	grpDiscipline->ItemIndex=-1;
	if(astr=="DH")grpDiscipline->ItemIndex=0;
	if(astr=="SL")grpDiscipline->ItemIndex=1;
	if(astr=="SG")grpDiscipline->ItemIndex=2;
	if(astr=="GS")grpDiscipline->ItemIndex=3;
	if(astr=="AC")grpDiscipline->ItemIndex=4;
	if(astr=="TE")grpDiscipline->ItemIndex=5;
	if(astr=="KOS")grpDiscipline->ItemIndex=6;
	if(astr=="KOG")grpDiscipline->ItemIndex=7;
	if(astr=="PGS")grpDiscipline->ItemIndex=8;
	if(astr=="PSL")grpDiscipline->ItemIndex=9;

	grpGender->ItemIndex=-1;
	astr=IniUltraAlpSki->ReadString("Competition "+sN,"GENDER","");
	setGender(astr);
	if(astr=="M")grpGender->ItemIndex=0;
	if(astr=="L")grpGender->ItemIndex=1;
	if(astr=="T")grpGender->ItemIndex=2;

	delete  IniUltraAlpSki;IniUltraAlpSki=NULL;

	eDate->Text=sDateINI;
	eFISCodex->Text=sCodexINI;
	eInfoName->Text=sEVENT;
	lSLimportN->Caption=sSLFile;

	AnsiString filename;
	AnsiString spath,sID;
	sID=lID->Caption;
	spath=ExtractFilePath(ApplicationPath)+sID+"\\SL"+sID+".xml";
	bool flag=FileExists(spath);
	if(flag){
		loadXML(spath);
		setXMLpath(spath);
		int itop=pRaceInfo->Top,ileft=pRaceInfo->Left+pRaceInfo->Width;
		showView(itop,ileft,400);
		pRaceViews->Show();
		showView(itop,ileft,-1);

	}
	else{
		CleaSLForm();
	}

}
//------------------------------------------------------------------------------
void __fastcall Races::maskedit_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift){
AnsiString astr;
TMaskEdit *edt=dynamic_cast<TMaskEdit*>(Sender);
astr=edt->Name;
String sEdit=edt->Text;
bool flag;
	TDate td;
	if(sEdit.Length()<10)
		flag=false;
	if(flag){
		flag=TryStrToDate(sEdit, /* out */ td);
		if(flag)
			edt->Text=td.FormatString("dd.mm.yyyy");
	}
	edt->Color=flag?clLime:clRed;
}
//------------------------------------------------------------------------------
void __fastcall Races::edit_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift){
AnsiString astr;
TEdit *edt=dynamic_cast<TEdit*>(Sender);
astr=edt->Name;
	if(astr=="eFISCodex"){
	try{
		int icodex=getCodexInRAM();
		if (icodex>0) {
			setCodex(icodex);
		}
	}
	catch(...){
	}
	}
	lID->Color=clRed;
}

void __fastcall Races::form_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift){
int i=0;
AnsiString astr=Sender->ClassName();///edt->Name;
if(astr=="TForm")return;
	lID->Color=clRed;

}
void __fastcall Races::form_key_down_startlist(TObject *Sender, WORD &Key, TShiftState Shift){
}
//_____________________________________________________________________________
//_____________________________________________________________________________
void __fastcall Races::form_resize(TObject *Sender){
int ichecklines=checkLines(),
	iracersN=getRacesN(),
	iformH=pRaceViews->Height,
	iracerH=iracersN*18,
	iDelta=panel3->Top+iracerH;
int ipaneltop=panel3->Top;
	if(ipaneltop<0){
		panel3->Top=iformH-iracerH-3*18;
	}
	ipaneltop=panel3->Top;
}
//______________________________________________________________________________
int __fastcall Races::checkLines(void){
int iHeight=pRaceViews->Height,iN,ih,itop;
	ih=SNHeight;
	itop=SNHeight+3*ih;
	iN=(iHeight-itop)/ih;
	return iN;
 }
//______________________________________________________________________________
void __fastcall Races::setRacersColor(_viewRL vsl){
int i=vsl.SN->Tag;
	if (i>=0){
	TColor cl1=clActiveCaption,cl2=clWhite,cl;
		vsl.SN->Color=clActiveCaption;
		cl=(i==icurrRace)?cl1:cl2;
		vsl.SN->Color=cl;
		vsl.RCodex->Color=cl;
	}
}
//______________________________________________________________________________
void __fastcall Races::radio_click(TObject *Sender){
int i=0;
TRadioGroup *rg=dynamic_cast<TRadioGroup*>(Sender);
String str=rg->Caption,igtag;
  i=rg->ItemIndex;
  str=rg->Items->Strings[i];
  igtag=rg->Tag;
  if (igtag=="1") {
	setDiscipline(str);
  }
  if (igtag=="2") {
		if (str=="Men")str="M";
		if (str=="Ladies")str="L";
		if (str=="Mixed")str="T";
		setGender(str);
  }

  lID->Color=clRed;
}
void __fastcall Races::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
  TLabel *lblmoused=dynamic_cast<TLabel*>(Sender);
	ilastcurrRace=icurrRace;
	String 	str=lblmoused->Caption,
			sname=lblmoused->Name;
	if(sname=="lID"){
		String sCodexINI=eFISCodex->Text;
		SaveInfo2INI();

		int  iCodex;
		try{
			iCodex=StrToFloat(sCodexINI);
			setCodex(iCodex);
			iCodex=getCodex();
		}
		catch (...){}
		return;
	}
	if(sname=="lSLimport"){
		StartListFileDialog->Filter = "Файлы CSV|*.csv";
		sname=lSLimportN->Caption;
		StartListFileDialog->InitialDir=sname;
		AnsiString astr=ExtractFileName(sname);
		StartListFileDialog->FileName=astr;
		ClearXMLpath();//="";
		if (StartListFileDialog->Execute()){
		  sname=StartListFileDialog->FileName;
		  if(sname.Pos(".csv")>0)
			  lSLimportN->Caption=sname;
			  setImportedFileName(sname);
			  if(sname.Length()>0)
				  LoadFromCSV(sname);
				  AnsiString spath,sname1;
				  sname1=lID->Caption;
				  spath=ExtractFilePath(ApplicationPath)+"\\"+sname1;
				  CreateDirectoryA(spath.c_str(),NULL);
				  setXMLpath(spath+"\\SL"+sname1+".xml");
				  saveXML(getXMLpath());
				  showView(pRaceInfo->Top,pRaceInfo->Left+pRaceInfo->Width,pRaceInfo->Height);

		}
		return;
	}
	if (str=="+") {
		RacePack rp;
		rp.Codex=eCompetition->Text;
		vector < RacePack > *rpp;

		int ii=RacesList.size(),irc=1;
		for(int ij=0;ij<ii;++ij){
			if (RacesList[ij].Codex  == rp.Codex) {
				irc=0;
				break;
			}
		}
		if (irc) {
			RacesList.push_back(rp);
			sort(RacesList.begin(),RacesList.end(),[](const RacePack  &a,const RacePack &b){return a.Codex >b.Codex;});

			int number_Of_competitions=0;

			IniUltraAlpSki=new TIniFile(ApplicationPath);
			for (RacePack  &a:RacesList) {
				++number_Of_competitions;
				String astr=a.Codex;
				IniUltraAlpSki->WriteString("Competition "+String(number_Of_competitions),"ID",astr);
			}
			IniUltraAlpSki->WriteInteger("Competitions","Number",number_Of_competitions);
			delete  IniUltraAlpSki;IniUltraAlpSki=NULL;

			showRaces();
			eCompetition->Text=rp.Codex;
		}
	}
	else{
		icurrRace=dynamic_cast<TLabel*>(Sender)->Tag;
		std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
		FillRaceDescription();

	}
}//end of proc
//------------------------------------------------------------------------------
void __fastcall Races::mouse_DblClick(TObject *Sender)
{
int i;
}
//_____________________________________________________________________________
void Races::LoadFromPath(String path){
	RacePack rp;
	TSearchRec sr;
	String spath=path+"*.usr";
	RacesList.clear();
	if (FindFirst(spath, faAnyFile | faDirectory, sr) == 0){
		rp.path=path+sr.Name;
		int  ipos=sr.Name.Pos(".usr");
		rp.Codex=sr.Name.SubString(1,ipos-1);
		RacesList.push_back(rp);

		while (FindNext(sr) == 0){
			rp.path=path+sr.Name;
			ipos=sr.Name.Pos(".usr");
			rp.Codex=sr.Name.SubString(1,ipos-1);
			RacesList.push_back(rp);
		}
	}

	FindClose(sr);
};



