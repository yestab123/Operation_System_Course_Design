#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>

#include "design_note.h"
#include "printf.c"
#include "openfile.c"
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
				i=create_file(para,"tx",ATTR_FILE);
				if(i==FAIL)
				{
					printf("OutOfSize\n");
				}
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

	else if((i=strcmp(option,"ls"))==0)
	{
	    print_file();
	}
    else if((i=strcmp(option,"open"))==0)
    {
        int st;
        printf("EnterOpenMode(r/w):");
        char c[10];
        scanf("%s",c);
        if(strcmp(c,"r")==0)
        {
	        st=open_file(para,OPEN_READ);
    	}
    	else if(strcmp(c,"w")==0)
    		{
    			st=open_file(para,OPEN_WRITE);
    		}
    	else
    	{
    		printf("WRONG ENTER\n");
    		return FAIL;
    	}
        if(st==FAIL)
        {
            printf("OPEN %s ERROR\n",para);
        }
    }
    else if((i=strcmp(option,"list"))==0)
    {
        list_fd();
    }
    else if((i==strcmp(option,"read"))==0)
    {
        int fd;
        printf("EnterFileFD:");
        scanf("%d",&fd);
        if(fd_test(fd)==FAIL)
        {
            printf("None FD\n");
            return FAIL;
        }
        content_read(fd);
    }
    else if((i==strcmp(option,"write"))==0)
    {
    	int fd;
    	printf("EnterFileFD:");
    	scanf("%d",&fd);
    	if(fd_test(fd)==FAIL)
    	{
    		printf("None FD\n");
    		return FAIL;
    	}
    	content_write(fd);
    }
    else if((i==strcmp(option,"close"))==0)
    {
        int fd;
    	printf("EnterFileFD:");
    	scanf("%d",&fd);
    	if(fd_test(fd)==FAIL)
    	{
    		printf("None FD\n");
    		return FAIL;
    	}
    	openfile_close(fd);

    }
    else if((i==strcmp(option,"status"))==0)
    {
        printf_fat();
        return TRUE;
    }

}


int main(int argc ,char **argv)
{

	char option[10];
	char para[10];
	int Running=1;
	init_all();
	SetConsoleTextAttribute(Handlea, 0x0F);
	while(Running)
	{
		memset(option,'\0',strlen(option));
		memset(para,'\0',strlen(para));
		printf("#");
		print_now_path();
		printf(":");
		scanf("%s",option);
		selection(option,para);
//		printf("%s %s\n",option,para);
	}
}
