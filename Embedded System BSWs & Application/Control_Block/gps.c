#include "gps.h"


void GPS_sendCommand(uint8 * command){
    uint8 commandCounter = 0; 

    /* Reset the buffer before sending any commands to get a proper response from the module */
    gps_gsm_reset_buffer();

    while(command[commandCounter] != '\0'){
        Uart_SendByte(GPS_MODULE_UART, command[commandCounter]);
        commandCounter++;
    }
    Uart_SendByte(GPS_MODULE_UART,'\r');
    Delay_ms(GPS_DELAY);
}

void GPS_init(){
    uint8 counter = 0;
    /* Send multiple AT command to let the module configure its baud rate automatically */
    for(counter = 0; counter < 5; counter++){
        GPS_sendCommand(GPS_AT_COMMAND);
    }

    /* Turn off command echos */
    GPS_sendCommand(GPS_ECHO_OFF_CMD);
    
    /* Turn on GPS & GNS */
    GPS_sendCommand(GNS_PWR_ON_CMD);

    /* Set RMC NMEA */
    GPS_sendCommand(GNS_RMC_NMEA_CMD);

    Uart_RxSetCallBack(GPS_MODULE_UART, gps_gsm_populate_buffer);
}


void GPS_getLocation(uint8 * latitude ,uint8 * longitude){
    uint8 buffer_counter = 0;
    uint8 latitudeCounter = 0, longitudeCounter = 0;
    uint8 numberOfCommas = 0;

    /* send get location command to the gps module */
    GPS_sendCommand(GNS_GET_LOCATION_CMD);

    /* Wait to receive the reponse and populate the buffer */
    while(!g_gps_gsm_rx_complete_flag);

    /* Now we have a buffer that has the response from the module
     * time to do some processing on that buffer 
     */
    for(buffer_counter = 0; buffer_counter < g_gps_gsm_buffer_index; buffer_counter++){
        if(g_gps_gsm_buffer[buffer_counter] == ','){
            numberOfCommas++;
        }
        if (numberOfCommas == 3) {
            if(g_gps_gsm_buffer[buffer_counter] != ','){
                latitude[latitudeCounter++] = g_gps_gsm_buffer[buffer_counter];
            }
        } else if (numberOfCommas == 4) {
            if(g_gps_gsm_buffer[buffer_counter] != ','){
                longitude[longitudeCounter++] = g_gps_gsm_buffer[buffer_counter];
            }
        } else if (numberOfCommas > 4) {
            /* No need to continue as we've already read the latitude and longitude */
            break;
        }
    }
    /* Add Null-Terminator at the end of the string */
    latitude[latitudeCounter] = '\0'; 
    longitude[longitudeCounter] = '\0';
}

void GPS_updateLocation(void){
    volatile uint8 httpMessageBody[120] = "";
    volatile uint8 latitude[10] = "";
    volatile uint8 longitude[10] = "";
    GPS_getLocation((uint8*)latitude, (uint8*)longitude);

    if( ( strcmp((uint8 *)latitude, "") == 0 ) && ( strcmp((uint8 *)longitude, "") == 0 ) ){
        return;
    }
    GSM_connectGPRS();
    strcat((uint8 *)httpMessageBody, API_KEY);
    strcat((uint8 *)httpMessageBody, "&field1=");
    strcat((uint8 *)httpMessageBody, (uint8 *)latitude);
    strcat((uint8 *)httpMessageBody, "&field2=");
    strcat((uint8 *)httpMessageBody, (uint8 *)longitude);
    GSM_sendHTTPRequest((uint8 *)URL, strlen((uint8 *)httpMessageBody), (uint8 *)httpMessageBody, GSM_URL_ENCODED_CONTENT);
    httpMessageBody[0] = '\0';
    gps_gsm_reset_buffer();

}