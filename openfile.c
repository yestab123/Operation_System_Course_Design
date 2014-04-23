int find_null_openfile()
{
	int i;
	if(openfile.length>=5)
	{
		return -1;
	}
	else
	{
		for(i=0;i<5;i++)
		{
			if(openfile.file[i].working==0)
			{
				return i;
			}
		}
	}
	return -1;
}

int openfile_close(int fd)
{
	openfile.file[fd].working=0;
	openfile.length--;
	return OK;
}

int fd_test(int fd)
{
	if(fd>5)
	{
		return FAIL;
	}
	if(openfile.file[fd].working==0)
	{
		return FAIL;
	}
	return TRUE;
}

int list_fd()
{
  int i;
  for(i=0;i<5;i++)
    {
    	if(openfile.file[i].working==1){
    	  printf("%d %s ",i,openfile.file[i].name);
	      switch(openfile.file[i].flag)
			{
			case 0:printf("%s","r");break;
			case 1:printf("%s","w");break;
			case 3:printf("%s","rw");break;
			}
   		   printf("\n");
		    }
	}
}

int no_open_test(unsigned char fat_num)
{
	for(i=0;i<5;i++)
	{
		if(openfile.file[fd].working==1)
		{
			if(openfile.file[fd].file_fat==fat_num)
			{
				return FAIL;
			}
		}
	}
	return TRUE;
}