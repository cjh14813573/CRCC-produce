#include "stdsys.h"
#define IC_NUM       50

//Version
//中软版本号为8.1，通号为7.1
#define LcdVersion  "   V8.1c  test @1118 "
#define LanServerVersion  "V8.1c  test IR@1118"
#define HardwareVersion  "EMB-HZ-IR"
#define LogoVersion      1   //表示中软和通号版本，0中软，1通号
//中软标有ctt2000e，通号为中性
#define CssLogo          0
#define CrscLogo         1


//////////////////////////////////////
//以下为属性用的宏

//中心地址
#define CENTER_ID               1
//设备号
#define POWER_DEVICE            1
#define UPS_DEVICE              2
#define ACDU_DEVICE             3
#define ENVIRONMENT_DEVICE      4
#define AIRCONDITIONER_DEVICE   5
#define SPD_DEVICE              6
#define BATTERY_DEVICE          7
#define SMART_LOCK_DEVICE       8
#define DCDU_DEVICE             9
#define GENERATOR_DEVICE        10
#define TEST_DEVICE             11

//各设备最多可能节点数
#define ID_SIZE              800
#define POWER_SIZE           119
#define UPS_SIZE             26
#define BATTERY_SIZE         500
#define ENVIRONMENT_SIZE     72
#define ACDU_SIZE            16
#define SPD_SIZE             17
#define AIR_SIZE             39
#define DEVICE_SIZE          15
#define TEST_SIZE            46

//出厂测试
#define TEST_SERIAL_1_CONNECTION           1
#define TEST_SERIAL_2_CONNECTION           2
#define TEST_SERIAL_3_CONNECTION           3
#define TEST_SERIAL_4_CONNECTION           4
#define TEST_SERIAL_5_CONNECTION           5
#define TEST_SERIAL_6_CONNECTION           6
#define TEST_SERIAL_7_CONNECTION           7
#define TEST_AI_1                          8
//8-23为AI量
#define TEST_DI_1                          24
//24-39为DI量
#define TEST_DO_1                          40
#define TEST_DO_2                          41
#define TEST_DO_3                          42
#define TEST_DO_4                          43
#define TEST_DO_5                          44
#define TEST_DO_6                          45
#define TEST_DO_SMOKE                      46

////以上为属性用的宏
//////////////////////////////////////////////////////////////////////////////////

//alarm
#define ALARM_FLAG_START            1
#define ALARM_FLAG_END              0
#define ALARM_FLAG_HIGH_START       1
#define ALARM_FLAG_LOW_START       -1
#define ALARM_CONTENT_RECOVER       0
#define ALARM_CONTENT_ALARM         1
#define ALARM_CONTENT_HIGH          2
#define ALARM_CONTENT_HIGH_1        3
#define ALARM_CONTENT_HIGH_2        4
#define ALARM_CONTENT_HIGH_3        5
#define ALARM_CONTENT_LOW           6
#define ALARM_CONTENT_LOW_1         7
#define ALARM_CONTENT_LOW_2         8
#define ALARM_CONTENT_LOW_3         9
#define ALARM_CONTENT_POWER_FAIL    10
#define ALARM_CONTENT_ERROR         11
#define ALARM_CONTENT_BREAK         12
#define ALARM_CONTENT_ON            13
#define ALARM_CONTENT_OFF           14
#define ALARM_CONTENT_FUSE_BREAK    15
#define ALARM_CONTENT_DISCHARGE     16


#define ALARM_ID_DI_1            101
//101-116为DI量的告警号
#define ALARM_ID_SERIAL_1        117
#define ALARM_ID_SERIAL_2        118
#define ALARM_ID_SERIAL_3        119
#define ALARM_ID_SERIAL_4        120
#define ALARM_ID_SERIAL_5        121
#define ALARM_ID_SERIAL_6        122
#define ALARM_ID_SERIAL_7        123
#define ALARM_ID_AI_HIGH         124
#define ALARM_ID_AI_LOW          125



//pw_PARA
#define PARA_PowerModel_NUM                        0

