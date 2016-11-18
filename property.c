#include "property.h"
#include "typedef.h"
#include "interface.h"




//定义节点ID号结构体

struct completeID id_struct[ID_SIZE];
short int id_number=0;
struct completeID test_struct[TEST_SIZE+1];
short int test_number=0;
struct completeID device_struct[DEVICE_SIZE+1];
short int device_number=0;

int test_to_DO[6]={1,2,3,4,5,6};  //全局变量，用于向 DOmeasure中传递某个设备使用的 DO口
int read_property_ini_string(char *section,char *key,char *buf,char *value)
{
	int sec_s;
	int sec_e;
	int key_s;
	int key_e;
	int value_s;
	int value_e;
	if(!parse_file(section,key,buf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e))
	{
		memset(value, 0, 256);
		return 0; //not find the key
	}
	else
	{
		int cpcount = value_e -value_s;
		if( 255 < cpcount)
		{
			cpcount =  255;
		}
		memset(value, 0, 256);
		memcpy(value,buf+value_s, cpcount );
		value[cpcount] = '\0';
		return 1;
	}
}


//初始化id结构体,ss初始化为1，point初始化为-1，只有有效的点才会赋值为正数
void init_struct(struct completeID *device_struct,short int rtu_address, short int deviceID, int size)
{
	int i;
	for(i=0;i<=size;i++)
	{
		(*(device_struct+i)).ss=CENTER_ID;
		(*(device_struct+i)).rtuID=rtu_address;
		(*(device_struct+i)).device=deviceID;
		(*(device_struct+i)).point=-1;
	}
}

//写入下一个id结构体
void write_next_id_struct(struct completeID *device_struct,short int *number, short int deviceID, short int pointID)
{
	(*number)++;
	(*(device_struct+(*number)-1)).device=deviceID;
	(*(device_struct+(*number)-1)).point=pointID;
}
void write_next_struct(struct completeID *device_struct,short int *number,short int pointID)
{
	(*number)++;
	(*(device_struct+(*number)-1)).point=pointID;
}

void write_property(char *buf,short int device,short int point)
{
	char *sections;
	char *keys;
	char value[256];
	char temp_section[10];
	sprintf(temp_section,"%d",point);
	sections=temp_section;	 //  节点ID
	keys="Type";
	read_property_ini_string(sections,keys,buf,value);
	gs_ProMng.Pro[device][point].Type=atoi(value);
	keys="Name";
	read_property_ini_string(sections,keys,buf,value);
	memset(&(gs_ProMng.Pro[device][point].Name[0]), 0x20, 30);
	unicode_to_char(value,&(gs_ProMng.Pro[device][point].Name[0]));
	keys="Des";
	read_property_ini_string(sections,keys,buf,value);
	memset(&(gs_ProMng.Pro[device][point].Des[0]), 0x20, 40);
	unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des[0]));
	switch(gs_ProMng.Pro[device][point].Type)
	{
		case 0://station
			break;

		case 1://device
			keys="DeviceType";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].DeviceType=atoi(value);
			keys="Productor";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Productor[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Productor[0]));
			keys="Version";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Version[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Version[0]));
			break;

		case 2://DI
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmEnable=atoi(value);
			keys="AlarmThresbhold";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmThresbhold=atoi(value);
			keys="Des0";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des0[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des0[0]));
			keys="Des1";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des1[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des1[0]));
			break;

		case 3://AI
			keys="MaxVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MinVal=atof(value);
			keys="Alarmlevel";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Alarmlevel=atoi(value);
			keys="AlarmEnable";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].AlarmEnable=atoi(value);
			keys="HiLimit1";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit1=atof(value);
			keys="HiLimit2";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit2=atof(value);
			keys="HiLimit3";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].HiLimit3=atof(value);
			keys="LoLimit1";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit1=atof(value);
			keys="LoLimit2";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit2=atof(value);
			keys="LoLimit3";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].LoLimit3=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Unit[0]), 0x20, 5);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Unit[0]));
			break;

		case 4://DO
			keys="Des0";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des0[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des0[0]));
			keys="Des1";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Des1[0]), 0x20, 10);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Des1[0]));
			break;

		case 5://AO
			keys="MaxVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MaxVal=atof(value);
			keys="MinVal";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].MinVal=atof(value);
			keys="Stander";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Stander=atof(value);
			keys="Percision";
			read_property_ini_string(sections,keys,buf,value);
			gs_ProMng.Pro[device][point].Percision=atof(value);
			keys="Unit";
			read_property_ini_string(sections,keys,buf,value);
			memset(&(gs_ProMng.Pro[device][point].Unit[0]), 0x20, 5);
			unicode_to_char(value,&(gs_ProMng.Pro[device][point].Unit[0]));
			break;

		default:
			break;
	}
}

