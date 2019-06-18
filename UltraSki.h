//---------------------------------------------------------------------------

#ifndef UltraSkiH
#define UltraSkiH

#define BOOST_USE_WINDOWS_H

//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTP.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <System.Classes.hpp>
#include <Vcl.Imaging.pngimage.hpp>


	#include "IniFiles.hpp"
	#include <System.ImageList.hpp>
	#include "System.SysUtils.hpp"
	#include "System.Zip.hpp"
	#include <System.IOUtils.hpp>

	#include <Vcl.BaseImageCollection.hpp>
	#include <Vcl.Dialogs.hpp>
	#include <Vcl.ImageCollection.hpp>
	#include <Vcl.Imaging.jpeg.hpp>
	#include <Vcl.Imaging.GIFImg.hpp>
	#include <Vcl.ImgList.hpp>
	#include <Vcl.Mask.hpp>

	#include <Xml.XMLDoc.hpp>
	#include <Xml.xmldom.hpp>
	#include <Xml.XMLIntf.hpp>

	#include <Data.DB.hpp>
	#include <Data.Win.ADODB.hpp>

	//---------------------------------------------------------------------------
	#include <DateUtils.hpp>

	#include <fstream>
	#include <iostream>
	#include <stdlib.h>

	//---------------------------------------------------------------------------
	#include <algorithm>
	#include <vector>
	#include <shellapi.h>
//---------------------------------------------------------------------------
extern TIniFile *IniUltraAlpSki;//ini file
extern TIniFile *IniUltraTimeKeeping;//ini file
extern TIdTCPClient *LiveFIS;

AnsiString toLatin(AnsiString &srussian);
void __fastcall SetClipBoard(AnsiString aboard);
//---------------------------------------------------------------------------
/*using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;
*/

//============================================================================

//============================================================================

using namespace std;
//---------------------------------------------------------------------------
AnsiString __fastcall _getTimeHHSSZZZ(void);
AnsiString __fastcall _getTimeHHSSZZZZ(void);
//---------------------------------------------------------------------------
class TfUltraSki : public TForm{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TImage *Image1;
	TImage *Image2;
	TLabel *pINFO;
	TEdit *emessage2FIS;
	TImage *imTimeMachine;
	TIdHTTP *IdHTTP1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TMemo *Memo1;
	TLabel *Label1;
	TIdFTP *FISftp;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall pINFOClick(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall imTimeMachineClick(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);

private:	// User declarations
public:		// User declarations
	__fastcall TfUltraSki(TComponent* Owner);
    void __fastcall MyException( TObject *Sender, Exception *E );
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
