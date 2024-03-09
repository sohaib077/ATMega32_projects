/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
#ifndef _STD_TYPES_H
#define _STD_TYPES_H

/*  Unsigned Type  */

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned long int   u32;
typedef unsigned long long  u64;


/* Signed Type */

typedef signed char         s8;
typedef signed short int    s16;
typedef signed long int     s32;
typedef signed long long    s64;



/*  Unsigned Type  */

typedef unsigned char*       pu8;
typedef unsigned short int*  pu16;
typedef unsigned long int*   pu32;
typedef unsigned long long*  pu64;


/* Signed Type */

typedef signed char*         ps8;
typedef signed short int*    ps16;
typedef signed long int*     ps32;
typedef signed long long*    ps64;


/*  Float Type */

typedef float              f32;
typedef double             f64;
typedef long double        f128;

typedef double*             pf64;

/*NULL MACRO */
#define NULL				 0
#define OK                   0
#define NOT_OK               1

/* Func States  */
#define IDLE 			0
#define BUSY			1

/* My States  */
#define OK           	0
#define NOT_OK          1
#define NULL_POINTER 	2
#define BUSY_STATE	 	3
#define TIMEOUT_STATE   4


#endif