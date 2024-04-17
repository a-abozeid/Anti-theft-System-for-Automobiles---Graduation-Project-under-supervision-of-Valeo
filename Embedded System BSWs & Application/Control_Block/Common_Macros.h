/*
==============================================================================
* Authour: Youssef El-Nemaky
*
* Date: 21/9/2021
*
* File: common_macros.h
*
* Description: This header contatins common macros used frequently
  MACRO(REGISTER,BIT) -> CLEAR_BIT(PORTB, PB0)
  this header contanins the following macros
  1) SET_BIT
  2) CLEAR_BIT
  3) TOGGLE_BIT
  4) ROR()
  5) ROL()
  6) IS_BIT_SET()
  7) IS_BIT_CLEAR()
==============================================================================
*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*==============================================================================
* [MACRO_NAME]: SET_BIT 
* 
* [DESCRIPTION]: used to SET a bit in a specific register
* 
* [ARGS]: 1) REG -> The register that contains the bit
*         2) BIT -> The bit's number that you want to SET
*          
* EXAMPLE: SET_BIT(PORTB, PB1) -> now PB1 of PORTB is SET
================================================================================*/
#define SET_BIT(REG,BIT)       (REG |= (1<<BIT))




/*==============================================================================
* [MACRO_NAME]: CLEAR_BIT 
* 
* [DESCRIPTION]: used to CLEAR a bit in a specific register
* 
* [ARGS]: 1) REG -> The register that contains the bit
*         2) BIT -> The bit's number that you want to CLEAR
*          
* EXAMPLE: CLEAR_BIT(PORTB, PB1) -> now PB1 of PORTB is CLEARED
================================================================================*/
#define CLEAR_BIT(REG,BIT)     (REG &= ~(1<<BIT))

/*==============================================================================
* [MACRO_NAME]: TOGGLE_BIT 
* 
* [DESCRIPTION]: used to TOGGLE a bit in a specific register
* 
* [ARGS]: 1) REG -> The register that contains the bit
*         2) BIT -> The bit's number that you want to TOGGLE
*          
* EXAMPLE: TOGGLE_BIT(PORTB, PB1) -> now PB1 of PORTB is TOGGLED (1 becomes 0 and 0 becomes 1)
================================================================================*/
#define TOGGLE_BIT(REG,BIT)    (REG ^= (1<<BIT))


/*==============================================================================
* [MACRO_NAME]: ROR 
* 
* [DESCRIPTION]: used to ROTATE a specific register to the right a specific
*                number of times.
* 
* [ARGS]: 1) REG -> The register that you want to rotate to the right
*         2) NUM -> Number of rotations to the right
*          
* EXAMPLE: ROR(PORTB, 5) -> now PORTB is rotated to the right 5 times
================================================================================*/
#define ROR(REG,NUM)           (REG = (REG>>NUM) | (REG<<((sizeof(REG) * 8)-NUM)))


/*==============================================================================
* [MACRO_NAME]: ROL 
* 
* [DESCRIPTION]: used to ROTATE a specific register to the left a specific
*                number of times.
* 
* [ARGS]: 1) REG -> The register that you want to rotate to the left
*         2) NUM -> Number of rotations to the left
*          
* EXAMPLE: ROL(PORTB, 3) -> now PORTB is rotated to the left 3 times
================================================================================*/
#define ROL(REG,NUM)           (REG = (REG<<NUM) | (REG>>((sizeof(REG) * 8)-NUM)))

/*==============================================================================
* [MACRO_NAME]: IS_BIT_SET 
* 
* [DESCRIPTION]: used to check whether a specific bit is SET or not.
* 
* [ARGS]: 1) REG -> The register that contains the bit.
*         2) BIT -> The bit's number that you want to check wether it's SET or not.
*
* [RETURN]: TRUE if the bit is SET
*           FALSE if the bit is not SET
*
* EXAMPLE: IS_BIT_SET(PORTB, PB5) -> returns TRUE if PB5 is SET ELSE returns FALSE 
================================================================================*/
#define IS_BIT_SET(REG,BIT)    (REG & (1<<BIT))

/*==============================================================================
* [MACRO_NAME]: IS_BIT_CLEAR
* 
* [DESCRIPTION]: used to check whether a specific bit is CLEARED or not.
* 
* [ARGS]: 1) REG -> The register that contains the bit.
*         2) BIT -> The bit's number that you want to check wether it's CLEARED or not.
*
* [RETURN]: TRUE if the bit is CLEARED
*           FALSE if the bit is not CLEARED
*
* EXAMPLE: IS_BIT_CLEAR(PORTB, PB5) -> returns TRUE if PB5 is CLEARED ELSE returns TRUE 
================================================================================*/
#define IS_BIT_CLEAR(REG,BIT)  (!(REG & (1<<BIT)))

#endif /* COMMON_MACROS_H_ */