long IDstruct_to_long(struct completeID device_struct)
{
	int a=device_struct.ss*134217728;
	int b=device_struct.rtuID*131072;
	int c=device_struct.device*2048;
	int d=device_struct.point;
	int whole_id=a+b+c+d;
	return whole_id;
}

struct completeID long_to_IDstruct(long whole_id)
{
	struct completeID device_struct;
	device_struct.ss=(short int)(whole_id>>27);
	device_struct.rtuID=(short int)((whole_id<<5)>>22);
	device_struct.device=(short int)(whole_id&0x01f800)/2048;
	device_struct.point=(short int)(whole_id&0x07ff);
	return device_struct;
}

void ini_to_array(char *str1, unsigned char *charResult,int n)
{
	int i=0,ii=0,iii;
	char *q;
	char qq[30]={0};
	q=qq;
	char *p=str1;
	for(iii=0;iii<n;iii++)
	{
	ii=0;memset(qq,0,30);
	 while( p[i]!=',' && p[i]!='\0'&&p[i]!='.'&&p[i]!=':'&&p[i]!='-')
	 {q[ii++]=p[i];i++;}
	 i+=1;
    *(charResult++)=atoi(qq);
    }
}


void init_property(void)
{
	char *inifile;
	int file_size;
	int i=0;
	//取rtu地址
	short int rtu_address;
	unsigned char rtu_temp_address[2];
	gs_RTUcfgMng.Getcfg(RTU_addr_NUM,&rtu_temp_address);
	rtu_address=rtu_temp_address[1];
	rtu_address=((rtu_address<<8)|rtu_temp_address[0]);

	//初始化id结构体
	init_struct(id_struct,rtu_address,-1,100);
	init_struct(test_struct,rtu_address,TEST_DEVICE,TEST_SIZE);
	init_struct(device_struct,rtu_address,-1,DEVICE_SIZE);

//  RTU station 节点号
	id_number++;
	(*(id_struct+id_number-1)).device=0;
	(*(id_struct+id_number-1)).point=0;

	for(i=1;i<=46;i++)
	{
		write_next_id_struct(id_struct,&id_number,TEST_DEVICE,i);
		write_next_struct(test_struct,&test_number,i);
	}

	//初始化设备节点
	//id_struct、device_struct中各添加一份
	write_next_id_struct(id_struct,&id_number,TEST_DEVICE,0);
	write_next_id_struct(device_struct,&device_number,TEST_DEVICE,0);

	//以上为节点初始化，下面为属性初始化
	//将属性从ini读取到结构体数组中
	printf("\n id property initializing is now started\n ");
	char rtu_buf[1024]={0};
	char test_buf[1024*20]={0};

	inifile="/app/rtu.pro.ini";
	load_ini_file(inifile,rtu_buf,&file_size);
	//printf("\nrtu buffer\n");
	inifile="/app/test.pro.ini";
	load_ini_file(inifile,test_buf,&file_size);
	//printf("\npower buffer\n");

	for(i=0;i<id_number;i++)
	{
	//	printf("\nnow is the %dth point\n",i);
		switch(id_struct[i].device)
		{
			case 0:
				write_property(rtu_buf,id_struct[i].device,id_struct[i].point);
				break;
			case TEST_DEVICE:
				write_property(test_buf,id_struct[i].device,id_struct[i].point);
				break;
			default:
				break;
		}
	}
	printf("\nid property initializing completed\n");
}
