#ifndef GPS_H
#define GPS_H

#include "Uart.h"
#include <string.h>
#include "gps_gsm_buffer.h"
#include "Sw_Delay.h"

/* Definitions */
#define GPS_DELAY 100
#define GPS_AT_COMMAND "AT"
#define GPS_ECHO_OFF_CMD "ATE0"
#define GNS_PWR_ON_CMD "AT+CGNSPWR=1"
#define GNS_RMC_NMEA_CMD "AT+CGNSSEQ=RMC"
#define GNS_GET_LOCATION_CMD "AT+CGNSINF"

#ifndef AT_OK_CMD
#define AT_OK_CMD "OK"
#endif


/* Function Prototypes */
void GPS_getLocation(uint8 * latitude ,uint8 * longitude);
void GPS_sendCommand(uint8 * command);
void GPS_receiveResponse(uint8 * response);
void GPS_init(void);
void GPS_updateLocation(void);


#endif

