#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"

extern int running_com;


void M500F(void)
{
	char *name="串口1测试";
	write_webinfo(1,name,0);
	unsigned short feeddog;
	int fd,nwrite;
	int data;
	fd = OpenDev(1);
	set_speed(fd,4);
	set_Parity(fd,1,0,2);
	int pw_time_flag=0;
	int pw_flag=1;
	int length;
	unsigned char hw_poll[21];
	unsigned char buff[256]={0},buffer[256]={0},new_command[256]={0};
	unsigned short crc1=0;
	int i_command=0,command_START=0,ni_command,command_END;
	hw_poll[0]=0x00;
	hw_poll[1]=0x00;
	hw_poll[2]=0x00;
	hw_poll[3]=0x00;
	hw_poll[4]=0x00;
	hw_poll[5]=0x00;
	hw_poll[6]=0xDD;
	hw_poll[7]=0x01;
	hw_poll[8]=0x00;
	hw_poll[9]=0x1E;
	int crc=cal_crc(hw_poll,10);
	hw_poll[10]=(unsigned char)((crc>>8)&0xff);
	hw_poll[11]=(unsigned char)(crc&0xff);
	send_message(&hw_poll[0],&buff[0],12,&length);
	while(pw_flag!=0)
	{
		if(running_com==1)
		{
			nwrite=write(fd,buff,length);
			length=0;
			i_command=0;
			ni_command=0;
			command_START=0;
			command_END=0;
			bzero(buffer,sizeof(buffer));
			bzero(new_command,sizeof(new_command));
			if(read(fd,buffer,sizeof(buffer))>0)
			{
				for(i_command=0;i_command<sizeof(buffer);i_command++)
				{
					if((buffer[i_command]==0x7e)&&command_START==0)
					{
						command_START=1;
						continue;
					}
					if((buffer[i_command]==0x7d)&&(command_START==1))
					{
						new_command[ni_command++]=((buffer[i_command+1])^0x20);
						i_command++;
						continue;
					}
					if((buffer[i_command]!=0x7d)&&(buffer[i_command-1]!=0x7d)&&(command_START==1)&&(buffer[i_command]!=0x7e))
						new_command[ni_command++]=buffer[i_command];
					if(buffer[i_command]==0x7e&&command_START==1)
					{
						length=ni_command;
						command_START=0;
						command_END=1;
						break;
					}
				}
				if(command_END==1&&length>2)
				{
					crc1=cal_crc(&new_command[0],length-2);
				}
				if((crc1!=0)&&((crc1&0xff)==new_command[length-2])&&(((crc1>>8)&0xff)==new_command[length-1]))
				{
					pw_time_flag=0;
				}
				else
				{
					pw_time_flag++;
					printf("\n111111 out of time\n");
				}
			}
			else
			{
				pw_time_flag++;
				printf("\n111111 out of time\n");
			}

			if(pw_time_flag==0)
			{
				data=1;//与电源通信正常
			}
			else if(pw_time_flag==2)
			{
				data=0;//与电源通信断
				pw_time_flag=2;
			}
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_1_CONNECTION,DATA,&data);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_1_CONNECTION,data,AlarmStat.test_alarm_flag[TEST_SERIAL_1_CONNECTION],ALARM_ID_SERIAL_1,ALARM_CONTENT_ALARM);
			turn_to_next_com();
		}
		sleep(1);
		SelfTest.fGetSelftest(2,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{
		feeddog=0;
		}
		SelfTest.fSetSelftest(2,&feeddog);
	}
}