#define PARA_FloatVoltLow_NUM                      1
#define PARA_FloatVoltHigh_NUM                     2
#define PARA_ConstantVoltLow_NUM               3
#define PARA_ConstantVoltHigh_NUM                  4
#define PARA_ACVoltLow_NUM                         5

#define PARA_ACVoltHigh_NUM                        6

#define PARA_DCVoltLow_NUM                         7

#define PARA_DCVoltHigh_NUM                        8

#define PARA_BattThresholdTemperature_NUM          9
#define PARA_ConstantTime_NUM                      10

#define PARA_ConstantCycle_NUM                     11

#define PARA_LVDRelinkVolt_NUM                     12
#define PARA_LVDLeaveVolt_NUM                      13
#define PARA_TemperatureModulus_NUM                14

#define PARA_ReferenceTemperature_NUM              15

#define PARA_BattGroupLowAlarmVolt_NUM             16
#define PARA_BattGroupProtectVolt_NUM              17

#define PARA_SMROverVoltShutDown_NUM               18

#define PARA_SMRLimitingAlarm_NUM                  19
#define PARA_ModultTotal_NUM                       20
#define PARA_Switch_NUM                            21
#define PARA_ConstantVolt_NUM                      22
#define PARA_FloatVolt_NUM                        23
#define SET_PARA_TYPE_NUM                      24
#define SET_PARA_ACTION_NUM                  25
#define SET_PARA_FLAG_NUM                      26

//Aircon
#define Aircon_Model_NUM                       1
#define Aircon_Switch_NUM                      2
#define Aircon_SetTemperature_NUM              3

//DB
#define DataBlock_Volt        1
#define DataBlock_Temp     2
#define DataBlock_BatteryPack1_NUM      0
#define DataBlock_BatteryPack2_NUM      1
#define DataBlock_BatteryPack3_NUM      2
#define DataBlock_BatteryPack4_NUM      3

//set_thre_val_flag
#define Set_AlarmThreVal_NUM 11
//pwalarmthreval
#define AC_higt_volt_NUM 0
#define AC_low_volt_NUM  1
#define AC_higt_curr_NUM 2
#define AC_low_curr_NUM 3
#define DC_higt_volt_NUM 4
#define DC_low_volt_NUM 5
#define high_temp_NUM 6
#define low_temp_NUM 7
#define high_humidity_NUM 8
#define low_humidity_NUM 9
#define RTU_log_NUM  19
#define RTU_lcd_NUM  20
#define RTU_backlight_NUM 21

//dbalarmthreval
#define DB_high_volt_NUM 0
#define DB_low_volt_NUM  1
#define DB_high_temp_NUM 2
#define DB_low_temp_NUM 3
#define DB_high_pressdiffvolt_NUM 4


//cfg
#define RTU_addr_NUM               0
#define RTU_startdelaytime_NUM     1
#define RTU_enddelaytime_NUM       2
#define RTU_Tel_NUM                3
#define RTU_AlarmReport_NUM        4
#define RTU_COM1_NUM               5
#define RTU_COM2_NUM               6
#define RTU_COM3_NUM               7
#define RTU_COM4_NUM               8
#define RTU_COM5_NUM               9
#define RTU_DI_NUM                 10
#define RTU_AI_NUM                 11
#define RTU_DB_NUM                 12
#define RTU_IP_NUM                 13
#define RTU_netmask_NUM            14
#define RTU_gateway_NUM            15
#define RTU_mac_NUM                16
#define RTU_pwmodel_NUM            17
#define RTU_pwaddr_NUM             18
#define RTU_acmodel_NUM            19
#define RTU_videolinkage_NUM       20
#define RTU_stat_NUM               21
#define RTU_DO_NUM				   22
#define RTU_COM6_NUM               23
#define RTU_COM7_NUM               24

#define DATA     0
#define STATUS   1

