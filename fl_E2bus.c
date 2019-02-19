// Includes
//-----------------------------------------------------------------------------

#include "knl_E2bus.h"
#include "fl_E2bus.h"


float fl_E2bus_Read_Temp(void) // Read Measurement Value 2 (Temperature [°C])
{
  st_E2_Return E2_Return;
  float Temp;
  unsigned char Temp_LB, Temp_HB;
  
  Temp = -300;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_MV2LO|(E2_DEVICE_ADR<<1));
  Temp_LB = E2_Return.DataByte;

  if(E2_Return.Status == 0)
  {
    E2_Return = knl_E2bus_readByteFromSlave(CB_MV2HI|(E2_DEVICE_ADR<<1));
    Temp_HB = E2_Return.DataByte;
	
    if(E2_Return.Status == 0)
    { 
      Temp = (Temp_LB + (float)(Temp_HB)*256) / 100 - 273.15;
    }
  }
  
  return Temp;
}

float fl_E2bus_Read_RH(void) // Read Measurement Value 1 (relative Humidity [%RH])
{
  st_E2_Return E2_Return;
  float RH;
  unsigned char RH_LB, RH_HB;
  
  RH = -1;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_MV1LO|(E2_DEVICE_ADR<<1));
  RH_LB = E2_Return.DataByte;
  
  if(E2_Return.Status == 0)
  {
    E2_Return = knl_E2bus_readByteFromSlave(CB_MV1HI|(E2_DEVICE_ADR<<1));
    RH_HB = E2_Return.DataByte;
	
    if(E2_Return.Status == 0)
    {
      RH = (RH_LB + (float)(RH_HB)*256) / 100;
    }
  }
  
  return RH;
}


float fl_E2bus_Read_CO2_RAW(void) // Read Measurement Value 3 (CO2 RAW [ppm])
{
  st_E2_Return E2_Return;
  float CO2_RAW;
  unsigned char CO2_LB, CO2_HB;
  
  CO2_RAW = -1;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_MV3LO|(E2_DEVICE_ADR<<1));
  CO2_LB = E2_Return.DataByte;
  
  if(E2_Return.Status == 0)
  {
    E2_Return = knl_E2bus_readByteFromSlave(CB_MV3HI|(E2_DEVICE_ADR<<1));
    CO2_HB = E2_Return.DataByte;
	
    if(E2_Return.Status == 0)
    {
      CO2_RAW = CO2_LB + (float)(CO2_HB)*256;
    }
  }
  
  return CO2_RAW;
}


float fl_E2bus_Read_CO2_MEAN(void) // Read Measurement Value 4 (CO2 MEAN [ppm])
{
  st_E2_Return E2_Return;
  float CO2_MEAN;
  unsigned char CO2_LB, CO2_HB;
  
  CO2_MEAN = -1;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_MV4LO|(E2_DEVICE_ADR<<1));
  CO2_LB = E2_Return.DataByte;
  
  if(E2_Return.Status == 0)
  {
    E2_Return = knl_E2bus_readByteFromSlave(CB_MV4HI|(E2_DEVICE_ADR<<1));
    CO2_HB = E2_Return.DataByte;
	
    if(E2_Return.Status == 0)
    {
      CO2_MEAN = CO2_LB + (float)(CO2_HB)*256;
    }
  }
  
  return CO2_MEAN;
}

unsigned char fl_E2bus_Read_Status(void) // read Statusbyte from E2-Interface
{
  st_E2_Return E2_Return;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_STATUS|(E2_DEVICE_ADR<<1));
  
  if(E2_Return.Status == 1)
  {
    E2_Return.DataByte = 0xFF;
  }
  
  return E2_Return.DataByte;
}


unsigned int fl_E2bus_Read_SensorType(void) // read Sensortype from E2-Interface
{
  st_E2_Return E2_Return;
  unsigned int Type;
  unsigned char Type_LB, Type_HB;
  
  Type = 0xFFFF;
  
  E2_Return = knl_E2bus_readByteFromSlave(CB_TYPELO|(E2_DEVICE_ADR<<1));
  Type_LB = E2_Return.DataByte;
  
  if(E2_Return.Status == 0)
  {
    E2_Return = knl_E2bus_readByteFromSlave(CB_TYPEHI|(E2_DEVICE_ADR<<1));
    Type_HB = E2_Return.DataByte;
	
    if(E2_Return.Status == 0)
    {
      Type = Type_LB + (unsigned int)(Type_HB)*256;
    }
  }
  
  return Type;
}

unsigned char fl_E2bus_Read_SensorSubType(void) // read Sensor Subtype from E2-Interface
{
  st_E2_Return E2_Return;
  E2_Return = knl_E2bus_readByteFromSlave(CB_TYPESUB|(E2_DEVICE_ADR<<1));
  
  if(E2_Return.Status == 1)
  {
    E2_Return.DataByte = 0xFF;
  }
  
  return E2_Return.DataByte;
}

unsigned char fl_E2bus_Read_AvailablePhysicalMeasurements(void) // read available physical Measurements from E2-Interface
{
  st_E2_Return E2_Return;
  E2_Return = knl_E2bus_readByteFromSlave(CB_AVPHMES|(E2_DEVICE_ADR<<1));
  
  if(E2_Return.Status == 1)
  {
    E2_Return.DataByte = 0xFF;
  }
  
  return E2_Return.DataByte;
}
