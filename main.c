#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>

#include "design_note.h"
#include "option.c"
#include "printf.c"
#include "file.c"
#include "openfile.c"
#include "init.c"
#include "fat.c"
#include "dir.c"

int selection()
{
	int i;
	i=strncmp(option,"cd",2);
	if(i==0)
	{
		if(para==NULL)
		{
			printf("usage:cd [DIR_NAME]\n");
			return FAIL;
		}
		if((i=strcmp(para,".."))==0)
		{
			cd_parent_dir();
			return OK;
		}
		if((i=dir_exist(para))==TRUE)
		{
			int j=cd_dir(para);
			if(j==FAIL)
			{
				printf("cd Dir error\n");
			}
			return OK;
		}
		else
		{
			printf("Dir doesn't exist.\n");
			return FAIL;
		}
	}
//=================================
//+++++++++++++++++++++++++++++++++
//=================================

	else if((i=strncmp(option,"mkdir",5))==0)
	{
		if(para==NULL)
		{
			printf("usage:mkdir [DIR_NAME]\n");
			return FAIL;
		}
		int t=create_dir(para);
		if(t==FAIL)
		{
			printf("create dir fail\n");
			return FAIL;
		}
		return OK;
	}
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
	else if((i=strncmp(option,"create",6))==0)
	{
		if(para==NULL)
		{
			printf("usage:create [FILE_NAME]\n");
			return FAIL;
		}
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
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
	else if((i=strncmp(option,"rm",2))==0)
	{

	}
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
	else if((i=strncmp(option,"ls",2))==0)
	{
	    print_file();
	}
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"open",4))==0)
    {
    	if(para==NULL)
    	{
    		printf("usage:open [file_name] [mode(r/w/c)]\n");
    		return FAIL;
    	}

    	option_second(para);

    	if(third==NULL)
    	{
    		printf("usage:open [file_name] [mode(r/w/c)]\n");
    		return FAIL;
    	}
        int st;

        if(strcmp(third,"r")==0)
        {
	        st=open_file(para,OPEN_READ,0);
    	}
    	else if(strcmp(third,"w")==0)
    	{
    		st=open_file(para,OPEN_WRITE,0);
    	}
    	else if(strcmp(third,"c")==0)
    	{
    		st=open_file(para,OPEN_WRITE,1);
    	}
    	else
    	{
    		printf("MODE WRONG\n");
    		return FAIL;
    	}

        if(st==FAIL)
        {
            printf("OPEN %s ERROR\n",para);
        }
    }

//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"list",4))==0)
    {
        list_fd();
    }
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"read",4))==0)
    {
    	if(para==NULL)
    	{
    		printf("usage:read [file_FD] [read_size]\n");
    		return FAIL;
    	}
    	option_second(para);
    	if(third==NULL)
    	{
    		printf("usage:read [file_FD] [read_size]\n");
    		return FAIL;
    	}
    	int fd=atoi(para);
    	int size=atoi(third);
    	int t=TRUE;
        if(fd_test(fd)==FAIL)
        {
            printf("WRONG FD\n");
            return FAIL;
        }
   		while(size>0)
   		{
        	t=read_byte(fd);
        	if(t==FAIL)
        	{
        		break;
        	}
      		size--;
   		}
   		if(size>0)
   		{
   			printf("#END#\n");
   		}
    }
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"write",5))==0)
    {
    	if(para==NULL)
    	{
    		printf("usage:write [file_FD] |End with #\n");
    		return FAIL;
    	}
    	int fd=atoi(para);
    	int t=TRUE;
        if(fd_test(fd)==FAIL)
        {
            printf("WRONG FD\n");
            return FAIL;
        }

        t=write_byte(fd);

    }
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"close",5))==0)
    {
    	if(para==NULL)
    	{
    		printf("usage:close [file_FD]\n");
    		return FAIL;
    	}
    	int fd=atoi(para);
    	if(fd_test(fd)==FAIL)
    	{
    		printf("WRONG FD\n");
    		return FAIL;
    	}
    	openfile_close(fd);
    }
//=================================
//+++++++++++++++++++++++++++++++++
//=================================
    else if((i=strncmp(option,"status",6))==0)
    {
        printf_fat();
        return TRUE;
    }

    else if((i=strncmp(option,"exit",4))==0)
    {
    	save_file();
    	exit(0);
    }

}


int main(int argc ,char **argv)
{

	int Running=1;
	init_all();
	SetConsoleTextAttribute(Handlea, 0x0F);
	while(Running)
	{
		save_file();
		memset(string,'\0',sizeof(string));
		option=NULL;
		para=NULL;
		third=NULL;
		printf("#");
		path_string();
		printf("%s",temp_path);
		printf(":");
		gets(string);
		option_init(string);
		selection();
//		printf("%s %s\n",option,para);
	}
}
