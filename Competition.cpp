//---------------------------------------------------------------------------

#pragma hdrstop

#include "Competition.h"
//____________________________________________________________________________

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


//____________________________________________________________________________
void RaceList::LoadFromExcel(AnsiString filename){
  TStringList *SL;
  string  item,i1,logi1,lastlogi1;
  AnsiString astr,lastastr;
  String str;

  SL = new TStringList;
  SL->LoadFromFile(filename);
  auto num1 = SL->Count;

  vector <string> RacerString;


  for (int i = 0; i < num1; i++) {
	// lastastr=astr;
	astr=SL->Strings[i];
	item=astr.c_str();
	regex re("[;]");
	sregex_token_iterator it(item.begin(), item.end(), re, -1);
	sregex_token_iterator reg_end;
	//int ilen =re;
	//logi1="";
	for (; it != reg_end; ++it) {
		 i1=it->str();
		 RacerString.push_back(it->str());
	//	 i1=it->str();
	//	 logi1+=i1+" ";
	}
   //	i1 = to_string(RacerString.size());
   //	logi1+=i1;
   //	lastlogi1=logi1;
	Racers.push_back(RacerString);
	RacerString.erase(RacerString.begin());
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
