/***************************************************/
/* datatypes.h
 *
 *  Created on: Sep 19, 2018
 *  Author: Madursk
 *  Brief: Datatypes according to MISRA-C 2004
 */
/************************************************/
#ifndef DATATYPES_H_
#define DATATYPES_H_

#define STD_ON 1u
#define STD_OFF 0u

#define E_OK 0x00u
#define E_NOT_OK 0x01u

typedef  unsigned char uint8_t;
typedef signed char int8_t;
typedef  unsigned short int uint16_t;
typedef short int int16_t;
typedef char char_t;
typedef uint8_t std_ReturnType;

#define NULLPTR ((void*)0)

#endif /* DATATYPES_H_ */
