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
