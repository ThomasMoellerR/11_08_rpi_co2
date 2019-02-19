#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/* headerfile for "knl_E2bus.c" module */
/***************************************************************************/
#ifndef ___KNL_E2BUS_INCLUDED
#define ___KNL_E2BUS_INCLUDED



typedef unsigned char	bit;



// constant definition
//-----------------------------------------------------------------------------
#define RETRYS 3 // number of read attempts
#define DELAY_FACTOR 2 // delay factor for configuration of interface speed

// pin assignment
//-----------------------------------------------------------------------------

// definition of structs
//-----------------------------------------------------------------------------
typedef struct st_E2_Return
{
unsigned char DataByte;
unsigned char Status;
}st_E2_Return;

// declaration of functions
//-----------------------------------------------------------------------------
st_E2_Return knl_E2bus_readByteFromSlave( unsigned char ControlByte );

void knl_E2bus_start(void);
void knl_E2bus_stop(void);
void knl_E2bus_sendByte(unsigned char);
unsigned char knl_E2bus_readByte(void);
void knl_E2bus_delay(unsigned int value);
char knl_E2bus_check_ack(void);
void knl_E2bus_send_ack(void);
void knl_E2bus_send_nak(void);
void knl_E2bus_set_SDA(void);
void knl_E2bus_clear_SDA(void);
bit knl_E2bus_read_SDA(void);
void knl_E2bus_set_SCL(void);
void knl_E2bus_clear_SCL(void);
#endif


#ifdef __cplusplus
}
#endif