//---------------------------------------------------------------------------

#ifndef UltraSkiH
#define UltraSkiH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "IniFiles.hpp"
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

//---------------------------------------------------------------------------
class TfUltraSki : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TXMLDocument *XMLDocument1;
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
#endif
