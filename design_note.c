//===========
//+默认值定义
//===========
#define n 5 		//实验中系统允许打开文件的最大数量
#define MAX_FILE 20	//每个目录最大目录项
#define TRUE 0 	
#define FALSE -1

//===========
//+属性定义
//===========
#define ATTR_READ_ONLY 	0x01 	//只读文件
#define ATTR_SYSTEM 	0x02 	//系统文件
#define ATTR_FILE 		0x04 	//普通文件
#define ATTR_DIR 		0x08 	//目录

//===========
//+宏操作
//===========
#define IS_DIR(x) ((x & ATTR_DIR) ? 1 : 0 )				//是目录就返回1，否则返回0
#define IS_FILE(x) ((x & ATTR_FILE) ? 1 : 0 )			//是普通文件就返回1，否则返回0
#define IS_READ_ONLY(x) ((x & ATTR_READ_ONLY) ? 1 : 0 )	//是只读文件就返回1，否则返回0
#define IS_SYSTEM(x) ((x & ATTR_SYSTEM) ? 1 : 0 )		//是系统文件就返回1，否则返回0

//===========
//+FAT表数字说明
//===========
#define ISNULL 		0
#define ISEND 		255
#define ISBROKEN 	254



typedef struct pointer_t{
	int dnum; 	//磁盘盘块号
	int bnum; 	//磁盘盘块内第几个字节
}pointer;

typedef struct OFTLE_S{
	char name[20]; 	//文件绝对路径名
	char attribute; //文件的属性|用1字节表示
	int number; 	//文件起始盘块号
	int length; 	//文件长度，文件占用的字节数
	int flag; 		//操作类型，用0表示以读操作方式打开文件，用1表示以写操作方式打开文件
	pointer read; 	//读文件的位置，文件打开时dnum为文件起始盘块号，bnum为0
	pointer write; 	// 写文件的位置，文件刚建立时dnum为文件起始盘块号，bnum为0,打开文件时dnum和bnum为文件的末尾位置
}OFTLE;				//已打开文件表项类型

struct openfile_s{
	OFILE file[n]; 	//已打开文件登记表
	int length; 	//已打开文件登记表中登记的文件数量
}openfile;			//已打开文件登记表定义




char fat[128];	//Fat表 数字i ->  struct buffer file[i];      0为空，255为文件末尾，254为磁盘损坏

struct buffer_s{
	char buffer[64];
};	//每个盘块内容

struct buffer_s store[128];		//总共128个盘块

typedef struct file_s{
	char file_name[3];
	char file_type[2];  		//DIR=NULL
	unsigned int file_attr:8;	//ATTR_*
	unsigned int start_fat:8;	//fat[start_fat]
	unsigned int fat_count:8; 	//DIR=NULL
	char under_file[MAX_FILE];	//拥有的文件FAT值//
}file_t;								//文件file或目录DIR属性表,保存在盘块中





int create_file(char * file_name,char * file_type,unsigned int attr);//创建目录项,返回TRUE OR FALSE

int find_null_fat();//查找空的FAT表项，返回对应数字
int delete_fat(int fat_num);//删除对应的FAT表项，返回TRUE OR FALSE