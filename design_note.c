#define n 5 //实验中系统允许打开文件的最大数量

typedef struct pointer_t{
	int dnum; //磁盘盘块号
	int bnum; //磁盘盘块内第几个字节
}pointer;

typedef struct{
	char name[20]; //文件绝对路径名
	char attribute; //文件的属性|用1字节表示
	int number; //文件起始盘块号
	int length; //文件长度，文件占用的字节数
	int flag; //操作类型，用0表示以读操作方式打开文件，用1表示以写操作方式打开文件
	pointer read; //读文件的位置，文件打开时dnum为文件起始盘块号，bnum为0
	pointer write; // 写文件的位置，文件刚建立时dnum为文件起始盘块号，bnum为0,打开文件时dnum和bnum为文件的末尾位置
}OFTLE;

struct {
	OFILE file[n];
	int length;
}openfile;



//Fat
char fat[128];

