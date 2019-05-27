//---------------------------------------------------------------------------

#pragma hdrstop

#include "Competition.h"
#include <StrUtils.hpp>
//____________________________________________________________________________
String __fastcall Race::LiveFISRaceclear(void){
String str,strTIME;
	String sCODEX=Codex;
	String sPASSWORD=LiveFISpassword.c_str();
	String sGENDER=Gender.c_str();
	DateTimeToString(strTIME, "hhmmsszzz", Now());
	String sSEQUENCE=strTIME;
	DateTimeToString(strTIME, "h:mm:ss", Now());
	String sTIMESTAMP=strTIME;

#if 1
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+sTIMESTAMP+"\">\
<command><clear/></command></livetiming>";
#else
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+sTIMESTAMP+"\">\
<command><clear/></command></livetiming>";
#endif

return str;
}
//_____________________________________________________________________________
String __fastcall Race::LiveFISRaceinfo(String run){

String str,strTIME;

	String sCODEX=Codex;
	String sPASSWORD=LiveFISpassword.c_str();
	String sGENDER=Gender.c_str();
	DateTimeToString(strTIME, "hhmmss", Now());
	String sSEQUENCE=strTIME;
	DateTimeToString(strTIME, "h:mm:ss", Now());
	String sTIMESTAMP=strTIME;

	String sDISCIPLINE=Discipline.c_str();
	String sCATEGORY=Category.c_str();
	String sRUNNO=run;//.c_str();

	String sEVENTname=Eventname.c_str();
	String sSLOPE=Slope.c_str();
	String sPLACE=Place.c_str();



	DateTimeToString(strTIME, "hh:mm:ss", Racedate);
	String sY=Racedate.FormatString(L"yyyy"),
	sM=Racedate.FormatString(L"mm"),
	sD=Racedate.FormatString(L"dd");
	String sINTER="1";

	String sHeader="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	#if 1
	String sLivetiming="<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+sTIMESTAMP+"\">";
	#else
	String sLivetiming="<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+sTIMESTAMP+"\">";
	#endif
	String sRaceinfo="<raceinfo><event>"+sEVENTname+"</event>";
	String sName="<name>"+sDISCIPLINE+"</name><slope />";
	String sSlope="<slope>"+sSLOPE+"</slope>";
	String sDiscipline="<discipline>"+sDISCIPLINE+"</discipline>";
	String sGender="<gender>"+sGENDER+"</gender>";
	String sCategory="<category>"+sCATEGORY+"</category>";
	String sPlace="<place>"+sPLACE+"</place>";
	String sTemperature="<tempunit>C</tempunit><longunit>m</longunit><speedunit>kmh</speedunit>";
	String SRunno="<run no=\""+sRUNNO+"\"><discipline>"+sDISCIPLINE+"</discipline><start /><finish /><height /><length /><gates /><turninggates />";
	String SYMDHM="<year>"+getRaceyyyy()+"</year><month>"+getRacemm()+"</month><day>"+getRacedd()+"</day><hour>"+getRacemm()+"</hour><minute>"+getRacedd()+"</minute>";
	String SRacedef="<racedef><inter i=\""+sINTER+"\" /></racedef>";
	String SEnding="</run></raceinfo><command><activerun no=\""+sRUNNO+"\" /></command></livetiming>";
///<command><activerun no=\""+sRUNNO+"\"/></command>

	str=sHeader+sLivetiming+sRaceinfo+sName+sSlope+sDiscipline+sGender+sCategory+sPlace+sTemperature+SRunno+SYMDHM+SRacedef+SEnding;
return str;
}
//______________________________________________________________________________
String __fastcall Race::LiveFISRacemessage(String message){

String str,strTIME;
	String sCODEX=Codex;
	String sPASSWORD=LiveFISpassword.c_str();
	DateTimeToString(strTIME, "hhmmsszzz", Now());
	String sSEQUENCE=strTIME;
	DateTimeToString(strTIME, "h:mm:ss", Now());
	String sTIMESTAMP=strTIME;
#if 1
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+sTIMESTAMP+"\">\
<message><text>"+message+"</text></message></livetiming>";
///<message><text>"+message+"</text><texttemp d=10>10 secs to disssapear></texttemp></message></livetiming>";

#else
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+sTIMESTAMP+"\">\
<message><text>"+message+"</text></message></livetiming>";
#endif

return str;
}
//______________________________________________________________________________
String __fastcall Race::LiveFISRaceactiverun(String srun){

String str,strTIME;
	String sRUN=srun;
	String sCODEX=Codex;
	String sPASSWORD=LiveFISpassword.c_str();
	DateTimeToString(strTIME, "hhmmsszzz", Now());
	String sSEQUENCE=strTIME;
	DateTimeToString(strTIME, "h:mm:ss", Now());
	String sTIMESTAMP=strTIME;
#if 1
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+sTIMESTAMP+"\">\
<command><activerun no=\""+sRUN+"\" /></command></livetiming>";

#else
	str="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+sTIMESTAMP+"\">\
<command><activerun no=\""+sRUN+"\" /></command></livetiming>";
#endif
return str;
}

