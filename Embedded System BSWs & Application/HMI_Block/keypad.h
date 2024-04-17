

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include"std_types.h"
#include "Dio.h"
#include "Port.h"

//#define KEYPAD_PORT PORTA_ID //we use PORTA for keypad connections
//#define KEYPAD_FRIST_COLUMN 4
//#define KEYPAD_FRIST_ROW    0
#define KEYPAD_NUM_COLS   4
#define KEYPAD_NUM_ROWS    4

///#define KEYPAD_FIRST_COLUMN_PIN_ID       PIN4_ID
//#define KEYPAD_FIRST_ROW_PINID          PIN0_ID
//#define KEYPAD_BUTTON_PRESSED          LOW
//#define KEYPAD_BUTTON_RELEASED         HIGH

//#define KEYPAD_BUTTON_PRESSED            HIGH
//#define KEYPAD_BUTTON_RELEASED           LOW
//#define LOW               0
//#define HIGH              1
//#define PIN_OUTPUT        1
//#define PIN_INPUT         0

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
