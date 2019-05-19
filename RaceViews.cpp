//---------------------------------------------------------------------------

#pragma hdrstop

#include "RaceViews.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall RaceStartListView::form_resize(TObject *Sender){
	checkLines();   //new commit 2
}
//______________________________________________________________________________
void __fastcall RaceStartListView::checkLines(void){
int iHeight=pRaceViews->Height,iN,ih,itop;

	ih=viewSL[0].SN->Height;
	itop=viewSL[0].SN->Top+3*ih;
	iN=(iHeight-itop)/ih;
	pRaceViews->Caption=iN;

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
	switch(Key){
	   case 35:
			icurrRacer=RL->getRacersN()-1;
	   break;
	   case 36:
			icurrRacer=1;
	   break;
	   case 40:
			if(icurrRacer<RL->getRacersN()-1)icurrRacer++;
			else icurrRacer=RL->getRacersN()-1;
	   break;
	   case 38:
			if(icurrRacer>1)icurrRacer--;
			else icurrRacer=1;
	   break;
	}
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
}
//_____________________________________________________________________________

void __fastcall RaceStartListView::showView(){
	if(pRaceViews!=NULL) delete pRaceViews;
	pRaceViews=new TForm(Application);
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
/*
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
TPanel *panel;

String str;
_viewSL *vsl;

	if(!viewSL.empty()) viewSL.clear();
int iN;

	panel= new TPanel(form);
	panel->Parent = form;
	panel->Font->Size=12;
	panel->Alignment=taLeftJustify;
	panel->VerticalAlignment=taAlignTop;
	panel->Top=3;
	panel->Left=3;
	panel->Width=pRaceViews->Width-panel->Left;
	panel->Visible=true;
	str.sprintf(L"RaceList%s",RL->getCODEX().c_str());
	panel->Caption=str;
	iN=RL->getRacersN();


	for(int i=0;i<iN;++i){
		vsl=new _viewSL();

		vsl->SN=new TLabel(panel);
		vsl->SN->Parent = panel;
		vsl->SN->AutoSize=false;
		vsl->SN->Transparent=false;
		vsl->SN->Tag=i;
		vsl->SN->Color=i>0?clWhite:clAqua;
		vsl->SN->Font->Size=10;
		vsl->SN->Width=30;
		vsl->SN->Height=18;
		vsl->SN->Top=i*vsl->SN->Height;
		vsl->SN->Left=1;
		vsl->SN->Alignment=taCenter;
		str=i>0?RL->getRacer(i,0).c_str():"№";
		vsl->SN->Caption=str;
		vsl->SN->OnMouseDown = mouse_down;


		vsl->FC=new TLabel(panel);
		vsl->FC->Parent = panel;
		vsl->FC->AutoSize=false;
		vsl->FC->Transparent=false;
		vsl->FC->Tag=i;
		vsl->FC->Color=vsl->SN->Color;
		vsl->FC->Font->Size=10;
		vsl->FC->Width=70;
		vsl->FC->Height=20;
		vsl->FC->Top=vsl->SN->Top;
		vsl->FC->Left=vsl->SN->Left+vsl->SN->Width;
		vsl->FC->Alignment=taLeftJustify;
		str=i>0?RL->getRacer(i,1).c_str():"код ФИС";
		vsl->FC->Caption=str;
		vsl->FC->OnMouseDown = vsl->SN->OnMouseDown;

		vsl->FIO=new TLabel(panel);
		vsl->FIO->Parent = panel;
		vsl->FIO->AutoSize=false;

		vsl->FIO->Transparent=vsl->SN->Transparent;
		vsl->FIO->Tag=vsl->SN->Tag;
		vsl->FIO->Color=vsl->SN->Color;

		vsl->FIO->Font->Size=10;
		vsl->FIO->Width=210;
		vsl->FIO->Height=20;
		vsl->FIO->Top=vsl->SN->Top;
		vsl->FIO->Left=vsl->FC->Left+vsl->FC->Width;
		vsl->FIO->Alignment=taLeftJustify;
		str=i>0?RL->getRacer(i,2).c_str():"ФАМИЛИЯ, Имя";

		vsl->FIO->Caption=str;
		vsl->FIO->OnMouseDown = vsl->SN->OnMouseDown;

		viewSL.push_back(*vsl);

	}
	panel->Height=iN*vsl->FIO->Height;

 /*
	startlabel=new TLabel(start_button);
	startlabel->Parent = start_button;
	startlabel->AutoSize=false;
	startlabel->Transparent=true;
	startlabel->Top=1;
	startlabel->Left=1;
	startlabel->Width=start_button->Width-2;
	startlabel->Height=start_button->Height-2;
	startlabel->Caption="Начать процедуру";
	startlabel->Layout=tlCenter;
	startlabel->Alignment=taCenter;
	startlabel->WordWrap=true;
	startlabel->Font->Size=14;
	startlabel->OnMouseDown = start_click;

	label1=new TLabel(panel);
	label1->Parent = panel;
	label1->Top=start_button->Top+14;
	label1->Left=start_button->Left+start_button->Width+10;
	label1->AutoSize=false;
	label1->Width=170;
	label1->Height=30;
	label1->Alignment=taRightJustify;
	str.sprintf("Начало: 00:00:00");
	label1->Caption=str;
	label1->Font->Size=14;

	label2=new TLabel(panel);
	label2->Parent = panel;
	label2->AutoSize=false;
	label2->Top=label1->Top+label1->Height+5;
	label2->Left=label1->Left;
	label2->Width=label1->Width;
	label2->Height=label1->Height;
	label2->Alignment=taRightJustify;
	str.sprintf("Осталось: 00:00:00");
	label2->Caption=str;
	label2->Font->Size=label1->Font->Size;

	stop_panel= new TPanel(panel);
	stop_panel->Parent = panel;
	stop_panel->Top=start_button->Top;
	stop_panel->Height=start_button->Height;
	stop_panel->Width=300;
	stop_panel->Left=label1->Left+label1->Width+14;
	stop_panel->Visible=false;

	stop_fill_label= new TLabel(stop_panel);
	stop_fill_label->Parent = stop_panel;
	stop_fill_label->AutoSize=false;
	stop_fill_label->Transparent=false;
	stop_fill_label->Alignment=taCenter;
	stop_fill_label->Font->Size=10;
	stop_fill_label->Caption="Завершить ангиографию досрочно?";
	stop_fill_label->Color=clCream;
	stop_fill_label->Top=1;
	stop_fill_label->Left=1;
	stop_fill_label->Height=stop_panel->Height-2;
	stop_fill_label->Width=stop_panel->Width-2;
	stop_fill_label->WordWrap=true;

	stop_panel_time_label=new TLabel(stop_panel);
	stop_panel_time_label->Parent = stop_panel;
	stop_panel_time_label->AutoSize=false;
	stop_panel_time_label->Font->Color=clRed;
	stop_panel_time_label->Font->Size=10;
	stop_panel_time_label->Top=24;
	stop_panel_time_label->Left=43;
	stop_panel_time_label->Width=label1->Width;
	stop_panel_time_label->Height=label1->Height;
	stop_panel_time_label->Alignment=taLeftJustify;
	str.sprintf("Осталось: 00:00:00");
	stop_panel_time_label->Caption=str;

	tln = new TShape(stop_panel);
	tln->Parent = stop_panel;
	tln->Top= stop_panel_time_label->Top+stop_panel_time_label->Height;
	tln->Left= 1;
	tln->Height= 1;
	tln->Width= stop_panel->Width;
	tln->Visible=true;

	yes_button=new TButton(stop_panel);
	yes_button->Parent = stop_panel;
	yes_button->Height=27;
	yes_button->Width=80;
	yes_button->Font->Size=11;
	yes_button->Top=stop_fill_label->Height-yes_button->Height-5;
	yes_button->Left=stop_fill_label->Width/2-yes_button->Width-3;
	yes_button->Caption="Да";
	yes_button->OnClick = yes_button_click;

	no_button=new TButton(stop_panel);
	no_button->Parent = stop_panel;
	no_button->Font->Size=yes_button->Font->Size;
	no_button->Height=yes_button->Height;
	no_button->Top=yes_button->Top;
	no_button->Left=stop_fill_label->Width/2+3;
	no_button->Width=yes_button->Width;
	no_button->Caption="Нет";
	no_button->OnClick = no_button_click;

	image=new TImage(stop_panel);
	image->Parent = stop_panel;
	image->Height=40;
	image->Top=3;
	image->Left=3;
	image->Width=40;
	image->Picture=F366->Image1->Picture;
*/

}//end of proc

