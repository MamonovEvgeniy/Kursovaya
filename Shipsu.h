//---------------------------------------------------------------------------
#ifndef shipsuH
#define shipsuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include<conio>
#include<dos>
#include<sys/stat>
#include<io>
#include<stdlib>
#include<mmsystem.hpp>
//---------------------------------------------------------------------------
const crMyCursor=1;
const crMyCursorh=2;
unsigned blok_up=0;
int shift_X;
int shift_Y;
int ship4=0;
int ship3=0;
int ship2=0;
int ship1=0;
int cover=0;
int count=0;
int count_sh=0;
int vector=1;
int fign[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int fign1[10]={1,2,2,3,3,3,4,4,4,4};		// количество фигур
int fign2[9]= {1,1,2,2,2,3,3,3,3};		// количество фигур
int fign3[12]={2,2,3,3,3,3,4,4,4,4,4,4};		// количество фигур
int array_choice[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int shoot_man=0;
int shoot_comp=0;
int covered_man=0;
int covered_comp=0;
int side_x_y=0;
int last_x;
int last_y;
int need=0;
int need_man=0;
int need_x=-1;
int need_y;
int result;
int left_right;
int right_x;
int right_y;
int last_x_show;
int last_y_show;
int tired_x=-1;
int tired_y;
int radar_sensitivity=3;
int set_radar=0;
int arr_radar[30]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
				   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int vect_12_wm=0;	  // 1 max 1
int vect_13_wm=0;
int vect_14_wm=0;
int vect_12_om=0;
int vect_13_om=0;
int vect_14_om=0;
int vect_12_nm=0;
int vect_13_nm=0;
int vect_14_nm=0;
int vect_12_sm=0;
int vect_13_sm=0;
int vect_14_sm=0;
int vect_12_w=0;	  // 1 max 1
int vect_13_w=0;
int vect_14_w=0;
int vect_12_o=0;
int vect_13_o=0;
int vect_14_o=0;
int vect_12_n=0;
int vect_13_n=0;
int vect_14_n=0;
int vect_12_s=0;
int vect_13_s=0;
int vect_14_s=0;
int first=0;
int count_think=0;
int repeat=0;
int count_mach=0;
int tired=0;
int ms=0;
int last_ship[4]={0,0,0,0};
int con_man=0;
//-----------------------------------------------------------------------------
class Field
{
private:
	int array[16][16];
	int array_deep[16][16];
	int count;
	int count_sum;
public:
	Field::Field();
	Field::Field(int data);
	Field::~Field();
	void Field::setup(int data);
	int Field::control(int i, int j, int vector, int length, int deep);
	void Field::next_ship( int position_scheme, int deep );
	int Field::show_bit(int x, int y);
	void Field::put_bit(int x, int y, int data);
	int Field::show_bit_deep(int x, int y);
	void Field::put_bit_deep(int x, int y);
	void Field::add_count();
	int Field::show_count();
	void Field::inc_count_sum(int data);
	int Field::show_count_sum();
	void Field::rewrite_arr_ver_gor(int * arr_in, int * arr_out, int len);
};
Field::Field()
{
}
Field::Field(int data)
{
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<16;j++)
		{
			if (i>=3&&i<=12&&j>=3&&j<=12)
				array[i][j]=data;
			else
				array[i][j]=3;
			array_deep[i][j]=data;
		}
		count=data;
		count_sum=data;
	}
}
Field::~Field()
{
}
void Field::setup(int data)
{
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<16;j++)
		{
			if (i>=3&&i<=12&&j>=3&&j<=12)
				array[i][j]=data;
			else
				array[i][j]=3;
			array_deep[i][j]=data;
		}
	}
}
void Field::rewrite_arr_ver_gor(int * arr_in, int * arr_out, int len)
{
	for (int i=0;i<len;i++)
		arr_in[i]=arr_out[i];
}
int Field::control(int i, int j, int vector, int length, int deep)
{
	int ofset=5-length;
	int result=0;
	int length_read=0;
	int array_vertic[38][2]={{-1,-1},
							 { 0,-1},
							 { 0,-2},   //
							 { 0,-3},   //
							 { 1,-1},
							 {-1, 0},
							 {-2, 0},  //
							 {-3, 0},  //
							 { 0, 0},
							 { 1, 0},
							 { 2, 0},   //
							 { 3, 0},   //
							 {-1,ofset},
							 { 0,ofset},
							 { 0,ofset+1}, //
							 { 0,ofset+2}, //
							 { 1,ofset},    //-----------//
							 {-1,ofset-1},
							 {-2,ofset-1},  //
							 {-3,ofset-1},  //
							 { 0,ofset-1},
							 { 1,ofset-1},
							 { 2,ofset-1},  //
							 { 3,ofset-1},  //------------
							 {-1,ofset-2},
							 {-2,ofset-2},  //
							 {-3,ofset-2},  //
							 { 0,ofset-2},
							 { 1,ofset-2},
							 { 2,ofset-2},  //
							 { 3,ofset-2},  //-----------
							 {-1,ofset-3},
							 {-2,ofset-3},  //
							 {-3,ofset-3},  //
							 { 0,ofset-3},
							 { 1,ofset-3},
							 { 2,ofset-3}, //
							 { 3,ofset-3}}; //--------------------
	int array_horiz[38][2]={{-1, 1},
							{-1, 0},
							{-2, 0},     //
							{-3, 0},     //
							{-1,-1},
							{ 0, 1},
							{ 0, 2},     //
							{ 0, 3},     //
							{ 0, 0},
							{ 0,-1},
							{ 0,-2},     //
							{ 0,-3},     //
							{ofset, 1},
							{ofset, 0},
							{ofset+1, 0}, //
							{ofset+2, 0}, //
							{ofset,-1},   //--------//
							{ofset-1, 1},
							{ofset-1, 2}, //
							{ofset-1, 3}, //
							{ofset-1, 0},
							{ofset-1,-1},
							{ofset-1,-2}, //
							{ofset-1,-3}, //-----------
							{ofset-2, 1},
							{ofset-2, 2}, //
							{ofset-2, 3}, //
							{ofset-2, 0},
							{ofset-2,-1},
							{ofset-2,-2}, //
							{ofset-2,-3}, //------------
							{ofset-3, 1},
							{ofset-3, 2}, //
							{ofset-3, 3}, //
							{ofset-3, 0},
							{ofset-3,-1},
							{ofset-3,-2},//
							{ofset-3,-3}};//-------------
	int array_verti2[28][2]={{-1,-1},
							 { 0,-1},
							 { 0,-2},   //
							 { 1,-1},
							 {-1, 0},
							 {-2, 0},  //
							 { 0, 0},
							 { 1, 0},
							 { 2, 0},   //
							 {-1,ofset},
							 { 0,ofset},
							 { 0,ofset+1}, //
							 { 1,ofset},    //-----------//
							 {-1,ofset-1},
							 {-2,ofset-1},  //
							 { 0,ofset-1},
							 { 1,ofset-1},
							 { 2,ofset-1},  //
							 {-1,ofset-2},
							 {-2,ofset-2},  //
							 { 0,ofset-2},
							 { 1,ofset-2},
							 { 2,ofset-2},  //
							 {-1,ofset-3},
							 {-2,ofset-3},  //
							 { 0,ofset-3},
							 { 1,ofset-3},
							 { 2,ofset-3}}; //
	int array_hori2[28][2]={{-1, 1},
							{-1, 0},
							{-2, 0},     //
							{-1,-1},
							{ 0, 1},
							{ 0, 2},     //
							{ 0, 0},
							{ 0,-1},
							{ 0,-2},     //
							{ofset, 1},
							{ofset, 0},
							{ofset+1, 0}, //
							{ofset,-1},   //--------//
							{ofset-1, 1},
							{ofset-1, 2}, //
							{ofset-1, 0},
							{ofset-1,-1},
							{ofset-1,-2}, //
							{ofset-2, 1},
							{ofset-2, 2}, //
							{ofset-2, 0},
							{ofset-2,-1},
							{ofset-2,-2}, //
							{ofset-3, 1},
							{ofset-3, 2}, //
							{ofset-3, 0},
							{ofset-3,-1},
							{ofset-3,-2}};//
	int array_verti1[18][2]={{-1,-1},
							 { 0,-1},
							 { 1,-1},
							 {-1, 0},
							 { 0, 0},
							 { 1, 0},
							 {-1,ofset},
							 { 0,ofset},
							 { 1,ofset},    //-----------//
							 {-1,ofset-1},
							 { 0,ofset-1},
							 { 1,ofset-1},
							 {-1,ofset-2},
							 { 0,ofset-2},
							 { 1,ofset-2},
							 {-1,ofset-3},
							 { 0,ofset-3},
							 { 1,ofset-3}};
	int array_hori1[18][2]={{-1, 1},
							{-1, 0},
							{-1,-1},
							{ 0, 1},
							{ 0, 0},
							{ 0,-1},
							{ofset, 1},
							{ofset, 0},
							{ofset,-1},   //--------//
							{ofset-1, 1},
							{ofset-1, 0},
							{ofset-1,-1},
							{ofset-2, 1},
							{ofset-2, 0},
							{ofset-2,-1},
							{ofset-3, 1},
							{ofset-3, 0},
							{ofset-3,-1}};
	if (deep==0)
		deep=1;
	switch (deep)
	{
		case 2:
			switch (vector)
			{
				case 0:
					rewrite_arr_ver_gor(*array_horiz,*array_hori2,56);
				break;
				case 1:
					rewrite_arr_ver_gor(*array_vertic,*array_verti2,56);
				break;
			}
		break;
		case 1:
			switch (vector)
			{
				case 0:
					rewrite_arr_ver_gor(*array_horiz,*array_hori1,34);
				break;
				case 1:
					rewrite_arr_ver_gor(*array_vertic,*array_verti1,34);
				break;
			}
		break;
	}
	switch ( length )
	{
		case 4:
				switch (deep)
				{
					case 3:length_read=16;			//длина читаемого массива masvg_
					break;
					case 2:length_read=12;			//длина читаемого массива masvg_
					break;
					case 1:length_read=8;			//длина читаемого массива masvg_
					break;
				}
		break;
		case 3:
				switch (deep)
				{
					case 3:length_read=23;			//длина читаемого массива masvg_
					break;
					case 2:length_read=17;			//длина читаемого массива masvg_
					break;
					case 1:length_read=11;			//длина читаемого массива masvg_
					break;
				}
		break;
		case 2:
				switch (deep)
				{
					case 3:length_read=30;			//длина читаемого массива masvg_
					break;
					case 2:length_read=22;			//длина читаемого массива masvg_
					break;
					case 1:length_read=14;			//длина читаемого массива masvg_
					break;
				}
		break;
		case 1:
				switch (deep)
				{
					case 3:length_read=37;			//длина читаемого массива masvg_
					break;
					case 2:length_read=27;			//длина читаемого массива masvg_
					break;
					case 1:length_read=17;			//длина читаемого массива masvg_
					break;
				}
		break;
	}
	switch ( vector )
	{
		case 0:
				for ( int ii=0;ii<=length_read;ii++ )
				{
					if ( array[(i+array_horiz[ii][0]+3)][j+array_horiz[ii][1]+3]==1 )
					{
						result=1;
						break;
					}
				}
				if ( ofset==4&&i>6||ofset==3&&i>7||ofset==2&&i>8 )
				{
					result=1;
				}
				break;
		case 1:
				for ( int ii=0;ii<=length_read;ii++ )
				{
					if ( array[(i+array_vertic[ii][0]+3)][j+array_vertic[ii][1]+3]==1 )
					{
						result=1;
						break;
					}
				}
				if ( ofset==4&&j>6||ofset==3&&j>7||ofset==2&&j>8 )
				{
					result=1;
				}
	}
	if ( result==0 )		 //пишем ship в мссив
	{
		switch ( vector )
		{
			case 1:
				for ( int l=0;l<ofset;l++ )
				{
					array[i+3][j+l+3]=1;
				}
				break;
			case 0:
				for ( int l=0;l<ofset;l++ )
				{
					array[i+l+3][j+3]=1;
				}
		}
	}
	return result;	// возвращаем 0, если пусто
}
//------------------------------------------------------------------------------
void Field::next_ship( int position_scheme, int deep )
{
	int count_figure=0;
	int vect;	//верт/гориз
	int pi;	 //верт
	int pj;	 //гориз
	int rand_data;	 //
	int contr_place;	// 0 норма
	switch ( position_scheme )
	{
		case 0:
				for ( int i=0;i<count_sh;i++ )
				{
					fign[i]=fign1[i];
				}
				break;
		case 1:
				for ( int i=0;i<count_sh;i++ )
				{
					fign[i]=fign2[i];
				}
				break;
		case 2:
				for ( int i=0;i<count_sh;i++ )
				{
					fign[i]=fign3[i];
				}
				break;
		case 3:
				for ( int i=0;i<count_sh;i++ )
				{
					fign[i]=array_choice[i];
				}
				break;
	}
	for ( int l=0;l<10;l++ )
	{
		for ( int ll=0;ll<10;ll++ )
		{
			array[l+3][ll+3]=0;
		}
	}
	for ( int i=0;i<count_sh;i++ )
	{
		do
		{
			pi=rand_data=rand()%1000;
			pi=pi%10;
			pj=rand_data=rand_data/10;
			pj=pj%10;
			vect=rand_data/10;
			switch ( vect )
			{
				case 0:
				case 2:
				case 4:
				case 6:
				case 8:
						vect=0;
						break;
				case 1:
				case 3:
				case 5:
				case 7:
				case 9:
						vect=1;
			}
			contr_place=control(pi, pj, vect, fign[i],deep);	//1,2,3 !!!
			count_figure++;
			if ( count_figure>(count_sh*100)&&contr_place==1 )  //2, 10!!!
			{
				i=-1;
				count_figure=0;
				for ( int l=0;l<10;l++ )
				{
					for ( int ll=0;ll<10;ll++ )
					{
						array[l+3][ll+3]=0;
					}
				}
				break;
			}
		} while(contr_place!=0);
	}
}
int Field::show_bit(int x, int y)
{
	return array[x+3][y+3];
}
void Field::put_bit(int x, int y, int data)
{
	array[x+3][y+3]=data;
}
int Field::show_bit_deep(int x, int y)
{
	return array_deep[x+3][y+3];
}
void Field::put_bit_deep(int x, int y)
{
	array_deep[x+3][y+3]=1;
}
void Field::add_count()
{
	count++;
}
int Field::show_count()
{
	return count;
}
void Field::inc_count_sum(int data)
{
	count_sum+=data;
}
int Field::show_count_sum()
{
	return count_sum;
}
//--------------------------------------------------------------------------
Field comp(0);
Field man(0);
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TBevel *BComp;
	TBevel *BMan;
	TImage *IMan;
	TImage *IComp;
	TPanel *PManCovered;
	TPanel *PManShoots;
	TPanel *PCompCovered;
	TPanel *PCompShoots;
	TBevel *BManResults;
	TBevel *BCompResults;
	TMainMenu *MainMenu1;
	TMenuItem *Game;
	TMenuItem *Help;
	TMenuItem *Help1;
	TMenuItem *About1;
	TMenuItem *NewGame1;
	TMenuItem *Sound1;
	TMenuItem *Example1;
	TMenuItem *ShowMap1;
	TMenuItem *Exit1;
	TRadioGroup *RadioGroup1;
	TButton *ButtonChoiceScheme;
	TTimer *TimerOwnScheme;
	TButton *ButtonOwnScheme;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TPanel *PVeryMany;
	TImage *IVeryMany;
	TTimer *TimerThinkComp;
	TTimer *TimerAroundBrok;
	TTimer *TimerMachine;
	TImage *Broken;
	TImage *Milk;
	TPanel *PBegin;
	TButton *BNemo;
	TButton *BMachine;
	TButton *BHideExample;
	TButton *BHideMap;
	TImage *Milk01;
	TImage *Milk02;
	TImage *Milk03;
	TImage *Milk04;
	TImage *Milk05;
	TImage *Brok01;
	TImage *Brok02;
	TImage *Brok03;
	TImage *Brok04;
	TImage *Brok05;
	TTimer *TimerTrassa;
	TTimer *TimerGo;
	TPanel *PWin;
	TImage *IRadarMan;
	TImage *IRadarComp;
	TImage *IShip;
	TImage *IZero;
	TBevel *BRadarMan;
	TBevel *BRadarComp;
	TImage *IClose;
	TUpDown *UpDown1;
	TUpDown *UpDown2;
	TUpDown *UpDown3;
	TUpDown *UpDown4;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label7;
	TLabel *Label8;
	TTimer *TimerFlash;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TTimer *TimerStart;
	TTimer *TimerRestart;
	TImage *ISchool;
	TImage *IBS10;
	TImage *IBS9;
	TImage *IBS8;
	TImage *IBS7;
	TImage *IBS6;
	TImage *IBS5;
	TImage *IBS4;
	TImage *IBS3;
	TImage *IBS2;
	TImage *IBS1;
	TImage *IMS10;
	TImage *IMS9;
	TImage *IMS8;
	TImage *IMS7;
	TImage *IMS6;
	TImage *IMS5;
	TImage *IMS4;
	TImage *IMS3;
	TImage *IMS2;
	TImage *IMS1;
	TMenuItem *Kind1;
	TMenuItem *Battle1;
	TMenuItem *School1;
	TPanel *PWont;
	TButton *BYes;
	TButton *BNo;
	TImage *IShipSch;
	TImage *IZeroSch;
	TImage *ICloseSch;
	TImage *IRadarSch;
	TImage *IVeryMany2;
	TMenuItem *Radar1;
	TMenuItem *Sensitivity31;
	TMenuItem *Sensitivity21;
	TMenuItem *Sensitivity11;
	TMenuItem *RadarOFF1;
	TButton *BDelLastShip;
	TButton *BOkFull;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TImage *Image13;
	TImage *Image14;
	TImage *Image15;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TImage *Image20;
	TImage *Image21;
	TImage *Image22;
	TImage *Image23;
	TImage *Image24;
	TImage *Image25;
	TImage *Image26;
	TImage *Image27;
	TImage *Image28;
	TImage *Image29;
	TImage *Image30;
	TImage *Image31;
	TImage *Image32;
	TImage *Image33;
	TImage *Image34;
	TImage *Image35;
	TImage *Image36;
	TImage *Image37;
	TImage *Image38;
	TImage *Image39;
	TImage *Image40;
	TImage *Image41;
	TImage *Image42;
	TImage *Image43;
	TImage *Image44;
	TImage *Image45;
	TImage *Image46;
	TImage *Image47;
	TImage *Image48;
	TImage *Image49;
	TImage *Image50;
	TImage *Image51;
	TImage *Image52;
	TImage *Image53;
	TImage *Image54;
	TImage *Image55;
	TImage *Image56;
	TImage *IBlue;
	TImage *IRed;
	TBevel *BevelL;
	TBevel *BevelR;
	TMenuItem *OwnMap1;
	TMenuItem *Hide1;
	TMenuItem *Show1;
	TMenuItem *Language1;
	TMenuItem *English1;
	TMenuItem *Russian1;
	TImage *IRadarBattle;
	TImage *IFold;
	TImage *IMyComp;
	TImage *IRecy;
	TImage *IWindows;
	TImage *IRadarWin;
	TImage *ICompOn1;
	TImage *ICompOn2;
	TImage *ICompOn3;
	TImage *ICompOn4;
	TImage *ICompOn5;
	TImage *ICompOn6;
	TImage *ICompOn7;
	TImage *ICompOn8;
	TImage *ICompOn9;
	TImage *IRecy1;
	TImage *IRecy2;
	TImage *IRecy3;
	TImage *IRecy4;
	TImage *IRecy5;
	TMenuItem *Windows1;
	TImage *IWinS;
	TImage *IWinZ;
	TImage *IWinC;
	TMenuItem *LastShoot1;
	TTimer *TimerLastShoot;
	TImage *ILast1;
	TImage *ILast2;
	TImage *ILast3;
	TImage *ILast4;
	TImage *ILast5;
	TPanel *PIThink;
	TPanel *PNowYou;
	TPanel *PMyShoot;
	TPanel *PYourShoot;
	TPanel *PCountMan;
	TPanel *PCountCom;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TPanel *PCountSM;
	TPanel *PCountSC;
        TMenuItem *Level1;
        TMenuItem *Heavily1;
        TMenuItem *Average1;
        TMenuItem *Easily1;
	void __fastcall write_read_arr_tired(int * arr_tired);
	void __fastcall write_deep(int step_x, int step_y, int data);
	void __fastcall count_man_com(int side);
	void __fastcall begin_move();
	void __fastcall mouse_down_left_0(int x, int y, int shift_else, int step);
	void __fastcall mouse_down_left_1(int x, int y, int shift_else, int step);
	void __fastcall mouse_down_right_x(int x, int y, int condition, int offset_if, int offset_else);
	void __fastcall mouse_down_right_y(int x, int y, int condition, int offset_if, int offset_else);
	void __fastcall set_bevel_counter(int t, int h);
	void __fastcall show_example();
	void __fastcall choice_coclour();
	void __fastcall paint_radar_man();
	void __fastcall paint_radar_comp();
	void __fastcall explotion(int ball);
	void __fastcall field_restart(int compression);
	void __fastcall radar_clean(int step);
	void __fastcall radar_zero(int step);
	void __fastcall radar_ship();
	void __fastcall write_arr_radar(int x, int y);
	void __fastcall serch_near_target();
	void __fastcall end_game(int man_com);
	void __fastcall brok_milk(int x, int y);
	void __fastcall marker_move(int x, int y);
	void __fastcall side_x(int y,int x,int a,int b,int c,int d,int f);
	void __fastcall side_y(int y,int x,int a,int b,int c,int d,int g);
	void __fastcall side(int x, int y, int control);
	void __fastcall review(int x, int y);
	void __fastcall mside_x(int y,int x,int a,int b,int c,int d,int f);
	void __fastcall mside_y(int y,int x,int a,int b,int c,int d,int g);
	void __fastcall mside(int x, int y, int control);
	void __fastcall mreview(int x, int y);
	void __fastcall paint_array(int x, int y);
	void __fastcall very_many(int a);
	void __fastcall count_ship_n( int a, int & ship );
	void __fastcall max_area( int & sh1, int & sh2, int & sh3, int & sh4, int & cover);
	void __fastcall ButtonChoiceSchemeClick(TObject *Sender);
	void __fastcall TimerOwnSchemeTimer(TObject *Sender);
	void __fastcall ButtonOwnSchemeClick(TObject *Sender);
	void __fastcall TimerThinkCompTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall IManMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IManMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ICompMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall TimerMachineTimer(TObject *Sender);
	void __fastcall BNemoClick(TObject *Sender);
	void __fastcall BMachineClick(TObject *Sender);
	void __fastcall TimerAroundBrokTimer(TObject *Sender);
	void __fastcall Example1Click(TObject *Sender);
	void __fastcall BHideExampleClick(TObject *Sender);
	void __fastcall ShowMap1Click(TObject *Sender);
	void __fastcall BHideMapClick(TObject *Sender);
	void __fastcall TimerTrassaTimer(TObject *Sender);
	void __fastcall TimerGoTimer(TObject *Sender);
	void __fastcall TimerFlashTimer(TObject *Sender);
	void __fastcall TimerStartTimer(TObject *Sender);
	void __fastcall NewGame1Click(TObject *Sender);
	void __fastcall TimerRestartTimer(TObject *Sender);
	void __fastcall Battle1Click(TObject *Sender);
	void __fastcall School1Click(TObject *Sender);
	void __fastcall BYesClick(TObject *Sender);
	void __fastcall BNoClick(TObject *Sender);
	void __fastcall Sound1Click(TObject *Sender);
	void __fastcall RadarOFF1Click(TObject *Sender);
	void __fastcall Sensitivity31Click(TObject *Sender);
	void __fastcall Sensitivity21Click(TObject *Sender);
	void __fastcall Sensitivity11Click(TObject *Sender);
	void __fastcall BDelLastShipClick(TObject *Sender);
	void __fastcall BOkFullClick(TObject *Sender);
	void __fastcall Hide1Click(TObject *Sender);
	void __fastcall Show1Click(TObject *Sender);
	void __fastcall English1Click(TObject *Sender);
	void __fastcall Russian1Click(TObject *Sender);
	void __fastcall Windows1Click(TObject *Sender);
	void __fastcall LastShoot1Click(TObject *Sender);
	void __fastcall TimerLastShootTimer(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall Help1Click(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
        void __fastcall UpDown3Click(TObject *Sender, TUDBtnType Button);
        void __fastcall UpDown4Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Heavily1Click(TObject *Sender);
        void __fastcall Average1Click(TObject *Sender);
        void __fastcall Easily1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
Graphics::TBitmap*BitMap;
Graphics::TBitmap*BitMapl;
Graphics::TBitmap*BitMaprr; //for repeat
Graphics::TBitmap*BitMaplr;
Graphics::TBitmap*BitMapm;
Graphics::TBitmap*BitMapb;
Graphics::TBitmap*BitMaprs;
Graphics::TBitmap*BitMaprz;
Graphics::TBitmap*BitMaprc;
Graphics::TBitmap*BitMaprf;
Graphics::TBitmap*BitMapw;
Graphics::TBitmap*BitMapLm;
Graphics::TBitmap*BitMapLc;
#endif
