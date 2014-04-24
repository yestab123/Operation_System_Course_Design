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
	file_t temp=get_fat_dir(mark);
	unsigned char t=temp.father_fat;
	file_t ftemp=get_fat_dir(t);
	t=temp.file_fat;
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