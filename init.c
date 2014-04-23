int init_all()
{

	int i;

//=================================
//+128个盘块初始化
//=================================
	for(i=0;i<128;i++)
	{
		fat[i]=0;
		memset(store[i].buffer,'\0',strlen(store[i].buffer));
	}
	openfile.length=0;	//打开文件初始化
	now_dir_fat=2;		//当前目录的FAT值，默认为根目录/ 即为fat=2;

//=================================
//+当前路径记录初始化，默认/为当前路径（根目录）
//=================================
	for(i=0;i<PATH_DEEP;i++)
	{
		now_path.now_fat[i]=FAT_NULL;
	}
	now_path.now_fat[0]=2;
	now_path.length=1;
}

int open_file(char *file_name,int flag)
{
  int i,j;
  if(openfile.length<=n)
    {
      return FAIL;
    }
  i=name_test(file_name);
  j=file_exist(file_name);
  if(i!=OK||j!=TRUE)
    {
      return FAIL;
    }
  file_t open_new;
  open_new=get_file_from_name(file_name);
  open_file_add(&openfile.file[openfile.length++],open_new,flag);
}

int open_file_add(OFILE *file,file_t open_new,int flag)
{
  sprintf(file->name,"%s/%s",print_now_path(),open_new.file_name);
  file->attribute=(unsigned)open_new.file_attr;

  file->number=fat[open_new.start_fat];
  //解决flag问题
  file->flag=flag;
    if(fat[open_new.start_fat]==255)//文件没有内容
  {
  	 file->write.dnum=-1;
  	 file->read.dnum=-1;
  }
  else
  {
  file->read.dnum=file->number;
  file->write.dnum=file->number;
	}
  file->read.bnum=0;
  file->write.bnum=0;//edit
}

int list_fd()
{
  int i;
  for(i=0;i<openfile.length;i++)
    {
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


int content_read(int fd)
{
	if(openfile.file[fd].read.dnum==-1)
	{
		printf("\n#END#\n");
		return FAIL;
	}
	if(openfile.file[fd].read.bnum>=64)
	{
		int fat_next=fat[openfile.file[fd].read.dnum];
		if(fat_next>0 && fat_next <128)
		{
			openfile.file[fd].read.dnum=fat_next;
			openfile.file[fd].read.bnum=0;
		}
		else
		{
			printf("\n#END#\n");
			return FAIL;
		}
	}
	char a;
	memcpy(&a,store[openfile.file[fd].read.dnum].buffer + openfile.file[fd].read.bnum,1);
	openfile.file[fd].read.bnum++;
	if(a!='#')
	{
		printf("%c",a);
	}
	else
	{
		printf("\n#END#\n");
		return FAIL;
	}
	return OK;

}

int content_write(int fd)
{
	char s;
	int i=0;
	int count;
	char buffer[300];
	s=getchar();
	while(s!='#')
	{
		buffer[i]=s;
		i++;
		if(i>=300)
			break;
		s=getchar();
	}
	if(i>(64-openfile.file[fd].write.bnum))
	{
		count=64-openfile.file[fd].write.bnum;
		memcpy(store[openfile.file[fd].write.dnum].buffer+openfile.file[fd].write.bnum,buffer,count);
		i=i-count;
		while(i>0)
		{
			unsigned char fat_t=find_null_fat();
			if(fat_t==FAIL)
			{
				return FAIL;
			}
			fat[openfile.file[fd].write.dnum]=fat_t;
			openfile.file[fd].write.dnum=fat_t;
			if(i<=64)
			{
				memcpy(store[fat_t].buffer,buffer+count,i);
				openfile.file[fd].write.bnum=i;
				count+=i;
				i-=i;
			}
			else
			{
				memcpy(store[fat_t].buffer,buffer+count,64);
				openfile.file[fd].write.bnum=64;
				count+=64;
				i-=64;
			}

		}
	}
	else
	{

		memcpy(store[openfile.file[fd].write.dnum].buffer+openfile.file[fd].write.bnum,buffer,i);
		openfile.file[fd].write.bnum+=i;
	}
	if(openfile.file[fd].write.bnum<64)
	{
		memcpy(store[openfile.file[fd].write.dnum].buffer+openfile.file[fd].write.bnum,"#",1);
	}
}


