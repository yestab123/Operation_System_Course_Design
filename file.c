int fat_save()
{
	int i;
	unsigned char t;
	for(i=0;i<64;i++)
	{
		t=fat[i];
		memcpy(&store[0].buffer[i],&t,1);
	}
	for(i=64;i<128;i++)
	{
		t=fat[i];
		memcpy(&store[1].buffer[i-64],&t,1);
	}
}

int fat_read()
{
	int i;
	unsigned char t;
	for(i=0;i<64;i++)
	{
		memcpy(&t,&store[0].buffer[i],1);
		fat[i]=t;
	}
	for(i=64;i<128;i++)
	{
		memcpy(&t,&store[1].buffer[i-64],1);
		fat[i]=t;
	}
}

int save_file()
{
	FILE *temp;
	temp=fopen("hard.disk","w");
	fat_save();
	int i;
	for(i=0;i<128;i++)
	{
		fwrite(store[i].buffer,64,1,temp);
	}
	fclose(temp);
}

int read_file()
{
	FILE *temp;
	temp=fopen("hard.disk","r");
	if(temp==NULL)
	{
		return FAIL;
	}
	int i;
	for(i=0;i<128;i++)
	{
		fread(store[i].buffer,64,1,temp);
	}
	fat_read();
	fclose(temp);
	return OK;
}