#ifndef GPS_GSM_BUFFER_H
#define GPS_GSM_BUFFER_H

/* Include files */
#include "Uart.h"
#include <string.h>
#include "gsm.h"

/* Definitions */
#define GPS_GSM_BUFFER_SIZE 250


/* Functions prototypes */
void gps_gsm_populate_buffer(uint8 uartData);
void gps_gsm_reset_buffer(void);

/* Externing variables */
extern volatile uint8 g_gps_gsm_buffer[GPS_GSM_BUFFER_SIZE];
extern volatile uint8 g_gps_gsm_buffer_index;
extern volatile uint8 g_gps_gsm_rx_complete_flag;
#endif