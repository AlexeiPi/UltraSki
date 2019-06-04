//---------------------------------------------------------------------------

#ifndef TimingDeviceH
#define TimingDeviceH
#if 0
class TimeKeeping{
private:
	struct _viewTM{
		TLabel *lSN;
		TLabel *lLine;
		TEdit *eTime;

		_viewT(TPanel*p,int i,RaceList *rL,TLabel *lbl){//constructor
			AnsiString str;
			SN=new TLabel(p);
			SN->Parent = p;
			SN->Name="tmSN";
			SN->AutoSize=false;
			SN->Transparent=false;
			SN->Tag=i;
			SN->Color=clWhite;
			SN->Font->Size=10;
			SN->Width=30;
			SN->Height=18;
			SN->Top=(i-1)*SN->Height;
			SN->Left=1;
			SN->Alignment=taCenter;
			str=i>0?rL->getRacer(i,0):"¹";
			SN->Caption=str;
			SN->OnMouseDown = lbl->OnMouseDown;

			lLine=new TLabel(p);
			lLine->Parent = p;
			lLine->Name="lLine";
2		q 			lLine->AutoSize=false;
			lLine->Transparent=false;
			lLine->Tag=SN->Tag;
			lLine->Color=SN->Color;
			lLine->Font->Size=SN->Font->Size;
			lLine->Width=70;
			lLine->Height=SN->Height;
			lLine->Top=SN->Top;
			lLine->Left=SN->Left+SN->Width;
			lLine->Alignment=taLeftJustify;
			str=i>0?rL->getRacer(i,1):"êîä ÔÈÑ";
			lLine->Caption=str;
			lLine->OnMouseDown = SN->OnMouseDown;

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
		~_viewSL(){
		}
	};

	struct Timing{
		int icurrpulseNumber;
		TTime tt;
		int electroLine;
		int distanceTime;
	};
	struct TimeMachine{
		String model;
		String Number;
	}
	TimeMachine tm(2);
	vector < Timing > timing;
public:
	TimeMachine(){};
	~TimeMachine(){};
}
#endif
//---------------------------------------------------------------------------
#endif
