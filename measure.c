#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "inifile.h"
#include "measure.h"
#include "interface.h"
#include "typedef.h"


int calculate_ai_data(float ad_volt)
{
	int  temp;
	temp=(int)((ad_volt*2.5*10)*10);
	return temp;
}

int AIMeasure(void)
{
	unsigned short ad_count[AD_REAL_CHANNEL],feeddog;
	int data=0;
	float ad_volt[AD_CHANNEL_NUMBER];
	int ad_handle;
	int i;
	ad_handle = open("/dev/ad", O_RDWR);
	if (ad_handle < 0)
	{
		return -1;
	}
	while(1)
	{
		read(ad_handle,ad_count,AD_REAL_CHANNEL*sizeof(unsigned short));
		for(i=0;i<16;i++)
		{
			//ad_volt[i] = Measure[i].vref*((ad_count[i] - ad_count[GND_CHANNEL])/(ad_count[VREF_CHANNEL]-ad_count[GND_CHANNEL]));
			ad_volt[i] = 2.3189*(((float)(ad_count[i] - ad_count[GND_CHANNEL]))/((float)(ad_count[VREF_CHANNEL]-ad_count[GND_CHANNEL])));
			//data=(int)((ad_volt[i]*Measure[i].Gain*Measure[i].ADK+Measure[i].ADB)*10);
			data=calculate_ai_data(ad_volt[i]);
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_AI_1+i,DATA,&data);
			gs_EventMng.fJudgeAI(TEST_DEVICE,TEST_AI_1+i,data,AlarmStat.test_alarm_flag[TEST_AI_1+i],ALARM_ID_AI_LOW,ALARM_ID_AI_HIGH);
		}
		sleep(2);
		SelfTest.fGetSelftest(3,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(3,&feeddog);
	}
}

int dio_handle;//DImeasure和 DOmeasure都用到的句柄，所以做成全局变量
int DI_val[16];//lcd程序中需要用到开关量状态，所以做成全局变量,并在lcd.c中extern一下
int DIMeasure(void)
{
	unsigned short feeddog;
	int i;
	unsigned short input;
	dio_handle = open("/dev/dio", O_RDWR);
	if (dio_handle < 0)
	{
		return -1;
	}
	while(1)
	{
		for(i=0;i<16;i++)
		{
			read(dio_handle, &input, sizeof(unsigned short));
			if(input&(0x1<<i))
				DI_val[i]=1;
			else
				DI_val[i]=0;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_DI_1+i,DATA,&DI_val[i]);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_DI_1+i,DI_val[i],AlarmStat.test_alarm_flag[TEST_DI_1+i],ALARM_ID_DI_1+i,ALARM_CONTENT_ALARM);
		}
		sleep(1);
		SelfTest.fGetSelftest(4,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(4,&feeddog);
	}
}


int DOMeasure(void)
{
	unsigned char output=0;
	unsigned char temp=0;
	int data=0;
	int status=0;
	int i=0;
	//初始化将烟感继电器给电，其他DO量下电。烟感继电器置0为给电，其他DO置1为开
	write(dio_handle, &output, sizeof(unsigned char));
	//烟感继电器在板上被固定为DO^0,因此其他DO量在实际使用时置位应多移一位(temp<<+1)
	while(1)
	{
		//灯控
		for(i=0;i<6;i++)
		{
			gs_NewDataMng.fGetCData(TEST_DEVICE,TEST_DO_1+i,DATA,&data);
			gs_NewDataMng.fGetCData(TEST_DEVICE,TEST_DO_1+i,STATUS,&status);
			if(data==1&&status==0xff)//遥控开灯,动作后data=1,status=0,遥控时只对data操作，不更改status
			{
				status=0;
				gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_DO_1+i,STATUS,&status);
				temp=1<<(test_to_DO[i]+1);
				output|=temp;
				write(dio_handle, &output, sizeof(unsigned char));
			}
			else if(data==0&&status==0)//遥控关灯,动作后data=0,status=0xff
			{
				status=0xff;
				gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_DO_1+i,STATUS,&status);
				temp=1<<(test_to_DO[i]+1);
				output&=~temp;
				write(dio_handle, &output, sizeof(unsigned char));
			}
		}

		//烟感复位
		//烟感是瞬间动作，只有一个命令，不需要status作为另一个标志
		gs_NewDataMng.fGetCData(TEST_DEVICE,TEST_DO_SMOKE,DATA,&data);
		if(data==1)
		{
			data=0;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_DO_SMOKE,DATA,&data);
			temp=1;
			output|=temp;
			write(dio_handle, &output, sizeof(unsigned char));
			sleep(3);
			output&=~temp;
			write(dio_handle, &output, sizeof(unsigned char));
		}

		usleep(500000);
	}
}
