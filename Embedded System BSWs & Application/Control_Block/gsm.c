#include "gsm.h"
#include "Sw_Delay.h"
/* Static functions prototypes */
static void integerToString(sint8 * dest, uint8 number);

/* call back ptrs */
static void (*disconnect_system_func_ptr)(void) = NULL_PTR;
static void (*connect_system_func_ptr)(void) = NULL_PTR;
static void (*change_auth_option_ptr)(uint8) = NULL_PTR;

void GSM_init(){
    uint8 counter = 0;
    /* Send multiple AT command to let the module configure its baud rate automatically */
    for(counter = 0; counter < 5; counter++){
        GSM_sendCommand(GSM_AT_COMMAND);
    }

    /* Enable Full functionality for GSM (both transmit and receive) */
    GSM_sendCommand(GSM_FULL_FUN_CMD);

    /* Ignore empty sms */
    GSM_sendCommand(GSM_IGNORE_EMPTY_SMS_CMD);

    /* Set SMS mode to text mode */
    GSM_sendCommand(GSM_SMS_TXT_MODE_CMD);
    
    /* Delete all previous SMS' */
    GSM_sendCommand(DELETE_ALL_SMS_CMD);
    
    /* Connect GPRS */
    GSM_connectGPRS();
}

void GSM_connectGPRS(void){
    /* Close the bearer */
    GSM_sendCommand(GSM_CLOSE_BEARER_CMD);
    /* Set bearer parameters */
    /* 3 for setting bearer paramaters
     * Contype: Type of Internet connection
     * GPRS: GPRS connection
     */
    GSM_sendCommand(GSM_SET_BEARER_PARAMS_CMD);
    /* Set bearer APN settings */
    GSM_sendCommand(GSM_SET_APN_SETTINGS_CMD);
    /* Set bearer APN username */
    GSM_sendCommand(GSM_SET_APN_USER_CMD);
    /* Set bearer APN password */
    GSM_sendCommand(GSM_SET_APN_PWD_CMD);
    /* Open bearer */
    GSM_sendCommand(GSM_OPEN_BEARER_CMD);
    Delay_ms(2500);
}

void GSM_sendHTTPRequest(uint8 * url, uint8 dataLength, uint8 * data, GSM_contentType content){
    uint8 urlCommand[200] = "";
    uint8 dataLengthCommand[60] = "";
    uint8 dataLengthStr[10] = "";

    GSM_connectGPRS();
    GSM_sendCommand(GSM_HTTP_INIT);
    GSM_sendCommand(GSM_BEARER_PROFILE_IDENTIFIER);
    strcat(urlCommand, GSM_HTTP_CLIENT_URL);
    strcat(urlCommand, url);
    GSM_sendCommand(urlCommand);

    switch (content)
    {
    case GSM_JSON_CONTENT:
        GSM_sendCommand(GSM_HTTP_JSON_CONTENT);
        break;
    case GSM_URL_ENCODED_CONTENT:
        GSM_sendCommand(GSM_HTTP_URL_ENCODED_CONTENT);
        break;
    }
    
    strcat(dataLengthCommand, GSM_HTTP_DATA_LENGTH);
    integerToString(dataLengthStr, dataLength);
    strcat(dataLengthCommand, dataLengthStr);
    strcat(dataLengthCommand, ",10000");
    GSM_sendCommand(dataLengthCommand);
    
    GSM_sendCommand(data);
    Delay_ms(1000);
    GSM_sendCommand(GSM_HTTP_POST_ACTION);
    Delay_ms(1000);
    GSM_sendCommand(GSM_HTTP_READ_RESPONSE);
    GSM_sendCommand(GSM_HTTP_TERMINATE);
}

void GSM_sendCommand(uint8 * command){
    uint8 commandCounter = 0; 
    
    /* Reset the buffer before sending any commands to get a proper response from the module */
    gps_gsm_reset_buffer();
    
    while(command[commandCounter] != '\0'){
        Uart_SendByte(GSM_MODULE_UART, command[commandCounter]);
        commandCounter++;
    }
    Uart_SendByte(GSM_MODULE_UART,'\r');
    
    if(strstr(command, SMS_READ) == NULL){
        Delay_ms(GSM_DELAY); // maybe replace me with while(!g_gps_gsm_rx_complete_flag) 
    }
    
}

