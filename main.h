#ifndef __MAIN_H_
#define __MAIN_H_
void init_gs_EventMng(void);
void init_gs_AirControlDataMng(void);
void init_gs_pwalarmMng(void);
void init_gs_cfgMng(void);
void init_gs_DOMng(void);
void init_gs_AI_coefficient(void);
void init_serialport(void);
void Comser(void);
//int TaskCreat(void);
void M500F(void);
int Tcpipser(void);
int AirCon(void);
int DataBlock(void);
int DataBlock2(void);
void Modem(void);
void AutoModem(void);
int AIMeasure(void);
int DIMeasure(void);
int DOMeasure(void);
void lcd(void);
void init_SelfTest(void);
void Self_Test(void);
void init_alarm(void);
void ACDU(void);
void init_gs_NewDataMng(void);
void init_Not_recovery_alarm(void);
void UPS(void);
void spd(void);
//void sql(void);
//void TaskofMeasure(void);

#endif //__MAIN_H
