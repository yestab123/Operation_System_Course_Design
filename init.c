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
  file->number=open_new.start_fat;
  //解决flag问题
  file->flag=flag;
  file->read.dnum=file->number;
  file->read.bnum=0;
  file->write.dnum=file->number;
  file->write.bnum=0;
}
  
int list_fd()
{
  int i;
  for(i=0;i<openfile.length;i++)
    {
      printf("%d %s",i,openfile.file[i].name);
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
  

