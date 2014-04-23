file_t get_fat_dir(int fat_num)
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
    if(((int)fat[now_dir_fat])==FAT_DIR)
    {
      file_t now_file=get_now_dir();
      if(now_file.under_file_count==0)
        printf("\n");
      else
      {
         int i;
         for(i=0;i<now_file.under_file_count;i++)
         {
             file_t son_file=get_fat_dir(((int)now_file.under_file[i]));
             printf("%s   %s",son_file.file_name,son_file.file_type);
         }
      }
    }
    else printf("当前为文件！");
}

int create_file(char * file_name,char * file_type,unsigned char attr)//创建目录项,返回TRUE OR FALSE    DJ
{
    file_t c_file;
    memset(&c_file,'\0',sizeof(file_t));
    strcpy(c_file.file_name,file_name);
    strcpy(c_file.file_type,file_type);
    c_file.file_attr=(unsigned int)attr;
    int i=0;
    while(fat[i]!=0) //获取空的fat值
    {
        i++;
    }
    fat[i]=255;
    memset(&store[i].buffer,'\0',sizeof(file_t));//清空对应的磁盘块；
    memcpy(&store[i].buffer,&c_file,sizeof(file_t));//将新建的file复制到对应的磁盘块；
    return 1;
}

int name_test(char *name)//判断名字（文件、目录）是否合法（不含特殊符号等）
{
    int i;
    if(strlen(name)>3) return 0;
    for(i=0;i<strlen(name);i++)
    {
        if(!((name[i]>='0'&&name[i]<='9')||(name[i]>='A'&&name[i]<='Z')||(name[i]>='a'&&name[i]<='b')||(name[i]=='_')))
            return 0;
    }
    return 1;
}