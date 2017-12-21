/*
 * Author: MSOE Team Xi Senior Design 2017
 * Date 12/2017
 * Description
 */

#ifndef NETWORKPACKET_H
#define NETWORKPACKET_H

/*******************************************
 * External includes                       *
 *******************************************/
#include <stdint.h>

/*******************************************
 * TypeDef Struct                          *
 *******************************************/
typedef struct{
	char datatype;
	char name[32];
	uint32_t size;
	char data[BUFFER_SIZE];
}packet_t;

#endif /* BLUETOOTH_PI3_H */
