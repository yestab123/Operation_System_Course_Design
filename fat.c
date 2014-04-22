

//查找空的FAT表项，返回对应数字
int find_null_fat() {
	int i;
	for( i = 3; i < FAT_LENGTH; i++) {
		if(fat[i] == FAT_NULL) {
			return i;
		}
	}
}		


//删除对应的FAT表项，返回TRUE OR FALSE
int delete_fat(int fat_num) {
	if(fat_num > FAT_LENGTH){
		return FALSE;
	} else if(fat[fat_num] == FAT_NULL) {
		return TRUE;
	} else {
		fat[fat_num] = FAT_NULL;
		memset(store[fat_num].buffer,'\0',strlen(store[fat_num].buffer));
		return FALSE;
	}
}
//返回当前路径字符窜
char *  string_now_path(){
	char str;
	for（i = 0; i < now_path.length; i++){
		 str += get_fat_dir(now_fat[i]).file_name + "/";
	}
	return str;
}		
//打印当前路径.
int print_now_path() {
	char str;
	for（i = 0; i < now_path.length; i++){
		 str += get_fat_dir(now_fat[i]).file_name + "/";
	}
	printf("%c\n",str);
}	

//2014/3/28
//判断当前目录是否存在dir_name目录，存在返回TRUE，不存在返回FALSE；
int dir_exist(char * dir_name) {
	file_t f_now_dir = get_now_dir();//获取当前
	int i;
	for( i = 0; i < f_now_dir.under_file_count; i++) {
		file_t i_file = get_fat_dir(f_now_dir.under_file[i])
		if(IS_DIR(i_file.file_attr) && i_file.file_name.strcmp(dir_name))
		return false;
	}
}

//判断当前目录是否存在file_name文件；存在返回TRUE，不存在返回FALSE
int file_exist(char * file_name) {
	file_t f_now_dir = get_now_dir();
	int i;
	for( i = 0; i < f_now_dir.under_file_count; i++) {
		file_t i_file = get_fat_dir(f_now_dir.under_file[i])
		if(IS_FILE(i_file.file_attr) && i_file.file_name.strcmp(file_name))
		return false;
	}
}

//根据文件名在当前目录获取文件项
file_t get_file_from_name(char *file_name) {
	filt_t f_now_dir = get_now_dir(); 
	int i;
	for( i = 0; i < f_now_dir.under_file_count; i++) {
		file_t i_file = get_fat_dir(f_now_dir.under_file[i])
		if(IS_FILE(i_file.file_attr) && i_file.file_name.strcmp(file_name))
		return i_file;
	}
}

int get_fat_from_name(char *file_name) {
	filt_t f_now_dir = get_now_dir(); 
	int i;
	for( i = 0; i < f_now_dir.under_file_count; i++) {
		file_t i_file = get_fat_dir(f_now_dir.under_file[i])
		if(IS_FILE(i_file.file_attr) && i_file.file_name.strcmp(file_name))
		return f_now_dir.under_file[i];
	}
}

int delete_file(char * file_name) {
	if (!file_exist(file_name))//判断文件是否存在
		return false;
	file_t ft = get_file_from_name(file_name);
	int s_fat = ft.start_fat;
	do{
		int n_fat = fat[s_fat];
		menset(store[s_fat].buffer,'\0',64);
		fat[s_fat] = FAT_NULL;//清空文件内容所在fat表的值

	}while(n_fat != FAT_END)
	int ft_fat = get_fat_from_name(file_name);
	menset(store[ft_fat].buffer,'\0',64);//清空目录项所在fat表值
}
  //切换到当前目录的file_name目录   SZ int
int cd_dir(char * file_name) {
	if (!dir_exist(file_name))
		return false;
	now_dir_fat = get_fat_from_name(file_name);
}

 
 //切换到父目录   
cd_parent_dir() {
	file_t ft = get_now_dir();
	now_dir_fat = ft.father_fat;
}