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

//---------------------------------------------------------------------------
class TfUltraSki : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TXMLDocument *XMLDocument1;
	TLabel *lClear;
	TIdTCPClient *LiveFIS;
	TLabel *lClearResponse;
	TLabel *lRaceInfo;
	TLabel *lRaceInfoResponse;
	TLabel *lMessage;
	TLabel *lMessageResponse;
	TLabel *lActiveRun;
	TLabel *lActiveRunResponse;
	TLabel *lMessage1;
	TLabel *lMessage1Response;
	TLabel *lHumidity;
	TLabel *lHumidityResponse;
	TADOTable *ADOTable1;
	TDataSource *DataSource1;
	TADOConnection *ADOConnection1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall lMessage1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
#endif
