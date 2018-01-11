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
 * External defines
 *******************************************/

#define BUFFER_SIZE 2048

#define OBDII_DATA 0
#define VOICE_DATA 1

/*******************************************
 * TypeDef Struct                          *
 *******************************************/
typedef struct{
	char datatype;
	char name[32];
	uint32_t size;
	char data[BUFFER_SIZE];
}packet_t;

typedef struct {
	int32_t fuelLevel;
	int32_t speed;
	int32_t rpm;
}obd2data_t;

#endif /* BLUETOOTH_PI3_H */
