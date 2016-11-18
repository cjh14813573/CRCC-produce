#include "stdsys.h"
#include <sys/types.h>
#include "task.h"
#include "typedef.h"
#include "main.h"
#include "property.h"

struct task M500FTask;
struct task TcpipTask;
struct task AirControlTask;
struct task DataBlockTask;
struct task DataBlock2Task;
struct task ComserTask;
struct task ModemTask;
struct task AutoModemTask;
struct task AIMeasureTask;
struct task DIMeasureTask;
struct task DOMeasureTask;
struct task lcdTask;
struct task selftestTask;
struct task upstask;
struct task ACDUTask;
struct task SPDTask;
//struct task AccessTask;
//struct task sqlTask;

//8月29号晚改，尝试将1、2、6、7串口收发全部放在一个序列中
/*
int com7=0;
extern int flag16;
extern int flag27;
*/

//1power,2ups,3acdu,4spd
int com_flag[4]={0};
int running_com=1;


int main(void)
{
	int total_com_device_number=0;//连接的串口设备总数，写入WEBinfo.ini
	system("rm /app/WEBinfo.ini");

	init_alarm();
	init_SelfTest();
	init_gs_EventMng();
	init_gs_AirControlDataMng();
	init_gs_pwalarmMng();
	init_gs_cfgMng();
	init_gs_DOMng();
	init_serialport();
	init_gs_NewDataMng();
	init_property();
	TaskCreat(&selftestTask, "self_test", (void*)Self_Test);
	TaskCreat(&lcdTask,"tasklcd",(void*)lcd);
	TaskCreat(&AIMeasureTask, "AIMeasures", (void*)AIMeasure);
	TaskCreat(&DIMeasureTask, "DIMeasures", (void*)DIMeasure);
	TaskCreat(&DOMeasureTask, "DOMeasures", (void*)DOMeasure);
	TaskCreat(&TcpipTask, "Tcpipserver", (void*)Tcpipser);


	TaskCreat(&M500FTask, "M500F", (void*)M500F);
	com_flag[0]=1;
	running_com=1;
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&upstask, "ups", (void*)UPS);
	com_flag[1]=1;
	running_com=2;
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&AirControlTask,"AirControl",(void*)AirCon);
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&DataBlockTask,"DataBlock",(void*)DataBlock);
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&DataBlock2Task,"DataBlock2",(void*)DataBlock2);
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&ACDUTask,"acdu",(void*)ACDU);
	com_flag[2]=1;
	running_com=3;
	total_com_device_number=total_com_device_number+1;


	TaskCreat(&SPDTask, "spd", (void*)spd);
	com_flag[3]=1;
	running_com=4;
	total_com_device_number=total_com_device_number+1;

	//写入串口设备总数
	char *files ="/app/WEBinfo.ini";
	char *sections="COM";
	char *keys="num";
	char cfg[4]={0};
	sprintf(cfg,"%d",total_com_device_number);
	write_profile_string(sections,keys,cfg,files);

	//写入软件版本
	sections="version";
	keys="software";
	write_profile_string(sections,keys,LanServerVersion,files);

	//写入硬件版本
	sections="version";
	keys="hardware";
	write_profile_string(sections,keys,HardwareVersion,files);

	while(1)
		sleep(1);
}
