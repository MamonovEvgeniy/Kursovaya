//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AboutForm.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
	Timer1->Enabled=false;
	AboutBox->Hide();
}
//---------------------------------------------------------------------------


void __fastcall TAboutBox::Timer1Timer(TObject *Sender)
{
	static int animation;
	switch (animation)
	{
		case 0:
			Image1->Show();
			Image2->Hide();
		break;
		case 1:
			Image2->Show();
			Image1->Hide();
		break;
		case 2:
			Image3->Show();
			Image2->Hide();
		break;
		case 3:
			Image4->Show();
			Image3->Hide();
		break;
		case 4:
			Image5->Show();
			Image4->Hide();
		break;
		case 5:
			Image6->Show();
			Image5->Hide();
		break;
		case 6:
			Image7->Show();
			Image6->Hide();
		break;
		case 7:
			Image8->Show();
			Image7->Hide();
		break;
		case 8:
			Image9->Show();
			Image8->Hide();
		break;
		case 9:
			Image10->Show();
			Image9->Hide();
		break;
		case 10:
			Image11->Show();
			Image10->Hide();
		break;
		case 11:
			Image12->Show();
			Image11->Hide();
		break;
		case 12:
			Image13->Show();
			Image12->Hide();
		break;
		case 13:
			Image14->Show();
			Image13->Hide();
		break;
		case 14:
			Image15->Show();
			Image14->Hide();
		break;
		case 15:
			Image16->Show();
			Image15->Hide();
		break;
		case 16:
			Image17->Show();
			Image16->Hide();
		break;
		case 17:
			Image18->Show();
			Image17->Hide();
		break;
		case 18:
			Image19->Show();
			Image18->Hide();
		break;
		case 19:
			Image20->Show();
			Image19->Hide();
		break;
		case 20:
			Image21->Show();
			Image20->Hide();
		break;
		case 21:
			Image20->Show();
			Image21->Hide();
		break;
		case 22:
			Image19->Show();
			Image20->Hide();
		break;
		case 23:
			Image18->Show();
			Image19->Hide();
		break;
		case 24:
			Image17->Show();
			Image18->Hide();
		break;
		case 25:
			Image16->Show();
			Image17->Hide();
		break;
		case 26:
			Image15->Show();
			Image16->Hide();
		break;
		case 27:
			Image14->Show();
			Image15->Hide();
		break;
		case 28:
			Image13->Show();
			Image14->Hide();
		break;
		case 29:
			Image12->Show();
			Image13->Hide();
		break;
		case 30:
			Image11->Show();
			Image12->Hide();
		break;
		case 31:
			Image10->Show();
			Image11->Hide();
		break;
		case 32:
			Image9->Show();
			Image10->Hide();
		break;
		case 33:
			Image8->Show();
			Image9->Hide();
		break;
		case 34:
			Image7->Show();
			Image8->Hide();
		break;
		case 35:
			Image6->Show();
			Image7->Hide();
		break;
		case 36:
			Image5->Show();
			Image6->Hide();
		break;
		case 37:
			Image4->Show();
			Image5->Hide();
		break;
		case 38:
			Image3->Show();
			Image4->Hide();
		break;
		case 39:
			Image2->Show();
			Image3->Hide();
			animation=-1;
		break;
	}
	animation++;
}
//---------------------------------------------------------------------------

