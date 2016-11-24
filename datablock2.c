#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

void DataBlock2(void)
{
	char *name="串口5测试";
	write_webinfo(5,name,0);

	unsigned short feeddog;
	int time_flag;
	unsigned char db_sendbuft[30];
	unsigned char db_time_alarm[192]={0};
	unsigned char dbmergebuff[255];
	int db_flag=1,fd,DB_nwrite,DB_nread;
	int status,iRtn;
	fd=OpenDev(5);
	set_speed(fd,4);
	set_Parity(fd,1,0,2);

	while(db_flag!=0)
	{
		ioctl(fd, TIOCSERGETLSR, &iRtn);
		ioctl(fd,TIOCMGET,&status);
		status&=~TIOCM_RTS;
		ioctl(fd,TIOCMSET,&status);

		db_sendbuft[0]=0x7E;
		db_sendbuft[1]=0x02;
		db_sendbuft[2]=0x01;
		db_sendbuft[3]=0x10;
		db_sendbuft[4]=((db_sendbuft[2]+db_sendbuft[3])&0xFF);
		db_sendbuft[5]=0x0D;
		DB_nwrite=write(fd,db_sendbuft,6);
		iRtn = 0;
		while(!iRtn)
		{
			ioctl(fd, TIOCSERGETLSR, &iRtn);
		}
		ioctl(fd,TIOCMGET,&status);
		status|=TIOCM_RTS;
		ioctl(fd,TIOCMSET,&status);
		sleep(1);
		memset(dbmergebuff,0,255);
		DB_nread=read(fd,dbmergebuff,255);
		if(DB_nread>6)
		{
			if(dbmergebuff[2+dbmergebuff[1]]==calculate_checksum(dbmergebuff))
			{
				db_time_alarm[0]=0;
			}
		}
		else
		{
			db_time_alarm[0]++;
			printf("\n555555 out of time\n");
		}
		if(db_time_alarm[0]==0)
		{
			time_flag=1;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_5_CONNECTION,DATA,&time_flag);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_5_CONNECTION,time_flag,AlarmStat.test_alarm_flag[TEST_SERIAL_5_CONNECTION],ALARM_ID_SERIAL_4,ALARM_CONTENT_ALARM);
		}
		if(db_time_alarm[0]>=3)
		{
			db_time_alarm[0]=3;
			time_flag=0;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_5_CONNECTION,DATA,&time_flag);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_5_CONNECTION,time_flag,AlarmStat.test_alarm_flag[TEST_SERIAL_5_CONNECTION],ALARM_ID_SERIAL_4,ALARM_CONTENT_ALARM);
		}
		SelfTest.fGetSelftest(6,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{feeddog=0;}
		SelfTest.fSetSelftest(6,&feeddog);
		sleep(1);
	}
}
