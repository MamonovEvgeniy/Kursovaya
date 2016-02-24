//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ships.res");
USEFORM("shipsu.cpp", Form1);
USEFORM("AboutForm.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->HelpFile = "hhh.hlp";
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
