#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

void AirCon(void)
{
	char *name="串口3测试";
	write_webinfo(3,name,0);

	unsigned short feeddog;
	unsigned char fd,Air_flag=1;;
	int connection_status;
	unsigned char air_message[32],airbuff[256]={0};
	int status,iRtn,nread;
	ioctl(fd,TIOCMGET,&status);
	status&=~TIOCM_RTS;
	ioctl(fd,TIOCMSET,&status);
	fd = OpenDev(3);
	set_speed(fd,1);
	set_Parity(fd,1,0,2);
	unsigned char Airchecksum,Air_ii,sign7d,Air_con_alarm_flag=0;
	unsigned char air_receive_time,air_i,air_START=0;
	unsigned char air_END=0,air_receive_len=0;
	int Air_nread;
	unsigned char airmergebuff[128]={0};
	while(Air_flag!=0)
	{
		air_message[0]=0x7E;
		air_message[1]=0x7D;
		air_message[2]=0x20;
		air_message[3]=0x7D;
		air_message[4]=0x20;
		air_message[5]=0xF0;
		air_message[6]=0x7D;
		air_message[7]=0x20;
		air_message[8]=0x7D;
		air_message[9]=0x20;
		air_message[10]=0xF0;


		ioctl(fd, TIOCSERGETLSR, &iRtn);
		ioctl(fd,TIOCMGET,&status);
		status&=~TIOCM_RTS;
		ioctl(fd,TIOCMSET,&status);
		write(fd,air_message,11);
		iRtn = 0;
		while(!iRtn)
		{
			ioctl(fd, TIOCSERGETLSR, &iRtn);
		}

		ioctl(fd,TIOCMGET,&status);
		status|=TIOCM_RTS;
		ioctl(fd,TIOCMSET,&status);

		sign7d=0;
		air_receive_time=0;
		air_receive_len=0;
		air_END=0;
		while (air_END==0&&air_receive_time<7)
		{
			if((Air_nread=read(fd,airbuff,7))>0)
			{
				Air_con_alarm_flag=0;
				for(air_i=0;air_i<Air_nread;air_i++)
				{
					if((airbuff[air_i]==0x7e)&&(air_START==0))
					{
						air_START=1;
						air_receive_len=1;
						airmergebuff[0]=0x7e;
						continue;
					}
					if(air_START==1&&airbuff[air_i]==0x7d)
					{
						sign7d=1;
						continue;
					}
					if(sign7d==1)
					{
						airmergebuff[air_receive_len++]=(airbuff[air_i]^0x20);
						sign7d=0;
						if(air_receive_len==7)
						{
							air_END=1;
							air_START=0;
							break;
						}
						continue;
					}
					if((airbuff[air_i]!=0x7d)&&(sign7d==0))
					{
						airmergebuff[air_receive_len++]=airbuff[air_i];
					}
					if(air_receive_len==7)
					{
						air_END=1;
						air_START=0;
						break;
					}
					else
						continue;
				}
			}
			else
			{
				usleep(100000);
				air_receive_time++;
			}
		}
		if(air_receive_time<7)
		{
			Airchecksum=0;
			for(Air_ii=1;Air_ii<6;Air_ii++)
			{
				Airchecksum=Airchecksum+airmergebuff[Air_ii];
			}
			if(Airchecksum==airmergebuff[6])
			{
				Air_con_alarm_flag=0;
			}
			else
			{
				Air_con_alarm_flag++;
				printf("\n333333 out of time\n");
			}
		}
		else
		{
			Air_con_alarm_flag++;
			printf("\n333333 out of time\n");
		}

		if(Air_con_alarm_flag==0)
		{
			//通信正常
			connection_status=1;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_3_CONNECTION,DATA,&connection_status);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_3_CONNECTION,connection_status,AlarmStat.test_alarm_flag[TEST_SERIAL_3_CONNECTION],ALARM_ID_SERIAL_3,ALARM_CONTENT_ALARM);
		}
		if(Air_con_alarm_flag>=2)
		{
			//通信断开，相应模块数据值的数据状态写成0xff,通信状态的数据状态写成alarmLevel
			Air_con_alarm_flag=2;
			connection_status=0;
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_3_CONNECTION,DATA,&connection_status);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_3_CONNECTION,connection_status,AlarmStat.test_alarm_flag[TEST_SERIAL_3_CONNECTION],ALARM_ID_SERIAL_3,ALARM_CONTENT_ALARM);
		}
		sleep(2);
		SelfTest.fGetSelftest(5,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(5,&feeddog);
	}
}
