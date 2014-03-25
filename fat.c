#define FAT_NULL 		0 	//对应fAT没有内容
#define FAT_DIR  		250	//该FAT为目录
#define FAT_END 		255	//该FAT的内容是最后一部分
#define FAT_BROKEN 		254	//该FAT已经损坏
#define FAT_LENGTH      128 //FAT表长度
char fat[128];					//Fat表 数字i ->  struct buffer file[i];      0为空，255为文件末尾，254为磁盘损坏


//查找空的FAT表项，返回对应数字
int find_null_fat() {
	for(int i = 3; i < FAT_LENGTH; i++) {
		if(fat[i] == FAT_NULL) {
			return i;
		}
	}
}		


//删除对应的FAT表项，返回TRUE OR FALSE
int delete_fat(int fat_num) {
	if(fat_num > FAT_LENGTH){
		return FALSE；
	} else if(fat[fat_num] == FAT_NULL) {
		return TRUE;
	} else {
		fat[fat_num] = FAT_NULL;
		memset(store[fat_num].buffer,'\0',strlen(store[fat_num].buffer));
		return FALSE;
	}
}

//打印当前路径.
int print_now_path() {
	char str;
	for（i = 0; i < now_path.length; i++){
		 str += get_fat_dir(now_fat[i]).file_name + "/";
	}
	printf("%c\n",str);
}	