#define ALARM_NUM 10
#define PORT  10001
#define MAXSOCKFD 30
#define EVENT_NUM 1000
#define BUF_SIZE 256
#define CH_NUM 16
#define USING_CH_NUM 12
typedef	unsigned char (*DATA_INTERFACE_FUNC)(unsigned short i, void *pDataBuf);
typedef	unsigned char (*CDATA_INTERFACE_FUNC)(short int device, short int point,int i,void *pDataBuf);
typedef	unsigned char (*EVENT_INTERFACE_FUNC)(void *pDataBuf);
typedef void (*EVENT_INTERFACE_AI_FUNC)(short int device, short int point, int value,signed char *alarm_status,int alarmIdLow,int alarmIdHigh);
typedef void (*EVENT_INTERFACE_DI_FUNC)(short int device, short int point, int value,signed char *alarm_status,int alarmID,int content);
typedef   unsigned char (*DBData_INTERFACE_FUNC)(unsigned char i,unsigned char ii,unsigned char iii,void*pDataBuf);
typedef   unsigned char (*Measure_INTERFACE_FUNC)(unsigned char i, unsigned char ii,void *pDataBuf);
typedef   int (*Property_INTERFACE_FUNC)(int i, int ii,void *pDataBuf,int ID);
typedef   unsigned char (*Set_Property_INTERFACE_FUNC)(short int i,short int ii);

typedef struct tagData
{
	int CData[230];
  signed short  Temperature;//鐜娓╁害
  signed short  Humidity;//鐜婀垮害
  signed short  KTVolt;//绌鸿皟鐢靛帇
  signed short  KTCurr;//绌鸿皟鐢垫祦
  signed short  KTTempandPSModel;//绌鸿皟璁惧畾娓╁害+鐢垫簮绫诲瀷
  signed short  ACVoltA;//浜ゆ祦A鐩哥數鍘?
  signed short  ACVoltB;//浜ゆ祦B鐩哥數鍘?
  signed short  ACVoltC;//浜ゆ祦C鐩哥數鍘?
  signed short  ACCurrA;//浜ゆ祦A鐩哥數娴?
  signed short  ACCurrB;//浜ゆ祦B鐩哥數娴?
  signed short  ACCurrC;//浜ゆ祦C鐩哥數娴?
  signed short  LoadCurr;//鐩存祦璐熻浇鎬荤數娴?
  signed short  RectCurr[16];//妯″潡1-16杈撳嚭鐢垫祦
  signed short  DCVolt;//鐩存祦杈撳嚭鎬荤數鍘?
  signed short  Batt1Volt;//鐢垫睜1鐢靛帇
  signed short  Batt2Volt;//鐢垫睜2鐢靛帇
  signed short  Batt1Curr;//钃勭數姹犵粍1鍏呮斁鐢垫祦
  signed short  Batt2Curr;//钃勭數姹犵粍2鍏呮斁鐢垫祦
  signed short  Batt1Temp;//钃勭數姹犵粍1娓╁害
  signed short  Batt2Temp;//钃勭數姹犵粍2娓╁害
  signed short  Batt1Cap;//钃勭數姹犵粍1瀹归噺
  signed short  Batt2Cap;//钃勭數姹犵粍2瀹归噺
  unsigned short  Switch[11];//閬ヤ俊閲?-11
} Data_TypeDef;//鍚堣		96瀛楄妭//gs_DataMng;//鍚堣		96瀛楄妭


typedef struct tagDataMng
{
  Data_TypeDef Data;
  DATA_INTERFACE_FUNC       fSetData;
  DATA_INTERFACE_FUNC       fGetData;
} DataMng_TypeDef;
extern DataMng_TypeDef gs_DataMng;
//Event
typedef struct tagEvent
{
    			 int Value;
	unsigned     int ID;
	unsigned 	char Name;
	unsigned 	char SYearHigh;
	unsigned 	char SYearLow;
	unsigned 	char SMonth;
	unsigned 	char SDay;
	unsigned 	char SHour;
	unsigned 	char SMinute;
	unsigned 	char SSecond;
	unsigned 	char EYearHigh;
	unsigned 	char EYearLow;
	unsigned 	char EMonth;
	unsigned 	char EDay;
	unsigned 	char EHour;
	unsigned 	char EMinute;
	unsigned 	char ESecond;
	  signed 	char Flag;
	unsigned     int Device;
	unsigned     int Point;
	unsigned    char level;
	unsigned    char AlarmLevel;
	unsigned    char Content;
	unsigned 	char Type;   // 是否上报
}Event_TypeDef;

