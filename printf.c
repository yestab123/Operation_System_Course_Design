#include "design_note.c"
HANDLE Handlea;//句柄声明
COORD setCOORD;//定位结构体

void init_printf()
{
	Handlea=GetStdHandle(STD_OUTPUT_HANDLE);
}
void setXY(int x,int y)
{
    setCOORD.X=x;
    setCOORD.Y=y;
    SetConsoleCursorPosition(Handlea,setCOORD);
}

void printf_fat()
{
	int i;
	int j;
	int k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<32;j++)
		{
			if(fat[k]==0)//NULL
				SetConsoleTextAttribute(setHandleaa, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==250)//DIR
				SetConsoleTextAttribute(setHandleaa, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==254)//BROKEN
				SetConsoleTextAttribute(setHandleaa, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(setHandleaa, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			printf("#");
			k++;
		}
		printf("\n");
	}
	SetConsoleTextAttribute(setHandleaa, 0x0F);
}