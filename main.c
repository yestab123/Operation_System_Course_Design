#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "design_note.c"
#include "init.c"

int main(int argc ,char **argv)
{
	char option[10];
	char para[10];
	int Running=1;
	init_all();
	while(Running)
	{
		memset(option,'\0',strlen(option));
		memset(para,'\0',strlen(para));
		printf("#");
		scanf("%s %s",option,para);
//		printf("%s %s\n",option,para);
	}
}
