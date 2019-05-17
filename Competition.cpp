//---------------------------------------------------------------------------

#pragma hdrstop

#include "Competition.h"
//____________________________________________________________________________
void RaceResults::LoadFromCSV(string filename){
	TStringList *SL;
	string  item;
	AnsiString astr;

	SL = new TStringList;
	SL->LoadFromFile(filename.c_str());
	auto num1 = SL->Count;

	vector <string> *RacerResults;
	Results.clear();
	for (int i = 0; i < num1; i++) {
		astr=SL->Strings[i];
		item=astr.c_str();
		regex re("[;]");
		sregex_token_iterator it(item.begin(), item.end(), re, -1);
		sregex_token_iterator reg_end;
		RacerResults=new vector <string>;
		for (; it != reg_end; ++it) {
			 RacerResults->push_back(it->str());
		}
		Results.push_back(*RacerResults);
		delete RacerResults;
	}
}
//____________________________________________________________________________
void RaceResults::saveXML(string filename){
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
void RaceList::LoadFromCSV(string filename){
	TStringList *SL;
	string  item;
	AnsiString astr;

	SL = new TStringList;
	SL->LoadFromFile(filename.c_str());
	auto num1 = SL->Count;

	vector <string> *RacerString;
	Racers.clear();
	for (int i = 0; i < num1; i++) {
		astr=SL->Strings[i];
		item=astr.c_str();
		regex re("[;]");
		sregex_token_iterator it(item.begin(), item.end(), re, -1);
		sregex_token_iterator reg_end;
		RacerString=new vector <string>;
		for (; it != reg_end; ++it) {
			 RacerString->push_back(it->str());
		}
		Racers.push_back(*RacerString);
		delete RacerString;
	}
}
//____________________________________________________________________________
void RaceList::saveXML(string filename){
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
			w1=Racers[0][iirs].c_str();
			work+=w1+";";
		}
		nodNew->SetAttribute("TitleNames", work);

		for (auto irs = 0;irs<rSize;++irs){
			IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Racer");
			rrs=Racers[irs].size();
			for (auto iirs = 0;iirs<rrs;++iirs){
				nodNew->SetAttribute(Racers[0][iirs].c_str(), Racers[irs][iirs].c_str());
			}
		}
		racelistXML->SaveToFile(filename.c_str());
  }
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//____________________________________________________________________________
void RaceList::loadXML(string filename){
String workstring;
string  item;
AnsiString astr;
IXMLNode *nodElement,*titleElement;

	vector <string> *RacerString;
	vector <string> TitleString;


	TXMLDocument *racelistXML = new TXMLDocument(Application);
	try{
		racelistXML->LoadFromFile(filename.c_str());
		racelistXML->Active = true;
		IXMLNode *XMLDoc = racelistXML->DocumentElement;
		const auto count = racelistXML->ChildNodes->Count;
		const auto n=XMLDoc->ChildNodes->Count;

		Racers.clear();
		for (int i = 0; i < n; i++){
			RacerString=new vector <string>;
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
					TitleString.push_back(it->str());
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
//____________________________________________________________________________
/*
void __fastcall RaceList::Locations(TForm* form){
	panel= new TPanel(form);
	panel->Parent = form;
	panel->Font->Size=14;              8
	panel->Alignment=taLeftJustify;
	panel->VerticalAlignment=taAlignTop;
	panel->Top=10;
	panel->Left=1;
	panel->Visible=true;
	str.sprintf("RaceList%d",sN);
	panel->Caption=str;

}//end of proc
*/
//---------------------------------------------------------------------------
#pragma package(smart_init)
