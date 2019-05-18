//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UltraSki.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Racer.h"
#include "Competition.h"
#include "RaceViews.h"
TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
__fastcall TfUltraSki::TfUltraSki(TComponent* Owner)
	: TForm(Owner){
AnsiString astr;
	Person p1("Иван","Иванович","Иванов","Ivan","Ivanovich","Ivanov","08.10.1957");
	Racer *r1=new Racer;

	r1->setFIScode("123456");
	r1->setPerson(&p1);
	astr=r1->getFIScode();

///	Racer r1("123456","Иван","Иванович","Иванов","Ivan","Ivanovich","Ivanov","08.10.1957");

	astr=r1->getFIO(0)+" возраст "+r1->getAge();
	astr=r1->getFIO(1)+" age "+r1->getAge();
	astr=r1->getIOF(0)+" возраст "+r1->getAge();
	astr=r1->getFio(0)+" возраст "+r1->getAge();
	astr=r1->getioF(0)+" возраст "+r1->getAge();
	astr=r1->getIOF(1)+" age "+r1->getAge();
	astr=r1->getFio(1)+" age "+r1->getAge();
	astr=r1->getioF(1)+" age "+r1->getAge();

	RaceList rcl;
	rcl.LoadFromCSV("C:\\test\\RPT_Start_910.csv");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");
	rcl.loadXML("C:\\test\\RPT_Start_910.xml");
	rcl.saveXML("C:\\test\\RPT_Start_910.xml");

	RaceStartListView rsl;
	rsl.showView();

}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::Timer1Timer(TObject *Sender){
//auto поw = std::chrono::system_clock::поw();
	fUltraSki->Caption="ULTRASKI "+Now().FormatString("dd.mm.yyyy hh:mm:ss");
}//end of proc
//---------------------------------------------------------------------------