static void integerToString(sint8 * dest, uint8 number){
    uint8 counter = 0;
    uint8 tempNumber = number;
    if(number == 0){
        dest[0] = '0';
        return;
    }
    /* Get the length of the number */
    while(number != 0){
        counter++;
        number /= 10;
    }
    
    while(tempNumber != 0){
        dest[--counter] = (tempNumber%10) + '0';
        tempNumber /= 10;
    }
}

void SMS_handler(){
    boolean isFromUser = FALSE;
    uint8 counter = 0;
    
    if(strstr((uint8*)g_gps_gsm_buffer, USER_PHONE_NUMBER) != NULL){
        counter = strstr((uint8*)g_gps_gsm_buffer, USER_PHONE_NUMBER) - (uint8 *)g_gps_gsm_buffer;
    }
    if (counter != 0 && counter < 70) {
        isFromUser = TRUE;
    } else{
        isFromUser = FALSE;
    } 


    if (isFromUser == TRUE) {
        if (strstr((uint8*)g_gps_gsm_buffer, SECURITY_SYSTEM_OFF_CMD)) {
            /* Call Back */
            if (disconnect_system_func_ptr != NULL_PTR) {
                (*disconnect_system_func_ptr)();
            }
            GSM_sendCommand(DELETE_ALL_SMS_CMD);
            return;
        }


        if (strstr((uint8*)g_gps_gsm_buffer, SECURITY_SYSTEM_ON_CMD)) {
            /* Call Back */
            if (connect_system_func_ptr != NULL_PTR) {
                (*connect_system_func_ptr)();
            }
            GSM_sendCommand(DELETE_ALL_SMS_CMD);
            return;
        }

        if(strstr((uint8*)g_gps_gsm_buffer, AUTH_OPT_1)){
            if(change_auth_option_ptr != NULL_PTR){
                (*change_auth_option_ptr)(1);
            }
            GSM_sendCommand(DELETE_ALL_SMS_CMD);
            return;
        }
        if(strstr((uint8*)g_gps_gsm_buffer, AUTH_OPT_2)){
            if(change_auth_option_ptr != NULL_PTR){
                (*change_auth_option_ptr)(2);
            }
            GSM_sendCommand(DELETE_ALL_SMS_CMD);
            return;
        }
        if(strstr((uint8*)g_gps_gsm_buffer, AUTH_OPT_3)){
            if(change_auth_option_ptr != NULL_PTR){
                (*change_auth_option_ptr)(3);
            }
            GSM_sendCommand(DELETE_ALL_SMS_CMD);
            return;
        }

        GSM_sendCommand(DELETE_ALL_SMS_CMD);
    } else {
        GSM_sendCommand(DELETE_ALL_SMS_CMD);

    }
}

void smsNotification_handler(){
    volatile uint8 counter = 0;
    uint8 smsID[10];
    uint8 smsCounter = 0;
    uint8 readSMSCMD[14] = "";

    if(strstr((uint8 *)g_gps_gsm_buffer, "+CMTI") != NULL && strstr((uint8 *)g_gps_gsm_buffer, ",") != NULL){
      Delay_ms(100);
      counter = (strstr((uint8 * )g_gps_gsm_buffer, "\"SM\",") - (uint8 *)g_gps_gsm_buffer) + 5;
        while (g_gps_gsm_buffer[counter] != '\0') {
            smsID[smsCounter++] = g_gps_gsm_buffer[counter];
            counter++;
        }
        smsID[smsCounter] = '\0';

        strcat(readSMSCMD, READ_SMS_CMD);
        strcat(readSMSCMD, smsID);
        GSM_sendCommand(readSMSCMD);
    }
}

void GSM_sendSmsToUser(uint8 * message){
    uint8 msgCounter = 0;
    uint8 sendSMSCmd[25] = "AT+CMGS=\"";
    strcat(sendSMSCmd, USER_PHONE_NUMBER);
    strcat(sendSMSCmd, "\"");
    GSM_sendCommand(sendSMSCmd);

    while (message[msgCounter] != '\0') {
        Uart_SendByte(GSM_MODULE_UART,message[msgCounter]);
        msgCounter++;
    }

    Uart_SendByte(GSM_MODULE_UART,(char)26);
}

void systemOffSetCallBackPtr(void (*ptrToFunc) (void)){
    disconnect_system_func_ptr = ptrToFunc;
}

void systemOnSetCallBackPtr(void (*ptrToFunc) (void)){
    connect_system_func_ptr = ptrToFunc;
}

void changeAuthOptSetCallBackPtr(void (*ptrToFunc) (uint8)){
    change_auth_option_ptr = ptrToFunc;
}
