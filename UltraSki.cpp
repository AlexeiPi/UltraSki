//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UltraSki.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Racer.h"
TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
__fastcall TfUltraSki::TfUltraSki(TComponent* Owner)
	: TForm(Owner)
{
AnsiString astr;
Racer r1("123456","����","��������","������","Ivan","Ivanovich","Ivanov","08.10.1957");
	astr=r1.getFIO(0)+" ������� "+r1.getAge();
	astr=r1.getFIO(1)+" age "+r1.getAge();
	astr=r1.getIOF(0)+" ������� "+r1.getAge();
	astr=r1.getFio(0)+" ������� "+r1.getAge();
	astr=r1.getioF(0)+" ������� "+r1.getAge();
	astr=r1.getIOF(1)+" age "+r1.getAge();
	astr=r1.getFio(1)+" age "+r1.getAge();
	astr=r1.getioF(1)+" age "+r1.getAge();
    astr=r1.getFIScode();

}
//---------------------------------------------------------------------------
void __fastcall TfUltraSki::Timer1Timer(TObject *Sender)
{
	fUltraSki->Caption="ULTRASKI "+Now().FormatString("dd.mm.yyyy hh:mm:ss");
}
//---------------------------------------------------------------------------

