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
