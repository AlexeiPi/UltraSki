//---------------------------------------------------------------------------

#pragma hdrstop

#include "TimingDevice.h"
#include <DateUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
TIniFile *IniUltraTimeKeeping;//ini file
extern Races *rcs;
/*
DateUtils.MilliSecondsBetween(Now, 0);
    TFormatSettings fs = TFormatSettings::Create();
    fs.DecimalSeparator = '.';
    TDateTime dateTime = StrToDateTime("02/02/2016 01:00:00.123", fs);
	// восстанавливать ничего не нужно

	TDateTime dateTime = StrToDateTime(String().sprintf("12.02.2016 01:02:03%c123",DecimalSeparator));
	Label1->Caption = FormatDateTime("dd.mm.yyyy hh:nn:ss.zzz",dateTime);
                                 int    int      int      int
    TDateTime Value = EncodeTime(Hours, Minutes, Seconds, Milliseconds);
    edtTime->Text = Value;
*/
//---------------------------------------------------------------------------
void __fastcall TimeKeeping::TimeKeepingLocations(TForm* form){
String str;
_viewTK *vsl;
int iN=-1;
	iN=this->getPulsesN();
	if(panel1==NULL){
		panel1= new TPanel(form);
		panel1->Parent = form;
		panel1->DoubleBuffered=true;
		panel1->Name="tmP1";
		panel1->Font->Size=12;
		panel1->Alignment=taLeftJustify;
		panel1->VerticalAlignment=taAlignTop;
		panel1->Top=3;
		panel1->Left=2;
		panel1->Visible=true;
		str.sprintf(L"Замеры времени");
		panel1->Caption="";//str;
		//	panel1->Color=clLime;
	}

	if(lsynch==NULL){
		lsynch= new TLabel(panel1);
		lsynch->Parent = panel1;
		lsynch->Name="lsynch";
		lsynch->Color=clRed;
		lsynch->Font->Size=12;
		lsynch->AutoSize=true;
		lsynch->Alignment=taCenter;
		lsynch->Transparent=false;
		lsynch->Top=2;
		lsynch->Left=17;
		lsynch->Visible=true;
		lsynch->Caption="Сихронизация";
		lsynch->OnMouseDown=mouse_down;
	}

	if(eAsynch==NULL){
		eAsynch=new TMaskEdit(panel1);
		eAsynch->EditMask="!99:99:99.9999;1;_";
		eAsynch->Parent = panel1;
		eAsynch->Name="eAsynch";
		eAsynch->Font->Size=10;
		eAsynch->AutoSize=false;
		eAsynch->Height=18;
		eAsynch->Top=lsynch->Top;
		eAsynch->Left=lsynch->Left+lsynch->Width+5;
		eAsynch->Width=90;
		eAsynch->Visible=true;
		eAsynch->Text="";
	}
	if(eBsynch==NULL){
		eBsynch=new TMaskEdit(panel1);
		eBsynch->EditMask="!99:99:99.9999;1;_";
		eBsynch->Parent = panel1;
		eBsynch->Name="eBsynchh";
		eBsynch->Font->Size=eAsynch->Font->Size;
		eBsynch->AutoSize=false;
		eBsynch->Height=eAsynch->Height;
		eBsynch->Top=lsynch->Top;
		eBsynch->Left=eAsynch->Left+eAsynch->Width+5;
		eBsynch->Width=eAsynch->Width;
		eBsynch->Visible=true;
		eBsynch->Text="";
	}

	if(l0pulse==NULL){
		l0pulse= new TLabel(panel1);
		l0pulse->Parent = panel1;
		l0pulse->Name="l0Pulse";
		l0pulse->Font->Size=12;
		l0pulse->AutoSize=false;
		l0pulse->Alignment=taCenter;
		l0pulse->Transparent=false;
		l0pulse->Top=eAsynch->Top+eAsynch->Height;
		l0pulse->Left=3;
		l0pulse->Width=SNWidth;
		l0pulse->Visible=true;
		l0pulse->Caption="";
	}


	if(l0pulseValue==NULL){
		l0pulseValue=new TLabel(panel1);
		l0pulseValue->Parent = panel1;
		l0pulseValue->Name="S0";
		l0pulseValue->Caption="START";
		l0pulseValue->Font->Size=12;
		l0pulseValue->AutoSize=false;
		l0pulseValue->Alignment=taCenter;
		l0pulseValue->Transparent=false;
		l0pulseValue->Top=l0pulse->Top;
		l0pulseValue->Left=l0pulse->Left+l0pulse->Width+2;
		l0pulseValue->Width=90;
		l0pulseValue->Visible=true;
	}

	if(l0pulseValue2==NULL){
		l0pulseValue2=new TLabel(panel1);
		l0pulseValue2->Parent = panel1;
		l0pulseValue2->Name="i10";
		l0pulseValue2->Caption="INTER 1";
		l0pulseValue2->Font->Size=12;
		l0pulseValue2->AutoSize=false;
		l0pulseValue2->Alignment=taCenter;
		l0pulseValue2->Transparent=false;
		l0pulseValue2->Top=l0pulse->Top;
		l0pulseValue2->Left=l0pulseValue->Left+l0pulseValue->Width+2;
		l0pulseValue2->Width=l0pulseValue->Width;
		l0pulseValue2->Visible=true;
		l0pulseValue2->OnMouseDown = mouse_down;
	}


	if(l0pulseValue3==NULL){
		l0pulseValue3=new TLabel(panel1);
		l0pulseValue3->Parent = panel1;
		l0pulseValue3->Name="i20";
		l0pulseValue3->Caption="INTER 2";
		l0pulseValue3->Font->Size=12;
		l0pulseValue3->AutoSize=false;
		l0pulseValue3->Alignment=taCenter;
		l0pulseValue3->Transparent=false;
		l0pulseValue3->Top=l0pulse->Top;
		l0pulseValue3->Left=l0pulseValue2->Left+l0pulseValue2->Width+2;
		l0pulseValue3->Width=l0pulseValue->Width;
		l0pulseValue3->Visible=true;
		l0pulseValue3->OnMouseDown = mouse_down;

	}

	if(l0pulseValue4==NULL){
		l0pulseValue4=new TLabel(panel1);
		l0pulseValue4->Parent = panel1;
		l0pulseValue4->Name="i30";
		l0pulseValue4->Caption="INTER 3";
		l0pulseValue4->Font->Size=12;
		l0pulseValue4->AutoSize=false;
		l0pulseValue4->Alignment=taCenter;
		l0pulseValue4->Transparent=false;
		l0pulseValue4->Top=l0pulse->Top;
		l0pulseValue4->Left=l0pulseValue3->Left+l0pulseValue3->Width+2;
		l0pulseValue4->Width=l0pulseValue->Width;
		l0pulseValue4->Visible=true;
		l0pulseValue4->OnMouseDown = mouse_down;
	}

	if(l0pulseValue5==NULL){
		l0pulseValue5=new TLabel(panel1);
		l0pulseValue5->Parent = panel1;
		l0pulseValue5->Name="i40";
		l0pulseValue5->Caption="INTER 4";
		l0pulseValue5->Font->Size=12;
		l0pulseValue5->AutoSize=false;
		l0pulseValue5->Alignment=taCenter;
		l0pulseValue5->Transparent=false;
		l0pulseValue5->Top=l0pulse->Top;
		l0pulseValue5->Left=l0pulseValue4->Left+l0pulseValue4->Width+2;
		l0pulseValue5->Width=l0pulseValue->Width;
		l0pulseValue5->Visible=true;
		l0pulseValue5->OnMouseDown = mouse_down;

	}

	if(l0pulseValue6==NULL){
		l0pulseValue6=new TLabel(panel1);
		l0pulseValue6->Parent = panel1;
		l0pulseValue6->Name="F0";
		l0pulseValue6->Caption="FINISH";
		l0pulseValue6->Font->Size=12;
		l0pulseValue6->AutoSize=false;
		l0pulseValue6->Alignment=taCenter;
		l0pulseValue6->Transparent=false;
		l0pulseValue6->Top=l0pulse->Top;
		l0pulseValue6->Left=l0pulseValue5->Left+l0pulseValue5->Width+2;
		l0pulseValue6->Width=l0pulseValue->Width;
		l0pulseValue6->Visible=true;
	}





	if(lpulse==NULL){
		lpulse= new TLabel(panel1);
		lpulse->Parent = panel1;
		lpulse->Name="lPulseA";
		lpulse->Font->Size=12;
		lpulse->AutoSize=false;
		lpulse->Alignment=taCenter;
		lpulse->Transparent=false;
		lpulse->Top=l0pulse->Top+l0pulse->Height;
		lpulse->Left=3;
		lpulse->Width=SNWidth;
		lpulse->Visible=true;
		lpulse->Caption="A";
		lpulse->OnMouseDown=mouse_down;
	}


	if(lpulseValue==NULL){
		lpulseValue=new TLabel(panel1);
		lpulseValue->Parent = panel1;
		lpulseValue->Name="S";
		lpulseValue->Font->Size=12;
		lpulseValue->AutoSize=false;
		lpulseValue->Alignment=taCenter;
		lpulseValue->Transparent=false;
		lpulseValue->Top=lpulse->Top;
		lpulseValue->Left=lpulse->Left+lpulse->Width+2;
		lpulseValue->Width=l0pulseValue->Width;
		lpulseValue->Color=clAqua;
		lpulseValue->Visible=true;
		lpulseValue->OnMouseDown=mouse_down;
	}

	if(lpulseValue2==NULL){
		lpulseValue2=new TLabel(panel1);
		lpulseValue2->Parent = panel1;
		lpulseValue2->Name="i1";
		lpulseValue2->Font->Size=12;
		lpulseValue2->AutoSize=false;
		lpulseValue2->Alignment=taCenter;
		lpulseValue2->Transparent=false;
		lpulseValue2->Top=lpulse->Top;
		lpulseValue2->Left=lpulseValue->Left+lpulseValue->Width+2;
		lpulseValue2->Width=lpulseValue->Width;
		lpulseValue2->Color=clAqua;
		lpulseValue2->Visible=true;
		lpulseValue2->OnMouseDown=mouse_down;
	}


	if(lpulseValue3==NULL){
		lpulseValue3=new TLabel(panel1);
		lpulseValue3->Parent = panel1;
		lpulseValue3->Name="i2";
		lpulseValue3->Font->Size=12;
		lpulseValue3->AutoSize=false;
		lpulseValue3->Alignment=taCenter;
		lpulseValue3->Transparent=false;
		lpulseValue3->Top=lpulse->Top;
		lpulseValue3->Left=lpulseValue2->Left+lpulseValue2->Width+2;
		lpulseValue3->Width=lpulseValue->Width;
		lpulseValue3->Color=clAqua;
		lpulseValue3->Visible=true;
		lpulseValue3->OnMouseDown=mouse_down;
	}

	if(lpulseValue4==NULL){
		lpulseValue4=new TLabel(panel1);
		lpulseValue4->Parent = panel1;
		lpulseValue4->Name="i3";
		lpulseValue4->Font->Size=12;
		lpulseValue4->AutoSize=false;
		lpulseValue4->Alignment=taCenter;
		lpulseValue4->Transparent=false;
		lpulseValue4->Top=lpulse->Top;
		lpulseValue4->Left=lpulseValue3->Left+lpulseValue3->Width+2;
		lpulseValue4->Width=lpulseValue->Width;
		lpulseValue4->Color=clAqua;
		lpulseValue4->Visible=true;
		lpulseValue4->OnMouseDown=mouse_down;
	}

	if(lpulseValue5==NULL){
		lpulseValue5=new TLabel(panel1);
		lpulseValue5->Parent = panel1;
		lpulseValue5->Name="i4";
		lpulseValue5->Font->Size=12;
		lpulseValue5->AutoSize=false;
		lpulseValue5->Alignment=taCenter;
		lpulseValue5->Transparent=false;
		lpulseValue5->Top=lpulse->Top;
		lpulseValue5->Left=lpulseValue4->Left+lpulseValue4->Width+2;
		lpulseValue5->Width=lpulseValue->Width;
		lpulseValue5->Color=clAqua;
		lpulseValue5->Visible=true;
		lpulseValue5->OnMouseDown=mouse_down;
	}

	if(lpulseValue6==NULL){
		lpulseValue6=new TLabel(panel1);
		lpulseValue6->Parent = panel1;
		lpulseValue6->Name="F";
		lpulseValue6->Font->Size=12;
		lpulseValue6->AutoSize=false;
		lpulseValue6->Alignment=taCenter;
		lpulseValue6->Transparent=false;
		lpulseValue6->Top=lpulse->Top;
		lpulseValue6->Left=lpulseValue5->Left+lpulseValue5->Width+2;
		lpulseValue6->Width=lpulseValue->Width;
		lpulseValue6->Color=clAqua;
		lpulseValue6->Visible=true;
		lpulseValue6->OnMouseDown=mouse_down;
	}


	if(lBpulse==NULL){
		lBpulse= new TLabel(panel1);
		lBpulse->Parent = panel1;
		lBpulse->Name="lPulseB";
		lBpulse->Font->Size=12;
		lBpulse->AutoSize=false;
		lBpulse->Alignment=taCenter;
		lBpulse->Transparent=false;
		lBpulse->Top=lpulse->Top+lpulse->Height+1;
		lBpulse->Left=3;
		lBpulse->Width=SNWidth;
		lBpulse->Visible=true;
		lBpulse->Caption="B";
		lBpulse->OnMouseDown=mouse_down;
	}


	if(lBpulseValue==NULL){
		lBpulseValue=new TLabel(panel1);
		lBpulseValue->Parent = panel1;
		lBpulseValue->Name="BS";
		lBpulseValue->Font->Size=12;
		lBpulseValue->AutoSize=false;
		lBpulseValue->Alignment=taCenter;
		lBpulseValue->Transparent=false;
		lBpulseValue->Top=lBpulse->Top;
		lBpulseValue->Left=lpulse->Left+lpulse->Width+2;
		lBpulseValue->Width=lpulseValue->Width;
		lBpulseValue->Color=clAqua;
		lBpulseValue->Visible=true;
		lBpulseValue->OnMouseDown=mouse_down;
	}

	if(lBpulseValue2==NULL){
		lBpulseValue2=new TLabel(panel1);
		lBpulseValue2->Parent = panel1;
		lBpulseValue2->Name="Bi1";
		lBpulseValue2->Font->Size=12;
		lBpulseValue2->AutoSize=false;
		lBpulseValue2->Alignment=taCenter;
		lBpulseValue2->Transparent=false;
		lBpulseValue2->Top=lBpulse->Top;
		lBpulseValue2->Left=lpulseValue->Left+lpulseValue->Width+2;
		lBpulseValue2->Width=lpulseValue->Width;
		lBpulseValue2->Color=clAqua;
		lBpulseValue2->Visible=true;
		lBpulseValue2->OnMouseDown=mouse_down;
	}


	if(lBpulseValue3==NULL){
		lBpulseValue3=new TLabel(panel1);
		lBpulseValue3->Parent = panel1;
		lBpulseValue3->Name="Bi2";
		lBpulseValue3->Font->Size=12;
		lBpulseValue3->AutoSize=false;
		lBpulseValue3->Alignment=taCenter;
		lBpulseValue3->Transparent=false;
		lBpulseValue3->Top=lBpulse->Top;
		lBpulseValue3->Left=lpulseValue2->Left+lpulseValue2->Width+2;
		lBpulseValue3->Width=lpulseValue->Width;
		lBpulseValue3->Color=clAqua;
		lBpulseValue3->Visible=true;
		lBpulseValue3->OnMouseDown=mouse_down;
	}

	if(lBpulseValue4==NULL){
		lBpulseValue4=new TLabel(panel1);
		lBpulseValue4->Parent = panel1;
		lBpulseValue4->Name="Bi3";
		lBpulseValue4->Font->Size=12;
		lBpulseValue4->AutoSize=false;
		lBpulseValue4->Alignment=taCenter;
		lBpulseValue4->Transparent=false;
		lBpulseValue4->Top=lBpulse->Top;
		lBpulseValue4->Left=lpulseValue3->Left+lpulseValue3->Width+2;
		lBpulseValue4->Width=lpulseValue->Width;
		lBpulseValue4->Color=clAqua;
		lBpulseValue4->Visible=true;
		lBpulseValue4->OnMouseDown=mouse_down;
	}

	if(lBpulseValue5==NULL){
		lBpulseValue5=new TLabel(panel1);
		lBpulseValue5->Parent = panel1;
		lBpulseValue5->Name="Bi4";
		lBpulseValue5->Font->Size=12;
		lBpulseValue5->AutoSize=false;
		lBpulseValue5->Alignment=taCenter;
		lBpulseValue5->Transparent=false;
		lBpulseValue5->Top=lBpulse->Top;
		lBpulseValue5->Left=lpulseValue4->Left+lpulseValue4->Width+2;
		lBpulseValue5->Width=lpulseValue->Width;
		lBpulseValue5->Color=clAqua;
		lBpulseValue5->Visible=true;
		lBpulseValue5->OnMouseDown=mouse_down;
	}

	if(lBpulseValue6==NULL){
		lBpulseValue6=new TLabel(panel1);
		lBpulseValue6->Parent = panel1;
		lBpulseValue6->Name="BF";
		lBpulseValue6->Font->Size=12;
		lBpulseValue6->AutoSize=false;
		lBpulseValue6->Alignment=taCenter;
		lBpulseValue6->Transparent=false;
		lBpulseValue6->Top=lBpulse->Top;
		lBpulseValue6->Left=lpulseValue5->Left+lpulseValue5->Width+2;
		lBpulseValue6->Width=lpulseValue->Width;
		lBpulseValue6->Color=clAqua;
		lBpulseValue6->Visible=true;
		lBpulseValue6->OnMouseDown=mouse_down;
		panel1->Width=lpulseValue6->Left+lpulseValue6->Width+2;
		panel1->Height=lBpulse->Top+lBpulse->Height+2;
	}


	if(panel2==NULL){
		panel2= new TPanel(panel1);
		panel2->Parent = panel1;
		panel2->DoubleBuffered=true;
		panel2->Name="tmP2";
		panel2->Font->Size=12;
		panel2->Alignment=taLeftJustify;
		panel2->VerticalAlignment=taAlignTop;
		panel2->Top=lBpulse->Top+lBpulse->Height;
		panel2->Left=2;
		panel2->Visible=true;
		panel2->Caption="";
	}
	if(panel3==NULL){
		panel3= new TPanel(panel2);
		panel3->Parent = panel2;
		panel3->DoubleBuffered=true;
		panel3->Name="tmP3";
		panel3->Font->Size=12;
		panel3->Alignment=taLeftJustify;
		panel3->VerticalAlignment=taAlignTop;
		panel3->Top=0;//18*2+8;
		panel3->Left=3;
		panel3->Visible=true;
		panel3->Caption="";
	}


	iN=IniUltraTimeKeeping->ReadInteger("TimeKeeping","Number",0);
	Timing tm;
	TimingList.clear();
	iN=0;
	IniUltraTimeKeeping->ReadSections(Sections);
	AnsiString ssection;
	int ipos;
	for (int i=0; i<Sections->Count; i++) {
		ssection=Sections->Strings[i];
		ipos=ssection.Pos("Time#");
		if(ipos>0){
			AnsiString atod,atype;
			iN++;
			atod=ssection;
			ipos=ssection.Pos("#");
			ssection.Delete(1,ipos);
			tm.icurrpulseNumber=iN;
			tm.TimeOfDay=ssection;

			atype=IniUltraTimeKeeping->ReadString(atod,"TYPE","");
			tm.electroLine=atype;
			TimingList.push_back(tm);
		}
	}

/*sort(TimingList.begin(),TimingList.end(),[](const Timing  &a,const Timing &b){return a.icurrpulseNumber >b.icurrpulseNumber;});*/

	show_viewTK();

	panel1->ShowCaption=false;panel1->Caption="Удаление:";panel1->Font->Size=10;
	panel2->ShowCaption=false;panel2->Caption="Добавление:";panel2->Font->Size=panel1->Font->Size;
	panel3->ShowCaption=false;panel3->Caption="3333333";panel3->Font->Size=panel1->Font->Size;
	panel2->Width=panel1->Width-4;
	panel3->Width=panel2->Width-4;

	form->Width=panel1->Width+2*panel1->Left+17;
//	form->Height=panel1->Height+45;
///	form->Left=0;
///	form->Top=0;

	TBorderIcons tempBI = form->BorderIcons;
	tempBI >> biMinimize;
	tempBI >> biMaximize;
	tempBI >> biHelp;
	form->BorderIcons = tempBI;
}//end of proc
//------------------------------------------------------------------------------
void __fastcall TimeKeeping::showTimeKeeping(void){
	TimeKeepingLocations(pTMViews);
	pTMViews->Show();
}
//------------------------------------------------------------------------------
void __fastcall TimeKeeping::TimePut(AnsiString atype,AnsiString aname,AnsiString atime){
Timing tm;
AnsiString astr;
	tm.TimeOfDay=atime;
	tm.electroLine=atype+aname;
	tm.icurrpulseNumber=TimingList.size()+1;
	TimingList.push_back(tm);

	astr=atype+"Time#"+atime;
	IniUltraTimeKeeping->WriteString(astr,"Type",atype+aname);
}
//------------------------------------------------------------------------------
#include <stdlib.h>
void __fastcall TimeKeeping::mouse_down(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y){
TLabel *lblmoused=dynamic_cast<TLabel*>(Sender);
String 	str=lblmoused->Caption,sname=lblmoused->Name;
AnsiString astr,atime,aa,bb;
int a,b;
//	srand(time(NULL));randomize();b=random(9);a=random(9);
	b=random(9);a=random(9);
	aa.sprintf("%d",a);
	bb.sprintf("%d",b);
	astr=str;
	astr=sname;
	atime=_getTimeHHSSZZZ();
	if(sname=="lsynch"){
		if(lblmoused->Color==clLime){
			lblmoused->Color=clRed;
			lblmoused->Font->Color=clYellow;
		}
		else{
			lsynch->Color=clLime;
			lblmoused->Font->Color=clRed;
		}
	}
	else{
		if(sname=="i10"||sname=="i20"||sname=="i30"||sname=="i40"){
			if(lblmoused->Color==clRed)lblmoused->Color=clLime; else lblmoused->Color=clRed;
		}
		else
		if(sname=="lPulseA"){
			lpulseValue->Caption="";lpulseValue1->Caption="";lpulseValue2->Caption="";lpulseValue3->Caption="";lpulseValue4->Caption="";lpulseValue5->Caption="";lpulseValue6->Caption="";
		}
		else if(sname=="lPulseB"){
			lBpulseValue->Caption="";lBpulseValue1->Caption="";lBpulseValue2->Caption="";lBpulseValue3->Caption="";lBpulseValue4->Caption="";lBpulseValue5->Caption="";lBpulseValue6->Caption="";
		}
		else{
			int ipos=sname.Pos("B");
			if(sname.Pos("F")){
				//srand(time(NULL));randomize();
				b=random(999);a=random(999);
				atime.SetLength(10);
				aa.sprintf("%03d",a);
				bb.sprintf("%03d",b);
			}

			if(ipos==0){
				lblmoused->Caption=atime+aa;
				if(a>=b){
					TimePut("B",sname,atime+bb);
					TimePut("A",sname,atime+aa);
				}
				else{
					TimePut("A",sname,atime+aa);
					TimePut("B",sname,atime+bb);
				}
			}
			else{
				TimePut("",sname,atime+bb);
				lblmoused->Caption=atime+bb;
			}
			IniUltraTimeKeeping->UpdateFile();

			show_viewTK();

		}
	}
}//end of proc
//------------------------------------------------------------------------------
void __fastcall TimeKeeping::OnTKtimer(TObject *Sender){
AnsiString atime;
	atime=_getTimeHHSSZZZ();
	pTMViews->Caption=atime;
}
//------------------------------------------------------------------------------
void __fastcall TimeKeeping::form_resize(TObject *Sender){
// 	showTimeKeeping();
}
//------------------------------------------------------------------------------
void __fastcall TimeKeeping::show_viewTK(void){
	int iN;
	iN=(pTMViews->Height-panel2->Top-36)/18;
	viewTK.reserve(iN);
	_viewTK *vtk;
	auto sz= viewTK.capacity();
	auto tmlsz= TimingList.size();
	for(int i=0,j=0;i<iN;++i){
		int secondsbetween;
		float it1,it2;
		float idiff;
		Timing *tm1,*tm2,*tmp1,*tmp2;
		TTime time1,time2;
		AnsiString asystem,bsystem,atime,btime,ahh,amm,ass,azzzz,bhh,bmm,bss,bzzzz,adiff;
		tm1=&TimingList[tmlsz-j-1];tm2=&TimingList[tmlsz-j-2];
		asystem=tm1->electroLine.SubString(1,1);bsystem=tm2->electroLine.SubString(1,1);
		atime=tm1->TimeOfDay;atime.SetLength(10);
		btime=tm2->TimeOfDay;btime.SetLength(10);
		time1=TTime(atime);
		time2=TTime(btime);
		secondsbetween=MilliSecondsBetween(time1,time2);
		if(secondsbetween>0){
			tmp1=NULL;tmp2=NULL;
			if(asystem=="A")tmp1=tm1;
			if(asystem=="B")tmp2=tm1;
			++j;
			idiff=0;
		}
		else{
			if(asystem=="A")tmp1=tm1;
			if(asystem=="B")tmp2=tm1;
			if(bsystem=="A")tmp1=tm2;
			if(bsystem=="B")tmp2=tm2;
			if(tmp1->electroLine=="AS"&&lsynch->Color==clLime){
				lsynch->Color=clRed;
                lsynch->Font->Color=clYellow;
				eAsynch->Text=tmp1->TimeOfDay;
				eBsynch->Text=tmp2->TimeOfDay;

			}
			float idif;
			ahh=tmp1->TimeOfDay.SubString(1,2);
			amm=tmp1->TimeOfDay.SubString(4,2);
			ass=tmp1->TimeOfDay.SubString(7,2);
			azzzz=tmp1->TimeOfDay.SubString(10,4);
			bhh=tmp2->TimeOfDay.SubString(1,2);
			bmm=tmp2->TimeOfDay.SubString(4,2);
			bss=tmp2->TimeOfDay.SubString(7,2);
			bzzzz=tmp2->TimeOfDay.SubString(10,4);
			it1=/*ahh.ToDouble()*60*60+amm.ToDouble()*60+ass.ToDouble()+*/azzzz.ToDouble()/10000;
			it2=/*bhh.ToDouble()*60*60+bmm.ToDouble()*60+bss.ToDouble()+*/bzzzz.ToDouble()/10000;
			idiff=(it2-it1);
			j+=2;



		}
		vtk=new _viewTK(panel3,i,idiff,tmp1,tmp2,lsynch);
		viewTK.push_back(*vtk);
		if(sz!=viewTK.capacity()){
			sz=viewTK.capacity();
		}
	}
	panel3->Height=72+iN*18;
	panel2->Height=panel3->Height+2;
	panel1->Height=panel2->Height+2;
	pTMViews->Show();
}
