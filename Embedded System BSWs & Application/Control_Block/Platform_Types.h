 /******************************************************************************
 *
 * Module: Common - Platform Abstraction
 *
 * File Name: Platform_Types.h
 *
 * Description: Contains the definitions for platform types for ARM Cortex-M4F.
 *
 * Author: Youssef El-Nemaky
 *
 *******************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/* Id for the company in the AUTOSAR */
#define PLATFORM_VENDOR_ID                          (1000U)


/*
 * Module Version 1.0.0
 */
#define PLATFORM_SW_MAJOR_VERSION                   (1U)
#define PLATFORM_SW_MINOR_VERSION                   (0U)
#define PLATFORM_SW_PATCH_VERSION                   (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION           (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION           (0U)
#define PLATFORM_AR_RELEASE_PATCH_VERSION           (3U)

/* CPU register type width */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)

/* Byte orderding */
#define HIGH_BYTE_FIRST               (0U)     /* Big endian byte ordering */
#define LOW_BYTE_FIRST                (1U)     /* Little endian byte ordering */

/* Bit ordering */
#define MSB_FIRST                     (0U)     /* Big endian bit ordering */
#define LSB_FIRST                     (1U)     /* Little endian bit ordering */

/* ARM Cortex-M4F */

/* CPU Register Width */
#define CPU_TYPE CPU_TYPE_32

/* CPY byte order */
#define CPU_BYTE_ORDER LOW_BYTE_FIRST

/* CPY bit order */
#define CPU_BIT_ORDER LSB_FIRST


/* Boolean Values */

#ifndef FALSE
#define FALSE (0U)
#endif

#ifndef TRUE
#define TRUE (1U)
#endif

typedef unsigned char         boolean;

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

#endif /* PLATFORM_TYPES_H */