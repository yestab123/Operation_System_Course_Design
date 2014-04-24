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

	file_t temp;
	temp.file_name[0]='/';
	temp.file_name[1]='\0';
	temp.file_fat=2;
	fat[2]=255;
	temp.under_file_count=0;
	temp.father_fat=2;
	temp.length=0;
	temp.file_attr=ATTR_DIR;
	memcpy(store[2].buffer,&temp,sizeof(file_t));
//=================================
//+当前路径记录初始化，默认/为当前路径（根目录）
//=================================
	for(i=0;i<PATH_DEEP;i++)
	{
		now_path.now_fat[i]=FAT_NULL;
	}
	for(i=0;i<5;i++)
	{
		openfile.file[i].working=0;
	}
	now_path.now_fat[0]=2;
	now_path.length=1;
	fat[0]=255;
	fat[1]=255;
	init_printf();
	read_file();
}

int open_file(char *file_name,int flag,int cover)
{
  int i,j;
  if(openfile.length>=n)
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
  if(no_open_test(open_new.file_fat)==FAIL)
  {
  	return FAIL;
  }
  i=find_null_openfile();
  if(i==-1)
  {
  	return FAIL;
  }
  //printf("%s",open_new.file_name);
  return open_file_add(&openfile.file[i],open_new,flag,i,cover);
}

int open_file_add(OFILE *file,file_t open_new,int flag,int fd,int cover)
{
	path_string();
  sprintf(file->name,"%s%s",temp_path,open_new.file_name);
  file->attribute=(unsigned)open_new.file_attr;
  file->working=1;
  file->number=open_new.start_fat;
  file->file_fat=open_new.file_fat;
  //解决flag问题
  file->flag=flag;
  file->length=open_new.length;
  file->read_length=0;
    if(open_new.start_fat==0)//文件没有内容
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
  if(flag==OPEN_WRITE)
  {
	  if(cover==1)
	  {
	  	cut_write_init(fd);
	  }
	  else
	  {
	  	add_write_init(fd);
	  }
	}
  openfile.length++;
  return TRUE;
}



int content_read(int fd)
{
	if(openfile.file[fd].flag!=OPEN_READ)
	{
		return FAIL;
	}
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
		openfile.file[fd].read.dnum=-1;
		printf("\n#END#\n");
		return FAIL;
	}
	return OK;

}

int content_write(int fd)//覆盖模式
{
	if(openfile.file[fd].flag!=OPEN_WRITE)
	{
		return FAIL;
	}
	char s;
	int i=0;
	int count;
	char buffer[300];
	if(openfile.file[fd].write.dnum==-1)
	{
		int t=find_null_fat();
		if(t>128)
		{
			return FAIL;
		}
		openfile.file[fd].write.dnum=t;
		openfile.file[fd].write.bnum=0;
		openfile.file[fd].number=t;
		fat[openfile.file[fd].file_fat]=t;
		fat[t]=255;
		file_t temp;
		memcpy(&temp,store[openfile.file[fd].file_fat].buffer,sizeof(file_t));
		temp.start_fat=t;
		memcpy(store[openfile.file[fd].file_fat].buffer,&temp,sizeof(file_t));
	}
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
			if(fat_t>=200)
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

int add_write(int fd)//追加模式
{
	int fat_num;
	if(openfile.file[fd].write.dnum==-1)
	{
		content_write(fd);
	}
	else
	{
		fat_num=openfile.file[fd].write.dnum;
		while(fat[fat_num]!=255)
		{
			fat_num=fat[fat_num];
		}
		openfile.file[fd].write.dnum=fat_num;
		char buffer[64];
		memcpy(buffer,store[fat_num].buffer,64);
		char c=buffer[0];
		int i=0;
		while(c!='#')
		{
			i++;
			c=buffer[i];
		}
		if(i>=64)
        {

        }
	}


}




//=================================
//+++++++++++++++++++++++++++++++++
//=================================
int write_byte(int fd)
{
	if(openfile.file[fd].flag!=OPEN_WRITE)
	{
		return FAIL;
	}
	if(openfile.file[fd].write.dnum==-1)
	{
		int t=find_null_fat();
		if(t>128)
		{
			return FAIL;
		}
		openfile.file[fd].number=t;
		openfile.file[fd].write.dnum=t;
		openfile.file[fd].write.bnum=0;
		fat[t]=255;
		openfile_update(fd,1);
	}
	char c;
	while((c=getchar())!='#')
	{
		if(openfile.file[fd].write.bnum>=64)
		{
			int t=find_null_fat();
			if(t>128)
			{
				return FAIL;
			}
			fat[openfile.file[fd].write.dnum]=t;
			openfile.file[fd].write.dnum=t;
			openfile.file[fd].write.bnum=0;
			fat[t]=255;
		}
		memcpy(&store[openfile.file[fd].write.dnum]\
			.buffer[openfile.file[fd].write.bnum],&c,1);
		openfile.file[fd].write.bnum++;
		openfile.file[fd].length++;
	}
	openfile_update(fd,0);
	getchar();
	return OK;
}

int read_byte(int fd)
{
	if(openfile.file[fd].flag!=OPEN_READ)
	{
		return FAIL;
	}
	if(openfile.file[fd].read.dnum==-1)
	{
		return FAIL;
	}
	if(openfile.file[fd].read_length>=openfile.file[fd].length)
	{
		return FAIL;
	}
	if(openfile.file[fd].read.bnum>=64)
	{
		if(fat[openfile.file[fd].read.dnum]==255)
		{
			return FAIL;
		}
		else
		{
			openfile.file[fd].read.dnum=fat[openfile.file[fd].read.dnum];
			openfile.file[fd].read.bnum=0;
		}
	}
	char c;
	memcpy(&c,&store[openfile.file[fd].read.dnum].\
		buffer[openfile.file[fd].read.bnum],1);
	openfile.file[fd].read.bnum++;
	openfile.file[fd].read_length++;
	printf("%c",c);
	return TRUE;
}
