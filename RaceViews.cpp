//---------------------------------------------------------------------------
#pragma hdrstop
#include "RaceViews.h"
#include "TimingDevice.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib,"shell32")


extern PACKAGE TfUltraSki *fUltraSki;
extern TimeKeeping *tk;
extern Races *rcs;
TIdTCPClient *LiveFIS;

//=============================================================================
void __fastcall SetClipBoard(AnsiString aboard){
	const char* output = aboard.c_str();
	const size_t len = strlen(output) + 1;
	HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}
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
	return iN;
 }
//______________________________________________________________________________
void __fastcall RaceStartListView::setRacersColor(_viewSL vsl){
int i=vsl.SN->Tag;
if (i==0) return;
TColor cl1=clActiveCaption,cl2=clWhite,cl;
	vsl.SN->Color=clActiveCaption;
	if(i==icurrRacer){
		if(tk)
			tk->SetBIBonStart(vsl.SN->Caption);

		cl=cl1;
	}
	else
		cl=cl2;
///	cl=(i==icurrRacer)?cl1:cl2;
	vsl.T2->Color=cl;
	vsl.T1->Color=cl;
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
	   case 35://end
			icurrRacer=iracersN-1;
			panel3->Top=(18*(ichecklines-iracersN+1));
	   break;
	   case 36: //home
			icurrRacer=1;
			panel3->Top=0;
	   break;
	   case 40://down
			if(icurrRacer<iracersN-1){
				icurH=(icurN+5)*18;
				if((icurH+ipaneltop+18)>iformH)
					panel3->Top-=18;

				icurrRacer++;
				icurH=icurrRacer*18;
			}
			else icurrRacer=iracersN-1;
	   break;
	   case 38://up
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
	for(auto i:viewSL)setRacersColor(i);
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::showView(int itop,int ileft,int iheight){
TDateTime tdt=Now();
String astr;
	if(pRaceSLViews!=NULL&&iheight==-1){
		pRaceSLViews->Top=itop;
		pRaceSLViews->Left=ileft;
		return;
	}

	if(pRaceSLViews!=NULL){
		Locations(pRaceSLViews);

		pRaceSLViews->Show();
		pRaceSLViews->Top=itop;
		pRaceSLViews->Left=ileft;
	}
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::mouse_DblClick(TObject *Sender){
int i;
AnsiString astr;
i=1;
	astr=viewSL[icurrRacer].SN->Caption;
	tk->ForceBIBonStart(astr);
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::SetCurRacer(int inewcurracer){
int isteps;
int ichecklines=checkLines(),iracersN=getRacersN();
    if(icurrRacer<0)icurrRacer=0;
int icurH,icurN,
	iformH=pRaceSLViews->Height,
	ipaneltop=panel3->Top;
	icurN=icurrRacer;

	ilastcurrRacer=icurrRacer;

	if(icurN==inewcurracer)return;
	if(icurN>inewcurracer){//up
		panel3->Top=-inewcurracer*18+(iformH-18*5-5)-(ichecklines-1)*18;
		icurrRacer=inewcurracer;
	}
	else{
	   isteps=inewcurracer-icurN+1;//down
		if(inewcurracer>iracersN-1)
			inewcurracer=iracersN-1;
		if(inewcurracer<=iracersN-1){
			if((/*60*/18*5+ipaneltop+inewcurracer*18)>=iformH){
				panel3->Top=-inewcurracer*18+(iformH-18*5-5);
			}
			icurrRacer=inewcurracer;
		}
	}
	for(auto i:viewSL)
		setRacersColor(i);
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
  String sname;
	sname=dynamic_cast<TLabel*>(Sender)->Name;
	if(sname=="SL2FIS"){
		l2live->Color=clRed;
		l2live->Repaint();

		int  iCodex=getCodex();//9872;
/*		setCodex(iCodex);
*/
		if (iCodex>0) {
			SetClipBoard("http://live.fis-ski.com/lv-a"+AnsiString(iCodex)+".htm#/startlist");

			if (LiveFIS!=NULL){
				if(LiveFIS->Connected())
					LiveFIS->Disconnect();
				delete LiveFIS;
				LiveFIS=NULL;
			}
			if (LiveFIS==NULL) {
try{
				setLiveFISpassword("08101957");
				LiveFIS=new TIdTCPClient;
				LiveFIS->Name="LiveFIS";
				LiveFIS->Port=1550;
				LiveFIS->Host="live.fisski.com";
				LiveFIS->Connect();

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
////				setRacedate(TDate("23.05.2019"));

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
	catch(...){
		ShowMessage("Проблемы с сетью");
	}

			}
		}
		l2live->Color=clLime;

	}
	else{
		int irc=dynamic_cast<TLabel*>(Sender)->Tag;
		setCurRacersColor(irc);
	}
}//end of proc
//_____________________________________________________________________________
void __fastcall RaceStartListView::Locations(TForm* form){
String str;
_viewSL *vsl;
int iN;

	if(!viewSL.empty()){
		for(auto i:viewSL)
			freevcls(i);
		viewSL.clear();
    }
	iN=this->getRacersN();
	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewSL(i==0?panel1:panel3,i,this,l2live);
		viewSL.push_back(*vsl);
		if(sz!=viewSL.capacity()){
			sz=viewSL.capacity();
		}
	}
	///String *sss=(String*)viewSL.data();
	panel3->Height=(iN-1)*vsl->FIO->Height;
	panel2->Height=panel3->Height;
	panel1->Height=panel2->Height+2;
	panel3->Width=vsl->T2->Width+vsl->T1->Width+vsl->FIO->Width+vsl->FC->Width+vsl->SN->Width+6;
	panel2->Width=panel3->Width+panel3->Left+2;
	panel1->Width=panel2->Width+panel2->Left+2;
	form->Width=panel1->Width+panel1->Left+14;
}//end of proc


//------------------------------------------------------------------------------
void __fastcall Races::showRaces(){
TDateTime tdt=Now();
String astr;

	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);

	Locations(pRaceViews);
	pRaceViews->Show();
	pRaceViews->Top=0;
	pRaceViews->Left=0;
}
//------------------------------------------------------------------------------
void __fastcall Races::showInfo(){
TDateTime tdt=Now();
String astr;

	LocationsInfo(pRaceInfo);
	pRaceInfo->Top=pRaceViews->Top;
	pRaceInfo->Left=pRaceViews->Top+pRaceViews->Width;
	pRaceInfo->Show();
	if (sCurrentXMLfilename.Length()>0) {
		int itop,ileft;
		itop=pRaceInfo->Top;
		ileft=pRaceInfo->Left+pRaceInfo->Width;
		showView(itop,ileft,-1);
	}
    if(tk!=NULL)
		tk->SetLeftTop(pRaceInfo->Left,pRaceInfo->Top+pRaceInfo->Height);
}
//------------------------------------------------------------------------------
void __fastcall Races::showStartList(){
	LocationsStartList(pRaceStartList);
	pRaceStartList->Show();
}
//------------------------------------------------------------------------------
void __fastcall Races::ReadINIsections(TIniFile *ini){
	if(ini) {
		ini->ReadSections(Sections);
///	for (int i=0; i<Sections->Count; i++) {
////	  ini->ReadSectionValues(Sections->Strings[i], Values);
///	  for (int j=0; j<Values->Count; j++) Memo1->Lines->Add(Values->Strings[j]);
	}

}

//==============================================================================
void __fastcall Races::Locations(TForm* form){
String str;
_viewRL *vsl;
int iN;

	if(!viewSL.empty()){
		viewSL.clear();

	}
//	if(eCompetition!=NULL)	{delete eCompetition,eCompetition=NULL;}
//	if(lplus!=NULL)	{delete lplus,lplus=NULL;}
//	if(panel3!=NULL)	{delete panel3,panel3=NULL;}
//	if(panel2!=NULL)	{delete panel2,panel2=NULL;}
//	if(panel1!=NULL)	{delete panel1,panel1=NULL;}
	iN=this->getRacesN();

	panel1=dynamic_cast<TPanel*> (form->FindComponent("P1"));
	if(!panel1){
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
		str.sprintf(L"Races");
		panel1->Caption="";//str;
	}


	lminus=dynamic_cast<TLabel*> (panel1->FindComponent("LMinus"));
	if(lminus==NULL){
		lminus= new TLabel(panel1);
		lminus->Parent = panel1;
		lminus->Name="LMinus";
		lminus->AutoSize=false;
		lminus->Alignment=taCenter;
		lminus->Transparent=false;
		lminus->Top=0;//SNHeight;
		lminus->Left=3;
		lminus->Width=SNWidth;
		lminus->Visible=true;
		lminus->Color=clRed;
		lminus->Caption="-";
		lminus->OnMouseDown=mouse_down;
	}

	lCompetition=dynamic_cast<TLabel*> (panel1->FindComponent("lCompetition"));
	if(lCompetition==NULL){
		lCompetition=new TLabel(panel1);
		lCompetition->Parent = panel1;
		lCompetition->Name="lCompetition";
		lCompetition->Font->Size=12;
		lCompetition->Top=lminus->Top;
		lCompetition->Left=34;
		lCompetition->Width=CodexWidth;
		lCompetition->Visible=true;
	}

	lplus=dynamic_cast<TLabel*> (panel1->FindComponent("LPlus"));
	if(lplus==NULL){
		lplus= new TLabel(panel1);
		lplus->Parent = panel1;
		lplus->Name="LPlus";
		lplus->AutoSize=false;
		lplus->Alignment=taCenter;
		lplus->Transparent=false;
		lplus->Top=lminus->Top+lminus->Height;
		lplus->Left=3;
		lplus->Width=SNWidth;
		lplus->Visible=true;
		lplus->Color=clLime;
		lplus->Caption="+";

		lplus->OnMouseDown=mouse_down;
		lplus->OnDblClick=mouse_DblClick;
	}



//	eCompetition=new TMaskEdit(panel2);
///	eCompetition->EditMask="!0000000000;1;_";
	if(eCompetition==NULL){
		eCompetition=new TEdit(panel1);
		eCompetition->Parent = panel1;
		eCompetition->Name="eCompetition";
		eCompetition->Font->Size=12;
		eCompetition->Top=lplus->Top;
		eCompetition->Left=lCompetition->Left;
		eCompetition->Width=CodexWidth;
		eCompetition->Visible=true;
		str=Now().FormatString("yyyymmdd01");
		eCompetition->Text=str;
	}

	if(panel2==NULL){
		panel2= new TPanel(panel1);
		panel2->Parent = panel1;
		panel2->Name="P2";
		panel2->Font->Size=12;
		panel2->Alignment=taLeftJustify;
		panel2->VerticalAlignment=taAlignTop;
		panel2->Top=eCompetition->Top+eCompetition->Height;
		panel2->Left=2;
		panel2->Width=panel1->Width-panel2->Left;
		panel2->Visible=true;
		panel2->Caption="";
	}

	if(panel3==NULL){
		panel3= new TPanel(panel2);
		panel3->Parent = panel2;
		panel3->Name="P3";
		panel3->Font->Size=12;
		panel3->Alignment=taLeftJustify;
		panel3->VerticalAlignment=taAlignTop;
		panel3->Top=0;//18*2+8;
		panel3->Left=3;
		panel3->Width=panel2->Width-panel3->Left;
		panel3->Visible=true;
		panel3->Caption="";
	}


//	iN=IniUltraAlpSki->ReadInteger("Competitions","Number",0);
	RacePack rp;
	RacesList.clear();

	iN=0;
	IniUltraAlpSki->ReadSections(Sections);
	if(Sections->Count>0){
		AnsiString ssection;
		int ipos;
		for (int i=0; i<Sections->Count; i++) {
			ssection=Sections->Strings[i];
			ipos=ssection.Pos("Competition#");
			if(ipos>0){
				iN++;
				ipos=ssection.Pos("#");
				ssection.Delete(1,ipos);
				rp.path="";
				rp.Codex=ssection;
				RacesList.push_back(rp);
			}
		}
		sort(RacesList.begin(),RacesList.end(),[](const RacePack  &a,const RacePack &b){
					return a.Codex >b.Codex;
		});


		viewSL.reserve(iN);
		auto sz= viewSL.capacity();
		for(int i=0;i<iN;++i){
			vsl=new _viewRL(panel3,i,this,lplus);
			viewSL.push_back(*vsl);
			if(sz!=viewSL.capacity()){
				sz=viewSL.capacity();
			}
		}
		panel3->Height=8+iN*18;
	}
	else
	    panel3->Height=1;
	panel2->Height=panel3->Height+2;
	panel1->Height=panel1->Height+panel2->Height;
/*	panel3->Color=clGradientActiveCaption;
	panel2->Color=clAqua;
	panel1->Color=clLime;
*/
	panel1->ShowCaption=false;panel1->Caption="Удаление:";panel1->Font->Size=10;
	panel2->ShowCaption=false;panel2->Caption="Добавление:";panel2->Font->Size=panel1->Font->Size;
	panel3->ShowCaption=false;panel3->Caption="3333333";panel3->Font->Size=panel1->Font->Size;
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
void __fastcall Races::FormDestroy(TObject *Sender){
TForm *ff=dynamic_cast<TForm*>(Sender);
AnsiString sname=ff->Name;
}
void __fastcall Races::FormHide(TObject *Sender){
TForm *ff=dynamic_cast<TForm*>(Sender);
AnsiString sname=ff->Name;
	if(sname=="RaceInfoForm"){
	}
	if(sname=="RaceViewsForm"){
		CleaSLForm();
		if(pRaceInfo!=NULL)
			pRaceInfo->Hide();
	}
}
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
		grpGender->Left = lID->Left+lID->Width+50+30;
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
		grpDiscipline->Left = grpGender->Left;
		grpDiscipline->Top = 6;
		grpDiscipline->Height = 40;
		grpDiscipline->Width = 430;
		grpDiscipline->Caption = "Альпийская дисциплина";
		grpDiscipline->Columns=10;
		grpDiscipline->ItemIndex = -1;
		grpDiscipline->OnClick=radio_click;


		lDate= new TLabel(form);
		lDate->Parent = form;
		lDate->Name="RaceDate";
		lDate->AutoSize=true;
		lDate->Alignment=taCenter;
		lDate->Transparent=false;
		lDate->Font->Size=10;
		lDate->Color=clLime;
		lDate->Top=lID->Top+lID->Height+5;
		lDate->Left=lID->Left;
		lDate->Visible=true;
		lDate->Caption="Дата и время соревнования";
		lDate->OnMouseDown=mouse_down;


		eDate=new TMaskEdit(form);
		eDate->EditMask="!99/99/0000;1;_";
		eDate->Parent = form;
		eDate->Name="eDate";
		eDate->Font->Size=8;
		eDate->Top=lDate->Top+lDate->Height+2;
		eDate->Left=lID->Left;
		eDate->Width=70;
		eDate->Visible=true;
		eDate->Text="";
		eDate->OnKeyDown=maskedit_key_down_info;

		eTime=new TMaskEdit(form);
		eTime->EditMask="!99:99;1;_";
		eTime->Parent = form;
		eTime->Name="eTime";
		eTime->Font->Size=eDate->Font->Size;
		eTime->Top=eDate->Top;
		eTime->Left=eDate->Left+eDate->Width;
		eTime->Width=40;
		eTime->Visible=true;
		eTime->Text="";
		eTime->OnKeyDown=maskedit_key_down_info;

		imageFIS=new TImage(form);
		imageFIS->Parent = form;
		imageFIS->Stretch=true;
		imageFIS->Height=38;
		imageFIS->Width=imageFIS->Height;
		imageFIS->Top=eDate->Top+eDate->Height+2;
		imageFIS->Left=lID->Left;
		imageFIS->Picture=fUltraSki->Image1->Picture;

		lFISCodex= new TLabel(form);
		lFISCodex->Parent = form;
		lFISCodex->Name="LFISCodex";
		lFISCodex->AutoSize=true;
		lFISCodex->Alignment=taCenter;
		lFISCodex->Transparent=false;
		lFISCodex->Color=clLime;
		lFISCodex->Top=eDate->Top+eDate->Height+2;
		lFISCodex->Left=imageFIS->Left+imageFIS->Width;
		lFISCodex->Visible=true;
		lFISCodex->Caption="ФИС кодекс";
		lFISCodex->OnMouseDown=mouse_down;


		eFISCodex=new /*TEdit*/TMaskEdit(form);
		eFISCodex->Parent = form;
		eFISCodex->EditMask="!0000;1;";
		eFISCodex->Name="eFISCodex";
		eFISCodex->Font->Size=eDate->Font->Size;
		eFISCodex->Top=lFISCodex->Top+lFISCodex->Height+2;
		eFISCodex->Left=lFISCodex->Left;
		eFISCodex->Width=35;
		eFISCodex->Visible=true;
		eFISCodex->Text="";
		eFISCodex->OnKeyDown=maskedit_key_down_info;//edit_key_down_info;

		lInfoName= new TLabel(form);
		lInfoName->Parent = form;
		lInfoName->Name="lInfoName"+form->Name;
		lInfoName->AutoSize=true;
		lInfoName->Font->Size=eDate->Font->Size+2;
		lInfoName->Alignment=taCenter;
		lInfoName->Transparent=false;
		lInfoName->Top=eFISCodex->Top+eFISCodex->Height+5;
		lInfoName->Left=lID->Left;
		lInfoName->Visible=true;
		lInfoName->Caption="Название соревнования";

		eInfoName=new TEdit(form);
		eInfoName->Parent = form;
		eInfoName->Name="eInfoName";
		eInfoName->Font->Size=eDate->Font->Size;
		eInfoName->Top=lInfoName->Top+lInfoName->Height+2;
		eInfoName->Left=lID->Left;
		eInfoName->Width=grpDiscipline->Width+grpDiscipline->Left-2;
		eInfoName->Visible=true;
		eInfoName->Text="";
		eInfoName->OnKeyDown=edit_key_down_info;//edit_key_down_info;

		lSLimport=new TLabel(form);
		lSLimport->Parent = form;
		lSLimport->Name="lSLimport";
		lSLimport->AutoSize=true;
		lSLimport->Font->Size=eDate->Font->Size+2;
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
		lSLimportN->Font->Size=eDate->Font->Size;
		lSLimportN->Top=lSLimport->Top+lSLimport->Height+2;
		lSLimportN->Left=lSLimport->Left;
		lSLimportN->Width=eInfoName->Width;
		lSLimportN->Transparent=false;
		lSLimportN->Visible=true;
		lSLimportN->Caption="";

		form->Width=eInfoName->Left+eInfoName->Width+55;
		form->Height=lSLimportN->Top+lSLimportN->Height+45;

		TBorderIcons tempBI = form->BorderIcons;
	//	tempBI >> biSystemMenu;
		tempBI >> biMinimize;
		tempBI >> biMaximize;
		tempBI >> biHelp;
		form->BorderIcons = tempBI;
	}
///	icurrRace=0;
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
}//end of proc
//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall Races::LocationsStartList(TForm* form){
}//end of proc
//-----------------------------------------------------------------------------
#include <filesystem>
namespace fs = std::filesystem;
void DeleteDir(AnsiString sname){
	fs::path dir = sname.c_str();
	std::uintmax_t n = fs::remove_all(dir);
}
//-----------------------------------------------------------------------------
void __fastcall Races::form_key_down(TObject *Sender, WORD &Key, TShiftState Shift){
int ik=Key,iflag=0;
AnsiString astr;
String sname;
int ichecklines=checkLines(),iracersN=this->getRacesN();
int icurH,icurH1,icurN,
	iformH=pRaceViews->Height,
	ipaneltop=panel3->Top;
	icurN=icurrRace;

	switch(Key){
	   case 46://delete
			Key=0;
			return;
	   break;
	   case 35://end
			icurrRace=iracersN-1;
			icurH1=iformH-panel2->Top-panel1->Top-3*18;
			icurH=icurrRace*18;
			panel3->Top=icurH1-icurH;
			if (panel3->Top>0) {
				panel3->Top=0;
			}
			Key=0;
	   break;
	   case 36://home
			icurrRace=0;
			panel3->Top=0;
	   break;
	   case 39://right
	   break;
	   case 40://down
			if(icurrRace<iracersN-1){
				icurrRace++;
				icurH=icurrRace*18;
				int ih=iformH-panel2->Top-4*18;
				if((icurH+ipaneltop)<ih){
					int i=iformH-4*8;
					i=panel2->Top;
					i=panel3->Top;
				}
				else{
					panel3->Top-=18;
				}
			}
			else{
				panel3->Top=0;
				icurrRace=0;
			}
			Key=0;
	   break;
	   case 38://up
			if(icurrRace>0){
				icurrRace--;
				icurH=icurrRace*18;
				if(icurH+ipaneltop<0)
					panel3->Top+=18;
			}
			else{
				icurrRace=iracersN-1;
				panel3->Top=18*(ichecklines-iracersN-1);
			}
			Key=0;
	   break;
	   default:
		   iflag=1;
	}
	if(iflag!=1)
		std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
	number_Of_competitions=viewSL.size();

	try{
		if(number_Of_competitions>0){
			FillRaceDescription();
		}
		else{
			sCurrentXMLfilename="";
			pRaceInfo->Hide();
			CleaSLForm();
		}
	}
	catch(...){
		ShowMessage("Приплыли 3");
	}
}
//------------------------------------------------------------------------------
void __fastcall Races::SaveInfo2INI(void){
	String 	sID,astr,sN,sDateINI,sTimeINI,sCodexINI,sEVENT,sSLFile;
	sN=viewSL[icurrRace].SN->Caption;
	sCodexINI=eFISCodex->Text;
	sDateINI=eDate->Text;
	sTimeINI=eTime->Text;
	sEVENT=eInfoName->Text;
	sSLFile=lSLimportN->Caption;
	sID=lID->Caption;

	IniUltraAlpSki->WriteString("Competition#"+sID,"DATE",sDateINI);
	IniUltraAlpSki->WriteString("Competition#"+sID,"TIME",sTimeINI);
	IniUltraAlpSki->WriteString("Competition#"+sID,"FISCODEX",sCodexINI);
	IniUltraAlpSki->WriteString("Competition#"+sID,"EVENT",sEVENT);
	IniUltraAlpSki->WriteString("Competition#"+sID,"SLFILE",sSLFile);
	IniUltraAlpSki->WriteString("Competition#"+sID,"DISCIPLINE",getDiscipline());
	IniUltraAlpSki->WriteString("Competition#"+sID,"GENDER",getGender());
	IniUltraAlpSki->UpdateFile();
	setEventname(sEVENT);
	setRacedate(TDate(sDateINI));
	setRacetime(TTime(sTimeINI));

	lID->Color=clLime;
}
//----------------------------------------------------------------------------
void __fastcall Races::FillRaceInfo(void){
String 	astr,sDateINI,sTimeINI,sCodexINI,sEVENT,sSLFile,sname,sN;
	if(icurrRace<0)return;
	try{
		sname=viewSL[icurrRace].RCodex->Caption;
		tk->SetRaceCode(sname);
		lCompetition->Caption=sname;
		eCompetition->Text=sname;
	}
	catch(...){
		int i=0;
	}
	if(lID==NULL){
		try{
			showInfo();
		}
		catch(...){
			int i=0;
		}

	}
	astr=IniUltraAlpSki->ReadString("Competition#"+sname,"ID","");
	sDateINI=IniUltraAlpSki->ReadString("Competition#"+sname,"DATE","");
	sTimeINI=IniUltraAlpSki->ReadString("Competition#"+sname,"TIME","");
	sTimeINI=IniUltraAlpSki->ReadString("Competition#"+sname,"TIME","");
	sCodexINI=IniUltraAlpSki->ReadString("Competition#"+sname,"FISCODEX","0");


	try{
		int icodex=StrToInt(sCodexINI);
		setCodex(icodex);
		if(icodex>0/*==9872||icodex==9871*/)
			LiveFISconnect();
		else{
			if(LiveFIS){
				delete LiveFIS;
                LiveFIS=NULL;
			}
		}
	}
	catch(...){
		sCodexINI=0;
	}

	sEVENT=IniUltraAlpSki->ReadString("Competition#"+sname,"EVENT","");
	setEventname(sEVENT);

	sSLFile=IniUltraAlpSki->ReadString("Competition#"+sname,"SLFILE","");

	astr=IniUltraAlpSki->ReadString("Competition#"+sname,"DISCIPLINE","");
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
	astr=IniUltraAlpSki->ReadString("Competition#"+sname,"GENDER","");
	setGender(astr);
	if(astr=="M")grpGender->ItemIndex=0;
	if(astr=="L")grpGender->ItemIndex=1;
	if(astr=="T")grpGender->ItemIndex=2;


	eDate->Text=sDateINI;
	if(sDateINI.Length()>0)
		setRacedate(TDate(sDateINI));
	eTime->Text=sTimeINI;
	if(sTimeINI.Length()>0)
		setRacetime(TTime(sTimeINI));


	eFISCodex->Text=sCodexINI;
	eInfoName->Text=sEVENT;
	lSLimportN->Caption=sSLFile;


	lID->Caption=sname;
	lID->Color=clLime;
}
//------------------------------------------------------------------------------
void __fastcall Races::FillRaceSL(void){
	AnsiString filename;
	AnsiString spath,sID;
	sID=lID->Caption;
	spath=DefaultPath+sID+"\\SL"+sID+".xml";
	bool flag=FileExists(spath);
	if(flag){
		sCurrentXMLfilename=spath;
		loadXML(spath);
		setXMLpath(spath);
		int itop=pRaceInfo->Top,ileft=pRaceInfo->Left+pRaceInfo->Width;
		showView(itop,ileft,400);
		pRaceViews->Show();
	}
	else{
		sCurrentXMLfilename="";
		CleaSLForm();
	}
}
void __fastcall Races::FillRaceDescription(void){
	FillRaceInfo();
	FillRaceSL();

}
//------------------------------------------------------------------------------
void __fastcall Races::maskedit_key_down_info(TObject *Sender, WORD &Key, TShiftState Shift){
AnsiString astr;
TMaskEdit *edt=dynamic_cast<TMaskEdit*>(Sender);
astr=edt->Name;

	if(astr=="eFISCodex"){
		lID->Color=clRed;
	return;
	}
	if(astr=="eInfoName"){
		lID->Color=clRed;
	return;
	}
	if(astr=="eTime"||astr=="eDate"){
		lID->Color=clRed;
	return;
	}
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
///	edt->Color=flag?clLime:clRed;
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
	iracesN=getRacesN(),
	iformH=pRaceViews->Height,
	iraceH=iracesN*18+5,
	iDelta=panel3->Top+iraceH;
	panel3->Height=iraceH;
	panel2->Height=panel3->Height+8+2*18;
	panel1->Height=panel2->Height+8;
	pRaceViews->Height=panel1->Height+8+2*18;
int ipaneltop=panel3->Top;
	if(ipaneltop<0){
		panel3->Top=iformH-iraceH-3*18;
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
		if(i==icurrRace)
			lCompetition->Caption=vsl.RCodex->Caption;
			eCompetition->Text=lCompetition->Caption;

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
//-----------------------------------------------------------------------

int __fastcall Races::LiveFISconnect(void){
int  iCodex=getCodex(),iConnected=0;//9872;
	if (iCodex>0) {

		if (LiveFIS!=NULL){
			if(LiveFIS->Connected())
				LiveFIS->Disconnect();
			delete LiveFIS;
			LiveFIS=NULL;
		}
		if(LiveFIS==NULL){
			setLiveFISpassword("08101957");
			LiveFIS=new TIdTCPClient;
			LiveFIS->Name="LiveFIS";
			LiveFIS->Port=1550;
			LiveFIS->Host="live.fisski.com";
		}
		if( !LiveFIS->Connected())
			LiveFIS->Connect();
	}
	iConnected=LiveFIS->Connected();
	return iConnected;
}
//-----------------------------------------------------------------------
void __fastcall Races::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
  TLabel *lblmoused=dynamic_cast<TLabel*>(Sender);
  int saveicurrRace=icurrRace,iflag=0;
  icurrRace=dynamic_cast<TLabel*>(Sender)->Tag;

//	ilastcurrRace=icurrRace;
	String 	str=lblmoused->Caption,
			sname=lblmoused->Name;
	if(sname=="RaceDate"){
		eDate->Text=Now().FormatString("dd.mm.yyyy");
		rcs->setRacedate(TDate(eDate->Text));
		eTime->Text=Now().FormatString("hh:MM");
		rcs->setRacetime(TTime(eTime->Text));
		lID->Color=clRed;
		return;
	}
	if(sname=="LFISCodex"){
		if(eFISCodex->Text=="9871")eFISCodex->Text=9872; else eFISCodex->Text="9871";
		setCodex(StrToInt(eFISCodex->Text));
		LiveFISconnect();
		lID->Color=clRed;
		return;
	}

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
				  lID->Color=clRed;
		}
		return;
	}
	if (str=="-") {
		if (viewSL.size()==0){
			return;
		}
		icurrRace=saveicurrRace;
		sname=viewSL[icurrRace].RCodex->Caption;
		try{
		RacesList.erase(RacesList.begin() + icurrRace);
		int iiii=RacesList.size();
		if(icurrRace==iiii)
			icurrRace--;
		IniUltraAlpSki->EraseSection("Competition#"+sname);
		IniUltraAlpSki->WriteInteger("Competitions","Number",iiii);
		IniUltraAlpSki->UpdateFile();
		}
		catch(...){
			ShowMessage("Проблемы сохранения базы соревнований ");

		}

		try{
		sname=DefaultPath+sname+"\\";
		DeleteDir(sname);
		showRaces();
		}
		catch(...){
			ShowMessage("Прииплылии");
		}
	}
	if (str=="+") {
		RacePack rp;
		rp.Codex=eCompetition->Text;
		rp.path=lSLimportN->Caption;
		vector < RacePack > *rpp;

		int ii=RacesList.size(),irc=1;
		for(int ij=0;ij<ii;++ij){
			if (RacesList[ij].Codex  == rp.Codex) {
				irc=0;
				break;
			}
		}
		if (irc) {
			iflag=1;
			RacesList.push_back(rp);
			String astr=rp.Codex;
			int isize=RacesList.size();
			IniUltraAlpSki->WriteString("Competition#"+rp.Codex,"ID",rp.Codex);
			IniUltraAlpSki->WriteString("Competition#"+rp.Codex,"PATH",rp.path);
			IniUltraAlpSki->WriteInteger("Competitions","Number",isize);
			IniUltraAlpSki->UpdateFile();
			showRaces();
			eCompetition->Text=rp.Codex;
			lCompetition->Caption=eCompetition->Text;

			AnsiString bstr,aastr=eCompetition->Text;
			int iN;
			bstr=aastr.SubString(9,2);
			try{
				iN=StrToInt(bstr);
				iN++;
				bstr.sprintf("%s%02d",aastr.SubString(1,8).c_str(),iN);
				eCompetition->Text=bstr;
			}
			catch(...){}

		}
		else{
			AnsiString astr,aastr=eCompetition->Text;
			int iN;
			astr=aastr.SubString(9,2);
			try{
				iN=StrToInt(astr);
				iN++;
				astr.sprintf("%s%02d",aastr.SubString(1,8).c_str(),iN);
				eCompetition->Text=astr;
			}
			catch(...){}

		}
	}
	else{
		ShowRaceInfoAndStartList();
/*		if(ilastcurrRace!=icurrRace){
			ilastcurrRace=icurrRace;
			std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
			FillRaceDescription();
			pRaceViews->SetFocus();
		}
*/
	}
}//end of proc
//------------------------------------------------------------------------------
void __fastcall Races::ShowRaceInfoAndStartList(void){
	if(ilastcurrRace!=icurrRace){
		ilastcurrRace=icurrRace;
		for(auto i:viewSL)
			setRacersColor(i);
		FillRaceDescription();
		pRaceViews->SetFocus();
	}
}
//------------------------------------------------------------------------------
void __fastcall Races::mouse_DblClick(TObject *Sender){
int i;
AnsiString astr;
	tk->ForceRaceCode(RacesList[icurrRace].Codex);
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



