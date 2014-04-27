int option_init(char *string)
{
	int i;
	int length;
	length=strlen(string);
	option=string;
	for(i=0;i<length;i++)
	{
		if(string[i]==' ')
		{
			string[i]='\0';
			para=&string[i+1];
			break;
		}
	}
}

int option_second(char *string)
{
	int i;
	int length=strlen(string);
	for(i=0;i<length;i++)
	{
		if(string[i]==' ')
		{
			string[i]='\0';
			third=&string[i+1];
			break;
		}
	}
}

 //获取fat目录项下name目录的fat值。
unsigned char find_single_dir_fat(unsigned fat_num,char *name)
{
	file_t temp;
	if(fat[fat_num]!=FAT_DIR)
	{
		return 254;
	}
	memcpy(&temp,store[fat_num].buffer,sizeof(file_t));
	int i;
	for( i = 0; i < temp.under_file_count; i++) {
		file_t i_file = get_fat_dir(temp.under_file[i]);
		if(IS_DIR(i_file.file_attr) && strcmp(name,i_file.file_name)==0)
		return i_file.file_fat;
	}
	return 254;
}


unsigned char find_dir_fat_from_name(char *name)
{
	unsigned char start_fat;
	int start=0;
	if(name[0]=='/')
	{
		start_fat=2;
		start=1;
	}
	else
	{
		start=0;
		start_fat=now_dir_fat;
	}
	char *p=&name[start];
	while(name[start]!='\0')
	{
		if(name[start]=='/')
		{
			name[start]='\0';
			start++;
			start_fat=find_single_dir_fat(start_fat,p);
			p=&name[start];
			if(start_fat==254)
			{
				break;
			}
		}
		else if(name[start+1]=='\0')
		{
			start_fat=find_single_dir_fat(start_fat,p);
			break;
		}
		else
		{
			start++;
		}
	}
	return start_fat;
}