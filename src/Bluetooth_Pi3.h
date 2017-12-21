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
#include "NetworkPackage.h"

/*******************************************
 * Function Prototypes                     *
 *******************************************/
void getBluetoothData(packet_t*);
void sendBluetoothData(packet_t*);
void initBluetooth_Pi3(void);
void closeBluetooth_Pi0W(void);


#endif /* BLUETOOTH_PI3_H */