//------------------------------------------------------------------------------
String __fastcall Race::LiveFISRacemeteo(String srun){

String str,strTIME;
String sRUN=srun;
String sCODEX=Codex;
String sPASSWORD=LiveFISpassword.c_str();
DateTimeToString(strTIME, "hhmmsszzz", Now());
String sSEQUENCE=strTIME;
DateTimeToString(strTIME, "h:mm:ss", Now());
String sTIMESTAMP=strTIME;
#if 1
	String strHeader="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" sequence=\""+sSEQUENCE+"\" timestamp=\""+sTIMESTAMP+"\">";
#else
	String strHeader="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<livetiming codex=\""+sCODEX+"\" passwd=\""+sPASSWORD+"\" timestamp=\""+sTIMESTAMP+"\">";
#endif
	String StrMeteo="<meteo run=\""+sRUN+"\"><weather>sun</weather><temperature>-44.0</temperature><wind>no</wind><snowtemperature>6.0</snowtemperature><snowcondition>sft</snowcondition><humidity>5</humidity></meteo></livetiming>";
	str=strHeader+StrMeteo;
return str;
}
//------------------------------------------------------------------------------
AnsiString rus[]={" ","А", "а", "Б","б","В","в","Г","г","Ґ","ґ","Д","д","Е","е","Є", "є", "Ж", "ж", "З", "з", "И", "и", "І", "і", "Ї", "ї", "Й", "й", "К", "к",
"Л", "л", "М", "м", "Н", "н", "О", "о", "П", "п","Р", "р", "С", "с", "Т", "т", "У", "у", "Ф", "ф","Х", "х", "Ц", "ц", "Ч", "ч","Ш", "ш",
"Щ", "щ", "Ь", "ь", "Ю", "ю","Я", "я", "Ы", "ы", "Ъ", "ъ", "Ё", "ё", "Э", "э"};

