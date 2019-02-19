#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/* headerfile for "fl_E2bus.c" module */
/***************************************************************************/
#ifndef ___FL_E2BUS_INCLUDED
#define ___FL_E2BUS_INCLUDED
// constant definition
//-----------------------------------------------------------------------------
#define CB_TYPELO 0x11 // ControlByte for reading Sensortype Low-Byte
#define CB_TYPESUB 0x21 // ControlByte for reading Sensor-Subtype
#define CB_AVPHMES 0x31 // ControlByte for reading Available physical measurements
#define CB_TYPEHI 0x41 // ControlByte for reading Sensortype High-Byte
#define CB_STATUS 0x71 // ControlByte for reading Statusbyte
#define CB_MV1LO 0x81 // ControlByte for reading Measurement value 1 Low-Byte
#define CB_MV1HI 0x91 // ControlByte for reading Measurement value 1 High-Byte
#define CB_MV2LO 0xA1 // ControlByte for reading Measurement value 2 Low-Byte
#define CB_MV2HI 0xB1 // ControlByte for reading Measurement value 2 High-Byte
#define CB_MV3LO 0xC1 // ControlByte for reading Measurement value 3 Low-Byte
#define CB_MV3HI 0xD1 // ControlByte for reading Measurement value 3 High-Byte
#define CB_MV4LO 0xE1 // ControlByte for reading Measurement value 4 Low-Byte
#define CB_MV4HI 0xF1 // ControlByte for reading Measurement value 4 High-Byte
#define E2_DEVICE_ADR 0 // Address of E2-Slave-Device
// declaration of functions
//-----------------------------------------------------------------------------
unsigned int fl_E2bus_Read_SensorType(void); // read Sensortype from E2-Interface
unsigned char fl_E2bus_Read_SensorSubType(void); // read Sensor Subtype from E2-Interface
unsigned char fl_E2bus_Read_AvailablePhysicalMeasurements(void); // read available physical Measurements from E2-Interface
float fl_E2bus_Read_RH(void); // Read Measurement Value 1 (relativ Humidity [%RH])
float fl_E2bus_Read_Temp(void); // Read Measurement Value 2 (Temperature [°C])
float fl_E2bus_Read_CO2_RAW(void); // Read Measurement Value 3 (CO2 RAW [ppm])
float fl_E2bus_Read_CO2_MEAN(void); // Read Measurement Value 4 (CO2 MEAN [ppm])
unsigned char fl_E2bus_Read_Status(void); // read Statusbyte from E2-Interface
#endif


#ifdef __cplusplus
}
#endif