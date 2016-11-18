#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

extern int running_com;
void ACDU(void)
{
	char *name="串口6测试";
	write_webinfo(6,name,0);

	unsigned short feeddog;
	int fd,nwrite,nread;
	unsigned char ACDU_time_alarm[6];
	unsigned char sendbuf[8],buff[40];
	int connection_status;


	int iRtn;
	fd = OpenDev(6);
	set_speed(fd,4);
	set_Parity(fd,1,0,2);
	while(1)
	{
		if(running_com==3)
		{
			sendbuf[0]=0x7e;
			sendbuf[1]=0x30;
			sendbuf[2]=0x31;
			sendbuf[3]=0x41;
			sendbuf[4]=0x0d;
			sendbuf[5]=0x7d;

			ioctl(fd,0x6001,0);
			nwrite=write(fd,sendbuf,6);
			//printf("\nACDU_nwrite=%d\n",nwrite);
			iRtn = 0;
			while(!iRtn)
			{
				ioctl(fd, TIOCSERGETLSR, &iRtn);
				//printf("%d",iRtn);
			}
			ioctl(fd,0x6002,0);

			usleep(500000);
			nread=read(fd,buff,255);

			if(nread>5&&buff[0]==0x7e&&buff[nread-1]==0x7d)
			{
				ACDU_time_alarm[0]=0;
			}
			else
			{
				ACDU_time_alarm[0]++;
				printf("\n666666 out of time\n");
			}

			if(ACDU_time_alarm[0]==0)
			{
				//通信正常
				connection_status=1;
				gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_6_CONNECTION,DATA,&connection_status);
				gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_6_CONNECTION,connection_status,AlarmStat.test_alarm_flag[TEST_SERIAL_6_CONNECTION],ALARM_ID_SERIAL_6,ALARM_CONTENT_ALARM);
			}
			if(ACDU_time_alarm[0]>=5)
			{
				//通信断开，相应模块数据值的数据状态写成0xff,通信状态的数据状态写成alarmLevel
				ACDU_time_alarm[0]=5;
				connection_status=0;
				gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_6_CONNECTION,DATA,&connection_status);
				gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_6_CONNECTION,connection_status,AlarmStat.test_alarm_flag[TEST_SERIAL_6_CONNECTION],ALARM_ID_SERIAL_6,ALARM_CONTENT_ALARM);
			}
			turn_to_next_com();
		}
		sleep(1);
		SelfTest.fGetSelftest(0,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(0,&feeddog);
	}
}
