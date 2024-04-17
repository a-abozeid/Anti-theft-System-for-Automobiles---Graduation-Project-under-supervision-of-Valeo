#ifndef GSM_H
#define GSM_H

#include "Uart.h"
#include "gps_gsm_buffer.h"
#include "gsm_cfg.h"

/* Definitions */
#define GSM_DELAY 100
#define GSM_AT_COMMAND "AT"

#ifndef AT_OK_CMD
#define AT_OK_CMD "OK"
#endif

#define GSM_IS_RDY_CMD "AT+CPIN?"
#define GSM_FULL_FUN_CMD "AT+CFUN=1"
#define GSM_VERBOSE_ERRS_ON_CMD "AT+CMEE=2"
#define GSM_ENABLE_BATTERY_CHECKS_CMD "AT+CBATCHK=1"
#define GMS_IS_NETWORK_REG_CMD "AT+CREG?"
#define GSM_SMS_TXT_MODE_CMD "AT+CMGF=1"
#define GSM_CLOSE_BEARER_CMD "AT+SAPBR=0,1"
#define GSM_OPEN_BEARER_CMD "AT+SAPBR=1,1"

/* 3 for setting bearer paramaters
 * Contype: Type of Internet connection
 * GPRS: GPRS connection 
 */
#define GSM_SET_BEARER_PARAMS_CMD "AT+SAPBR=3,1,\"Contype\",\"GPRS\""
/* 
Vodafone APN Settings 
#define GSM_SET_APN_SETTINGS_CMD "AT+SAPBR=3,1,\"APN\",\"internet.vodafone.net\""
#define GSM_SET_APN_USER_CMD "AT+SAPBR=3,1,\"USER\",\"internet\""
#define GSM_SET_APN_PWD_CMD "AT+SAPBR=3,1,\"PWD\",\"internet\""
*/


/* WE APN Settings */
#define GSM_SET_APN_SETTINGS_CMD "AT+SAPBR=3,1,\"APN\",\"internet.we.net\""
#define GSM_SET_APN_USER_CMD "AT+SAPBR=3,1,\"USER\",\"\""
#define GSM_SET_APN_PWD_CMD "AT+SAPBR=3,1,\"PWD\",\"\""
#define GSM_QUERY_BEARER_CMD "AT+SAPBR=2,1"
#define GSM_IGNORE_EMPTY_SMS_CMD "AT+CSMP=17,167,0,0"

#define SECURITY_SYSTEM_ON_CMD "systemOn"
#define SECURITY_SYSTEM_OFF_CMD "systemOff"
#define AUTH_OPT_1 "auth = op1"
#define AUTH_OPT_2 "auth = op2"
#define AUTH_OPT_3 "auth = op3"



#define SMS_RECEIVED "+CMTI"
#define SMS_READ "+CMGR"
#define READ_SMS_CMD "AT+CMGR="
#define DELETE_ALL_SMS_CMD "AT+CMGD=1,4"



/* HTTP Request related defintions */
#define GSM_HTTP_INIT "AT+HTTPINIT"
#define GSM_BEARER_PROFILE_IDENTIFIER "AT+HTTPPARA=\"CID\",1"
#define GSM_HTTP_CLIENT_URL "AT+HTTPPARA=\"URL\","
#define GSM_HTTP_JSON_CONTENT "AT+HTTPPARA=\"CONTENT\",\"application/json\""
#define GSM_HTTP_URL_ENCODED_CONTENT "AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\""
#define GSM_HTTP_DATA_LENGTH "AT+HTTPDATA="
#define GSM_HTTP_POST_ACTION "AT+HTTPACTION=1"
#define GSM_HTTP_TERMINATE "AT+HTTPTERM"
#define GSM_HTTP_READ_RESPONSE "AT+HTTPREAD"

typedef enum{
    GSM_JSON_CONTENT,GSM_URL_ENCODED_CONTENT
} GSM_contentType;
/* Function Prototypes */
void GSM_sendCommand(uint8 * command);
void GSM_clearBuffer(void);
void GSM_setBuffer(void);
void GSM_init();
void GSM_connectGPRS(void);
void GSM_sendHTTPRequest(uint8 * url, uint8 dataLength, uint8 * data, GSM_contentType content);
void pumpSetCallBackPtr(void (*ptrToFunc) (void));
void systemOffSetCallBackPtr(void (*ptrToFunc) (void));
void systemOnSetCallBackPtr(void (*ptrToFunc) (void));
void changeAuthOptSetCallBackPtr(void (*ptrToFunc) (uint8));
void smsNotification_handler();
void SMS_handler();
void GSM_sendSmsToUser(uint8 * message);

#endif