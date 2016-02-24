//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "shipsu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
#include "AboutForm.cpp"
//---------------------------------------------------------------------------
TForm1 *Form1;
//-------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::side_x(int x,int y,int a,int b,int c,int d,int f)
{
	if ( x>=a )
	{
		comp.put_bit(x+b,y,3);
	}
	comp.put_bit(x+c, y,3);
	IComp->Canvas->Draw((x+d)*25,y*25,BitMapm);
	IComp->Canvas->Draw((x+f)*25,y*25,BitMapm);
}
void __fastcall TForm1::side_y(int x,int y,int a,int b,int c,int d,int g)
{
	if ( y>=a )
	{
		comp.put_bit(x,y+b,3);
	}
	comp.put_bit(x, y+c, 3);
	IComp->Canvas->Draw(x*25,(y+d)*25,BitMapm);
	IComp->Canvas->Draw(x*25,(y+g)*25,BitMapm);
}
void __fastcall TForm1::side(int x, int y, int control)
{
	int vector_free2_w=0;
	int vector_free3_w=0;
	int vector_free2_o=0;
	int vector_free3_o=0;
	int vector_free2_n=0;
	int vector_free3_n=0;
	int vector_free2_s=0;
	int vector_free3_s=0;
	int vect_w=0;	// для выбора направления по массиву
	int vect_n=0;	// для выбора направления по массиву
	int vect_o=0;	// для выбора направления по массиву
	int vect_s=0;	// для выбора направления по массиву
	int vect_1w=0;	// для выбора направления по массиву
	int vect_1n=0;	// для выбора направления по массиву
	int vect_1o=0;	// для выбора направления по массиву
	int vect_1s=0;	// для выбора направления по массиву
	int vect_2w=0;	// для выбора направления по массиву
	int vect_2n=0;	// для выбора направления по массиву
	int vect_2o=0;	// для выбора направления по массиву
	int vect_2s=0;	// для выбора направления по массиву

	int array_around[12][2]={{ 0,-1},
							{ 0,-2},
							{ 0,-3},
							{ 0, 1},		//	3 3	  3 3	  3 3	  3 3			  3 3
							{ 0, 2},		//
							{ 0, 3},		//  1 2 * 0  1 2 * 3  3 2 * 0  3 2 * 1		  3 2 * 0
							{-1, 0},		//	0 3	  0 3	  0 3	  0 3			  0 3
							{-2, 0},		//
							{-3, 0},
							{ 1, 0},
							{ 2, 0},
							{ 3, 0}};
	vect_12_wm=0;	  // 1 max 1
	vect_13_wm=0;
	vect_14_wm=0;
	vect_12_om=0;
	vect_13_om=0;
	vect_14_om=0;
	vect_12_nm=0;
	vect_13_nm=0;
	vect_14_nm=0;
	vect_12_sm=0;
	vect_13_sm=0;
	vect_14_sm=0;
	for ( int i=0;i<12;i++ )
	{
		if ( comp.show_bit(x+array_around[i][1],y+array_around[i][0])==1 )
		{
			switch ( i )					 //
			{
				case 0:
						vect_12_wm++;
						break;
				case 1:
						vect_13_wm++;
						break;
				case 2:
						vect_14_wm++;
						break;
				case 3:
						vect_12_om++;
						break;
				case 4:
						vect_13_om++;
						break;
				case 5:
						vect_14_om++;
						break;
				case 6:
						vect_12_nm++;
						break;
				case 7:
						vect_13_nm++;
						break;
				case 8:
						vect_14_nm++;
						break;
				case 9:
						vect_12_sm++;
						break;
				case 10:
						vect_13_sm++;
						break;
				case 11:
						vect_14_sm++;
			}
		}
		if ( comp.show_bit(x+array_around[i][1],y+array_around[i][0])==2 )
		{
			switch ( i )
			{
				case 0:
						vect_1w++;
				case 1:
						vect_2w++;
				case 2:
						vect_w++;
						break;
				case 3:
						vect_1o++;
				case 4:
						vect_2o++;
				case 5:
						vect_o++;
						break;
				case 6:
						vect_1n++;
				case 7:
						vect_2n++;
				case 8:
						vect_n++;
						break;
				case 9:
						vect_1s++;
				case 10:
						vect_2s++;
				case 11:
						vect_s++;
			}
		}
		if ( comp.show_bit(x+array_around[i][1],y+array_around[i][0])==0||comp.show_bit(x+array_around[i][1],y+array_around[i][0])==3 )
		{
			switch ( i )
			{
				case 0:
						vector_free2_w++;
						break;
				case 1:
						vector_free3_w++;
						break;
				case 3:
						vector_free2_o++;
						break;
				case 4:
						vector_free3_o++;
						break;
				case 6:
						vector_free2_n++;
						break;
				case 7:
						vector_free3_n++;
						break;
				case 9:
						vector_free2_s++;
						break;
				case 10:
						vector_free3_s++;
						break;
				default: ;
				}
		}
	}
	if (!RadarOFF1->Checked)
	{
		paint_radar_man();
	}
	if (control)
	{
		if ( vector_free2_w==1&&vector_free2_n==1&&vector_free2_o==1&&vector_free2_s==1) // фигура 1 клетка
		{
			side_x(x,y,1,-1,1,-1,1);
			side_y(x,y,1,-1,1,-1,1);
		}
		else if ( vect_w==3 )	// фигура 4 клетки  на оду сторону
		{
			side_x(x,y,4,-4,1,-4,1);
		}
		else if ( vect_o==3 )	// фигура 4 клетки  на оду сторону
		{
			side_x(x,y,1,-1,4,-1,4);
		}
		else if ( vect_n==3 )	// фигура 4 клетки  на оду сторону
		{
			side_y(x,y,4,-4,1,1,-4);
		}
		else if ( vect_s==3 )	// фигура 4 клетки  на оду сторону
		{
			side_y(x,y,1,-1,4,-1,4);
		}
		else if ( vect_2o==2&&vect_1w==1 )	// фигура 4 клетки со смещением направо
		{ //1011
			side_x(x,y,2,-2,3,-2,3);
		}
		else if ( vect_2w==2&&vect_1o==1 )	// фигура 4 клетки со смещением налево
		{
			side_x(x,y,3,-3,2,-3,2);
		}
		else if ( vect_2n==2&&vect_1s==1 )	// фигура 4 клетки со смещением вверх
		{
			side_y(x,y,3,-3,2,2,-3);
		}
		else if ( vect_2s==2&&vect_1n==1 )	// фигура 4 клетки со смещением вниз
		{
			side_y(x,y,2,-2,3,-2,3);
		}
		else if ( vect_2w==2&&vector_free2_o==1&&vect_14_wm==0 )	// фигура 3 клетки  на оду сторону
		{
			side_x(x,y,3,-3,1,-3,1);
		}
		else if ( vect_2o==2&&vector_free2_w==1&&vect_14_om==0 )	// фигура 3 клетки  на оду сторону
		{
			side_x(x,y,1,-1,3,-1,3);
		}
		else if ( vect_2n==2&&vector_free2_s==1&&vect_14_nm==0 )	// фигура 3 клетки  на оду сторону
		{
			side_y(x,y,3,-3,1,1,-3);
		}
		else if ( vect_2s==2&&vector_free2_n==1&&vect_14_sm==0 )	// фигура 3 клетки  на оду сторону
		{
			side_y(x,y,1,-1,3,-1,3);
		}
		else if ( vect_1w==1&&vect_1o==1&&vector_free3_w==1&&vector_free3_o==1 ) // фигура 3 клетки по 1 на две стороны
		{  //101
			side_x(x,y,2,-2,2,-2,2);
		}
		else if ( vect_1n==1&&vect_1s==1&&vector_free3_n==1&&vector_free3_s==1 ) // фигура 3 клетки по 1 на две стороны
		{  //101
			side_y(x,y,2,-2,2,-2,2);
		}
		else if ( vect_1w==1&&vector_free2_o==1&&vector_free3_w==1 ) // фигура 2 клетки
		{
			side_x(x,y,2,-2,1,-2,1);
		}
		else if ( vect_1o==1&&vector_free2_w==1&&vector_free3_o==1 ) // фигура 2 клетки
		{
			side_x(x,y,1,-1,2,-1,2);
		}
		else if ( vect_1n==1&&vector_free2_s==1&&vector_free3_n==1 ) // фигура 2 клетки
		{
			side_y(x,y,2,-2,1,1,-2);
		}
		else if ( vect_1s==1&&vector_free2_n==1&&vector_free3_s==1 ) // фигура 2 клетки
		{
			side_y(x,y,1,-1,2,-1,2);
		}
	}
}
void __fastcall TForm1::review(int x, int y)
{
	int array_around[4][2]={{-1,-1},
					  {-1, 1},
					  { 1, 1},
					  { 1,-1}};
	if ( y==0&&x==0 )
	{
		comp.put_bit(x+array_around[2][0],y+array_around[2][0],3);
		IComp->Canvas->Draw((x+array_around[2][0])*25,(y+array_around[2][0])*25,BitMapm);
	}
	else if ( y==9&&x==0 )
	{
		comp.put_bit(x+array_around[2][0],y+array_around[1][0],3);
		IComp->Canvas->Draw((x+array_around[2][0])*25,(y+array_around[1][0])*25,BitMapm);
	}
	else if ( y==9&&x==9 )
	{
		comp.put_bit(x+array_around[1][0],y+array_around[1][0],3);
		IComp->Canvas->Draw((x+array_around[1][0])*25,(y+array_around[1][0])*25,BitMapm);
	}
	else if ( y==0&&x==9 )
	{
		comp.put_bit(x+array_around[1][0],y+array_around[2][0],3);
		IComp->Canvas->Draw((x+array_around[1][0])*25,(y+array_around[2][0])*25,BitMapm);
	}
	else if ( y==0 )
	{
		for ( int i=2;i<4;i++ )	//расставили по углам 3 в массиве
		{
			comp.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IComp->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
	else if ( x==0 )
	{
		for ( int i=1;i<3;i++ )	//расставили по углам 3 в массиве
		{
			comp.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IComp->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
	else
	{
		for ( int i=0;i<4;i++ )	//расставили по углам 3 в массиве
		{
			comp.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IComp->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
}
//----------------------------------------------------------------
void __fastcall TForm1::mside_x(int x,int y,int a,int b,int c,int d,int f)
{
	side_x_y=1;
	if ( x>=a )
	{
		man.put_bit(x+b,y,3);
	}
	man.put_bit(x+c, y,3);
	IMan->Canvas->Draw((x+d)*25,y*25,BitMapm);
	IMan->Canvas->Draw((x+f)*25,y*25,BitMapm);
}
void __fastcall TForm1::mside_y(int x,int y,int a,int b,int c,int d,int g)
{
	side_x_y=1;
	if ( y>=a )
	{
		man.put_bit(x,y+b,3);
	}
	man.put_bit(x, y+c, 3);
	IMan->Canvas->Draw(x*25,(y+d)*25,BitMapm);
	IMan->Canvas->Draw(x*25,(y+g)*25,BitMapm);
}
void __fastcall TForm1::mside(int x, int y, int control)
{
	int vector_free2_w=0;
	int vector_free3_w=0;
	int vector_free2_o=0;
	int vector_free3_o=0;
	int vector_free2_n=0;
	int vector_free3_n=0;
	int vector_free2_s=0;
	int vector_free3_s=0;
	int vect_w=0;	// для выбора направления по массиву
	int vect_n=0;	// для выбора направления по массиву
	int vect_o=0;	// для выбора направления по массиву
	int vect_s=0;	// для выбора направления по массиву
	int vect_1w=0;	// для выбора направления по массиву
	int vect_1n=0;	// для выбора направления по массиву
	int vect_1o=0;	// для выбора направления по массиву
	int vect_1s=0;	// для выбора направления по массиву
	int vect_2w=0;	// для выбора направления по массиву
	int vect_2n=0;	// для выбора направления по массиву
	int vect_2o=0;	// для выбора направления по массиву
	int vect_2s=0;	// для выбора направления по массиву

	int array_around[12][2]={{ 0,-1},
							{ 0,-2},
							{ 0,-3},
							{ 0, 1},		//	3 3	  3 3	  3 3	  3 3			  3 3
							{ 0, 2},		//
							{ 0, 3},		//  1 2 * 0  1 2 * 3  3 2 * 0  3 2 * 1		  3 2 * 0
							{-1, 0},		//	0 3	  0 3	  0 3	  0 3			  0 3
							{-2, 0},		//
							{-3, 0},
							{ 1, 0},
							{ 2, 0},
							{ 3, 0}};
	vect_12_w=0;	  // 1 max 1
	vect_13_w=0;
	vect_14_w=0;
	vect_12_o=0;
	vect_13_o=0;
	vect_14_o=0;
	vect_12_n=0;
	vect_13_n=0;
	vect_14_n=0;
	vect_12_s=0;
	vect_13_s=0;
	vect_14_s=0;
	for ( int i=0;i<12;i++ )
	{
		if ( man.show_bit(x+array_around[i][1],y+array_around[i][0])==1 )
		{
			switch ( i )					 //
			{
				case 0:
						vect_12_w++;
						break;
				case 1:
						vect_13_w++;
						break;
				case 2:
						vect_14_w++;
						break;
				case 3:
						vect_12_o++;
						break;
				case 4:
						vect_13_o++;
						break;
				case 5:
						vect_14_o++;
						break;
				case 6:
						vect_12_n++;
						break;
				case 7:
						vect_13_n++;
						break;
				case 8:
						vect_14_n++;
						break;
				case 9:
						vect_12_s++;
						break;
				case 10:
						vect_13_s++;
						break;
				case 11:
						vect_14_s++;
			}
		}
		if ( man.show_bit(x+array_around[i][1],y+array_around[i][0])==2 )
		{
			switch ( i )
			{
				case 0:
						vect_1w++;
				case 1:
						vect_2w++;
				case 2:
						vect_w++;
						break;
				case 3:
						vect_1o++;
				case 4:
						vect_2o++;
				case 5:
						vect_o++;
						break;
				case 6:
						vect_1n++;
				case 7:
						vect_2n++;
				case 8:
						vect_n++;
						break;
				case 9:
						vect_1s++;
				case 10:
						vect_2s++;
				case 11:
						vect_s++;
			}
		}
		if ( man.show_bit(x+array_around[i][1],y+array_around[i][0])==0||man.show_bit(x+array_around[i][1],y+array_around[i][0])==3 )
		{
			switch ( i )
			{
				case 0:
						vector_free2_w++;
						break;
				case 1:
						vector_free3_w++;
						break;
				case 3:
						vector_free2_o++;
						break;
				case 4:
						vector_free3_o++;
						break;
				case 6:
						vector_free2_n++;
						break;
				case 7:
						vector_free3_n++;
						break;
				case 9:
						vector_free2_s++;
						break;
				case 10:
						vector_free3_s++;
						break;
				default: ;
			}
		}
	}
	if (!RadarOFF1->Checked)
	{
		paint_radar_comp();
		if (vect_12_w==1)
			write_arr_radar(x-1,y);
		if (vect_12_n==1)
			write_arr_radar(x,y-1);
		if (vect_12_o==1)
			write_arr_radar(x+1,y);
		if (vect_12_s==1)
			write_arr_radar(x,y+1);
		if (Sensitivity31->Checked)
		{
			if (vect_13_w==1)
				write_arr_radar(x-2,y);
			if (vect_13_n==1)
				write_arr_radar(x,y-2);
			if (vect_13_o==1)
				write_arr_radar(x+2,y);
			if (vect_13_s==1)
				write_arr_radar(x,y+2);
			if (vect_14_w==1)
				write_arr_radar(x-3,y);
			if (vect_14_n==1)
				write_arr_radar(x,y-3);
			if (vect_14_o==1)
				write_arr_radar(x+3,y);
			if (vect_14_s==1)
				write_arr_radar(x,y+3);
		}
		else if (Sensitivity21->Checked)
		{
			if (vect_13_w==1)
				write_arr_radar(x-2,y);
			if (vect_13_n==1)
				write_arr_radar(x,y-2);
			if (vect_13_o==1)
				write_arr_radar(x+2,y);
			if (vect_13_s==1)
				write_arr_radar(x,y+2);
		}
	}
	if (control)
	{
		if ( vector_free2_w==1&&vector_free2_n==1&&vector_free2_o==1&&vector_free2_s==1) // фигура 1 клетка
		{
			mside_x(x,y,1,-1,1,-1,1);
			mside_y(x,y,1,-1,1,-1,1);
		}
		else if ( vect_w==3 )	// фигура 4 клетки  на оду сторону
		{
			mside_x(x,y,4,-4,1,-4,1);
		}
		else if ( vect_o==3 )	// фигура 4 клетки  на оду сторону
		{
			mside_x(x,y,1,-1,4,-1,4);
		}
		else if ( vect_n==3 )	// фигура 4 клетки  на оду сторону
		{
			mside_y(x,y,4,-4,1,1,-4);
		}
		else if ( vect_s==3 )	// фигура 4 клетки  на оду сторону
		{
			mside_y(x,y,1,-1,4,-1,4);
		}
		else if ( vect_2o==2&&vect_1w==1 )	// фигура 4 клетки со смещением направо
		{ //1011
			mside_x(x,y,2,-2,3,-2,3);
		}
		else if ( vect_2w==2&&vect_1o==1 )	// фигура 4 клетки со смещением налево
		{
			mside_x(x,y,3,-3,2,-3,2);
		}
		else if ( vect_2n==2&&vect_1s==1 )	// фигура 4 клетки со смещением вверх
		{
			mside_y(x,y,3,-3,2,2,-3);
		}
		else if ( vect_2s==2&&vect_1n==1 )	// фигура 4 клетки со смещением вниз
		{
			mside_y(x,y,2,-2,3,-2,3);
		}
		else if ( vect_2w==2&&vector_free2_o==1&&vect_14_w==0 )	// фигура 3 клетки  на оду сторону
		{
			mside_x(x,y,3,-3,1,-3,1);
		}
		else if ( vect_2o==2&&vector_free2_w==1&&vect_14_o==0 )	// фигура 3 клетки  на оду сторону
		{
			mside_x(x,y,1,-1,3,-1,3);
		}
		else if ( vect_2n==2&&vector_free2_s==1&&vect_14_n==0 )	// фигура 3 клетки  на оду сторону
		{
			mside_y(x,y,3,-3,1,1,-3);
		}
		else if ( vect_2s==2&&vector_free2_n==1&&vect_14_s==0 )	// фигура 3 клетки  на оду сторону
		{
			mside_y(x,y,1,-1,3,-1,3);
		}
		else if ( vect_1w==1&&vect_1o==1&&vector_free3_w==1&&vector_free3_o==1 ) // фигура 3 клетки по 1 на две стороны
		{  //101
			mside_x(x,y,2,-2,2,-2,2);
		}
		else if ( vect_1n==1&&vect_1s==1&&vector_free3_n==1&&vector_free3_s==1 ) // фигура 3 клетки по 1 на две стороны
		{  //101
			mside_y(x,y,2,-2,2,-2,2);
		}
		else if ( vect_1w==1&&vector_free2_o==1&&vector_free3_w==1 ) // фигура 2 клетки
		{
			mside_x(x,y,2,-2,1,-2,1);
		}
		else if ( vect_1o==1&&vector_free2_w==1&&vector_free3_o==1 ) // фигура 2 клетки
		{
			mside_x(x,y,1,-1,2,-1,2);
		}
		else if ( vect_1n==1&&vector_free2_s==1&&vector_free3_n==1 ) // фигура 2 клетки
		{
			mside_y(x,y,2,-2,1,1,-2);
		}
		else if ( vect_1s==1&&vector_free2_n==1&&vector_free3_s==1 ) // фигура 2 клетки
		{
			mside_y(x,y,1,-1,2,-1,2);
		}
	}
}
void __fastcall TForm1::mreview(int x, int y)
{
	int array_around[4][2]={{-1,-1},
							{-1, 1},
							{ 1, 1},
							{ 1,-1}};
	if ( y==0&&x==0 )
	{
		man.put_bit(x+array_around[2][0],y+array_around[2][0],3);
		IMan->Canvas->Draw((x+array_around[2][0])*25,(y+array_around[2][0])*25,BitMapm);
	}
	else if ( y==9&&x==0 )
	{
		man.put_bit(x+array_around[2][0],y+array_around[1][0],3);
		IMan->Canvas->Draw((x+array_around[2][0])*25,(y+array_around[1][0])*25,BitMapm);
	}
	else if ( y==9&&x==9 )
	{
		man.put_bit(x+array_around[1][0],y+array_around[1][0],3);
		IMan->Canvas->Draw((x+array_around[1][0])*25,(y+array_around[1][0])*25,BitMapm);
	}
	else if ( y==0&&x==9 )
	{
		man.put_bit(x+array_around[1][0],y+array_around[2][0],3);
		IMan->Canvas->Draw((x+array_around[1][0])*25,(y+array_around[2][0])*25,BitMapm);
	}
	else if ( y==0 )
	{
		for ( int i=2;i<4;i++ )	//расставили по углам 3 в массиве
		{
			man.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IMan->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
	else if ( x==0 )
	{
		for ( int i=1;i<3;i++ )	//расставили по углам 3 в массиве
		{
			man.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IMan->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
	else
	{
		for ( int i=0;i<4;i++ )	//расставили по углам 3 в массиве
		{
			man.put_bit(x+array_around[i][1],y+array_around[i][0],3);
			IMan->Canvas->Draw((x+array_around[i][1])*25,(y+array_around[i][0])*25,BitMapm);
		}
	}
	BitMapl->Assign(IMan->Picture);	// if not shape!!!
}
void __fastcall TForm1::very_many( int a)
{
	PVeryMany->Visible=true;
	if (School1->Checked)
		IVeryMany2->Visible=true;
	else
		IVeryMany->Visible=true;
	switch ( a )
	{
		case 0:
				if (English1->Checked)
					PVeryMany->Caption="WHERE IS SHIPS ?";
				else
					PVeryMany->Caption="Где Корабли?";
				break;
		case 1:     ;
				if (English1->Checked)
					PVeryMany->Caption="VERY MANY SHIPS !";
				else
					PVeryMany->Caption="Много Кораблей!";
	}
}
void __fastcall TForm1::max_area( int & sh1, int & sh2, int & sh3, int & sh4, int & cover)
{
	cover=(21*sh4+17*sh3+12*sh2+8.5*sh1)/1.5;
}
void __fastcall TForm1::count_ship_n( int a, int & ship )
{
	if ( ship!=0 )
	{
		for ( int i=count_sh;i<count_sh+ship;i++ )
		{
			array_choice[i]=a;
		}
		count_sh=count_sh+ship;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonChoiceSchemeClick(TObject *Sender)
{
	RadioGroup1->Visible=false;
	ButtonChoiceScheme->Visible=false;
	if (RadioGroup1->ItemIndex==3)
	{
		TimerOwnScheme->Enabled=true;
		ButtonOwnScheme->Visible=true;
		Label3->Visible=true;
		Label4->Visible=true;
		Label5->Visible=true;
		Label6->Visible=true;
		Label1->Visible=true;
		Label2->Visible=true;
		Label7->Visible=true;
		Label8->Visible=true;
		UpDown1->Visible=true;
		UpDown2->Visible=true;
		UpDown3->Visible=true;
		UpDown4->Visible=true;
		Bevel1->Visible=true;
		Bevel2->Visible=true;
		Bevel3->Visible=true;
		Bevel4->Visible=true;
		Kind1->Enabled=false;
	}
	else
	{
		switch (RadioGroup1->ItemIndex)
		{
			case 0:
				count=20;
				count_sh=10;
			break;
			case 1:
				count=25;
				count_sh=9;
			break;
			case 2:
				count=20;
				count_sh=12;
			break;
		}
		TimerFlash->Enabled=false;
		Radar1->Enabled=false;
                Level1->Enabled=false;
		radar_zero(1);
		if (Sensitivity31->Checked)
			;
		else if (Sensitivity21->Checked)
			radar_clean(3);
		else if (Sensitivity11->Checked)
			radar_clean(2);
		else
			radar_clean(1);
		TimerThinkComp->Enabled=true;
		PIThink->Visible=true;
		Kind1->Enabled=false;
	}
	Example1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerOwnSchemeTimer(TObject *Sender)
{
	Label1->Caption=IntToStr(UpDown1->Position);
	Label2->Caption=IntToStr(UpDown2->Position);
	Label7->Caption=IntToStr(UpDown3->Position);
	Label8->Caption=IntToStr(UpDown4->Position);
	ship1=UpDown1->Position;
	ship2=UpDown2->Position;
	ship3=UpDown3->Position;
	ship4=UpDown4->Position;
	max_area( ship1, ship2, ship3, ship4, cover );
	if (cover>94)
	{
                blok_up=1;
		very_many( 1 );
	}
	else if(cover>0)
	{
                blok_up=0;
		PVeryMany->Visible=false;
	if (School1->Checked)
		IVeryMany2->Visible=false;
	else
		IVeryMany->Visible=false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonOwnSchemeClick(TObject *Sender)
{
	if (!PVeryMany->Visible)
	{
		if ( (ship4+ship3+ship2+ship1)!=0 )
		{
			count_ship_n( 1, ship4 );
			count_ship_n( 2, ship3 );
			count_ship_n( 3, ship2 );
			count_ship_n( 4, ship1 );
		}
		else
		{
			very_many( 0 );
		}
		if ( count_sh!=0&&cover<97)  //прописываем массив новый array_choice
		{
			ButtonOwnScheme->Visible=false;
			Label3->Visible=false;
			Label4->Visible=false;
			Label5->Visible=false;
			Label6->Visible=false;
			Label1->Visible=false;
			Label2->Visible=false;
			Label7->Visible=false;
			Label8->Visible=false;
			UpDown1->Visible=false;
			UpDown2->Visible=false;
			UpDown3->Visible=false;
			UpDown4->Visible=false;
			Bevel1->Visible=false;
			Bevel2->Visible=false;
			Bevel3->Visible=false;
			Bevel4->Visible=false;
			PVeryMany->Visible=false;
			if (School1->Checked)
				IVeryMany2->Visible=false;
			else
				IVeryMany->Visible=false;
			TimerOwnScheme->Enabled=false;
			TimerThinkComp->Enabled=true;
			PIThink->Visible=true;
			Kind1->Enabled=false;
			count=4*ship4+3*ship3+2*ship2+ship1;
			TimerFlash->Enabled=false;
			Radar1->Enabled=false;
                        Level1->Enabled=false;
			radar_zero(1);
			if (Sensitivity31->Checked)
				;
			else if (Sensitivity21->Checked)
				radar_clean(3);
			else if (Sensitivity11->Checked)
				radar_clean(2);
			else
				radar_clean(1);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerThinkCompTimer(TObject *Sender)
{
	count_think++;
	IComp->Picture->Assign(BitMap);
	for (int x=0;x<10;x++)
	{
		for (int y=0;y<10;y++)
		{
			paint_array(x,y);
		}
	}
	comp.next_ship(RadioGroup1->ItemIndex,1);
	if (count_think==30) // 50 75
	{
                if (!Easily1->Checked)
                {
		        comp.next_ship(RadioGroup1->ItemIndex,radar_sensitivity);
                }
                else
                {
		        comp.next_ship(RadioGroup1->ItemIndex,1);
                }
		count_think=0;
		PIThink->Visible=false;
		TimerThinkComp->Enabled=false;
		PNowYou->Visible=true;
		cover=0;
		IComp->Picture->Assign(BitMap);
		Kind1->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	BitMap=new Graphics::TBitmap;
	BitMap->Width=250;
	BitMap->Height=250;
	BitMap->Assign(IComp->Picture);
	BitMapl=new Graphics::TBitmap;
	BitMapl->Width=250;
	BitMapl->Height=250;
	BitMapl->Assign(IMan->Picture);
	BitMaplr=new Graphics::TBitmap;
	BitMaplr->Width=250;
	BitMaplr->Height=250;
	BitMaplr->Assign(IMan->Picture);
	BitMaprr=new Graphics::TBitmap;
	BitMaprr->Width=250;
	BitMaprr->Height=250;
	BitMaprr->Assign(IComp->Picture);
	BitMapm=new Graphics::TBitmap;
	BitMapm->Width=25;
	BitMapm->Height=25;
	BitMapm->Assign(Milk->Picture);
	BitMapb=new Graphics::TBitmap;
	BitMapb->Width=25;
	BitMapb->Height=25;
	BitMaprs=new Graphics::TBitmap;
	BitMaprs->Width=8;
	BitMaprs->Height=8;
	BitMaprs->Assign(IShip->Picture);
	BitMaprz=new Graphics::TBitmap;
	BitMaprz->Width=8;
	BitMaprz->Height=8;
	BitMaprz->Assign(IZero->Picture);
	BitMaprc=new Graphics::TBitmap;
	BitMaprc->Width=8;
	BitMaprc->Height=8;
	BitMaprc->Assign(IClose->Picture);
	BitMaprf=new Graphics::TBitmap;
	BitMaprf->Width=120;
	BitMaprf->Height=120;
	BitMapw=new Graphics::TBitmap;
	BitMapw->Width=25;
	BitMapw->Height=25;
	BitMapw->Assign(IFold->Picture);
	BitMapLm=new Graphics::TBitmap;
	BitMapLm->Width=25;
	BitMapLm->Height=25;
	BitMapLc=new Graphics::TBitmap;
	BitMapLc->Width=25;
	BitMapLc->Height=25;
	IRadarMan->Picture->Assign(IRadarBattle->Picture);
	IRadarComp->Picture->Assign(IRadarBattle->Picture);
	Screen->Cursors[crMyCursor]=LoadCursor(HInstance,"TARGET");
	Screen->Cursors[crMyCursorh]=LoadCursor(HInstance,"HOOK");
	IMan->Cursor=(TCursor)crMyCursorh;
	IComp->Cursor=(TCursor)crMyCursor;
	srand(time(0));
	if (Sound1->Checked)
	{
		PlaySound("sounopen.wav",0,SND_ASYNC);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	BitMap->Free();
	BitMapl->Free();
	BitMaplr->Free();
	BitMaprr->Free();
	BitMapm->Free();
	BitMapb->Free();
	BitMaprs->Free();
	BitMaprz->Free();
	BitMaprc->Free();
	BitMapw->Free();
	BitMapLm->Free();
	BitMapLc->Free();
	Application->HelpCommand(HELP_QUIT,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paint_array(int x, int y)
{
	if (comp.show_bit(x,y)==1||comp.show_bit(x,y)==2)    //comp
	{
		if (School1->Checked)
		{
			IComp->Canvas->Pen->Width=3;
			IComp->Canvas->Pen->Color=clNavy;
			IComp->Canvas->Brush->Color=clGray;
			IComp->Canvas->Rectangle(x*25+1,y*25+1,x*25+25-1,y*25+25-1);
		}
		else if (Windows1->Checked)
			IComp->Canvas->Draw(x*25,y*25,BitMapw);
		else
		{
			IComp->Canvas->Brush->Color = clTeal;
			IComp->Canvas->Pen->Color = clTeal;
			IComp->Canvas->Rectangle(x*25,y*25,x*25+25,y*25+25 );
		}
	}
}
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IManMouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (PNowYou->Visible&&(count_sh-cover))	//||!PMyShoot->Visible)
	{
		IMan->Picture->Assign(BitMapl);
		if (Button==mbRight)
		{
			if (Sound1->Checked)
			{
				PlaySound("sounturn.wav",0,SND_ASYNC);
			}
			switch(vector)
			{
				case 0:
					vector=1;
					shift_X=0;
					switch(fign[cover])
					{
						case 1:
							if (X>224)
								shift_Y=-3;
							else if (Y>199)
								shift_Y=-2;
							else if (Y>174)
								shift_Y=-1;
						break;
						case 2:
							if (Y>224)
								shift_Y=-2;
							else if (Y>199)
								shift_Y=-1;
						break;
						case 3:
							if (Y>224)
								shift_Y=-1;
						break;
						case 4:
								shift_Y=0;
						break;
					}
					switch(fign[cover])
					{
						case 1:
							mouse_down_right_y(X,Y,174,100,150);
						break;
						case 2:
							mouse_down_right_y(X,Y,199,75,175);
						break;
						case 3:
							mouse_down_right_y(X,Y,224,50,200);
						break;
						case 4:
							if (Windows1->Checked)
							{
								IMan->Canvas->Draw(X/25*25,Y/25*25,BitMapw);
							}
							else
							{
								IMan->Picture->Assign(BitMapl);
								choice_coclour();
								IMan->Canvas->Rectangle(X/25*25,Y/25*25,X/25*25+25,Y/25*25+25 );
							}
						break;
					}
				break;
				case 1:
					vector=0;
					shift_Y=0;
					switch(fign[cover])
					{
						case 1:
							if (X>224)
								shift_X=-3;
							else if (X>199)
								shift_X=-2;
							else if (X>174)
								shift_X=-1;
						break;
						case 2:
							if (X>224)
								shift_X=-2;
							else if (X>199)
								shift_X=-1;
						break;
						case 3:
							if (X>224)
								shift_X=-1;
						break;
						case 4:
								shift_X=0;
						break;
					}
					switch(fign[cover])
					{
						case 1:
							mouse_down_right_x(X,Y,174,100,150);
						break;
						case 2:
							mouse_down_right_x(X,Y,199,75,175);
						break;
						case 3:
							mouse_down_right_x(X,Y,224,50,200);
						break;
						case 4:
							if (Windows1->Checked)
							{
								IMan->Canvas->Draw(X/25*25,Y/25*25,BitMapw);
							}
							else
							{
								IMan->Picture->Assign(BitMapl);
								choice_coclour();
								IMan->Canvas->Rectangle(X/25*25,Y/25*25,X/25*25+25,Y/25*25+25 );
							}
						break;
					}
				break;
			}
		}
		else if (Button == mbLeft)
		{
			if (!man.control(X/25+shift_X, Y/25+shift_Y, vector, fign[cover],1))	// not 2,1 !!!
			{
				if (Sound1->Checked)
				{
					PlaySound("sounplas.wav",0,SND_ASYNC);
				}
				switch(vector)
				{
					case 0:
					switch(fign[cover])
					{
						case 1:
							mouse_down_left_0(X,Y,100,1);
						break;
						case 2:
							mouse_down_left_0(X,Y,75,2);
						break;
						case 3:
							mouse_down_left_0(X,Y,50,3);
						break;
						case 4:
							mouse_down_left_0(X,Y,25,4);
						break;
					}
					break;
					case 1:
					switch(fign[cover])
					{
						case 1:
							mouse_down_left_1(X,Y,100,1);
						break;
						case 2:
							mouse_down_left_1(X,Y,75,2);
						break;
						case 3:
							mouse_down_left_1(X,Y,50,3);
						break;
						case 4:
							mouse_down_left_1(X,Y,25,4);
						break;
					}
					break;
				}
				if (cover==count_sh-1)
				{
					BitMapl->Assign(IMan->Picture);	// if not shape!!!
					BOkFull->Visible=true;
					last_ship[0]=X/25+shift_X;
					last_ship[1]=Y/25+shift_Y;
					last_ship[2]=vector;
					last_ship[3]=5-fign[cover];
					BDelLastShip->Visible=true;
					cover++;
				}
				else
				{
					last_ship[0]=X/25+shift_X;
					last_ship[1]=Y/25+shift_Y;
					last_ship[2]=vector;
					last_ship[3]=5-fign[cover];
					BDelLastShip->Visible=true;
					BitMapl->Assign(IMan->Picture);
					cover++;
				}
			}
			else
			{
				if (Sound1->Checked)
				{
					PlaySound("sounmeta.wav",0,SND_ASYNC);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IManMouseMove(TObject *Sender, TShiftState Shift,
	  int X, int Y)
{
	if (PNowYou->Visible&&(count_sh-cover))
	{
		IMan->Picture->Assign(BitMapl);
		if (X<=224)
			shift_X=0;
		if (Y<=224)
			shift_Y=0;
		switch(vector)
		{
			case 0:
				shift_Y=0;
				switch(fign[cover])
				{
					case 1:
						if (X>224)
							shift_X=-3;
						else if (X>199)
							shift_X=-2;
						else if (X>174)
							shift_X=-1;
					break;
					case 2:
						if (X>224)
							shift_X=-2;
						else if (X>199)
							shift_X=-1;
					break;
					case 3:
						if (X>224)
							shift_X=-1;
					break;
					case 4:
							shift_X=0;
					break;
				}
			break;
			case 1:
				shift_X=0;
				switch(fign[cover])
				{
					case 1:
						if (Y>224)
							shift_Y=-3;
						else if (Y>199)
							shift_Y=-2;
						else if (Y>174)
							shift_Y=-1;
					break;
					case 2:
						if (Y>224)
							shift_Y=-2;
						else if (Y>199)
							shift_Y=-1;
					break;
					case 3:
						if (Y>224)
							shift_Y=-1;
					break;
					case 4:
							shift_Y=0;
					break;
				}
			break;
		}
		switch(vector)
		{
			case 0:
				switch(fign[cover])
				{
					case 1:
						mouse_down_right_x(X,Y,174,100,150);
					break;
					case 2:
						mouse_down_right_x(X,Y,199,75,175);
					break;
					case 3:
						mouse_down_right_x(X,Y,224,50,200);
					break;
					case 4:
						if (Windows1->Checked)
						{
							IMan->Canvas->Draw(X/25*25,Y/25*25,BitMapw);
						}
						else
						{
							IMan->Picture->Assign(BitMapl);
							choice_coclour();
							IMan->Canvas->Rectangle(0+X/25*25,0+Y/25*25,X/25*25+25,Y/25*25+25 );
						}
					break;
				}
			break;
			case 1:
				switch(fign[cover])
				{
					case 1:
						mouse_down_right_y(X,Y,174,100,150);
					break;
					case 2:
						mouse_down_right_y(X,Y,199,75,175);
					break;
					case 3:
						mouse_down_right_y(X,Y,224,50,200);
					break;
					case 4:
						if (Windows1->Checked)
						{
							IMan->Canvas->Draw(X/25*25,Y/25*25,BitMapw);
						}
						else
						{
							IMan->Picture->Assign(BitMapl);
							choice_coclour();
							IMan->Canvas->Rectangle(0+X/25*25,0+Y/25*25,X/25*25+25,Y/25*25+25 );
						}
					break;
				}
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ICompMouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (!TimerMachine->Enabled&&!ButtonChoiceScheme->Visible&&
		!ButtonOwnScheme->Visible&&!PIThink->Visible&&!PNowYou->Visible&&
		!PBegin->Visible&&!TimerAroundBrok->Enabled&&!BHideMap->Visible&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!PWin->Visible&&
		!TimerFlash->Enabled&&!TimerStart->Enabled&&!TimerRestart->Enabled)
	{
		int sum_brok=0;
		left_right=1;
		LastShoot1->Enabled=false;
		switch (comp.show_bit(X/25,Y/25))
		{
			case 0:
				result=0;
				right_x=X/25;
				right_y=Y/25;
				comp.put_bit(right_x,right_y,3);
				side(X/25,Y/25,0);
				shoot_man++;
				covered_man++;
				need_man=0;
				if (English1->Checked)
				{
					PManShoots->Caption="Shoots: "+IntToStr(shoot_man);
					PManCovered->Caption="Covered: "+IntToStr(covered_man)+" % ";
				}
				else
				{
					PManShoots->Caption="Выстрелы: "+IntToStr(shoot_man);
					PManCovered->Caption="Накрыто: "+IntToStr(covered_man)+" % ";
				}
				TimerAroundBrok->Enabled=true;
				Kind1->Enabled=false;
			break;
			case 1:
				LastShoot1->Enabled=true;
				result=1;
				right_x=X/25;
				right_y=Y/25;
				comp.put_bit(right_x,right_y,2);
				side(X/25,Y/25,1);
				review(X/25,Y/25);
				shoot_man++;
				covered_man=0;
				for (int i=0;i<10;i++)
				{
					for (int j=0;j<10;j++)
					{
						if (comp.show_bit(i,j)==2)
						{
							covered_man++;
							sum_brok++;
						}
						if (comp.show_bit(i,j)==3)
						{
							covered_man++;
						}
					}
				}
				need_man=1;
				if (English1->Checked)
				{
					PManShoots->Caption="Shoots: "+IntToStr(shoot_man);
					PManCovered->Caption="Covered: "+IntToStr(covered_man)+" % ";
				}
				else
				{
					PManShoots->Caption="Выстрелы: "+IntToStr(shoot_man);
					PManCovered->Caption="Накрыто: "+IntToStr(covered_man)+" % ";
				}
				switch(count-sum_brok)
				{
					case 0:
						Image56->Picture->Assign(IRed->Picture);
					case 1:
						Image55->Picture->Assign(IRed->Picture);
					case 2:
						Image54->Picture->Assign(IRed->Picture);
					case 3:
						Image53->Picture->Assign(IRed->Picture);
					case 4:
						Image52->Picture->Assign(IRed->Picture);
					case 5:
						Image51->Picture->Assign(IRed->Picture);
					case 6:
						Image50->Picture->Assign(IRed->Picture);
					case 7:
						Image49->Picture->Assign(IRed->Picture);
					case 8:
						Image48->Picture->Assign(IRed->Picture);
					case 9:
						Image47->Picture->Assign(IRed->Picture);
					case 10:
						Image46->Picture->Assign(IRed->Picture);
					case 11:
						Image45->Picture->Assign(IRed->Picture);
					case 12:
						Image44->Picture->Assign(IRed->Picture);
					case 13:
						Image43->Picture->Assign(IRed->Picture);
					case 14:
						Image42->Picture->Assign(IRed->Picture);
					case 15:
						Image41->Picture->Assign(IRed->Picture);
					case 16:
						Image40->Picture->Assign(IRed->Picture);
					case 17:
						Image39->Picture->Assign(IRed->Picture);
					case 18:
						Image38->Picture->Assign(IRed->Picture);
					case 19:
						Image37->Picture->Assign(IRed->Picture);
					case 20:
						Image36->Picture->Assign(IRed->Picture);
					case 21:
						Image35->Picture->Assign(IRed->Picture);
					case 22:
						Image34->Picture->Assign(IRed->Picture);
					case 23:
						Image33->Picture->Assign(IRed->Picture);
					case 24:
						Image32->Picture->Assign(IRed->Picture);
					case 25:
						Image31->Picture->Assign(IRed->Picture);
					case 26:
						Image30->Picture->Assign(IRed->Picture);
					case 27:
						Image29->Picture->Assign(IRed->Picture);
				}
				TimerAroundBrok->Enabled=true;
				Kind1->Enabled=false;
			break;
			case 2:
			case 3:
				LastShoot1->Enabled=true;
				if (Sound1->Checked)
				{
					PlaySound("sounnpla.wav",0,SND_ASYNC);
				}
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::marker_move(int x, int y)
{
	IMan->Picture->Assign(BitMapl);
	IMan->Canvas->Pen->Width=2;
	IMan->Canvas->Pen->Mode=pmMergeNotPen;
	IMan->Canvas->Ellipse(x-3,y-3,x+29,y+29);
	IMan->Canvas->Pen->Width=1;
	IMan->Canvas->Rectangle(x+12,y+12,x+14,y+14);
	IMan->Canvas->Rectangle(x+12,y+6,x+14,y+9);    //n
	IMan->Canvas->Rectangle(x+12,y,x+14,y+4);      //u
	IMan->Canvas->Rectangle(x+12,y+16,x+14,y+19);    //s
	IMan->Canvas->Rectangle(x+12,y+21,x+14,y+25);      //d
	IMan->Canvas->Rectangle(x+6,y+12,x+9,y+14);     //w
	IMan->Canvas->Rectangle(x,y+12,x+4,y+14);       //l
	IMan->Canvas->Rectangle(x+16,y+12,x+19,y+14);     //o
	IMan->Canvas->Rectangle(x+21,y+12,x+25,y+14);       //r
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::TimerMachineTimer(TObject *Sender)
{
	static int step_x;
	static int step_y;
	static int	add_x_or_y;
	int arr_tired[198]={0};
	if (first==0&&tired_x<0)
	{
		first=1;
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==0||man.show_bit(i,j)==1)
				{
					arr_tired[tired*2]=i;
					arr_tired[tired*2+1]=j;
					tired++;
				}
			}
		}
		tired=(rand()%tired)*2;
		step_x=arr_tired[tired];
		step_y=arr_tired[tired+1];
		tired=0;
		PMyShoot->Visible=true;
		PYourShoot->Visible=false;
		marker_move(step_x*25,step_y*25);
	}
	else
	{
		if (tired_x<0)
		{
			count_mach++;
			if (!(count_mach%2)&&!ms)
			{
				int step=rand()%100;
				if (step<25)
				{
					if (step_x>0)
					{
						step_x--;
						add_x_or_y=2;
					}
					else
					{
						step_x++;
						add_x_or_y=1;
					}
				}
				else if (step<50)
				{
					if (step_x<9)
					{
						step_x++;
						add_x_or_y=1;
					}
					else
					{
						step_x--;
						add_x_or_y=2;
					}
				}
				else if (step<75)
				{
					if (step_y>0)
					{
						step_y--;
						add_x_or_y=4;
					}
					else
					{
						step_y++;
						add_x_or_y=3;
					}
				}
				else
				{
					if (step_y<9)
					{
						step_y++;
						add_x_or_y=3;
					}
					else
					{
						step_y--;
						add_x_or_y=4;
					}
				}
			}
			if (count_mach%2)
			{
				marker_move(step_x*25,step_y*25);
			}
			else
			{
				count_mach--;
				ms++;
				if (ms>3)
				{
					count_mach++;
					ms=0;
				}
				else
				{
					switch(add_x_or_y)
					{
						case 1:
							marker_move(step_x*25-(24-6*ms),step_y*25);
						break;
						case 2:
							marker_move(step_x*25+(24-6*ms),step_y*25);
						break;
						case 3:
							marker_move(step_x*25,step_y*25-(24-6*ms));
						break;
						case 4:
							marker_move(step_x*25,step_y*25+(24-6*ms));
						break;
					}
				}
			}
		}
		else
		{
			tired=0;
			count_mach=19;
			tired_x=-1;
			step_x=need_x;
			step_y=need_y;
			PYourShoot->Visible=false;
			PMyShoot->Visible=true;
		}
		if (count_mach==19)	//20
		{
			left_right=0;
			if (man.show_bit_deep(step_x,step_y)==1&&man.show_bit(step_x,step_y)!=1)
			{
				if (Sound1->Checked)
				{
					PlaySound("sounnpla.wav",0,SND_ASYNC);
				}
				write_read_arr_tired(arr_tired);
			}
			else
			{
				switch (man.show_bit(step_x,step_y))
				{
					case 0:
						tired=0;
						result=0;
						man.put_bit(step_x,step_y,3);
						IMan->Picture->Assign(BitMapl);
						mside(step_x,step_y,0);
						first=0;
						count_mach=0;
						brok_milk(step_x,step_y);
						if (radar_sensitivity&&Heavily1->Checked)
						{
							switch (radar_sensitivity)
							{
								case 3:
									write_deep(step_x,step_y,3);
								break;
								case 2:
									write_deep(step_x,step_y,2);
								break;
								case 1:
									write_deep(step_x,step_y,1);
								break;
							}
						}
						PMyShoot->Visible=false;
						PYourShoot->Visible=true;
					break;
					case 1:
						need=1;
						tired=0;
						result=1;
						man.put_bit(step_x,step_y,2);
						if (radar_sensitivity&&Heavily1->Checked)
						{
							switch (radar_sensitivity)
							{
								case 3:
									write_deep(step_x,step_y,3);
								break;
								case 2:
									write_deep(step_x,step_y,2);
								break;
								case 1:
									write_deep(step_x,step_y,1);
								break;
							}
						}
						IMan->Picture->Assign(BitMapl);
						mside(step_x,step_y,1);
						mreview(step_x,step_y);
						first=0;
						count_mach=0;
						brok_milk(step_x,step_y);
					break;
					case 2:
					case 3:
						if (Sound1->Checked)
						{
							PlaySound("sounnpla.wav",0,SND_ASYNC);
						}
						write_read_arr_tired(arr_tired);
					break;
				}
			}
		}
	}
	if (tired_x>=0)
	{
		need_x=step_x;
		need_y=step_y;
		TimerTrassa->Enabled=true;
		TimerMachine->Enabled=false;
		Kind1->Enabled=false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BNemoClick(TObject *Sender)
{
	begin_move();
	PYourShoot->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BMachineClick(TObject *Sender)
{
	begin_move();
	PMyShoot->Visible=true;
	TimerMachine->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerAroundBrokTimer(TObject *Sender)
{
	if (!RadarOFF1->Checked&&!repeat)
	{
		NewGame1->Enabled=false;
		if (left_right)
			BitMaprf->Assign(IRadarMan->Picture);
		else
			BitMaprf->Assign(IRadarComp->Picture);
	}
	if (!repeat)
	{
		switch (result)
		{
		  case 0:
				if (Sound1->Checked)
				{
					PlaySound("sounmilk.wav",0,SND_ASYNC);
				}
		  break;
		  case 1:
				if (Sound1->Checked)
				{
					PlaySound("sounbrok.wav",0,SND_ASYNC);
				}
		  break;
		}
	}
	switch(result)
	{
		case 0:
			switch(repeat)
			{
				case 0:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS1->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy1->Picture);
					else
						BitMapb->Assign(Milk01->Picture);
				break;
				case 1:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS2->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy2->Picture);
					else
						BitMapb->Assign(Milk02->Picture);
				break;
				case 2:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS3->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy3->Picture);
					else
						BitMapb->Assign(Milk03->Picture);
				break;
				case 3:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS4->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy4->Picture);
					else
						BitMapb->Assign(Milk04->Picture);
				break;
				case 4:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS5->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy5->Picture);
					else
						BitMapb->Assign(Milk05->Picture);
				break;
				case 5:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS6->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy1->Picture);
					else
						BitMapb->Assign(Milk04->Picture);
				break;
				case 6:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS7->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy2->Picture);
					else
						BitMapb->Assign(Milk03->Picture);
				break;
				case 7:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS8->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy3->Picture);
					else
						BitMapb->Assign(Milk02->Picture);
				break;
				case 8:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS9->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy4->Picture);
					else
						BitMapb->Assign(Milk01->Picture);
				break;
				case 9:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IMS10->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IRecy->Picture);
					else
						BitMapb->Assign(Milk->Picture);
				break;
			}
		break;
		case 1:
			switch(repeat)
			{
				case 0:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS1->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn1->Picture);
					else
						BitMapb->Assign(Brok01->Picture);
				break;
				case 1:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS2->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn2->Picture);
					else
						BitMapb->Assign(Brok02->Picture);
				break;
				case 2:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS3->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn3->Picture);
					else
						BitMapb->Assign(Brok03->Picture);
				break;
				case 3:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS4->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn4->Picture);
					else
						BitMapb->Assign(Brok04->Picture);
				break;
				case 4:
					if (!RadarOFF1->Checked)
					{
						explotion(1);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS5->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn5->Picture);
					else
						BitMapb->Assign(Brok05->Picture);
				break;
				case 5:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS6->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn6->Picture);
					else
						BitMapb->Assign(Brok04->Picture);
				break;
				case 6:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS7->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn7->Picture);
					else
						BitMapb->Assign(Brok03->Picture);
				break;
				case 7:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS8->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn8->Picture);
					else
						BitMapb->Assign(Brok02->Picture);
				break;
				case 8:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS9->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(ICompOn9->Picture);
					else
						BitMapb->Assign(Brok01->Picture);
				break;
				case 9:
					if (!RadarOFF1->Checked)
					{
						explotion(0);
					}
					if (School1->Checked)
						BitMapb->Assign(IBS10->Picture);
					else if (Windows1->Checked)
						BitMapb->Assign(IMyComp->Picture);
					else
						BitMapb->Assign(Broken->Picture);
				break;
			}
	}
	repeat++;
	if (left_right==0)
	{
		IMan->Canvas->Draw(need_x*25,need_y*25,BitMapb);    // */
		last_x_show=need_x;
		last_y_show=need_y;
	}
	else
		IComp->Canvas->Draw(right_x*25,right_y*25,BitMapb);    // */
	BitMapl->Assign(IMan->Picture);	// if not shape!!!
	if (repeat==10)
	{
		repeat=0;
		NewGame1->Enabled=true;
		TimerAroundBrok->Enabled=false;
		Kind1->Enabled=true;
		if (left_right==0)
		{
			if (!RadarOFF1->Checked)
			{
				for (int i=0;i<28;i+=2)
				{
					if (arr_radar[i]>=0)
					{
						set_radar=1;
						break;
					}
					set_radar=0;
				}
			}
			switch(result)
			{
				case 0:
					if (need==1)
					{
						need_x=last_x;
						need_y=last_y;
					}
					if (!RadarOFF1->Checked&&set_radar)
						need=1;
					LastShoot1->Enabled=true;
				break;
				case 1:
					int sum_brok=0;	//0;
					for (int i=0;i<10;i++)
					{
						for (int j=0;j<10;j++)
						{
							if (man.show_bit(i,j)==2)
								sum_brok++;
						}
					}
					switch(count-sum_brok)
					{
						case 0:
							Image28->Picture->Assign(IRed->Picture);
						case 1:
							Image27->Picture->Assign(IRed->Picture);
						case 2:
							Image26->Picture->Assign(IRed->Picture);
						case 3:
							Image25->Picture->Assign(IRed->Picture);
						case 4:
							Image24->Picture->Assign(IRed->Picture);
						case 5:
							Image23->Picture->Assign(IRed->Picture);
						case 6:
							Image22->Picture->Assign(IRed->Picture);
						case 7:
							Image21->Picture->Assign(IRed->Picture);
						case 8:
							Image20->Picture->Assign(IRed->Picture);
						case 9:
							Image19->Picture->Assign(IRed->Picture);
						case 10:
							Image18->Picture->Assign(IRed->Picture);
						case 11:
							Image17->Picture->Assign(IRed->Picture);
						case 12:
							Image16->Picture->Assign(IRed->Picture);
						case 13:
							Image15->Picture->Assign(IRed->Picture);
						case 14:
							Image14->Picture->Assign(IRed->Picture);
						case 15:
							Image13->Picture->Assign(IRed->Picture);
						case 16:
							Image12->Picture->Assign(IRed->Picture);
						case 17:
							Image11->Picture->Assign(IRed->Picture);
						case 18:
							Image10->Picture->Assign(IRed->Picture);
						case 19:
							Image9->Picture->Assign(IRed->Picture);
						case 20:
							Image8->Picture->Assign(IRed->Picture);
						case 21:
							Image7->Picture->Assign(IRed->Picture);
						case 22:
							Image6->Picture->Assign(IRed->Picture);
						case 23:
							Image5->Picture->Assign(IRed->Picture);
						case 24:
							Image4->Picture->Assign(IRed->Picture);
						case 25:
							Image3->Picture->Assign(IRed->Picture);
						case 26:
							Image2->Picture->Assign(IRed->Picture);
						case 27:
							Image1->Picture->Assign(IRed->Picture);
					}
					if (side_x_y==1)
					{
						side_x_y=0;
						need=0;
						int game_end=0;	//0;
						for (int i=0;i<10;i++)
						{
							for (int j=0;j<10;j++)
							{
								if (man.show_bit(i,j)==1)
									game_end=1;
							}
						}
						 if (!game_end)
							end_game(1);
						else
						{
							if (!RadarOFF1->Checked&&set_radar)
							{
								need=1;
								serch_near_target();
							}
							else
							{
								TimerMachine->Enabled=true;
								Kind1->Enabled=false;
							}
						}
					}
					else
					{
						serch_near_target();
					}
				break;
			}
		}
		else
		{
			int game_end=0;
			if (result==0)
			{
				TimerMachine->Enabled=true;
				Kind1->Enabled=false;
			}
			else
			{
				for (int i=0;i<10;i++)
				{
					for (int j=0;j<10;j++)
					{
						if (comp.show_bit(i,j)==1)
							game_end=1;
					}
				}
				if (!game_end)
					end_game(0);
			}
			if (need_man==0&&need==1)
				serch_near_target();
		}
	}
	if (tired_x==0)	//&&need==0)
	{
		TimerMachine->Enabled=false;
		TimerGo->Enabled=true;
		Kind1->Enabled=false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Example1Click(TObject *Sender)
{
	if (BHideExample->Visible)
	{
		Kind1->Enabled=true;
		ButtonChoiceScheme->Enabled=true;
		BHideExample->Visible=false;
		IMan->Canvas->Draw(0,0,BitMapl);
		cover=0;
		count=0;
		count_sh=0;
		vector=1;
		for ( int i=0;i<16;i++ )
		{
			fign[i]=0;
		}
		for (int x=0;x<10;x++)
		{
			for (int y=0;y<10;y++)
			{
				man.put_bit(x,y,0);
			}
		}
	}
	else
	{
		Kind1->Enabled=false;
		switch (RadioGroup1->ItemIndex)
		{
			case 0:
				count=20;
				count_sh=10;
			break;
			case 1:
				count=25;
				count_sh=9;
			break;
			case 2:
				count=20;
				count_sh=12;
			break;
			case 3:
				count=20;
				count_sh=10;
				RadioGroup1->ItemIndex=0;
			break;
		}
		ButtonChoiceScheme->Enabled=false;
		BHideExample->Visible=true;
		man.next_ship(RadioGroup1->ItemIndex,1);
		show_example();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BHideExampleClick(TObject *Sender)
{
	Kind1->Enabled=true;
	ButtonChoiceScheme->Enabled=true;
	BHideExample->Visible=false;
	IMan->Canvas->Draw(0,0,BitMapl);
	cover=0;
	count=0;
	count_sh=0;
	vector=1;
	for ( int i=0;i<16;i++ )
	{
		fign[i]=0;
	}
	for (int x=0;x<10;x++)
	{
		for (int y=0;y<10;y++)
		{
			man.put_bit(x,y,0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowMap1Click(TObject *Sender)
{
	if (BHideMap->Visible)
	{
		Kind1->Enabled=true;
		IComp->Picture->Assign(BitMap);
		BHideMap->Visible=false;
		PCompCovered->Visible=true;
		PCompShoots->Visible=true;
		BCompResults->Visible=true;
	}
	else
	{
		con_man=1;
		Kind1->Enabled=false;
		BHideMap->Visible=true;
		PCompCovered->Visible=false;
		PCompShoots->Visible=false;
		BCompResults->Visible=false;
		BitMap->Assign(IComp->Picture);
		if (School1->Checked)
			IComp->Picture->Assign(ISchool->Picture);
		else if (Windows1->Checked)
			IComp->Picture->Assign(IWindows->Picture);
		else
			IComp->Picture->Assign(BitMaprr);
		for (int x=0;x<10;x++)
		{
			for (int y=0;y<10;y++)
			{
				paint_array(x,y);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BHideMapClick(TObject *Sender)
{
	Kind1->Enabled=true;
	IComp->Picture->Assign(BitMap);
	BHideMap->Visible=false;
	PCompCovered->Visible=true;
	PCompShoots->Visible=true;
	BCompResults->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::brok_milk(int x, int y)
{
	need_x=x;
	need_y=y;
	shoot_comp++;
	covered_comp=0;
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			if (man.show_bit(i,j)==2)
			{
				covered_comp++;
			}
			if (man.show_bit(i,j)==3)
			{
				covered_comp++;
			}
	   }
   }
	if (English1->Checked)
	{
		PCompShoots->Caption="Shoots: "+IntToStr(shoot_comp);
		PCompCovered->Caption="Covered: "+IntToStr(covered_comp)+" % ";
	}
	else
	{
		PCompShoots->Caption="Выстрелы: "+IntToStr(shoot_comp);
		PCompCovered->Caption="Накрыто: "+IntToStr(covered_comp)+" % ";
	}
	TimerMachine->Enabled=false;
	TimerAroundBrok->Enabled=true;
	Kind1->Enabled=false;
}
//--------------------------------------------------------------------------

void __fastcall TForm1::end_game(int man_com)
{
	if(man_com)
	{
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (comp.show_bit(i,j)==1)
				{
					if (School1->Checked)
					{
						IComp->Canvas->Pen->Width=3;
						IComp->Canvas->Pen->Color=clBlue;	//Navy;
						IComp->Canvas->Brush->Color=clGray;
						IComp->Canvas->Rectangle(i*25+1,j*25+1,i*25+25-1,j*25+25-1);
					}
					else if (Windows1->Checked)
						IComp->Canvas->Draw(i*25,j*25,BitMapw);
					else
					{
						IComp->Canvas->Brush->Color = clTeal;
						IComp->Canvas->Pen->Color = clTeal;
						IComp->Canvas->Rectangle(i*25,j*25,i*25+25,j*25+25 );
					}
				}
			}
		}
		PWin->Visible=true;
		if (English1->Checked)
			PWin->Caption="I Am Winner!!!";
		else
			PWin->Caption="Я Выиграл!!!";
		PMyShoot->Visible= false;
		Language1->Enabled=false;
		Kind1->Enabled=false;
		OwnMap1->Enabled=false;
		ShowMap1->Enabled=false;
		count_man_com(1);
		if (Sound1->Checked)
		{
			PlaySound("sounholi.wav",0,SND_ASYNC);
		}
	}
	else
	{
		if (Show1->Enabled)
		{
			for (int i=0;i<10;i++)
			{
				for (int j=0;j<10;j++)
				{
					if (man.show_bit(i,j)==1)
					{
						if (School1->Checked)
						{
							IMan->Canvas->Pen->Width=3;
							IMan->Canvas->Pen->Color=clBlue;	//Navy;
							IMan->Canvas->Brush->Color=clGray;
							IMan->Canvas->Rectangle(i*25+1,j*25+1,i*25+25-1,j*25+25-1);
						}
						else if (Windows1->Checked)
							IMan->Canvas->Draw(i*25,j*25,BitMapw);
						else
						{
							IMan->Canvas->Brush->Color = clTeal;
							IMan->Canvas->Pen->Color = clTeal;
							IMan->Canvas->Rectangle(i*25,j*25,i*25+25,j*25+25 );
						}
					}
				}
			}
		}
		PWin->Visible=true;
		if (con_man)
		{
			if (English1->Checked)
				PWin->Caption="It was the training.";
			else
				PWin->Caption="Это была тренировка.";
			if (Sound1->Checked)
			{
				PlaySound("sounhihi.wav",0,SND_ASYNC);
			}
		}
		else
		{
			if (English1->Checked)
				PWin->Caption="You Are Winner!!!";
			else
				PWin->Caption="Вы Выиграли!!!";
			count_man_com(0);
			if (Sound1->Checked)
			{
				PlaySound("sounhihi.wav",0,SND_ASYNC);
			}
		}
		PYourShoot->Visible=false;
		Language1->Enabled=false;
		Kind1->Enabled=false;
		OwnMap1->Enabled=false;
		ShowMap1->Enabled=false;
	}
	PWont->Visible=true;
	BYes->Visible=true;
	BNo->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerTrassaTimer(TObject *Sender)
{
	static int count_x=0;
	static int count_y=0;
	count_x++;
	count_y++;
	static int msx=0;
	static int msy=0;
	if ( tired_x==need_x&&tired_y==need_y )
	{
		count_x=0;
		count_y=0;
		msx=0;
		msy=0;
		TimerTrassa->Enabled=false;
		TimerMachine->Enabled=true;
		Kind1->Enabled=false;
	}
	else
	{
		if ( (tired_x!=need_x)&&!msy )
		{
			if ( tired_x>need_x )
			{
				if ((count_x%2)==0)
				{
					if (!msx)
						need_x++;
					msx++;
					count_x--;
					switch(msx)
					{
						case 2:
						case 3:
								need_x++;
						break;
					}
					marker_move(need_x*25-(24-6*msx),need_y*25 );
					switch(msx)
					{
						case 1:
						case 2:
								need_x--;
						break;
					}
					if (msx>=3)
					{
						msx=0;
						count_x++;
					}
				}
				else
					marker_move(need_x*25,need_y*25 );
			}
			else
			{
				if ((count_x%2)==0)
				{
					if (!msx)
						need_x--;
					msx++;
					count_x--;
					switch(msx)
					{
						case 2:
						case 3:
								need_x--;
						break;
					}
					marker_move(need_x*25+(24-6*msx),need_y*25);
					switch(msx)
					{
						case 1:
						case 2:
								need_x++;
						break;
					}
					if (msx>=3)
					{
						msx=0;
						count_x++;
					}
				}
				else
					marker_move(need_x*25,need_y*25 );
			}
		}
		if ( (tired_y!=need_y)&&!msx )
		{
			if ( tired_y>need_y )
			{
				if ((count_y%2)==0)
				{
					if (!msy)
						need_y++;
					msy++;
					count_y--;
					switch(msy)
					{
						case 2:
						case 3:
								need_y++;
						break;
					}
					marker_move(need_x*25,need_y*25-(24-6*msy));
					switch(msy)
					{
						case 1:
						case 2:
								need_y--;
						break;
					}
					if (msy>=3)
					{
						msy=0;
						count_y++;
					}
				}
				else
					marker_move(need_x*25,need_y*25);
			}
			else
			{
				if ((count_y%2)==0)
				{
					if (!msy)
						need_y--;
					msy++;
					count_y--;
					switch(msy)
					{
						case 2:
						case 3:
								need_y--;
						break;
					}
					marker_move(need_x*25,need_y*25+(24-6*msy));
					switch(msy)
					{
						case 1:
						case 2:
								need_y++;
						break;
					}
					if (msy>=3)
					{
						msy=0;
						count_y++;
					}
				}
				else
					marker_move(need_x*25,need_y*25);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerGoTimer(TObject *Sender)
{
	static int nx=0;
	static int ny=0;
	static int lx=0;
	static int ly=0;
	static int c=0;
	if (c==0)
	{
	c++;
	nx=need_x*25;
	ny=need_y*25;
	lx=last_x*25;
	ly=last_y*25;
	}
	if ( lx==nx&&ly==ny )
	{
	c=0;
		nx=0;
		ny=0;
		lx=0;
		ly=0;
		TimerGo->Enabled=false;
		TimerMachine->Enabled=true;
		Kind1->Enabled=false;
	}
	else
	{
		if ( lx!=nx )
		{
			if ( lx>nx )
			{
				lx-=5;
				marker_move(lx,ly );
			}
			else
			{
				lx+=5;
				marker_move(lx,ly );
			}
		}
		if ( ly!=ny )
		{
			if ( ly>ny )
			{
				ly-=5;
				marker_move(lx,ly );
			}
			else
			{
				ly+=5;
				marker_move(lx,ly );
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::serch_near_target()
{
	int arr_around[4]={0,0,0,0};
	int arr_x[4]={-1,0,1,0};
	int arr_y[4]={0,-1,0,1};
	need=1;         //???
	int count_need=0;
	last_x=need_x;
	last_y=need_y;
	if (!RadarOFF1->Checked&&set_radar)
	{
		for (int i=0;i<28;i+=2)
		{
			if (arr_radar[i]>=0)
			{
				need_x=arr_radar[i];
				need_y=arr_radar[i+1];
				arr_radar[i]=-1;
				tired_x=0;
				break;
			}
		}
	}
	else
	{
		for (int i=0;i<4;i++)
		{
			switch(i)
			{
				case 0:
					if (man.show_bit(last_x-1,last_y)==0||man.show_bit(last_x-1,last_y)==1)
					{
						count_need++;
						arr_around[i]=1;
					}
				break;
				case 1:
					if (man.show_bit(last_x,last_y-1)==0||man.show_bit(last_x,last_y-1)==1)
					{
						count_need++;
						arr_around[i]=1;
					}
				break;
				case 2:
					if (man.show_bit(last_x+1,last_y)==0||man.show_bit(last_x+1,last_y)==1)
					{
						count_need++;
						arr_around[i]=1;
					}
				break;
				case 3:
					if (man.show_bit(last_x,last_y+1)==0||man.show_bit(last_x,last_y+1)==1)
					{
						count_need++;
						arr_around[i]=1;
					}
				break;
			}
		}
		if (count_need==0)
		{
			for (int i=0;i<4;i++)
			{
				switch(i)
				{
					case 0:
						if (man.show_bit(last_x-1,last_y)==2)
						{
							for (int i=2;i<=3;i++)
							{
								if (man.show_bit(last_x-i,last_y)==2)
								{
									continue;
								}
								else
								{
									need_x-=i;
									break;
								}
							}
						}
					break;
					case 1:
						if (man.show_bit(last_x,last_y-1)==2)
						{
							for (int i=2;i<=3;i++)
							{
								if (man.show_bit(last_x,last_y-i)==2)
								{
									continue;
								}
								else
								{
									need_y-=i;
									break;
								}
							}
						}
					break;
					case 2:
						if (man.show_bit(last_x+1,last_y)==2)
						{
							for (int i=2;i<=3;i++)
							{
								if (man.show_bit(last_x+i,last_y)==2)
								{
									continue;
								}
								else
								{
									need_x+=i;
									break;
								}
							}
						}
					break;
					case 3:
						if (man.show_bit(last_x,last_y+1)==2)
						{
							for (int i=2;i<=3;i++)
							{
								if (man.show_bit(last_x,last_y+i)==2)
								{
									continue;
								}
								else
								{
									need_y+=i;
									break;
								}
							}
						}
					break;
				}
			}
		}
		switch (count_need)
		{
			case 0:	//???
			tired_x=0; //!!!
			break;
			case 1:
			tired_x=0; //!!!
					if (arr_around[0]==1)
					{
						need_x=last_x-1;
						need_y=last_y;
					}
					if (arr_around[1]==1)
					{
						need_x=last_x;
						need_y=last_y-1;
					}
					if (arr_around[2]==1)
					{
						need_x=last_x+1;
						need_y=last_y;
					}
					if (arr_around[3]==1)
					{
						need_x=last_x;
						need_y=last_y+1;
					}
			break;
			case 2:
			tired_x=0; //!!!
				switch(rand()%4)
				{
					case 0:
						if (arr_around[0]==1)
						{
							need_x=last_x-1;
							need_y=last_y;
						}
						else
						{
							for (int i=0;i<4;i++)
							{
								if (arr_around[i]==1)
								{
									need_x=last_x+arr_x[i];
									need_y=last_y+arr_y[i];
									break;
								}
							}
						}
					break;
					case 1:
						if (arr_around[1]==1)
						{
							need_x=last_x;
							need_y=last_y-1;
						}
						else
						{
							for (int i=0;i<4;i++)
							{
								if (arr_around[i]==1)
								{
									need_x=last_x+arr_x[i];
									need_y=last_y+arr_y[i];
									break;
								}
							}
						}
					break;
					case 2:
						if (arr_around[2]==1)
						{
							need_x=last_x+1;
							need_y=last_y;
						}
						else
						{
							for (int i=0;i<4;i++)
							{
								if (arr_around[i]==1)
								{
									need_x=last_x+arr_x[i];
									need_y=last_y+arr_y[i];
									break;
								}
							}
						}
					break;
					case 3:
						if (arr_around[3]==1)
						{
							need_x=last_x;
							need_y=last_y+1;
						}
						else
						{
							for (int i=0;i<4;i++)
							{
								if (arr_around[i]==1)
								{
									need_x=last_x+arr_x[i];
									need_y=last_y+arr_y[i];
									break;
								}
							}
						}
					break;
				}
			break;
			case 3:
			tired_x=0; //!!!
				switch(rand()%4)
				{
					case 0:
						if (arr_around[0]==1)
						{
							need_x=last_x-1;
							need_y=last_y;
						}
						else
						{
							need_x=last_x+1;
							need_y=last_y;
						}
					break;
					case 1:
						if (arr_around[1]==1)
						{
							need_x=last_x;
							need_y=last_y-1;
						}
						else
						{
							need_x=last_x;
							need_y=last_y+1;
						}
					break;
					case 2:
						if (arr_around[2]==1)
						{
							need_x=last_x+1;
							need_y=last_y;
						}
						else
						{
							need_x=last_x-1;
							need_y=last_y;
						}
					break;
					case 3:
						if (arr_around[3]==1)
						{
							need_x=last_x;
							need_y=last_y+1;
						}
						else
						{
							need_x=last_x;
							need_y=last_y-1;
						}
					break;
				}
			break;
			case 4:
			tired_x=0; //!!!
				switch(rand()%4)
				{
					case 0:
						need_x=last_x-1;
						need_y=last_y;
					break;
					case 1:
						need_x=last_x;
						need_y=last_y-1;
					break;
					case 2:
						need_x=last_x+1;
						need_y=last_y;
					break;
					case 3:
						need_x=last_x;
						need_y=last_y+1;
					break;
				}
			break;
		}
	}
	TimerMachine->Enabled=true;
	Kind1->Enabled=false;
}
//--------------------------------------------------------------------------


void __fastcall TForm1::TimerFlashTimer(TObject *Sender)
{
	static int adar=0;
	switch (adar)
	{
		case 0:
			adar=1;
			radar_clean(1);
		break;
		case 1:
			adar=2;
			radar_zero(1);
			if (Sensitivity31->Checked)
				;
			else if (Sensitivity21->Checked)
				radar_clean(3);
			else if (Sensitivity11->Checked)
				radar_clean(2);
			else
				radar_clean(1);
			break;
		case 2:
			adar=3;
			radar_clean(1);
		break;
		case 3:
			adar=0;
			radar_ship();
			if (Sensitivity31->Checked)
				;
			else if (Sensitivity21->Checked)
				radar_clean(3);
			else if (Sensitivity11->Checked)
				radar_clean(2);
			else
				radar_clean(1);
		break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::write_arr_radar(int x, int y)
{
	for ( int i=0;i<=28 ;i+=2 )
	{
		if ( arr_radar[i]<0 )	//поиск пустого места в массиве
		{
			arr_radar[i]=x;
			arr_radar[i+1]=y;
			for ( int j=i+2;j<=28;j+=2 )
			{
				if ( j==30 )        //
				{
					break;
				}
				if ( arr_radar[j]==x&&arr_radar[j+1]==y )
				{
					arr_radar[j]=-1;
					break;
				}
			}
			break;
		}
		else
		{
			if ( arr_radar[i]==x&&arr_radar[i+1]==y)
			{
				break;
			}
			else
			{
				continue;
			}
		}
	}
}
//------------------------------------------------------------------------------

void __fastcall TForm1::radar_clean(int step)
{
	switch (step)
	{
		case 1:
			IRadarMan->Canvas->Draw(41,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,41,BitMaprc);
			IRadarMan->Canvas->Draw(71,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,71,BitMaprc);
			IRadarComp->Canvas->Draw(41,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,41,BitMaprc);
			IRadarComp->Canvas->Draw(71,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,71,BitMaprc);
		case 2:
			IRadarMan->Canvas->Draw(27,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,26,BitMaprc);
			IRadarMan->Canvas->Draw(85,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,86,BitMaprc);
			IRadarComp->Canvas->Draw(27,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,26,BitMaprc);
			IRadarComp->Canvas->Draw(85,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,86,BitMaprc);
		case 3:
			IRadarMan->Canvas->Draw(13,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,11,BitMaprc);
			IRadarMan->Canvas->Draw(99,56,BitMaprc);
			IRadarMan->Canvas->Draw(56,101,BitMaprc);
			IRadarComp->Canvas->Draw(13,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,11,BitMaprc);
			IRadarComp->Canvas->Draw(99,56,BitMaprc);
			IRadarComp->Canvas->Draw(56,101,BitMaprc);
		break;
	}
}
//------------------------------------------------------------------------------

void __fastcall TForm1::radar_zero(int step)
{
	switch(step)
	{
		case 1:
			IRadarMan->Canvas->Draw(41,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,41,BitMaprz);
			IRadarMan->Canvas->Draw(71,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,71,BitMaprz);
			IRadarComp->Canvas->Draw(41,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,41,BitMaprz);
			IRadarComp->Canvas->Draw(71,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,71,BitMaprz);
		case 2:
			IRadarMan->Canvas->Draw(27,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,26,BitMaprz);
			IRadarMan->Canvas->Draw(85,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,86,BitMaprz);
			IRadarComp->Canvas->Draw(27,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,26,BitMaprz);
			IRadarComp->Canvas->Draw(85,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,86,BitMaprz);
		case 3:
			IRadarMan->Canvas->Draw(13,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,11,BitMaprz);
			IRadarMan->Canvas->Draw(99,56,BitMaprz);
			IRadarMan->Canvas->Draw(56,101,BitMaprz);
			IRadarComp->Canvas->Draw(13,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,11,BitMaprz);
			IRadarComp->Canvas->Draw(99,56,BitMaprz);
			IRadarComp->Canvas->Draw(56,101,BitMaprz);
		break;
	}
}
//------------------------------------------------------------------------------

void __fastcall TForm1::radar_ship()
{
	IRadarMan->Canvas->Draw(41,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,41,BitMaprs);
	IRadarMan->Canvas->Draw(71,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,71,BitMaprs);
	IRadarMan->Canvas->Draw(27,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,26,BitMaprs);
	IRadarMan->Canvas->Draw(85,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,86,BitMaprs);
	IRadarMan->Canvas->Draw(13,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,11,BitMaprs);
	IRadarMan->Canvas->Draw(99,56,BitMaprs);
	IRadarMan->Canvas->Draw(56,101,BitMaprs);
	IRadarComp->Canvas->Draw(41,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,41,BitMaprs);
	IRadarComp->Canvas->Draw(71,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,71,BitMaprs);
	IRadarComp->Canvas->Draw(27,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,26,BitMaprs);
	IRadarComp->Canvas->Draw(85,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,86,BitMaprs);
	IRadarComp->Canvas->Draw(13,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,11,BitMaprs);
	IRadarComp->Canvas->Draw(99,56,BitMaprs);
	IRadarComp->Canvas->Draw(56,101,BitMaprs);
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::TimerStartTimer(TObject *Sender)
{
	static int change_images=0;
	change_images++;
	if (change_images==1)	//?
	{
		IMan->Height=0;
		IMan->Width=0;
		IComp->Width=0;
		IComp->Height=0;
		IMan->Left=165;
		IMan->Top=135;
		IComp->Left=525;
		IComp->Top=135;
		IMan->Visible=true;
		IComp->Visible=true;
		Windows1->Checked=false;                         //
		School1->Checked=true;                           //
		Battle1->Checked=false;                          //
		IRadarMan->Picture->Assign(IRadarSch->Picture);  //
		IRadarComp->Picture->Assign(IRadarSch->Picture); //
		BitMaprc->Assign(ICloseSch->Picture);            //
		BitMaprz->Assign(IZeroSch->Picture);             //
		BitMaprs->Assign(IShipSch->Picture);             //
		BitMapm->Assign(IMS10->Picture);                 //
		BitMapb->Assign(IBS10->Picture);                 //
		BitMap->Assign(ISchool->Picture);                //
		BitMapl->Assign(ISchool->Picture);               //
		IMan->Picture->Assign(BitMapl);                  //
		IComp->Picture->Assign(BitMap);                  //
	}
	else if (change_images<7)
	{
		field_restart(1);
	}
	else
	{
		TimerStart->Enabled=false;
		English1->Checked=false;         //
		Russian1->Checked=true;
                Level1->Caption="Уровень";
                Heavily1->Caption="Тяжело";
                Average1->Caption="Средне";
                Easily1->Caption="Легко";
		Form1->Caption="Морской Бой";
		NewGame1->Caption="Новая Игра";
		Sound1->Caption="Звук";
		LastShoot1->Caption="Посл. Удар";
		Game->Caption="Игра";
		Example1->Caption="Пример";
		Help->Caption="Помощь";
		Help1->Caption="Справка";
		About1->Caption="О Программе";
		ShowMap1->Caption="Карта";
		OwnMap1->Caption="Своя Карта";
		Hide1->Caption="Скрыть";
		Show1->Caption="Показать";
		Language1->Caption="Язык";
		English1->Caption="Английский";
		Russian1->Caption="Русский";
		Radar1->Caption="Радар";
		Sensitivity31->Caption="Чувствительность 3";
		Sensitivity21->Caption="Чувствительность 2";
		Sensitivity11->Caption="Чувствительность 1";
		RadarOFF1->Caption="Радар Выкл.";
		Kind1->Caption="Вид";
		Battle1->Caption="Сундук";
		School1->Caption="Школа";
		Windows1->Caption="Wокнаs";
		Exit1->Caption="Выход";
		RadioGroup1->Caption=" Выбор  Схемы ";
		Label3->Caption="1 Труба";
		Label4->Caption="2 Трубы";
		Label5->Caption="3 Трубы";
		Label6->Caption="4 Трубы";
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Основная");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Большие");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Малые");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Своя");
		PWont->Caption="Ещё Одну Игру?";
		BYes->Caption="ДА";
		BNo->Caption="НЕТ";
		PBegin->Caption="Кто Начинает Первым?";
		BNemo->Caption="Нахимов";
		BMachine->Caption="Железо";
		BDelLastShip->Caption="Убрать Последний";
		PIThink->Caption="Я Думаю";
		PNowYou->Caption="Теперь Вы";
		PMyShoot->Caption="Мой Ход";   //
		PYourShoot->Caption="Ваш ход";
		PManShoots->Caption="Выстрелы";
		PManCovered->Caption="Накрыто";
		PCompShoots->Caption="Выстрелы";
		PCompCovered->Caption="Накрыто";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGame1Click(TObject *Sender)
{
	if (!TimerRestart->Enabled&&!TimerStart->Enabled)
	{
		TimerMachine->Enabled=false;
		TimerOwnScheme->Enabled=false;
		TimerAroundBrok->Enabled=false;
		TimerThinkComp->Enabled=false;
		TimerTrassa->Enabled=false;
		TimerGo->Enabled=false;
		TimerRestart->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerRestartTimer(TObject *Sender)
{
	static int change_images=0;
	if (change_images==1)
	{
		if (Sound1->Checked)
		{
			PlaySound("sounrest.wav",0,SND_ASYNC);
		}
		count_think=0;
		first=0;
		repeat=0;
		count_mach=0;
		tired=0;
		ms=0;
		ship4=0;
		ship3=0;
		ship2=0;
		ship1=0;
		cover=0;
		count=0;
		count_sh=0;
		vector=1;
		shoot_man=0;
		shoot_comp=0;
		covered_man=0;
		covered_comp=0;
		side_x_y=0;
		need=0;
		need_man=0;
		need_x=-1;
		tired_x=-1;
		for (int i=0;i<16;i++)
		{
			fign[i]=0;
			array_choice[i]=0;
		}
		for (int i=0;i<30;i++)
			arr_radar[i]=-1;
		for (int i=0;i<4;i++)
			last_ship[i]=0;
		man.setup(0);
		comp.setup(0);
		if (Battle1->Checked)
		{
			IMan->Picture->Assign(BitMaplr);
			IComp->Picture->Assign(BitMaprr);
			BitMapl->Assign(IMan->Picture);
			BitMap->Assign(IComp->Picture);
		}
		else if (Windows1->Checked)
		{
			IMan->Picture->Assign(IWindows->Picture);
			IComp->Picture->Assign(IWindows->Picture);
			BitMapl->Assign(IWindows->Picture);
			BitMap->Assign(IWindows->Picture);
		}
		else
		{
			IMan->Picture->Assign(ISchool->Picture);
			IComp->Picture->Assign(ISchool->Picture);
			BitMapl->Assign(ISchool->Picture);
			BitMap->Assign(ISchool->Picture);
		}
		BHideMap->Visible=false;
		BHideExample->Visible=false;
		Language1->Enabled=true;
		OwnMap1->Enabled=false;
		Kind1->Enabled=true;
		Hide1->Enabled=true;
		Show1->Enabled=false;
		Image1->Visible=false;
		Image29->Visible=false;
		Image2->Visible=false;
		Image30->Visible=false;
		Image3->Visible=false;
		Image31->Visible=false;
		Image4->Visible=false;
		Image32->Visible=false;
		Image5->Visible=false;
		Image33->Visible=false;
		Image6->Visible=false;
		Image34->Visible=false;
		Image7->Visible=false;
		Image35->Visible=false;
		Image8->Visible=false;
		Image36->Visible=false;
		Image9->Visible=false;
		Image37->Visible=false;
		Image10->Visible=false;
		Image38->Visible=false;
		Image11->Visible=false;
		Image39->Visible=false;
		Image12->Visible=false;
		Image40->Visible=false;
		Image13->Visible=false;
		Image41->Visible=false;
		Image14->Visible=false;
		Image42->Visible=false;
		Image15->Visible=false;
		Image43->Visible=false;
		Image16->Visible=false;
		Image44->Visible=false;
		Image17->Visible=false;
		Image45->Visible=false;
		Image18->Visible=false;
		Image46->Visible=false;
		Image19->Visible=false;
		Image47->Visible=false;
		Image20->Visible=false;
		Image48->Visible=false;
		Image21->Visible=false;
		Image49->Visible=false;
		Image22->Visible=false;
		Image50->Visible=false;
		Image23->Visible=false;
		Image51->Visible=false;
		Image24->Visible=false;
		Image52->Visible=false;
		Image25->Visible=false;
		Image53->Visible=false;
		Image26->Visible=false;
		Image54->Visible=false;
		Image27->Visible=false;
		Image55->Visible=false;
		Image28->Visible=false;
		Image56->Visible=false;
		BOkFull->Visible=false;
		BevelL->Visible=false;
		BevelR->Visible=false;
		BDelLastShip->Visible=false;
		PWont->Visible=false;
		BYes->Visible=false;
		BNo->Visible=false;
		Radar1->Enabled=true;	//false;
                Level1->Enabled=true;
		RadarOFF1->Checked=false;
		Sensitivity31->Checked=true;
		Sensitivity21->Checked=false;
		Sensitivity11->Checked=false;
		radar_zero(1);
		radar_sensitivity=3;
		Example1->Enabled=true;
		ShowMap1->Enabled=false;
		Kind1->Enabled=false;
		if (English1->Checked)
		{
			PCompCovered->Caption="Covered";
			PManCovered->Caption="Covered";
			PCompShoots->Caption="Shoots";
			PManShoots->Caption="Shoots";
		}
		else
		{
			PCompCovered->Caption="Накрыто";
			PManCovered->Caption="Накрыто";
			PCompShoots->Caption="Выстелы";
			PManShoots->Caption="Выстелы";
		}
		PIThink->Hide();
		PNowYou->Hide();
		PMyShoot->Hide();
		PYourShoot->Hide();
		PCompCovered->Visible=false;
		PCompShoots->Visible=false;
		BCompResults->Visible=false;
		PManCovered->Visible=false;
		PManShoots->Visible=false;
		BManResults->Visible=false;
		PIThink->Visible=false;
		PNowYou->Visible=false;
		PMyShoot->Visible=false;
		PYourShoot->Visible=false;
		PBegin->Visible=false;
		BNemo->Visible=false;
		BMachine->Visible=false;
		PWin->Visible=false;
		RadioGroup1->ItemIndex=0;
		UpDown1->Position=0;
		UpDown2->Position=0;
		UpDown3->Position=0;
		UpDown4->Position=0;
		RadioGroup1->Visible=false;
		UpDown1->Visible=false;
		UpDown2->Visible=false;
		UpDown3->Visible=false;
		UpDown4->Visible=false;
		ButtonChoiceScheme->Visible=false;
		ButtonOwnScheme->Visible=false;
		Label1->Visible=false;
		Label2->Visible=false;
		Label3->Visible=false;
		Label4->Visible=false;
		Label5->Visible=false;
		Label6->Visible=false;
		Label7->Visible=false;
		Label8->Visible=false;
		Bevel1->Visible=false;
		Bevel2->Visible=false;
		Bevel3->Visible=false;
		Bevel4->Visible=false;
		PVeryMany->Visible=false;
		IVeryMany2->Visible=false;
		IVeryMany->Visible=false;
		con_man=0;
	}
	else if (change_images>1&&change_images<7)
	{
		field_restart(0);
	}
	else if (change_images>6&&change_images<12)
	{
		field_restart(1);
	}
	else if (change_images>11)
	{
		change_images=0;
		TimerRestart->Enabled=false;
		RadioGroup1->Visible=true;
		ButtonChoiceScheme->Visible=true;
		Kind1->Enabled=true;
		TimerFlash->Enabled=true;
	}
	change_images++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Battle1Click(TObject *Sender)
{
	if (!Battle1->Checked&&!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!TimerStart->Enabled&&
		!TimerRestart->Enabled&&!TimerThinkComp->Enabled)
	{
		Windows1->Checked=false;
		School1->Checked=false;
		Battle1->Checked=true;
		IRadarMan->Picture->Assign(IRadarBattle->Picture);
		IRadarComp->Picture->Assign(IRadarBattle->Picture);
		BitMaprc->Assign(IClose->Picture);
		BitMaprz->Assign(IZero->Picture);
		BitMaprs->Assign(IShip->Picture);
		if (!RadarOFF1->Checked)
		{
			paint_radar_man();
			paint_radar_comp();
		}
		BitMapm->Assign(Milk->Picture);
		BitMapb->Assign(Broken->Picture);
		IMan->Picture->Assign(BitMaplr);
		IComp->Picture->Assign(BitMaprr);
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==2)
					IMan->Canvas->Draw(i*25,j*25,BitMapb);
				else if (man.show_bit(i,j)==3)
					IMan->Canvas->Draw(i*25,j*25,BitMapm);
				else if (man.show_bit(i,j)==1)
				{
					if (Hide1->Enabled)
					{
						IMan->Canvas->Pen->Color=clTeal;
						IMan->Canvas->Brush->Color=clTeal;
						IMan->Canvas->Rectangle(i*25,j*25,i*25+25,j*25+25);
					}
				}
				if (comp.show_bit(i,j)==2)
					IComp->Canvas->Draw(i*25,j*25,BitMapb);
				else if (comp.show_bit(i,j)==3)
					IComp->Canvas->Draw(i*25,j*25,BitMapm);
			}
		}
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::School1Click(TObject *Sender)
{
	if (!School1->Checked&&!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!TimerStart->Enabled
		&&!TimerRestart->Enabled&&!TimerThinkComp->Enabled)
	{
		Windows1->Checked=false;
		School1->Checked=true;
		Battle1->Checked=false;
		IRadarMan->Picture->Assign(IRadarSch->Picture);
		IRadarComp->Picture->Assign(IRadarSch->Picture);
		BitMaprc->Assign(ICloseSch->Picture);
		BitMaprz->Assign(IZeroSch->Picture);
		BitMaprs->Assign(IShipSch->Picture);
		if (!RadarOFF1->Checked)
		{
			paint_radar_man();
			paint_radar_comp();
		}
		BitMapm->Assign(IMS10->Picture);
		BitMapb->Assign(IBS10->Picture);
		BitMap->Assign(ISchool->Picture);
		BitMapl->Assign(ISchool->Picture);
		IMan->Picture->Assign(BitMapl);
		IComp->Picture->Assign(BitMap);
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==2)
					IMan->Canvas->Draw(i*25,j*25,BitMapb);
				else if (man.show_bit(i,j)==3)
					IMan->Canvas->Draw(i*25,j*25,BitMapm);
				else if (man.show_bit(i,j)==1)
				{
					if (Hide1->Enabled)
					{
						IMan->Canvas->Pen->Width=3;
						IMan->Canvas->Pen->Color=clNavy;
						IMan->Canvas->Brush->Color=clGray;
						IMan->Canvas->Rectangle(i*25+1,j*25+1,i*25+25-1,j*25+25-1);
					}
				}
				if (comp.show_bit(i,j)==2)
					IComp->Canvas->Draw(i*25,j*25,BitMapb);
				else if (comp.show_bit(i,j)==3)
					IComp->Canvas->Draw(i*25,j*25,BitMapm);
			}
		}
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::field_restart(int compression)
{
	switch(compression)
	{
		case 1:
			  IMan->Height+=50;
			  IMan->Width+=50;
			  IComp->Width+=50;
			  IComp->Height+=50;
			  IMan->Left-=25;
			  IMan->Top-=25;
			  IComp->Left-=25;
			  IComp->Top-=25 ;
		break;
		case 0:
			  IMan->Height-=50;
			  IMan->Width-=50;
			  IComp->Width-=50;
			  IComp->Height-=50;
			  IMan->Left+=25;
			  IMan->Top+=25;
			  IComp->Left+=25;
			  IComp->Top+=25 ;
		break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BYesClick(TObject *Sender)
{
	PWin->Visible=false;
	PWont->Visible=false;
	BYes->Visible=false;
	BNo->Visible=false;
	TimerRestart->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BNoClick(TObject *Sender)
{
	PWin->Visible=false;
	PWont->Visible=false;
	BYes->Visible=false;
	BNo->Visible=false;
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::explotion(int ball)
{
	static int xm=55;
	static int ym=55;
	static int xm1=65;
	static int ym1=65;
	static int xc=55;
	static int yc=55;
	static int xc1=65;
	static int yc1=65;
	if (left_right)
		IRadarMan->Picture->Assign(BitMaprf);
	else
		IRadarComp->Picture->Assign(BitMaprf);
	if (ball)
	{
		if (left_right)
		{
			xc-=9;
			yc-=9;
			xc1+=9;
			yc1+=9;
			IRadarMan->Canvas->Pen->Width=1;
			IRadarMan->Canvas->Pen->Mode=pmMergeNotPen;
			IRadarMan->Canvas->Ellipse(xc,yc,xc1,yc1);
		}
		else
		{
			xm-=9;
			ym-=9;
			xm1+=9;
			ym1+=9;
			IRadarComp->Canvas->Pen->Width=1;
			IRadarComp->Canvas->Pen->Mode=pmMergeNotPen;
			IRadarComp->Canvas->Ellipse(xm,ym,xm1,ym1);
		}
	}
	else
	{
		if (left_right)
		{
			xc+=9;
			yc+=9;
			xc1-=9;
			yc1-=9;
			IRadarMan->Canvas->Pen->Width=1;
			IRadarMan->Canvas->Pen->Mode=pmMergeNotPen;
			IRadarMan->Canvas->Ellipse(xc,yc,xc1,yc1);
		}
		else
		{
			xm+=9;
			ym+=9;
			xm1-=9;
			ym1-=9;
			IRadarComp->Canvas->Pen->Width=1;
			IRadarComp->Canvas->Pen->Mode=pmMergeNotPen;
			IRadarComp->Canvas->Ellipse(xm,ym,xm1,ym1);
		}
	}
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::paint_radar_man()
{
	(vect_12_wm==1)?IRadarMan->Canvas->Draw(41,56,BitMaprs):IRadarMan->Canvas->Draw(41,56,BitMaprz);
	(vect_12_nm==1)?IRadarMan->Canvas->Draw(56,41,BitMaprs):IRadarMan->Canvas->Draw(56,41,BitMaprz);
	(vect_12_om==1)?IRadarMan->Canvas->Draw(71,56,BitMaprs):IRadarMan->Canvas->Draw(71,56,BitMaprz);
	(vect_12_sm==1)?IRadarMan->Canvas->Draw(56,71,BitMaprs):IRadarMan->Canvas->Draw(56,71,BitMaprz);
	if (Sensitivity31->Checked)
	{
		(vect_13_wm==1)?IRadarMan->Canvas->Draw(27,56,BitMaprs):IRadarMan->Canvas->Draw(27,56,BitMaprz);
		(vect_13_nm==1)?IRadarMan->Canvas->Draw(56,26,BitMaprs):IRadarMan->Canvas->Draw(56,26,BitMaprz);
		(vect_13_om==1)?IRadarMan->Canvas->Draw(85,56,BitMaprs):IRadarMan->Canvas->Draw(85,56,BitMaprz);
		(vect_13_sm==1)?IRadarMan->Canvas->Draw(56,86,BitMaprs):IRadarMan->Canvas->Draw(56,86,BitMaprz);
		(vect_14_wm==1)?IRadarMan->Canvas->Draw(13,56,BitMaprs):IRadarMan->Canvas->Draw(13,56,BitMaprz);
		(vect_14_nm==1)?IRadarMan->Canvas->Draw(56,11,BitMaprs):IRadarMan->Canvas->Draw(56,11,BitMaprz);
		(vect_14_om==1)?IRadarMan->Canvas->Draw(99,56,BitMaprs):IRadarMan->Canvas->Draw(99,56,BitMaprz);
		(vect_14_sm==1)?IRadarMan->Canvas->Draw(56,101,BitMaprs):IRadarMan->Canvas->Draw(56,101,BitMaprz);
	}
	else if (Sensitivity21->Checked)
	{
		(vect_13_wm==1)?IRadarMan->Canvas->Draw(27,56,BitMaprs):IRadarMan->Canvas->Draw(27,56,BitMaprz);
		(vect_13_nm==1)?IRadarMan->Canvas->Draw(56,26,BitMaprs):IRadarMan->Canvas->Draw(56,26,BitMaprz);
		(vect_13_om==1)?IRadarMan->Canvas->Draw(85,56,BitMaprs):IRadarMan->Canvas->Draw(85,56,BitMaprz);
		(vect_13_sm==1)?IRadarMan->Canvas->Draw(56,86,BitMaprs):IRadarMan->Canvas->Draw(56,86,BitMaprz);
	}
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::paint_radar_comp()
{
	(vect_12_w==1)?IRadarComp->Canvas->Draw(41,56,BitMaprs):IRadarComp->Canvas->Draw(41,56,BitMaprz);
	(vect_12_n==1)?IRadarComp->Canvas->Draw(56,41,BitMaprs):IRadarComp->Canvas->Draw(56,41,BitMaprz);
	(vect_12_o==1)?IRadarComp->Canvas->Draw(71,56,BitMaprs):IRadarComp->Canvas->Draw(71,56,BitMaprz);
	(vect_12_s==1)?IRadarComp->Canvas->Draw(56,71,BitMaprs):IRadarComp->Canvas->Draw(56,71,BitMaprz);
	if (Sensitivity31->Checked)
	{
		(vect_13_w==1)?IRadarComp->Canvas->Draw(27,56,BitMaprs):IRadarComp->Canvas->Draw(27,56,BitMaprz);
		(vect_13_n==1)?IRadarComp->Canvas->Draw(56,26,BitMaprs):IRadarComp->Canvas->Draw(56,26,BitMaprz);
		(vect_13_o==1)?IRadarComp->Canvas->Draw(85,56,BitMaprs):IRadarComp->Canvas->Draw(85,56,BitMaprz);
		(vect_13_s==1)?IRadarComp->Canvas->Draw(56,86,BitMaprs):IRadarComp->Canvas->Draw(56,86,BitMaprz);
		(vect_14_w==1)?IRadarComp->Canvas->Draw(13,56,BitMaprs):IRadarComp->Canvas->Draw(13,56,BitMaprz);
		(vect_14_n==1)?IRadarComp->Canvas->Draw(56,11,BitMaprs):IRadarComp->Canvas->Draw(56,11,BitMaprz);
		(vect_14_o==1)?IRadarComp->Canvas->Draw(99,56,BitMaprs):IRadarComp->Canvas->Draw(99,56,BitMaprz);
		(vect_14_s==1)?IRadarComp->Canvas->Draw(56,101,BitMaprs):IRadarComp->Canvas->Draw(56,101,BitMaprz);
	}
	if (Sensitivity21->Checked)
	{
		(vect_13_w==1)?IRadarComp->Canvas->Draw(27,56,BitMaprs):IRadarComp->Canvas->Draw(27,56,BitMaprz);
		(vect_13_n==1)?IRadarComp->Canvas->Draw(56,26,BitMaprs):IRadarComp->Canvas->Draw(56,26,BitMaprz);
		(vect_13_o==1)?IRadarComp->Canvas->Draw(85,56,BitMaprs):IRadarComp->Canvas->Draw(85,56,BitMaprz);
		(vect_13_s==1)?IRadarComp->Canvas->Draw(56,86,BitMaprs):IRadarComp->Canvas->Draw(56,86,BitMaprz);
	}
}
//---------------------------------------------------------------------------------

void __fastcall TForm1::choice_coclour()
{
	if (School1->Checked)
	{
		IMan->Canvas->Brush->Color = clYellow;
		IMan->Canvas->Pen->Color = clYellow;
	}
	else
	{
		IMan->Canvas->Brush->Color = clGray;
		IMan->Canvas->Pen->Color = clGray;
	}
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::Sound1Click(TObject *Sender)
{
	switch (Sound1->Checked)
	{
	  case 0:
			Sound1->Checked=true;
	  break;
	  case 1:
			Sound1->Checked=false;
	  break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadarOFF1Click(TObject *Sender)
{
	if (!TimerMachine->Enabled &&!TimerAroundBrok->Enabled&&!TimerTrassa->Enabled&&
		!TimerGo->Enabled&&!TimerStart->Enabled&&!TimerRestart->Enabled&&!RadarOFF1->Checked)
	{
		radar_sensitivity=0;
		RadarOFF1->Checked=true;
		Sensitivity31->Checked=false;
		Sensitivity21->Checked=false;
		Sensitivity11->Checked=false;
                Level1->Enabled=false;
		radar_clean(1);
		need=0;
		set_radar=0;
		for (int i=0;i<30;i++)
			arr_radar[i]=-1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sensitivity31Click(TObject *Sender)
{
	if (!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&!TimerTrassa->Enabled&&
		!TimerGo->Enabled&&!TimerStart->Enabled&&!TimerRestart->Enabled&&!Sensitivity31->Checked)
	{
		radar_sensitivity=3;
		if (RadarOFF1->Checked)
			radar_zero(1);
		else if (Sensitivity11->Checked)
		{
			radar_zero(2);
		}
		else
		{
			radar_zero(3);
		}
		RadarOFF1->Checked=false;
		Sensitivity31->Checked=true;
		Sensitivity21->Checked=false;
		Sensitivity11->Checked=false;
                Level1->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sensitivity21Click(TObject *Sender)
{
	if (!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&!TimerTrassa->Enabled&&
		!TimerGo->Enabled&&!TimerStart->Enabled&&!TimerRestart->Enabled&&!Sensitivity21->Checked)
	{
		radar_sensitivity=2;
		if (RadarOFF1->Checked)
		{
			radar_zero(1);
			radar_clean(3);
		}
		else if (Sensitivity31->Checked)
		{
			radar_clean(3);
		}
		else
		{
			radar_zero(2);
			radar_clean(3);
		}
		RadarOFF1->Checked=false;
		Sensitivity31->Checked=false;
		Sensitivity21->Checked=true;
		Sensitivity11->Checked=false;
                Level1->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sensitivity11Click(TObject *Sender)
{
	if (!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&!TimerTrassa->Enabled&&
		!TimerGo->Enabled&&!TimerStart->Enabled&&!TimerRestart->Enabled&&!Sensitivity11->Checked)
	{
		radar_sensitivity=1;
		if (RadarOFF1->Checked)
		{
			radar_zero(1);
			radar_clean(2);
		}
		else if (Sensitivity31->Checked)
		{
			radar_clean(2);
		}
		else
		{
			radar_clean(2);
		}
		RadarOFF1->Checked=false;
		Sensitivity31->Checked=false;
		Sensitivity21->Checked=false;
		Sensitivity11->Checked=true;
                Level1->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BDelLastShipClick(TObject *Sender)
{
	BDelLastShip->Visible=false;
	BOkFull->Visible=false;
	switch(last_ship[2])
	{
		case 0:
			for (int i=last_ship[0];i<last_ship[0]+last_ship[3];i++)
				man.put_bit(i,last_ship[1],0);
		break;
		case 1:
			for (int i=last_ship[1];i<last_ship[1]+last_ship[3];i++)
				man.put_bit(last_ship[0],i,0);
		break;
	}
	cover--;
	if (Battle1->Checked)
		IMan->Picture->Assign(BitMaplr);
	else if (Windows1->Checked)
		IMan->Picture->Assign(IWindows->Picture);
	else
		IMan->Picture->Assign(ISchool->Picture);
	show_example();
	BitMapl->Assign(IMan->Picture);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::show_example()
{
	if (School1->Checked)
	{
		IMan->Canvas->Pen->Width=3;
		IMan->Canvas->Pen->Color=clNavy;
		IMan->Canvas->Brush->Color=clGray;
	}
	else if (Battle1->Checked)
	{
		IMan->Canvas->Brush->Color = clTeal;
		IMan->Canvas->Pen->Color = clTeal;
	}
	for (int x=0;x<10;x++)
	{
		for (int y=0;y<10;y++)
		{
			if (man.show_bit(x,y))    //comp
			{
				if (School1->Checked)
					IMan->Canvas->Rectangle(x*25+1,y*25+1,x*25+25-1,y*25+25-1);
				else if (Windows1->Checked)
					IMan->Canvas->Draw(x*25,y*25,BitMapw);
				else
					IMan->Canvas->Rectangle(x*25,y*25,x*25+25,y*25+25 );
			}
		}
	}
}
void __fastcall TForm1::BOkFullClick(TObject *Sender)
{
	PBegin->Visible=true;
	OwnMap1->Enabled=true;
	BNemo->Visible=true;
	BMachine->Visible=true;
	PNowYou->Visible=false;
	Kind1->Enabled=false;
	BDelLastShip->Visible=false;	//after chenge!!!
	BOkFull->Visible=false;	//after chenge!!!
	int stop_bevel=0;
	switch(28-count)
	{
		case 0:
			if (!stop_bevel)
			{
				set_bevel_counter(32,234);
				stop_bevel=1;
			}
			Image1->Visible=true;
			Image29->Visible=true;
		case 1:
			if (!stop_bevel)
			{
				set_bevel_counter(40,226);
				stop_bevel=1;
			}
			Image2->Visible=true;
			Image30->Visible=true;
		case 2:
			if (!stop_bevel)
			{
				set_bevel_counter(48,218);
				stop_bevel=1;
			}
			Image3->Visible=true;
			Image31->Visible=true;
		case 3:
			if (!stop_bevel)
			{
				set_bevel_counter(56,210);
				stop_bevel=1;
			}
			Image4->Visible=true;
			Image32->Visible=true;
		case 4:
			if (!stop_bevel)
			{
				set_bevel_counter(64,202);
				stop_bevel=1;
			}
			Image5->Visible=true;
			Image33->Visible=true;
		case 5:
			if (!stop_bevel)
			{
				set_bevel_counter(72,194);
				stop_bevel=1;
			}
			Image6->Visible=true;
			Image34->Visible=true;
		case 6:
			if (!stop_bevel)
			{
				set_bevel_counter(80,186);
				stop_bevel=1;
			}
			Image7->Visible=true;
			Image35->Visible=true;
		case 7:
			if (!stop_bevel)
			{
				set_bevel_counter(88,178);
			stop_bevel=1;
			}
			Image8->Visible=true;
			Image36->Visible=true;
		case 8:
			if (!stop_bevel)
			{
				set_bevel_counter(96,170);
				stop_bevel=1;
			}
			Image9->Visible=true;
			Image37->Visible=true;
		case 9:
			if (!stop_bevel)
			{
				set_bevel_counter(104,162);
				stop_bevel=1;
			}
			Image10->Visible=true;
			Image38->Visible=true;
		case 10:
			if (!stop_bevel)
			{
				set_bevel_counter(112,154);
				stop_bevel=1;
			}
			Image11->Visible=true;
			Image39->Visible=true;
		case 11:
			if (!stop_bevel)
			{
				set_bevel_counter(120,146);
				stop_bevel=1;
			}
			Image12->Visible=true;
			Image40->Visible=true;
		case 12:
			if (!stop_bevel)
			{
				set_bevel_counter(128,138);
				stop_bevel=1;
			}
			Image13->Visible=true;
			Image41->Visible=true;
		case 13:
			if (!stop_bevel)
			{
				set_bevel_counter(136,130);
				stop_bevel=1;
			}
			Image14->Visible=true;
			Image42->Visible=true;
		case 14:
			if (!stop_bevel)
			{
				set_bevel_counter(144,122);
				stop_bevel=1;
			}
			Image15->Visible=true;
			Image43->Visible=true;
		case 15:
			if (!stop_bevel)
			{
				set_bevel_counter(152,114);
				stop_bevel=1;
			}
			Image16->Visible=true;
			Image44->Visible=true;
		case 16:
			if (!stop_bevel)
			{
				set_bevel_counter(160,106);
				stop_bevel=1;
			}
			Image17->Visible=true;
			Image45->Visible=true;
		case 17:
			if (!stop_bevel)
			{
				set_bevel_counter(168,98);
				stop_bevel=1;
			}
			Image18->Visible=true;
			Image46->Visible=true;
		case 18:
			if (!stop_bevel)
			{
				set_bevel_counter(176,90);
				stop_bevel=1;
			}
			Image19->Visible=true;
			Image47->Visible=true;
		case 19:
			if (!stop_bevel)
			{
				set_bevel_counter(184,82);
				stop_bevel=1;
			}
			Image20->Visible=true;
			Image48->Visible=true;
		case 20:
			if (!stop_bevel)
			{
				set_bevel_counter(192,74);
				stop_bevel=1;
			}
			Image21->Visible=true;
			Image49->Visible=true;
		case 21:
			if (!stop_bevel)
			{
				set_bevel_counter(200,66);
				stop_bevel=1;
			}
			Image22->Visible=true;
			Image50->Visible=true;
		case 22:
			if (!stop_bevel)
			{
				set_bevel_counter(208,58);
				stop_bevel=1;
			}
			Image23->Visible=true;
			Image51->Visible=true;
		case 23:
			if (!stop_bevel)
			{
				set_bevel_counter(216,50);
				stop_bevel=1;
			}
			Image24->Visible=true;
			Image52->Visible=true;
		case 24:
			if (!stop_bevel)
			{
				set_bevel_counter(224,42);
				stop_bevel=1;
			}
			Image25->Visible=true;
			Image53->Visible=true;
		case 25:
			if (!stop_bevel)
			{
				set_bevel_counter(232,34);
				stop_bevel=1;
			}
			Image26->Visible=true;
			Image54->Visible=true;
		case 26:
			if (!stop_bevel)
			{
				set_bevel_counter(240,26);
				stop_bevel=1;
			}
			Image27->Visible=true;
			Image55->Visible=true;
		case 27:
			if (!stop_bevel)
			{
				set_bevel_counter(248,18);
				stop_bevel=1;
			}
			Image28->Visible=true;
			Image56->Visible=true;
		break;
	}
	BevelL->Visible=true;
	BevelR->Visible=true;
	Image1->Picture->Assign(IBlue->Picture);
	Image2->Picture->Assign(IBlue->Picture);
	Image3->Picture->Assign(IBlue->Picture);
	Image4->Picture->Assign(IBlue->Picture);
	Image5->Picture->Assign(IBlue->Picture);
	Image6->Picture->Assign(IBlue->Picture);
	Image7->Picture->Assign(IBlue->Picture);
	Image8->Picture->Assign(IBlue->Picture);
	Image9->Picture->Assign(IBlue->Picture);
	Image10->Picture->Assign(IBlue->Picture);
	Image11->Picture->Assign(IBlue->Picture);
	Image12->Picture->Assign(IBlue->Picture);
	Image13->Picture->Assign(IBlue->Picture);
	Image14->Picture->Assign(IBlue->Picture);
	Image15->Picture->Assign(IBlue->Picture);
	Image16->Picture->Assign(IBlue->Picture);
	Image17->Picture->Assign(IBlue->Picture);
	Image18->Picture->Assign(IBlue->Picture);
	Image19->Picture->Assign(IBlue->Picture);
	Image20->Picture->Assign(IBlue->Picture);
	Image21->Picture->Assign(IBlue->Picture);
	Image22->Picture->Assign(IBlue->Picture);
	Image23->Picture->Assign(IBlue->Picture);
	Image24->Picture->Assign(IBlue->Picture);
	Image25->Picture->Assign(IBlue->Picture);
	Image26->Picture->Assign(IBlue->Picture);
	Image27->Picture->Assign(IBlue->Picture);
	Image28->Picture->Assign(IBlue->Picture);
	Image29->Picture->Assign(IBlue->Picture);
	Image30->Picture->Assign(IBlue->Picture);
	Image31->Picture->Assign(IBlue->Picture);
	Image32->Picture->Assign(IBlue->Picture);
	Image33->Picture->Assign(IBlue->Picture);
	Image34->Picture->Assign(IBlue->Picture);
	Image35->Picture->Assign(IBlue->Picture);
	Image36->Picture->Assign(IBlue->Picture);
	Image37->Picture->Assign(IBlue->Picture);
	Image38->Picture->Assign(IBlue->Picture);
	Image39->Picture->Assign(IBlue->Picture);
	Image40->Picture->Assign(IBlue->Picture);
	Image41->Picture->Assign(IBlue->Picture);
	Image42->Picture->Assign(IBlue->Picture);
	Image43->Picture->Assign(IBlue->Picture);
	Image44->Picture->Assign(IBlue->Picture);
	Image45->Picture->Assign(IBlue->Picture);
	Image46->Picture->Assign(IBlue->Picture);
	Image47->Picture->Assign(IBlue->Picture);
	Image48->Picture->Assign(IBlue->Picture);
	Image49->Picture->Assign(IBlue->Picture);
	Image50->Picture->Assign(IBlue->Picture);
	Image51->Picture->Assign(IBlue->Picture);
	Image52->Picture->Assign(IBlue->Picture);
	Image53->Picture->Assign(IBlue->Picture);
	Image54->Picture->Assign(IBlue->Picture);
	Image55->Picture->Assign(IBlue->Picture);
	Image56->Picture->Assign(IBlue->Picture);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Hide1Click(TObject *Sender)
{
	if (!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!TimerStart->Enabled&&
		!TimerRestart->Enabled&&!TimerThinkComp->Enabled)
	{
		Hide1->Enabled=false;
		Show1->Enabled=true;
		if (Battle1->Checked)
		{
			IMan->Picture->Assign(BitMaplr);
			BitMapm->Assign(Milk->Picture);
			BitMapb->Assign(Broken->Picture);
		}
		else if (Windows1->Checked)
		{
			IMan->Picture->Assign(IWindows->Picture);
			BitMapm->Assign(IRecy->Picture);
			BitMapb->Assign(IMyComp->Picture);
		}
		else
		{
			IMan->Picture->Assign(ISchool->Picture);
			BitMapm->Assign(IMS10->Picture);
			BitMapb->Assign(IBS10->Picture);
		}
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==2)
					IMan->Canvas->Draw(i*25,j*25,BitMapb);
				if (man.show_bit(i,j)==3)
					IMan->Canvas->Draw(i*25,j*25,BitMapm);
			}
		}
		BitMapl->Assign(IMan->Picture);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Show1Click(TObject *Sender)
{
	if (!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!TimerStart->Enabled&&
		!TimerRestart->Enabled&&!TimerThinkComp->Enabled)
	{
		Hide1->Enabled=true;
		Show1->Enabled=false;
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==1)
				{
					if (School1->Checked)
					{
						IMan->Canvas->Pen->Width=3;
						IMan->Canvas->Pen->Color=clNavy;
						IMan->Canvas->Brush->Color=clGray;
						IMan->Canvas->Rectangle(i*25+1,j*25+1,i*25+25-1,j*25+25-1);
					}
					else if (Windows1->Checked)
						IMan->Canvas->Draw(i*25,j*25,BitMapw);
					else
					{
						IMan->Canvas->Pen->Color=clTeal;
						IMan->Canvas->Brush->Color=clTeal;
						IMan->Canvas->Rectangle(i*25,j*25,i*25+25,j*25+25);
					}
				}
			}
		}
		BitMapl->Assign(IMan->Picture);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::English1Click(TObject *Sender)
{
	if (!English1->Checked)
	{
		English1->Checked=true;
		Russian1->Checked=false;
		Form1->Caption="Ships";
                Level1->Caption="Level";
                Heavily1->Caption="Heavily";
                Average1->Caption="Average";
                Easily1->Caption="Easily";
		NewGame1->Caption="New Game";
		Sound1->Caption="Sound";
		Game->Caption="Game";
		Example1->Caption="Example";
		LastShoot1->Caption="Last Shoot";
		Help->Caption="Help";
		Help1->Caption="Help";
		About1->Caption="About";
		ShowMap1->Caption="Show Map";
		OwnMap1->Caption="Own Map";
		Hide1->Caption="Hide";
		Show1->Caption="Show";
		Language1->Caption="Language";
		English1->Caption="English";
		Russian1->Caption="Russian";
		Radar1->Caption="Radar";
		Sensitivity31->Caption="Sensitivity 3";
		Sensitivity21->Caption="Sensitivity 2";
		Sensitivity11->Caption="Sensiyivity 1";
		RadarOFF1->Caption="Radar OFF";
		Kind1->Caption="Kind";
		Battle1->Caption="Battle";
		School1->Caption="School";
		Windows1->Caption="Windows";
		Exit1->Caption="Exit";
		RadioGroup1->Caption=" Choice Scheme ";
		Label3->Caption="1 Pipe";
		Label4->Caption="2 Pipes";
		Label5->Caption="3 Pipes";
		Label6->Caption="4 Pipes";
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Classic");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Big Ships");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Small Ships");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Own Scheme");
		PWont->Caption="You Want Another Game?";
		BYes->Caption="YES";
		BNo->Caption="NO";
		PBegin->Caption="Who Beginst By First?";
		BNemo->Caption="Nemo";
		BMachine->Caption="Machine";
		BDelLastShip->Caption="Delete Last Ship";
		PIThink->Caption="I Think";
		PNowYou->Caption="Now You";
		PMyShoot->Caption="My Move";   //
		PYourShoot->Caption="Your Move";
		PManShoots->Caption="Shoots";
		PManCovered->Caption="Covered";
		PCompShoots->Caption="Shoots";
		PCompCovered->Caption="Covered";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Russian1Click(TObject *Sender)
{
	if (!Russian1->Checked)
	{
		English1->Checked=false;
		Russian1->Checked=true;
                Level1->Caption="Уровень";
                Heavily1->Caption="Тяжело";
                Average1->Caption="Средне";
                Easily1->Caption="Легко";
		Form1->Caption="Морской Бой";
		NewGame1->Caption="Новая Игра";
		Sound1->Caption="Звук";
		LastShoot1->Caption="Посл. Удар";
		Game->Caption="Игра";
		Example1->Caption="Пример";
		Help->Caption="Помощь";
		Help1->Caption="Справка";
		About1->Caption="О Программе";
		ShowMap1->Caption="Карта";
		OwnMap1->Caption="Своя Карта";
		Hide1->Caption="Скрыть";
		Show1->Caption="Показать";
		Language1->Caption="Язык";
		English1->Caption="Английский";
		Russian1->Caption="Русский";
		Radar1->Caption="Радар";
		Sensitivity31->Caption="Чувствительность 3";
		Sensitivity21->Caption="Чувствительность 2";
		Sensitivity11->Caption="Чувствительность 1";
		RadarOFF1->Caption="Радар Выкл.";
		Kind1->Caption="Вид";
		Battle1->Caption="Сундук";
		School1->Caption="Школа";
		Windows1->Caption="Wокнаs";
		Exit1->Caption="Выход";
		RadioGroup1->Caption=" Выбор  Схемы ";
		Label3->Caption="1 Труба";
		Label4->Caption="2 Трубы";
		Label5->Caption="3 Трубы";
		Label6->Caption="4 Трубы";
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Основная");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Большие");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Малые");
		RadioGroup1->Items->Delete(0);
		RadioGroup1->Items->Add("Своя");
		PWont->Caption="Ещё Одну Игру?";
		BYes->Caption="ДА";
		BNo->Caption="НЕТ";
		PBegin->Caption="Кто Начинает Первым?";
		BNemo->Caption="Нахимов";
		BMachine->Caption="Железо";
		BDelLastShip->Caption="Убрать Последний";
		PIThink->Caption="Я Думаю";
		PNowYou->Caption="Теперь Вы";
		PMyShoot->Caption="Мой Ход";   //
		PYourShoot->Caption="Ваш ход";
		PManShoots->Caption="Выстрелы";
		PManCovered->Caption="Накрыто";
		PCompShoots->Caption="Выстрелы";
		PCompCovered->Caption="Накрыто";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::set_bevel_counter(int t, int h)
{
	BevelL->Top=t;
	BevelR->Top=t;
	BevelL->Height=h;
	BevelR->Height=h;
}
//----------------------------------------------------------------------------

void __fastcall TForm1::mouse_down_right_y(int x, int y, int condition, int offset_if, int offset_else)
{
	IMan->Picture->Assign(BitMapl);
	if (y<=condition)
	{
		if (Windows1->Checked)
		{
			IMan->Canvas->Draw(x/25*25,y/25*25,BitMapw);
			switch (offset_if/25)
			{
				case 4:
					IMan->Canvas->Draw(x/25*25,y/25*25+75,BitMapw);
				case 3:
					IMan->Canvas->Draw(x/25*25,y/25*25+50,BitMapw);
				case 2:
					IMan->Canvas->Draw(x/25*25,y/25*25+25,BitMapw);
				break;
			}
		}
		else
		{
			choice_coclour();
			IMan->Canvas->Rectangle(x/25*25,y/25*25,x/25*25+25,y/25*25+offset_if );
		}
	}
	else
	{
		if (Windows1->Checked)
		{
			IMan->Canvas->Draw(x/25*25,225,BitMapw);
			switch (offset_if/25)
			{
				case 4:
					IMan->Canvas->Draw(x/25*25,150,BitMapw);
				case 3:
					IMan->Canvas->Draw(x/25*25,175,BitMapw);
				case 2:
					IMan->Canvas->Draw(x/25*25,200,BitMapw);
				break;
			}
		}
		else
		{
			choice_coclour();
			IMan->Canvas->Rectangle(x/25*25,offset_else,x/25*25+25,250 );
		}
	}
}
//----------------------------------------------------------------------------

void __fastcall TForm1::mouse_down_right_x(int x, int y, int condition, int offset_if, int offset_else)
{
	IMan->Picture->Assign(BitMapl);
	if (x<=condition)
	{
		if (Windows1->Checked)
		{
			IMan->Canvas->Draw(x/25*25,y/25*25,BitMapw);
			switch (offset_if/25)
			{
				case 4:
					IMan->Canvas->Draw(x/25*25+75,y/25*25,BitMapw);
				case 3:
					IMan->Canvas->Draw(x/25*25+50,y/25*25,BitMapw);
				case 2:
					IMan->Canvas->Draw(x/25*25+25,y/25*25,BitMapw);
				break;
			}
		}
		else
		{
			choice_coclour();
			IMan->Canvas->Rectangle(x/25*25,y/25*25,x/25*25+offset_if,y/25*25+25 );
		}
	}
	else
	{
		if (Windows1->Checked)
		{
			IMan->Canvas->Draw(225,y/25*25,BitMapw);
			switch (offset_if/25)
			{
				case 4:
					IMan->Canvas->Draw(150,y/25*25,BitMapw);
				case 3:
					IMan->Canvas->Draw(175,y/25*25,BitMapw);
				case 2:
					IMan->Canvas->Draw(200,y/25*25,BitMapw);
				break;
			}
		}
		else
		{
			choice_coclour();
			IMan->Canvas->Rectangle(offset_else,y/25*25,250,y/25*25+25 );
		}
	}
}
//----------------------------------------------------------------------------

void __fastcall TForm1::mouse_down_left_0(int x, int y, int shift_else, int step)
{
	if (School1->Checked)
	{
		IMan->Canvas->Pen->Width=3;
		IMan->Canvas->Pen->Color=clNavy;
		IMan->Canvas->Brush->Color=clGray;
		switch (step)
		{
			case 1:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+76,(y/25+shift_Y)*25+1,(x/25+shift_X)*25+99,(y/25+shift_Y)*25+24);
			case 2:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+51,(y/25+shift_Y)*25+1,(x/25+shift_X)*25+74,(y/25+shift_Y)*25+24);
			case 3:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+26,(y/25+shift_Y)*25+1,(x/25+shift_X)*25+49,(y/25+shift_Y)*25+24);
			case 4:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+1,y/25*25+1,(x/25+shift_X)*25+24,y/25*25+24);
			break;
		}
	}
	else if (Windows1->Checked)
	{
		switch (step)
		{
			case 1:
				IMan->Canvas->Draw((x/25+shift_X)*25+75,(y/25+shift_Y)*25,BitMapw);
			case 2:
				IMan->Canvas->Draw((x/25+shift_X)*25+50,(y/25+shift_Y)*25,BitMapw);
			case 3:
				IMan->Canvas->Draw((x/25+shift_X)*25+25,(y/25+shift_Y)*25,BitMapw);
			case 4:
				IMan->Canvas->Draw((x/25+shift_X)*25,y/25*25,BitMapw);
			break;
		}
	}
	else
	{
		IMan->Canvas->Brush->Color = clTeal;
		IMan->Canvas->Pen->Color = clTeal;
		IMan->Canvas->Rectangle((x/25+shift_X)*25,(y/25+shift_Y)*25,(x/25+shift_X)*25+shift_else,(y/25+shift_Y)*25+25 );
	}
}
//----------------------------------------------------------------------------

void __fastcall TForm1::mouse_down_left_1(int x, int y, int shift_else, int step)
{
	if (School1->Checked)
	{
		IMan->Canvas->Pen->Width=3;
		IMan->Canvas->Pen->Color=clNavy;
		IMan->Canvas->Brush->Color=clGray;
		switch (step)
		{
			case 1:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+1,(y/25+shift_Y)*25+76,(x/25+shift_X)*25+24,(y/25+shift_Y)*25+99);
			case 2:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+1,(y/25+shift_Y)*25+51,(x/25+shift_X)*25+24,(y/25+shift_Y)*25+74);
			case 3:
				IMan->Canvas->Rectangle((x/25+shift_X)*25+1,(y/25+shift_Y)*25+26,(x/25+shift_X)*25+24,(y/25+shift_Y)*25+49);
			case 4:
				IMan->Canvas->Rectangle(x/25*25+1,(y/25+shift_Y)*25+1,x/25*25+24,(y/25+shift_Y)*25+24);
			break;
		}
	}
	else if(Windows1->Checked)
	{
		switch (step)
		{
			case 1:
				IMan->Canvas->Draw((x/25+shift_X)*25,(y/25+shift_Y)*25+75,BitMapw);
			case 2:
				IMan->Canvas->Draw((x/25+shift_X)*25,(y/25+shift_Y)*25+50,BitMapw);
			case 3:
				IMan->Canvas->Draw((x/25+shift_X)*25,(y/25+shift_Y)*25+25,BitMapw);
			case 4:
				IMan->Canvas->Draw(x/25*25,(y/25+shift_Y)*25,BitMapw);
			break;
		}
	}
	else
	{
		IMan->Canvas->Brush->Color = clTeal;
		IMan->Canvas->Pen->Color = clTeal;
		IMan->Canvas->Rectangle((x/25+shift_X)*25,(y/25+shift_Y)*25,(x/25+shift_X)*25+25,(y/25+shift_Y)*25+shift_else );
	}
}
//-----------------------------------------------------------------------------

void __fastcall TForm1::begin_move()
{
	PBegin->Visible=false;
	BNemo->Visible=false;
	BMachine->Visible=false;
	PManCovered->Visible=true;
	PManShoots->Visible=true;
	PCompCovered->Visible=true;
	PCompShoots->Visible=true;
	BManResults->Visible=true;
	BCompResults->Visible=true;
	ShowMap1->Enabled=true;
	if (RadarOFF1->Checked)
		radar_clean(1);
	else if(Sensitivity11->Checked)
	{
		radar_zero(1);
		radar_clean(2);
	}
	else if(Sensitivity21->Checked)
	{
		radar_zero(1);
		radar_clean(3);
	}
	else
		radar_zero(1);
	Kind1->Enabled=true;
}
//-----------------------------------------------------------------------------
void __fastcall TForm1::Windows1Click(TObject *Sender)
{
	if (!Windows1->Checked&&!TimerMachine->Enabled&&!TimerAroundBrok->Enabled&&
		!TimerTrassa->Enabled&&!TimerGo->Enabled&&!TimerStart->Enabled&&
		!TimerRestart->Enabled&&!TimerThinkComp->Enabled)
	{
		Battle1->Checked=false;
		School1->Checked=false;
		Windows1->Checked=true;
		IRadarMan->Picture->Assign(IRadarWin->Picture);
		IRadarComp->Picture->Assign(IRadarWin->Picture);
		BitMaprc->Assign(IWinC->Picture);
		BitMaprz->Assign(IWinZ->Picture);
		BitMaprs->Assign(IWinS->Picture);
		if (!RadarOFF1->Checked)
		{
			paint_radar_man();
			paint_radar_comp();
		}
		BitMapm->Assign(IRecy->Picture);
		BitMapb->Assign(IMyComp->Picture);
		IMan->Picture->Assign(IWindows->Picture);
		IComp->Picture->Assign(IWindows->Picture);
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if (man.show_bit(i,j)==2)
					IMan->Canvas->Draw(i*25,j*25,BitMapb);
				else if (man.show_bit(i,j)==3)
					IMan->Canvas->Draw(i*25,j*25,BitMapm);
				else if (man.show_bit(i,j)==1)
				{
					if (Hide1->Enabled)
					{
						IMan->Canvas->Draw(i*25,j*25,BitMapw);
					}
				}
				if (comp.show_bit(i,j)==2)
					IComp->Canvas->Draw(i*25,j*25,BitMapb);
				else if (comp.show_bit(i,j)==3)
					IComp->Canvas->Draw(i*25,j*25,BitMapm);
			}
		}
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LastShoot1Click(TObject *Sender)
{
	TimerLastShoot->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerLastShootTimer(TObject *Sender)
{
	static int repeat=0;
	if (!repeat)
	{
		BitMapl->Assign(IMan->Picture);
		BitMap->Assign(IComp->Picture);
	}
	switch (repeat)
	{
		case 0:
			BitMapLm->Assign(ILast1->Picture);
			BitMapLc->Assign(ILast1->Picture);
		break;
		case 1:
			BitMapLm->Assign(ILast2->Picture);
			BitMapLc->Assign(ILast2->Picture);
		break;
		case 2:
			BitMapLm->Assign(ILast3->Picture);
			BitMapLc->Assign(ILast3->Picture);
		break;
		case 3:
			BitMapLm->Assign(ILast4->Picture);
			BitMapLc->Assign(ILast4->Picture);
		break;
		case 4:
			BitMapLm->Assign(ILast5->Picture);
			BitMapLc->Assign(ILast5->Picture);
		break;
		case 5:
			BitMapLm->Assign(ILast4->Picture);
			BitMapLc->Assign(ILast4->Picture);
		break;
		case 6:
			BitMapLm->Assign(ILast3->Picture);
			BitMapLc->Assign(ILast3->Picture);
		break;
		case 7:
			BitMapLm->Assign(ILast2->Picture);
			BitMapLc->Assign(ILast2->Picture);
		break;
		case 8:
			BitMapLm->Assign(ILast1->Picture);
			BitMapLc->Assign(ILast1->Picture);
		break;
		case 9:
			TimerLastShoot->Enabled=false;
			IMan->Picture->Assign(BitMapl);
			IComp->Picture->Assign(BitMap);
			repeat=0;
			return;
	}
	repeat++;
	IMan->Picture->Assign(BitMapl);
	IComp->Picture->Assign(BitMap);
	if (shoot_man)
		IComp->Canvas->Draw(right_x*25,right_y*25,BitMapLm);
	if (shoot_comp)
		IMan->Canvas->Draw(last_x_show*25,last_y_show*25,BitMapLc);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::count_man_com(int side)
{
	int count=0;
	switch (side)
	{
		case 0:
			for (int i=0;i<10;i++)
			{
				for (int j=0;j<10;j++)
				{
					if (man.show_bit(i,j)==1)
						count++;
				}
			}
			man.inc_count_sum(count);
			man.add_count();
		break;
		case 1:
			for (int i=0;i<10;i++)
			{
				for (int j=0;j<10;j++)
				{
					if (comp.show_bit(i,j)==1)
						count++;
				}
			}
			comp.inc_count_sum(count);
			comp.add_count();
		break;
	}
	if (man.show_count()>comp.show_count())
	{
		PCountMan->Color=clGreen;
		PCountCom->Color=clRed;
	}
	else if (man.show_count()==comp.show_count())
	{
		PCountMan->Color=clGray;
		PCountCom->Color=clGray;
	}
	else
	{
		PCountMan->Color=clRed;
		PCountCom->Color=clGreen;
	}
	if (man.show_count_sum()>comp.show_count_sum())
	{
		PCountSM->Color=clGreen;
		PCountSC->Color=clRed;
	}
	else if (man.show_count_sum()==comp.show_count_sum())
	{
		PCountSM->Color=clGray;
		PCountSC->Color=clGray;
	}
	else
	{
		PCountSM->Color=clRed;
		PCountSC->Color=clGreen;
	}
	PCountMan->Caption=IntToStr(man.show_count());
	PCountMan->Show();
	PCountCom->Caption=IntToStr(comp.show_count());
	PCountCom->Show();
	PCountSM->Caption=IntToStr(man.show_count_sum());
	PCountSM->Show();
	PCountSC->Caption=IntToStr(comp.show_count_sum());
	PCountSC->Show();
}

void __fastcall TForm1::About1Click(TObject *Sender)
{
	AboutBox->Show();
	AboutBox->Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Help1Click(TObject *Sender)
{
	Application->HelpCommand(HELP_CONTENTS, 0);
}
//---------------------------------------------------------------------------

void _fastcall TForm1::write_deep(int step_x, int step_y, int data)
{
	for (int i=step_x-data,j=0;j<(data*2+1);j++,i++)
		man.put_bit_deep(i,step_y);
	for (int i=step_y-data,j=0;j<(data*2+1);j++,i++)
		man.put_bit_deep(step_x,i);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::write_read_arr_tired(int * arr_tired)
{
	count_mach=0;
	if (++tired>2)	//&&covered_comp>1)	//||tired>6 )
	{
		tired=0;
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				if ((man.show_bit(i,j)==0||man.show_bit(i,j)==1)&&man.show_bit_deep(i,j)==0)
				{
					arr_tired[tired*2]=i;
					arr_tired[tired*2+1]=j;
					tired++;
				}
			}
		}
		tired=(rand()%tired)*2;
		tired_x=arr_tired[tired];
		tired_y=arr_tired[tired+1];
	}
}
void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        if(blok_up)
        {
                UpDown1->Position=UpDown1->Position-1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
        if(blok_up)
        {
                UpDown2->Position=UpDown2->Position-1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown3Click(TObject *Sender, TUDBtnType Button)
{
        if(blok_up)
        {
                UpDown3->Position=UpDown3->Position-1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown4Click(TObject *Sender, TUDBtnType Button)
{
        if(blok_up)
        {
                UpDown4->Position=UpDown4->Position-1;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Heavily1Click(TObject *Sender)
{
        Heavily1->Checked=true;
        Average1->Checked=false;
        Easily1->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Average1Click(TObject *Sender)
{
        Heavily1->Checked=false;
        Average1->Checked=true;
        Easily1->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Easily1Click(TObject *Sender)
{
        Heavily1->Checked=false;
        Average1->Checked=false;
        Easily1->Checked=true;
}
//---------------------------------------------------------------------------

