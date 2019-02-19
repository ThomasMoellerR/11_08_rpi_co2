// Includes
//-----------------------------------------------------------------------------
#include "knl_E2bus.h"



// Definitions
//-----------------------------------------------------------------------------
#define ACK 1
#define NAK 0
#define DELAY_FACTOR 2


st_E2_Return knl_E2bus_readByteFromSlave( unsigned char ControlByte ) // read byte from slave with controlbyte
{
  unsigned char Checksum;
  unsigned char counter=0;
  st_E2_Return E2_Return;
  
  E2_Return.Status = 1;

  while (E2_Return.Status && counter<RETRYS) // RETRYS...Number of read attempts
  {
    knl_E2bus_start(); // send E2 start condition
    knl_E2bus_sendByte( ControlByte ); // send 0xA1 (example for reading Temp_Low byte)
	
    if ( knl_E2bus_check_ack() == ACK ) // ACK received?
    {
	  E2_Return.DataByte = knl_E2bus_readByte(); // read Temp_low (example for reading Temp_Low byte)
      knl_E2bus_send_ack(); // send ACK
      Checksum = knl_E2bus_readByte(); // read checksum
      knl_E2bus_send_nak(); // send NACK
      if ( ( ( ControlByte + E2_Return.DataByte ) % 0x100 ) == Checksum )
    	  // checksum OK?
      E2_Return.Status = 0;
    }
	
    knl_E2bus_stop(); // send E2 stop condition
    counter++;
  }
  
  return E2_Return;
}


void knl_E2bus_start(void) // send start condition to E2-Interface
{
  knl_E2bus_set_SDA();
  knl_E2bus_set_SCL();
  knl_E2bus_delay(30);
  knl_E2bus_clear_SDA();
  knl_E2bus_delay(30);
}
void knl_E2bus_stop(void) // send stop condition to E2-Interface
{
  knl_E2bus_clear_SCL();
  knl_E2bus_delay(20);
  knl_E2bus_clear_SDA();
  knl_E2bus_delay(20);
  knl_E2bus_set_SCL();
  knl_E2bus_delay(20);
  knl_E2bus_set_SDA();
}




void knl_E2bus_sendByte(unsigned char value) // send byte to E2-Interface
{
  unsigned char mask;
  
  for ( mask = 0x80; mask > 0; mask >>= 1)
  {
    knl_E2bus_clear_SCL();
    knl_E2bus_delay(10);
	
    if ((value & mask) != 0)
    {
	  knl_E2bus_set_SDA();
    }
    else
    {
	  knl_E2bus_clear_SDA();
    }
	
    knl_E2bus_delay(20);
    knl_E2bus_set_SCL();
    knl_E2bus_delay(30);
    knl_E2bus_clear_SCL();
  }
  
  knl_E2bus_set_SDA();
}


unsigned char knl_E2bus_readByte(void) // read Byte from E2-Interface
{
  unsigned char data_in = 0x00;
  unsigned char mask = 0x80;
  
  for (mask=0x80;mask>0;mask >>=1)
  {
	knl_E2bus_clear_SCL();
    knl_E2bus_delay(30);
    knl_E2bus_set_SCL();
    knl_E2bus_delay(15);
	
    if (knl_E2bus_read_SDA())
    {
	  data_in |= mask;
    }
	
    knl_E2bus_delay(15);
    knl_E2bus_clear_SCL();
  }
  
  return data_in;
}


char knl_E2bus_check_ack(void) // check for acknowledge
{
  bit input;
  knl_E2bus_clear_SCL();
  knl_E2bus_delay(30);
  knl_E2bus_set_SCL();
  knl_E2bus_delay(15);
  input = knl_E2bus_read_SDA();
  knl_E2bus_delay(15);
  
  if(input == 1) // SDA = LOW ==> ACK, SDA = HIGH ==> NAK
  return NAK;
  else
  return ACK;
}
void knl_E2bus_send_ack(void) // send acknowledge
{
  knl_E2bus_clear_SCL();
  knl_E2bus_delay(15);
  knl_E2bus_clear_SDA();
  knl_E2bus_delay(15);
  knl_E2bus_set_SCL();
  knl_E2bus_delay(28);
  knl_E2bus_clear_SCL();
  knl_E2bus_delay(2);
  knl_E2bus_set_SDA();
}



void knl_E2bus_send_nak(void) // send NOT-acknowledge
{
  knl_E2bus_clear_SCL();
  knl_E2bus_delay(15);
  knl_E2bus_set_SDA();
  knl_E2bus_delay(15);
  knl_E2bus_set_SCL();
  knl_E2bus_delay(30);
  knl_E2bus_set_SCL();
}


#include <wiringPi.h>
#include "gpio.h"


void knl_E2bus_delay(unsigned int count) // knl_E2bus_delay function
{
  int i,j;

  for(i = 0; i < count; i++)
  {
    for (j = 0; j < GPIO_u16Delay; j++);
  }
}

// adapt this code for your target processor !!! Value = 1 ==> Physical Signal is High, Value = 0 ==> Physical Signal is Low

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void knl_E2bus_set_SDA(void)
{
  pinMode(GPIO_u8SDA_Pin, OUTPUT);
  digitalWrite(GPIO_u8SDA_Pin, 1);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void knl_E2bus_clear_SDA(void)
{
  pinMode(GPIO_u8SDA_Pin, OUTPUT);
  digitalWrite(GPIO_u8SDA_Pin, 0);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

bit knl_E2bus_read_SDA(void)
{
    pinMode(GPIO_u8SDA_Pin, INPUT);
    //printf("%d\n", digitalRead(GPIO_u8SDA_Pin));
    return digitalRead(GPIO_u8SDA_Pin);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void knl_E2bus_set_SCL(void)
{
  pinMode(GPIO_u8SCL_Pin, OUTPUT);
  digitalWrite(GPIO_u8SCL_Pin, 1);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void knl_E2bus_clear_SCL(void)
{
  pinMode(GPIO_u8SCL_Pin, OUTPUT);
  digitalWrite(GPIO_u8SCL_Pin, 0);
}
