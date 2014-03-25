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