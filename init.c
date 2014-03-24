int init_all()
{
	int i;
	for(i=0;i<128;i++)
	{
		fat[i]=0;
		memset(store[i].buffer,'\0',strlen(store[i].buffer));
	}
	openfile.length=0;
	now_dir_fat=3;
}