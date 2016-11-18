#include "stdsys.h"
#include "basetype.h"
#include "mutex.h"
#include "typedef.h"

AirControlDataMng_TypeDef gs_AirControlMng;

void init_gs_AirControlDataMng(void)
{
  gs_AirControlMng.AirConData.Address=0;;
  gs_AirControlMng.AirConData.Model=0;
  gs_AirControlMng.AirConData.Switch=0;
  gs_AirControlMng.AirConData.SetTemperature=0;
  gs_AirControlMng.AirConData.Controlflag=0xff;
}
