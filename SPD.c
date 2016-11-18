#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

/*
int flag16=0;
int flag27=0;
extern int UPS_flag;
extern int com7;
*/

extern int running_com;

void spd(void)
{
	char *name="串口7测试";
	write_webinfo(7,name,0);

	unsigned short feeddog;
	int fd;
	unsigned char air_message[24],airbuff[256]={0};
	unsigned short ALARM;
	int status,iRtn,nwrite,nread;
	ioctl(fd,TIOCMGET,&status);
	status&=~TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);
	fd = OpenDev(7);
	set_speed(fd,4);
	set_Parity(fd,1,0,2);
	int data;
	int spd_flag=1;
	while(spd_flag)
	{
		if(running_com==4)
		{
			ioctl(fd,0x6001,0);
			air_message[0]=0x7e;
			air_message[1]=0x03;
			air_message[2]=0x00;
			air_message[3]=0x00;
			air_message[4]=0x00;
			air_message[5]=0x7d;
			nwrite=write(fd,air_message,6);
			iRtn = 0;
			while(!iRtn)
			{
				ioctl(fd, TIOCSERGETLSR, &iRtn);
				//printf("%d",iRtn);
			}
			ioctl(fd,0x6002,0);
			usleep(500000);
			nread=read(fd,airbuff,255);
			if(nread>5&&airbuff[0]==0x7e&&airbuff[nread-1]==0x7d)
			{
				ALARM=0;
				data=1;
				gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_7_CONNECTION,DATA,&data);
				gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_7_CONNECTION,data,AlarmStat.test_alarm_flag[TEST_SERIAL_7_CONNECTION],ALARM_ID_SERIAL_7,ALARM_CONTENT_ALARM);
			}
			else
			{
				ALARM++;
				printf("\n777777 out of time\n");
				if(ALARM>6)
				{
					//通信告警
					ALARM=7;
					data=0;
					gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_7_CONNECTION,DATA,&data);
					gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_7_CONNECTION,data,AlarmStat.test_alarm_flag[TEST_SERIAL_7_CONNECTION],ALARM_ID_SERIAL_7,ALARM_CONTENT_ALARM);
				}
			}

			turn_to_next_com();

		}
		sleep(1);
		SelfTest.fGetSelftest(7,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(7,&feeddog);
	}
}
