//---------------------------------------------------------------------------

#pragma hdrstop

#include "Competition.h"
//____________________________________________________________________________
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <Xml.XMLDoc.hpp>
//____________________________________________________________________________
void RaceList::LoadFromCSV(AnsiString filename){
  TStringList *SL;
  string  item;
  AnsiString astr;

  SL = new TStringList;
  SL->LoadFromFile(filename);
  auto num1 = SL->Count;

  vector <string> *RacerString;
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
void RaceList::saveXML(AnsiString filename){
  TXMLDocument* racelistXML = new TXMLDocument(NULL);
   try{
	   racelistXML->Active=true;
		racelistXML->Encoding = "UTF-8";
		racelistXML->Options = racelistXML->Options << doNodeAutoIndent;
		_di_IXMLNode nodElement = racelistXML->CreateElement(L"RaceList", L"");
		racelistXML->ChildNodes->Add(nodElement);

		int rSize=Racers.size();
		int rrs;
		for (auto irs = 0;irs<rSize;++irs){
			IXMLNode *nodNew = racelistXML->ChildNodes->Last()->AddChild(L"Racer");
			rrs=Racers[irs].size();
			for (auto iirs = 0;iirs<rrs;++iirs){
				nodNew->SetAttribute(Racers[0][iirs].c_str(), Racers[irs][iirs].c_str());
			}
		}
		racelistXML->SaveToFile(filename);
  }
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//____________________________________________________________________________
void RaceList::loadXML(AnsiString filename){
String  SN,FC,RNAM,RNAT,GBJ,RREG,RORT,RRAS,LNAM,LNAT;
IXMLNode *nodElement;
	TXMLDocument *racelistXML = new TXMLDocument(Application);
	try{
		racelistXML->LoadFromFile(filename);
		racelistXML->Active = true;
		IXMLNode *XMLDoc = racelistXML->DocumentElement;
		const auto count = racelistXML->ChildNodes->Count;
		const auto n=XMLDoc->ChildNodes->Count;
		for (int i = 0; i < n; i++){
			nodElement = XMLDoc->ChildNodes->Nodes[i];
			SN = nodElement->GetAttribute("SN");
			FC= nodElement->GetAttribute("FC");
			RNAM= nodElement->GetAttribute("RNAM");
			RNAT= nodElement->GetAttribute("RNAT");
			GBJ= nodElement->GetAttribute("GBJ");
			RREG= nodElement->GetAttribute("RREG");
			RORT= nodElement->GetAttribute("RORT");
			RRAS= nodElement->GetAttribute("RRAS");
			LNAM= nodElement->GetAttribute("LNAM");
			LNAT= nodElement->GetAttribute("LNAT");
		}
	}
	__finally {
		FreeAndNil(&racelistXML); delete racelistXML;
	}
}
//____________________________________________________________________________
void __fastcall RaceList::Locations(TForm* form){
/*	panel= new TPanel(form);
	panel->Parent = form;
	panel->Font->Size=14;              8
	panel->Alignment=taLeftJustify;
	panel->VerticalAlignment=taAlignTop;
	panel->Top=10;
	panel->Left=1;
	panel->Visible=true;
	str.sprintf("RaceList%d",sN);
	panel->Caption=str;
*/
}//end of proc

//---------------------------------------------------------------------------
#pragma package(smart_init)
