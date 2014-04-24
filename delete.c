int file_count_sort(file_t *temp,unsigned char fat_num)
{
	int i;
	int j;
	for(i=0;i<(temp->under_file_count);i++)
	{
		if(temp->under_file[i]==fat_num)
		{
			break;
		}
	}
	for(j=i+1;j<temp->under_file_count;j++)
	{
		temp->under_file[i]=temp->under_file[j];
		i++;
	}
	temp->under_file_count--;
	return OK;
}

int delete_file(char *file_name)
{
	if (!file_exist(file_name))//判断文件是否存在
		return FAIL;
	int mark=get_fat_from_name(file_name);
	if(no_open_test(mark)==FAIL)
	{
		int fd=get_fd(mark);
		openfile_close(fd);
	}
	file_t temp=get_fat_dir(mark);
	unsigned char t=temp.father_fat;
	file_t ftemp=get_fat_dir(t);
	t=temp.file_fat;
	fat[t]=0;
	memset(store[t].buffer,'\0',64);
	file_count_sort(&ftemp,t);
	memcpy(store[ftemp.file_fat].buffer,&ftemp,sizeof(file_t));
	t=temp.start_fat;
	if(t==0)
	{
		return OK;
	}
	memset(store[t].buffer,'\0',64);
	unsigned char j=t;
	while(fat[t]!=255)
	{
		t=fat[t];
		fat[j]=0;
		memset(store[j].buffer,'\0',64);
		j=t;
	}
	fat[t]=0;
	memset(store[t].buffer,'\0',64);
	return OK;

}

int delete_file_fat(unsigned char fat_num)
{
	file_t temp=get_fat_dir(fat_num);
	fat[fat_num]=0;
	memset(store[fat_num].buffer,'\0',64);
	if(no_open_test(fat_num)==FAIL)
	{
		int fd=get_fd(fat_num);
		openfile_close(fd);
	}
	if(temp.start_fat==0)
	{
		return 0;
	}
	int t=temp.start_fat;
	int j=t;
	while(fat[t]!=255)
	{
		t=fat[t];
		fat[j]=0;
		j=t;
		memset(store[j].buffer,'\0',64);
	}
	fat[t]=0;
	memset(store[t].buffer,'\0',64);

}

int delete_dir_roll(file_t temp)
{
	int i=0;
	for(i=0;i<temp.under_file_count;i++)
	{
		file_t lin=get_fat_dir(temp.under_file[i]);
		if(IS_DIR(lin.file_attr)==1)
		{
			delete_dir_roll(lin);
		}
		else
		{
			delete_file_fat(lin.file_fat);
		}
	}
	memset(store[temp.file_fat].buffer,'\0',64);
	fat[temp.file_fat]=0;
}

int delete_dir(unsigned char fat_num)
{
	file_t temp=get_fat_dir(fat_num);
	file_t father=get_fat_dir(temp.father_fat);
	file_count_sort(&father,temp.file_fat);
	memcpy(store[father.file_fat].buffer,&father,sizeof(file_t));
	delete_dir_roll(temp);
	
}
