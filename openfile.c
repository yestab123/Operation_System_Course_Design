int openfile_update(int fd,int flag_fat_update)
{
	int fat_num=openfile.file[fd].file_fat;
	file_t temp;
	memcpy(&temp,store[fat_num].buffer,sizeof(file_t));
	temp.length=openfile.file[fd].length;
	if(flag_fat_update==1)
	{
		fat[fat_num]=openfile.file[fd].number;
		temp.start_fat=openfile.file[fd].number;
	}
	memcpy(store[fat_num].buffer,&temp,sizeof(file_t));
}


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
    int i;
	for(i=0;i<5;i++)
	{
		if(openfile.file[i].working==1)
		{
			if(openfile.file[i].file_fat==fat_num)
			{
				return FAIL;
			}
		}
	}
	return TRUE;
}

int cut_write_init(int fd)
{
	if(openfile.file[fd].write.dnum==-1)
	{
		return TRUE;
	}
	int i,j;
	i=openfile.file[fd].number;
	j=i;
	while(fat[i]!=255)
	{
		i=fat[i];
		fat[i]=0;
		memset(store[i].buffer,'\0',64);
	}
	fat[j]=255;
	openfile.file[fd].length=0;
	openfile.file[fd].write.bnum=0;
	openfile_update(fd,0);
}

int add_write_init(int fd)
{
	if(openfile.file[fd].write.dnum==-1)
	{
		return TRUE;
	}
	int i=openfile.file[fd].number;
	while(fat[i]!=255)
	{
		i=fat[i];
	}
	openfile.file[fd].write.dnum=i;
	int count=openfile.file[fd].length;
	while(count>64)
	{
		count-=64;
	}
	openfile.file[fd].write.bnum=count;

}
