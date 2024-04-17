#include "gps_gsm_buffer.h"

volatile uint8 g_gps_gsm_buffer[GPS_GSM_BUFFER_SIZE] = "";
volatile uint8 g_gps_gsm_buffer_index = 0;
volatile uint8 g_gps_gsm_rx_complete_flag = 0;

void gps_gsm_populate_buffer(uint8 uartData){
    /*
     * Commands are usually followed by a response that includes.
     * "<CR><LF><response><CR><LF>"
     */
    if (uartData != '\n' && uartData != '\r') {
        g_gps_gsm_buffer[g_gps_gsm_buffer_index++] = uartData;
        if (strstr((uint8*)g_gps_gsm_buffer, "OK") != NULL || strstr((uint8*)g_gps_gsm_buffer, "ERROR") != NULL) {
            g_gps_gsm_rx_complete_flag = 1;
            if (strstr((uint8*)g_gps_gsm_buffer, (uint8*)SMS_READ) != NULL) {
                SMS_handler();
            }
        }

    } else if (uartData == '\n') {
        if (strstr((uint8*)g_gps_gsm_buffer, (uint8*)SMS_RECEIVED) != NULL) {
            smsNotification_handler();
        }
    }
}

void gps_gsm_reset_buffer(void){
    uint8 bufferCounter = 0; 

    /* Reset the buffer itself */
    for(bufferCounter = 0; bufferCounter < GPS_GSM_BUFFER_SIZE; bufferCounter++){
        g_gps_gsm_buffer[bufferCounter] = '\0';
    }
    
    /* Reset the buffer index */
    g_gps_gsm_buffer_index = 0;

    /* Reset the buffer receive complete flag */
    g_gps_gsm_rx_complete_flag = 0;

}