AnsiString eng[]={" ","A", "a", "B", "b","V", "v","G", "g", "G", "g", "D", "d", "E", "e", "E", "E", "Zh", "zh", "Z", "z", "I", "i", "I", "I", "Yi", "yi", "J", "j", "K", "k",
"L", "l", "M", "m", "N", "n", "O", "o", "P", "p","R", "r", "S", "s", "T", "t", "U", "u", "F", "f","KH", "kh", "TS", "ts", "CH", "ch", "SH", "sh",
"SHH", "shh", "'", "'", "YU", "yu","YA", "ya", "Y", "y", "", "", "YO", "yo", "E", "e"};
AnsiString toLatin(AnsiString &srussian){
AnsiString ret="",senglish="",rLet,eLet;
int iN=srussian.Length(),iNN=sizeof(rus)/sizeof(rus[0]);
	for(int i=0; i<iN; i++){
		auto find=false;
		rLet=srussian.c_str()[i];
		eLet=rLet;
		for(int j=0;j<iNN;j++){
			if(rLet==rus[j]){
				eLet=eng[j];
				senglish+=eLet;
				find=true;
				break;
			}
		}
		if(!find)
			senglish+=eLet;
	}
	ret=senglish;
return ret;
}
//______________________________________________________________________________
String __fastcall RaceList::LiveFISRacestartLIST(int srun,String filename){
String str,strTIME;
String sRUN=String(srun);
String sCODEX=getCodex();
String sPASSWORD=getLiveFISpassword();
DateTimeToString(strTIME, "hhmmsszzz", Now());
String sSEQUENCE=strTIME;
DateTimeToString(strTIME, "h:mm:ss", Now());
String sTIMESTAMP=strTIME;

	LoadFromCSV(filename+".csv");
	saveXML(filename+".xml");
	loadXML(filename+".xml");

	int rSize=getRacersN();

	AnsiString work="";
	String order,nat,fa,im,fc,fio,yob;
	String  TOTAL,item,i1,i2,i3,i4,i5,i6,i7,i8;
	DateTimeToString(strTIME, "hh:mm:ss", Now());
	 i1="<?xml version=\"1.0\" encoding=\"UTF-8\"?><livetiming codex=\"";
	 String i22=sCODEX;
	 i3="\" passwd=\"";
	 String i23=sPASSWORD;
	 #if 0
		 i4="\" sequence=\"";
		 String i24=sSEQUENCE;
	 #else
	 #endif
	 i5="\" timestamp=\"";
	 String i25=strTIME;
	 i6="\"><startlist runno=\"1\">";

	 #if 0
		TOTAL=i1+i22+i3+i23+i4+i24+i5+i25+i6;//sCODEX;//+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">";
	 #else
		TOTAL=i1+i22+i3+i23+i5+i25+i6;//sCODEX;//+"\" passwd=\""+sPASSWORD+"\" sequence=\"" + sSEQUENCE + "\" timestamp=\""+strtime+"\">";
	 #endif
	String str1,str2,str3;
	int iSN=0;
	for (auto iirs = 1;iirs<rSize;++iirs){
		str1="";str2="";str3="";
		order=getRacer(iirs,0);
		if (order.Length()==0)continue;
        iSN++;
		fc=getRacer(iirs,1);
		nat=getRacer(iirs,9);
		if (nat.Length()==0) {
			nat="RUS";
		}
		str2=fc;
		str1=getRacer(iirs,8);
		if(str1.Length()==0){
			AnsiString sstr1=getRacer(iirs,2);
			sstr1=toLatin(sstr1);
			str1=sstr1.c_str();
		}

		str1=str1.Trim();
		auto pos = str1.Pos(" ");

		if(pos>0){
			str2 = str1.SubString(0,pos-1);
			str3 = str1.SubString(pos+1,str1.Length()-pos);
		}
		else
			str2 = str1,str3 ="";

		 i1="<racer order=\"";
		 i2= order;
		 i3="\"><bib>";
		 i4="</bib><lastname>";
		 i5=str2;
		 i6="</lastname><firstname>";
		 i7=str3;
		 i8="</firstname><nat>"+nat+"</nat><fiscode>"+fc+"</fiscode></racer>";
		im=im;
		item=i1+i2+i3+i2+i4+i5+i6+i7+i8;
		TOTAL+=item;
	}
	i1="</startlist></livetiming>";
	TOTAL+=i1;
	str=TOTAL;
return str;
}

