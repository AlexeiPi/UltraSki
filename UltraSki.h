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
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.Dialogs.hpp>

//---------------------------------------------------------------------------
class TfUltraSki : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TXMLDocument *XMLDocument1;
	TIdTCPClient *LiveFIS;
	TADOTable *ADOTable1;
	TDataSource *DataSource1;
	TADOConnection *ADOConnection1;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *Edit1;
	TFileOpenDialog *FileOpenDialog1;
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton2;
	void __fastcall Timer1Timer(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
#endif
