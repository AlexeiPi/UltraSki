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
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall lClearClick(TObject *Sender);
	void __fastcall LiveFISStatus(TObject *ASender, const TIdStatus AStatus, const UnicodeString AStatusText);
	void __fastcall LiveFISWorkBegin(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCountMax);
	void __fastcall lRaceInfoClick(TObject *Sender);
	void __fastcall lMessageClick(TObject *Sender);
	void __fastcall lActiveRunClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall lMessage1Click(TObject *Sender);
	void __fastcall lHumidityClick(TObject *Sender);





private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
#endif
