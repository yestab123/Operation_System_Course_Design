
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
void getXY()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(Handlea,&info);    
    setCOORD.X=info.dwCursorPosition.X; 
    setCOORD.Y=info.dwCursorPosition.Y; 
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
				SetConsoleTextAttribute(Handlea, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==250)//DIR
				SetConsoleTextAttribute(Handlea, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==254)//BROKEN
				SetConsoleTextAttribute(Handlea, FOREGROUND_RED |FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(Handlea, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			printf("#");
			k++;
		}
		printf("\n");
	}
	SetConsoleTextAttribute(Handlea, 0x0F);
}

void printf_fat_all()
{
	int i;
	int j;
	int k=0;
	getXY();
	int x_a=setCOORD.X;
	int y_a=setCOORD.Y;
	int x=32;
	int y=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<32;j++)
		{
			setXY(x,y);
			if(fat[k]==0)//NULL
				SetConsoleTextAttribute(Handlea, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==250)//DIR
				SetConsoleTextAttribute(Handlea, FOREGROUND_RED |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			else if(fat[k]==254)//BROKEN
				SetConsoleTextAttribute(Handlea, FOREGROUND_RED |FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(Handlea, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			printf("#");
			k++;
			x++;
		}
		y++;
		x=32;
	}
	SetConsoleTextAttribute(Handlea, 0x0F);
	/*if(y_a>32)
	{
		y_a=0;
	}*/
	setXY(x_a,y_a);
}
