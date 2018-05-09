/*
 * Author: MSOE Team Xi Senior Design 2017
 * Date 12/2017
 * Description:
 */

#ifndef BLUETOOTH_PI3_H
#define BLUETOOTH_PI3_H

/*******************************************
 * External Includes                       *
 *******************************************/
#include "NetworkPacket.h"

/*******************************************
 * Function Prototypes                     *
 *******************************************/
int getAudio(char*, int);
int getData(packet_t*);
void sendAudio(char*, int);
void sendData(packet_t*);
void initBluetooth_Pi3(void);
void closeBluetooth_Pi0W(void);
void* handleBluetoothSender(void*);
void* handleBluetoothReceiver(void*);

#endif /* BLUETOOTH_PI3_H */
