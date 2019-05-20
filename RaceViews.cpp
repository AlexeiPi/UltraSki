//---------------------------------------------------------------------------
#pragma hdrstop
#include "RaceViews.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall RaceStartListView::form_resize(TObject *Sender){
int ichecklines=checkLines(),
	iracersN=RL->getRacersN(),
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
int __fastcall RaceStartListView::checkLines(void){
int iHeight=pRaceViews->Height,iN,ih,itop;
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
int ichecklines=checkLines(),iracersN=RL->getRacersN();
int icurH,icurN,
	iformH=pRaceViews->Height,//=icurrRacer*18;
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
void __fastcall RaceStartListView::showView(){
TDateTime tdt=Now();
String astr;
	DateTimeToString(astr, "ddmmyyyyhhmmss", tdt);
	if(pRaceViews!=NULL)
		delete pRaceViews;
	pRaceViews=new TForm(Application);
	pRaceViews->Name="Form"+astr;
	pRaceViews->Caption=pRaceViews->Name;
	pRaceViews->DoubleBuffered=true;
	pRaceViews->OnKeyDown=form_key_down;
	pRaceViews->OnResize=form_resize;
	Locations(pRaceViews);
	pRaceViews->Show();
}
//_____________________________________________________________________________
void __fastcall RaceStartListView::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
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
}//end of proc
//_____________________________________________________________________________
void __fastcall RaceStartListView::Locations(TForm* form){
String str;
_viewSL *vsl;
int iN;

	if(!viewSL.empty()) viewSL.clear();
	iN=RL->getRacersN();

	panel1= new TPanel(form);
	panel1->Parent = form;
	panel1->Name="P1";
	panel1->Font->Size=12;
	panel1->Alignment=taLeftJustify;
	panel1->VerticalAlignment=taAlignTop;
	panel1->Top=3;
	panel1->Left=3;
	panel1->Width=pRaceViews->Width-panel1->Left;
	panel1->Visible=true;
	str.sprintf(L"RaceList%s",RL->getCODEX().c_str());
	panel1->Caption=str;

	panel2= new TPanel(panel1);
	panel2->Parent = panel1;
	panel2->Name="P2";
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
	panel3->Name="P3";
	panel3->Font->Size=12;
	panel3->Alignment=taLeftJustify;
	panel3->VerticalAlignment=taAlignTop;
	panel3->Top=0;
	panel3->Left=3;
	panel3->Width=panel2->Width-panel3->Left;
	panel3->Visible=true;
	panel3->Caption="";

	lbl= new TLabel(pRaceViews);
	lbl->Name="Label"+pRaceViews->Name;
	lbl->OnMouseDown=mouse_down;


	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewSL(i==0?panel1:panel3,i,RL,lbl);
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

