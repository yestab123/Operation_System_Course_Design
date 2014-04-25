file_t get_fat_dir(unsigned char fat_num)
{
    file_t fat_dir;
    memset(&fat_dir,'\0',sizeof(file_t));
    memcpy(&fat_dir,store[fat_num].buffer,sizeof(file_t));
    return fat_dir;
}

file_t get_now_dir()		//获取当前目录的FILE项
{
    file_t now_dir;
    memset(&now_dir,'\0',sizeof(file_t));
    memcpy(&now_dir,store[now_dir_fat].buffer,sizeof(file_t));
    return now_dir;
}

int print_file()			//列出当前目录拥有的文件和目录
{
    file_t dir=get_now_dir();
    printf("+-----------------------+\n");
    printf("|NAME\tSIZE\tTYPE\t|\n");
    printf("+-----------------------+\n");
    if(dir.under_file_count>0)
    {
        int i=0;
       // printf("\n");
        for(i=0;i<dir.under_file_count;i++)
        {
            file_t fileDIR=get_fat_dir(dir.under_file[i]);
            printf("|  %s\t",fileDIR.file_name);
            if(IS_DIR(fileDIR.file_attr))
            {
            	printf("\tDIR\t|");
            }
            else
            {
            	printf("%d\tFILE\t|",fileDIR.length);
            }
            printf("\n");
        }
        printf("+-----------------------+\n");
    }
    else
    {
    	printf("\n");
    }

}

int create_file(char * file_name,char * file_type,unsigned char attr)//创建目录项,返回TRUE OR FALSE    DJ
{
    file_t c_file;
    file_t dir_file=get_now_dir();
    if(dir_file.under_file_count>MAX_FILE)
    {
    	return FAIL;
    }
    memset(&c_file,'\0',sizeof(file_t));
    strcpy(c_file.file_name,file_name);
    strcpy(c_file.file_type,file_type);
    c_file.file_attr=(unsigned int)attr;
    c_file.start_fat=0;
    c_file.fat_count=0;
    c_file.length=0;
    c_file.father_fat=now_dir_fat;
    unsigned char i=find_null_fat();
    if(i>128)
    {
    	return FAIL;
    }
    fat[i]=255;
    c_file.file_fat=i;
    memset(store[i].buffer,'\0',64);//清空对应的磁盘块；
    memcpy(store[i].buffer,&c_file,sizeof(file_t));//将新建的file复制到对应的磁盘块；
    dir_file.under_file[dir_file.under_file_count++]=i;
    memcpy(store[now_dir_fat].buffer,&dir_file,sizeof(file_t));
    return OK;
}

int name_test(char *name)//判断名字（文件、目录）是否合法（不含特殊符号等）
{/*
    int i;
    if(strlen(name)>3) return FAIL;
    for(i=0;i<strlen(name);i++)
    {
        if((!(name[i]>='0'&&name[i]<='9')||!(name[i]>='A'&&name[i]<='Z')||!(name[i]>='a'&&name[i]<='b')||!(name[i]=='_')))
            return 0;
    }*/
    return OK;
}

int create_dir(char *dir_name)
{
	if(strlen(dir_name)>3)
	{
		return FAIL;
	}
	if(name_test(dir_name)==FAIL)
	{
		return FAIL;
	}
	if(dir_exist(dir_name)==TRUE)
	{
		return FAIL;
	}
	int i;
	i=find_null_fat();
	if(i>200)
	{
		return FAIL;
	}
	file_t temp=get_now_dir();
	if(temp.under_file_count>=MAX_FILE)
	{
		return FAIL;
	}
	file_t dir_temp;
	strcpy(dir_temp.file_name,dir_name);
	dir_temp.file_attr=ATTR_DIR;
	dir_temp.start_fat=0;
	dir_temp.file_fat=i;
	fat[i]=255;
	dir_temp.under_file_count=0;
	dir_temp.father_fat=now_dir_fat;
	temp.under_file[temp.under_file_count++]=i;
	dir_temp.length=0;
	memcpy(store[now_dir_fat].buffer,&temp,sizeof(file_t));
	memcpy(store[i].buffer,&dir_temp,sizeof(file_t));
	return OK;

}