typedef struct tagEventMng
{
	int GetEventNum;
	int SetEventNum;
	Event_TypeDef   EventArray[EVENT_NUM];
	int Eventnum[EVENT_NUM];
	EVENT_INTERFACE_FUNC        fSetEvent;
	EVENT_INTERFACE_FUNC        fGetEvent;
	EVENT_INTERFACE_AI_FUNC     fJudgeAI;
	EVENT_INTERFACE_DI_FUNC     fJudgeDI;
}EventMng_TypeDef;
extern EventMng_TypeDef gs_EventMng;

//Aircon
typedef struct tagAirControlData
{
	unsigned char Address;
	unsigned char Model;
	unsigned short Switch;
	unsigned char SetTemperature;
	unsigned char Controlflag;
}AirControlData_TypeDef;

typedef struct tagAirControlDataMng
{
	AirControlData_TypeDef    AirConData;
} AirControlDataMng_TypeDef;
extern AirControlDataMng_TypeDef gs_AirControlMng;
//DB
typedef struct tagDataBlockData
{
	int Bat1Volt[24];
	int Bat2Volt[24];
	int Bat3Volt[24];
	int Bat4Volt[24];
	int Bat1Temp[24];
	int Bat2Temp[24];
	int Bat3Temp[24];
	int Bat4Temp[24];
	int Bat1Resistance[24];
	int Bat2Resistance[24];
	int Bat3Resistance[24];
	int Bat4Resistance[24];
	int GetBATRS;
}DataBlockData_TypeDef;
typedef struct tagBlockDataDataMng
{
	DataBlockData_TypeDef DBData;
	DBData_INTERFACE_FUNC    DBSetData;
	DBData_INTERFACE_FUNC    DBGetData;
}DataBlockDataMng_TypeDef;
extern DataBlockDataMng_TypeDef gs_DBDataMng;

//PW
typedef struct pw_alarm_thre_val
{
	int AC_high_volt;
	int AC_low_volt;
	int AC_high_curr;
	int AC_low_curr;
	int DC_high_volt;
	int DC_low_volt;
	int Temp_high;
	int Temp_low;
	int Humidity_high;
	int Humidity_low;
}pw_alarm_thre_val_TypeDef;
typedef struct tagpw_alarm_thre_valMng
{
	int threval_flag;
	unsigned short log;
	unsigned char lcd;
	unsigned char backlight;
	pw_alarm_thre_val_TypeDef  thre_val;
	DATA_INTERFACE_FUNC  Setthre_val;
	DATA_INTERFACE_FUNC  Getthre_val;
}pw_alarm_thre_valMng_TypeDef;
extern pw_alarm_thre_valMng_TypeDef gs_pwalarmMng;
//DB
typedef struct db_alarm_thre_val
{
	int DB_high_volt;
	int DB_low_volt;
	int DB_high_temp;
	int DB_low_temp;
	int DB_highpressdiffVolt;
	int DB2_high_volt;
	int DB2_low_volt;
	int DB2_highpressdiffVolt;
	int DB3_high_volt;
	int DB3_low_volt;
	int DB3_highpressdiffVolt;
	int DB4_high_volt;
	int DB4_low_volt;
	int DB4_highpressdiffVolt;
}db_alarm_thre_val_TypeDef;
typedef struct tagdb_alarm_thre_valMng
{
	int threval_flag;
	db_alarm_thre_val_TypeDef  thre_val;
	DATA_INTERFACE_FUNC  Setthre_val;
	DATA_INTERFACE_FUNC  Getthre_val;
}db_alarm_thre_valMng_TypeDef;
extern db_alarm_thre_valMng_TypeDef gs_dbalarmMng;

//cfg
typedef struct tagrtuaddrtime
{
	char address[2];
	char startdelaytime;
	char enddelaytime;
}AddrDelay_TypeDef;
typedef struct tagcomset
{
	unsigned char com1[7];
	unsigned char com2[7];
	unsigned char com3[7];
	unsigned  char com4[7];
	unsigned  char com5[7];
	unsigned  char com6[7];
	unsigned  char com7[7];
}SerialPortSetup_TypeDef;