//______________________________________________________________________________
void RaceResults::saveXML(String filename){
  TXMLDocument* racelistXML = new TXMLDocument(NULL);
   try{
	   racelistXML->Active=true;
		racelistXML->Encoding = "UTF-8";
		racelistXML->Options = racelistXML->Options << doNodeAutoIndent;
		_di_IXMLNode nodElement = racelistXML->CreateElement(L"RaceResults", L"");
		racelistXML->ChildNodes->Add(nodElement);

		int rSize=Results.size();
		int rrs;
		IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Title");
		rrs=Results[1].size();
		rrs=Results[0].size();
		AnsiString work="",w1;
		for (auto iirs = 0;iirs<rrs;++iirs){
			w1=Results[0][iirs].c_str();
			work+=w1+";";
		}
		nodNew->SetAttribute("TitleNames", work);

		for (auto irs = 0;irs<rSize;++irs){
			IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"RacerResults");
			rrs=Results[irs].size();
			for (auto iirs = 0;iirs<rrs;++iirs){
				nodNew->SetAttribute(Results[0][iirs].c_str(), Results[irs][iirs].c_str());
			}
		}
		racelistXML->SaveToFile(filename.c_str());
  }
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//____________________________________________________________________________
void RaceList::LoadFromCSV(String filename){
	TStringList *SL;
	AnsiString astr;
	String Str;

	SL = new TStringList;
	SL->LoadFromFile(filename);
	auto num1 = SL->Count;

	vector <String> *RacerString;
	Racers.clear();

	for (int i = 0; i < num1; i++) {
		astr=SL->Strings[i];
		if (astr.Length()==0)
			continue;
		int ipos=1,ipos1;
		ipos1=PosEx(";",astr,ipos);
		RacerString=new vector <String>;
		while(ipos1>0){
			Str=astr.SubString(ipos,ipos1-ipos);
			ipos=ipos1+1;
			RacerString->push_back(Str);
			ipos1=PosEx(";",astr,ipos);
		}
		Str=astr.SubString(ipos,astr.Length()-ipos+1);
		RacerString->push_back(Str);
		Racers.push_back(*RacerString);
		delete RacerString;
	}
}
//____________________________________________________________________________
void RaceList::saveXML(String filename){
String Str;
  TXMLDocument* racelistXML = new TXMLDocument(NULL);
   try{
	   racelistXML->Active=true;
		racelistXML->Encoding = "UTF-8";
		racelistXML->Options = racelistXML->Options << doNodeAutoIndent;
		_di_IXMLNode nodElement = racelistXML->CreateElement(L"RaceList", L"");
		racelistXML->ChildNodes->Add(nodElement);

		int rSize=Racers.size();
		int rrs;
		IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Title");
		rrs=Racers[1].size();
		rrs=Racers[0].size();
		AnsiString work="",w1;
		for (auto iirs = 0;iirs<rrs;++iirs){
			w1=Racers[0][iirs]/*.c_str()*/;
			work+=w1+";";
		}
		nodNew->SetAttribute("TitleNames", work);

		for (auto irs = 0;irs<rSize;++irs){
			IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Racer");
			rrs=Racers[irs].size();
			for (auto iirs = 0;iirs<rrs;++iirs){
				Str=Racers[irs][iirs];
				nodNew->SetAttribute(Racers[0][iirs]/*.c_str()*/, Racers[irs][iirs]/*.c_str()*/);
			}
		}
		racelistXML->SaveToFile(filename/*.c_str()*/);
  }
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//____________________________________________________________________________
void RaceList::loadXML(String filename){
String workstring;
string  item;
AnsiString astr;
IXMLNode *nodElement,*titleElement;

	vector <String> *RacerString;
	vector <String> TitleString;


	TXMLDocument *racelistXML = new TXMLDocument(Application);
	try{
		racelistXML->LoadFromFile(filename);
		racelistXML->Active = true;
		IXMLNode *XMLDoc = racelistXML->DocumentElement;
		const auto count = racelistXML->ChildNodes->Count;
		const auto n=XMLDoc->ChildNodes->Count;

		Racers.clear();
		for (int i = 0; i < n; i++){
			RacerString=new vector <String>;
			nodElement = XMLDoc->ChildNodes->Nodes[i];
			astr=nodElement->GetNodeName();
			if(astr=="Title"){
				astr=nodElement->GetAttribute("TitleNames");
				item=astr.c_str();
				regex re("[;]");
				sregex_token_iterator it(item.begin(), item.end(), re, -1);
				sregex_token_iterator reg_end;
				TitleString.clear();
				for (; it != reg_end; ++it) {
					String Str;
					item=it->str();
                    Str=item.c_str();
					TitleString.push_back(Str);
				}
			}
			else{
				for (int jj = 0; jj < TitleString.size(); jj++) {
						astr=TitleString[jj].c_str();
						workstring=nodElement->GetAttribute(astr);
						AnsiString ss=workstring;
						RacerString->push_back(ss.c_str());
				}
				Racers.push_back(*RacerString);
				delete RacerString;
				RacerString=NULL;
			}
		}
	}
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//---------------------------------------------------------------------------
void __fastcall Races::showView(){
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
}
//------------------------------------------------------------------------------
void __fastcall Races::Locations(TForm* form){
String str;
_viewRL *vsl;
int iN;

	if(!viewSL.empty()){
		viewSL.clear();
		delete eCompetition;
		delete lbl;
		delete panel3;
		delete panel2;
		delete panel1;
	}
	iN=this->getRacesN();

	panel1= new TPanel(form);
	panel1->Parent = form;
	panel1->Name="P1";
	panel1->Font->Size=12;
	panel1->Alignment=taLeftJustify;
	panel1->VerticalAlignment=taAlignTop;
	panel1->Top=3;
	panel1->Left=2;
	panel1->Width=pRaceViews->Width-panel1->Left;
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
	panel2->Top=18;
	panel2->Left=2;
	panel2->Width=panel1->Width-panel2->Left;
	panel2->Visible=true;
	panel2->Caption="";

	eCompetition=new TEdit(panel2);
	eCompetition->Parent = panel2;
	eCompetition->Name="P2";
	eCompetition->Font->Size=12;
	eCompetition->Top=18;
	eCompetition->Left=34;
	eCompetition->Width=90;
	eCompetition->Visible=true;
	eCompetition->Text="";


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

	lbl= new TLabel(pRaceViews);
	lbl->Name="Label"+pRaceViews->Name;
	lbl->OnMouseDown=mouse_down;
	lbl->OnDblClick=mouse_DblClick;


	viewSL.reserve(iN);
	auto sz= viewSL.capacity();
	for(int i=0;i<iN;++i){
		vsl=new _viewRL(panel3,i,this,lbl);
		viewSL.push_back(*vsl);
		if(sz!=viewSL.capacity()){
			sz=viewSL.capacity();
		}
	}
	///String *sss=(String*)viewSL.data();
	panel3->Height=48+(iN+1)*vsl->SN->Height;
	panel2->Height=panel3->Height;
	panel1->Height=panel2->Height+2;
	panel3->Color=clGradientActiveCaption;
	panel2->Color=clAqua;
	panel1->Color=clLime;
	panel1->ShowCaption=true;panel1->Caption="Регистрация";panel1->Font->Size=10;
	panel2->ShowCaption=true;panel2->Caption="соревнований:";panel2->Font->Size=panel1->Font->Size;
	panel3->ShowCaption=true;panel3->Caption="3333333";panel3->Font->Size=panel1->Font->Size;
	panel3->Width=viewSL[0].SN->Width+viewSL[0].RCodex->Width+3*2;
	panel2->Width=panel3->Width+2*panel3->Left;
	panel1->Width=panel2->Width+2*panel2->Left;
	pRaceViews->Width=panel1->Width+2*panel1->Left+15;
	pRaceViews->Height=panel1->Height+40;

	TBorderIcons tempBI = pRaceViews->BorderIcons;
//	tempBI >> biSystemMenu;
	tempBI >> biMinimize;
	tempBI >> biMaximize;
	tempBI >> biHelp;
	pRaceViews->BorderIcons = tempBI;

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


void __fastcall Races::form_key_down(TObject *Sender, WORD &Key, TShiftState Shift){
int ik=Key;
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
	}
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
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
	ih=viewSL[0].SN->Height;
	itop=viewSL[0].SN->Top+3*ih;
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
void __fastcall Races::mouse_down(TObject *Sender, TMouseButton Button,
  TShiftState Shift, int X, int Y){
	ilastcurrRace=icurrRace;
	icurrRace=dynamic_cast<TLabel*>(Sender)->Tag;
	std::for_each(viewSL.begin(),viewSL.end(),setRacersColor);
}//end of proc
//------------------------------------------------------------------------------
void __fastcall Races::mouse_DblClick(TObject *Sender)
{
int i;
}
//_____________________________________________________________________________


#pragma package(smart_init)
