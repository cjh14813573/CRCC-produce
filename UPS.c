#include "typedef.h"
#include "basetype.h"
#include "stdsys.h"
#include "com.h"
#include "interface.h"
extern int running_com;

int readUPSbuf(char fd,unsigned char *mergebuff,int *length,int *time)
{
	unsigned short feeddog;
	unsigned char buff[1024]={0};
	int pw_START=0,pw_END=0,nread,len=0,i,time_rec=0,read_flag=0;
	while (pw_END==0&&time_rec<11)
	{
		if((nread=read(fd,buff,1024))>0)
		{
			read_flag=1;
			for(i=0;i<nread;i++)
			{
				if((buff[i]==0x7e)&&(pw_START==0))
				{
					pw_START=1;
					len=0;
				}
				if(pw_START==1)
				{
					mergebuff[len]=buff[i];
				}
				if(mergebuff[len]==0x0d||len>500)
				{
					pw_END=1;len++;break;
				}
				len++;
			}
		}
		else
		{
			usleep(100000);
			time_rec++;
			SelfTest.fGetSelftest(1,&feeddog);
			feeddog++;
			if(feeddog>65530)
			{
				feeddog=0;
			}
			SelfTest.fSetSelftest(1,&feeddog);
		}
	}
	*length=len;
	*time=time_rec;
	return(read_flag);
}


void UPS(void)      // 中达 Delta UPS Protocol Version 1.55
{
	char *name="串口2测试";
	write_webinfo(2,name,0);

	int UPS_time_flag=0;
	int UPS_flag=1;
	unsigned short feeddog;
	int fd,nwrite;
	int data=0;
	unsigned char buff[256]={0},buffer[256]={0},new_command[256]={0};
	int i_command=0,command_START=0,ni_command,command_END;
	unsigned short crc1=0;
	int length;
	fd = OpenDev(2);
	set_speed(fd,4);
	set_Parity(fd,1,0,2);
	unsigned char UPS_poll[21];
	UPS_poll[0]=0x00;
	UPS_poll[1]=0x00;
	UPS_poll[2]=0x00;
	UPS_poll[3]=0x00;
	UPS_poll[4]=0x00;
	UPS_poll[5]=0x00;
	UPS_poll[6]=0xDD;
	UPS_poll[7]=0x01;
	UPS_poll[8]=0x00;
	UPS_poll[9]=0x1E;
	int crc=cal_crc(UPS_poll,10);
	UPS_poll[10]=(unsigned char)((crc>>8)&0xff);
	UPS_poll[11]=(unsigned char)(crc&0xff);
	send_message(&UPS_poll[0],&buff[0],12,&length);
	while(UPS_flag!=0)
	{
		if(running_com==2)
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
					UPS_time_flag=0;
				}
				else
				{
					UPS_time_flag++;
					printf("\n111111 out of time\n");
				}
			}
			else
			{
				UPS_time_flag++;
				printf("\n111111 out of time\n");
			}

			if(UPS_time_flag==0)
			{
				data=1;//与ups通信正常
			}
			else if(UPS_time_flag==2)
			{
				UPS_time_flag=2;
				data=0;//与ups通信断
			}
			gs_NewDataMng.fSetCData(TEST_DEVICE,TEST_SERIAL_2_CONNECTION,DATA,&data);
			gs_EventMng.fJudgeDI(TEST_DEVICE,TEST_SERIAL_2_CONNECTION,data,AlarmStat.test_alarm_flag[TEST_SERIAL_2_CONNECTION],ALARM_ID_SERIAL_2,ALARM_CONTENT_ALARM);

			turn_to_next_com();
		}
		sleep(1);
		SelfTest.fGetSelftest(1,&feeddog);
		feeddog++;
		if(feeddog>65530)
		{
			feeddog=0;
		}
		SelfTest.fSetSelftest(1,&feeddog);
	}
}
