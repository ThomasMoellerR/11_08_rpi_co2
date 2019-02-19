

#include <wiringPi.h>

#include "fl_E2bus.h"
#include "gpio.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARGS_FILE 1
#define ARGS_SDA 2
#define ARGS_SCL 3
#define ARGS_DELAY 4




int main(int argc, const char** argv) 
{
  wiringPiSetup () ;
  
  printf("\nFile: %s",argv[ARGS_FILE]);
  printf("\nSDA_Pin: %s",argv[ARGS_SDA]);
  printf("\nSCL_Pin: %s",argv[ARGS_SCL]);  
  printf("\nDelay: %s",argv[ARGS_DELAY]);  

  GPIO_u8SDA_Pin = atoi(argv[ARGS_SDA]);
  GPIO_u8SCL_Pin = atoi(argv[ARGS_SCL]);
  GPIO_u16Delay =  atoi(argv[ARGS_DELAY]);
      
  printf("\n");  
  
  printf("Sensor Subtype: %d\n", fl_E2bus_Read_SensorSubType()); // read Sensor Subtype from E2-Interface    
  
  printf("available physical Measurements: %d\n", fl_E2bus_Read_AvailablePhysicalMeasurements()); // read available physical Measurements from E2-Interface 
      
  int iCO2_Mean;
  unsigned char Status;

  //while(1)
  //{

      iCO2_Mean = (int) fl_E2bus_Read_CO2_MEAN(); // Read Measurement Value 4 (CO2 MEAN [ppm])

      Status = fl_E2bus_Read_Status(); // Read Statusbyte from E2-Interface
      
      printf("Status: %d, Wert: %d \n", Status, iCO2_Mean);   


      FILE *f = fopen(argv[ARGS_FILE], "w");
      fprintf(f, "%d\n", iCO2_Mean);
      fclose(f);
      
      //delay(15000);
  //}
    
  return 0;
}