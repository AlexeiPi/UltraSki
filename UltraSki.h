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
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>

//---------------------------------------------------------------------------
class TfUltraSki : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TImage *Image1;
	TImage *Image2;
	TLabel *pINFO;
	TEdit *emessage2FIS;
	TImage *Image3;
	TIdHTTP *IdHTTP1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TMemo *Memo1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall pINFOClick(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
    void __fastcall MyException( TObject *Sender, Exception *E );
};
//---------------------------------------------------------------------------
extern PACKAGE TfUltraSki *fUltraSki;
//---------------------------------------------------------------------------
#endif
