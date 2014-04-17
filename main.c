#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "design_note.c"
#include "init.c"
#include "fat.c"
#include "dir.c"

int selection(char *option,char * para)
{
	int i;
	if((i=strcmp(option,"cd"))==0)
	{
		if((i=dir_exist(para))==TRUE)
		{
			cd_dir(para);
			return OK;
		}
		else
		{
			printf("dir doesn't exist!!\n");
			return FAIL;
		}
	}
	else if((i=strcmp(option,"create"))==0)
	{
		if((i=strlen(para))!=0 && i<=4)
		{
			if(name_test(para) && !file_exist(para))
			{
				create_file(para,"tx",ATTR_FILE)
			}
			else
				goto CREATE_FAIL;
		}
		else
		{
CREATE_FAIL:
			printf("file name wrong!!\n");
			return FAIL;
		}
	}

	else if((i=strcmp(option,"rm"))==0)
	{

	}



}


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
		print_now_path();
		printf(":");
		scanf("%s %s",option,para);
		selection(option,para);
//		printf("%s %s\n",option,para);
	}
}