typedef struct tagnetset
{
	unsigned   char IPAddress[4];
	unsigned   char  NetMask[4];
	unsigned    char Gateway[4];
	unsigned  char MACAddress[6];
}NetCardSetup_TypeDef;
typedef struct tagstandbychannelset
{
	char AlarmTel[16];
	char AlarmReport;
}Sbchannelset_TypeDef;
typedef struct tagRTUcfg
{
	AddrDelay_TypeDef        Addrdelaytime;
	Sbchannelset_TypeDef     Standbychannelset;
	SerialPortSetup_TypeDef  ComSet;
	unsigned   char DIset[17];
	unsigned  char AIset[17];
	unsigned char DBset[7];
	unsigned char DOset[7];

	int pwModel;
	unsigned char pwaddr;
	unsigned char acModel;
	unsigned char time;
	unsigned char RTUstat;
	NetCardSetup_TypeDef     NetcardSet;
}RTUcfg_TypeDef;

typedef struct tagRTUcfgMng
{
	RTUcfg_TypeDef RTUcfg;
	DATA_INTERFACE_FUNC       Setcfg;
	DATA_INTERFACE_FUNC       Getcfg;
}RTUcfgMng_TypeDef;
extern RTUcfgMng_TypeDef gs_RTUcfgMng;

struct comtask
{
	unsigned char UPS[7];
	unsigned char ACDU[7];
	unsigned char IC[7];
	unsigned char pw[7];
	unsigned char db[7];
	unsigned char ac[7];
	unsigned char mn[7];
	unsigned char sb[7];
}comTASK;//task_TypeDef;


typedef struct channelPara
{
	float vref;
	float Gain;
	float ADK;
	float ADB;
}ChannelPara_TypeDef;

typedef struct tagselftest
{
	unsigned short mn;
	unsigned short sb;
	unsigned short pw;
	unsigned short ai;
	unsigned short di;
	unsigned short ac;
	unsigned short db;
	unsigned short lan;
	unsigned short lcd;
    DATA_INTERFACE_FUNC       fSetSelftest;
	DATA_INTERFACE_FUNC       fGetSelftest;
} SelfTest_TypeDef;
extern SelfTest_TypeDef SelfTest;

unsigned short LanTEST;
unsigned char LCDTASK;
typedef struct tagalarmstat
{
	signed char test_alarm_flag[TEST_SIZE][3];
}Alarmstat_TypeDef;
extern Alarmstat_TypeDef AlarmStat;


typedef struct tagNewData
{
  int  Data[230];
  int  CData[15][500][2];//一维是device，二维是point，三维是数据和状态
} NewData_TypeDef;
typedef struct tagNewDataMng
{
	NewData_TypeDef NewData;
	CDATA_INTERFACE_FUNC      fSetCData;
	CDATA_INTERFACE_FUNC      fGetCData;
} NewDataMng_TypeDef;
extern NewDataMng_TypeDef gs_NewDataMng;


///// CRCC

typedef struct tagPro
{
  	unsigned char Type;
	unsigned char Alarmlevel;
   	unsigned char AlarmEnable;
	unsigned char AlarmThresbhold;
	unsigned char DeviceType;
  	unsigned char Name[30];
   	unsigned char Des[40];
	unsigned char Des0[10];
	unsigned char Des1[10];
	unsigned char Unit[5];
	unsigned char Productor[10];
	unsigned char Version[10];
 	float Stander;
	float Percision;
	float MaxVal;
	float MinVal;
  	float HiLimit1;
 	float LoLimit1;
	float HiLimit2;
	float LoLimit2;
	float HiLimit3;
	float LoLimit3;
} Pro_TypeDef;  //  CRCC 数据属性结构
typedef struct tagProMng
{
  Pro_TypeDef Pro[15][500];
  Pro_TypeDef Pro_to_modify;
  Set_Property_INTERFACE_FUNC    fSetPro;
  Property_INTERFACE_FUNC    fGetPro;
} ProMng_TypeDef;
extern ProMng_TypeDef gs_ProMng;
