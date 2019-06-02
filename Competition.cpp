//---------------------------------------------------------------------------

#pragma hdrstop

#include "Competition.h"
#include <StrUtils.hpp>
TIniFile *IniUltraAlpSki;//ini file
AnsiString toLatin(AnsiString &srussian);
//____________________________________________________________________________
//-----------------------------------------------------------------------------

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
	String sRUNNO=run;

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
String __fastcall Race::LiveFISRacemessage(String anymessage){

String str,strTIME,message;
AnsiString astr;
	astr=anymessage;
	astr=toLatin(astr);
	message=astr;

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
AnsiString toLatin(AnsiString &srussian){
AnsiString ret="",senglish="",rLet,eLet;
AnsiString rus[]={" ","À", "à", "Á","á","Â","â","Ã","ã","Ä","ä","Å","å","¨", "¸", "Æ", "æ", "Ç", "ç", "È", "è", "É", "é", "Ê", "ê",
"Ë", "ë", "Ì", "ì", "Í", "í", "Î", "î", "Ï", "ï","Ð", "ð", "Ñ", "ñ", "Ò", "ò", "Ó", "ó", "Ô", "ô","Õ", "õ", "Ö", "ö", "×", "÷","Ø", "ø",
"Ù", "ù", "Ü", "ü", "Þ", "þ","ß", "ÿ", "Û", "û", "Ú", "ú", "¨", "¸", "Ý", "ý"};

AnsiString eng[]={" ","A", "a", "B", "b","V", "v","G", "g", "D", "d", "E", "e", "E", "e", "Zh", "zh", "Z", "z", "I", "i",  "I", "i", "K", "k",
"L", "l", "M", "m", "N", "n", "O", "o", "P", "p","R", "r", "S", "s", "T", "t", "U", "u", "F", "f","KH", "kh", "TS", "ts", "CH", "ch", "SH", "sh",
"SHCH", "shch", "", "", "IU", "iu","IA", "ia", "Y", "y", "", "", "E", "e", "E", "e"};

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

/*	LoadFromCSV(filename+".csv");
	saveXML(filename+".xml");
	loadXML(filename+".xml");
*/

	if(filename.Pos(".xml")==0)
	   filename+=".xml";
	loadXML(filename);
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
			w1=Racers[0][iirs];
			work+=w1+";";
		}
		nodNew->SetAttribute("TitleNames", work);

		for (auto irs = 0;irs<rSize;++irs){
			IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Racer");
			rrs=Racers[irs].size();
			for (auto iirs = 0;iirs<rrs;++iirs){
				Str=Racers[irs][iirs];
				nodNew->SetAttribute(Racers[0][iirs], Racers[irs][iirs]);
			}
		}
		racelistXML->SaveToFile(filename);
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
/*				item=astr.c_str();
				regex re(";");
				sregex_token_iterator it(item.begin(), item.end(), re, -1);
				sregex_token_iterator reg_end;
				TitleString.clear();
				for (; it != reg_end; ++it) {
					String Str;
					item=it->str();
					Str=item.c_str();
					TitleString.push_back(Str);
				}
*/
				int ipos1,ipos2,ipos3;
				AnsiString substr;
				ipos1=0;
				TitleString.clear();
				while (1){
					ipos2=PosEx(";", astr, ipos1+1);
					if (ipos2>0) {
						substr=astr.SubString(ipos1+1,ipos2-ipos1-1);
						TitleString.push_back(substr);
						ipos1=ipos2;
					}
					else{
						break;
					}

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
#pragma package(smart_init)
