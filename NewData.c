#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "typedef.h"


//extern DataMng_TypeDef gs_DataMng;
static MUTEX_T hMutexReadWriteNewData=PTHREAD_MUTEX_INITIALIZER;
unsigned char SetCData(short int device, short int point,int i,void *pDataBuf)
{
	MutexLock(&hMutexReadWriteNewData);
	if(device<=DEVICE_SIZE&&point<=1000)
	{
		gs_NewDataMng.NewData.CData[device][point][i]=*((int *)pDataBuf);
	}
	else
	{
		MutexUnlock(&hMutexReadWriteNewData);
		return  FALSE;
	}
	MutexUnlock(&hMutexReadWriteNewData);
	return  TRUE;
}
static MUTEX_T hMutexReadWriteNewData1=PTHREAD_MUTEX_INITIALIZER;
unsigned char GetCData(short int device, short int point,int i,void *pDataBuf)
{
	MutexLock(&hMutexReadWriteNewData1);
	if(device<=DEVICE_SIZE&&point<=1000)
	{
		*((int *)pDataBuf)=gs_NewDataMng.NewData.CData[device][point][i];
	}
	else
	{
		MutexUnlock(&hMutexReadWriteNewData1);
		return  FALSE;
	}
	MutexUnlock(&hMutexReadWriteNewData1);
	return  TRUE;
}


NewDataMng_TypeDef gs_NewDataMng;

void init_gs_NewDataMng(void)
{
	int i;
	int j;
	for(i=0;i<230;i++)
	{
		gs_NewDataMng.NewData.Data[i]=0;
	}
	for(i=0;i<=10;i++)
	{
		for(j=0;j<=500;j++)
		{
			gs_NewDataMng.NewData.CData[i][j][DATA]=0;
			gs_NewDataMng.NewData.CData[i][j][STATUS]=0xff;
		}
	}

/////////////////////////////////
	gs_NewDataMng.fSetCData = SetCData;
	gs_NewDataMng.fGetCData = GetCData;

}
