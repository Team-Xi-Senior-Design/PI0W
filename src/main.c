/* Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: Main c file for the helmet side controller
 */

 /********************
 * External Includes *
 *********************/
#include "main.h"
#include "Audio.h"
#include "Video.h"
#include "NetworkPacket.h"
#include "Global.h"
#include <ncurses.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Bluetooth_Pi3.h"

#define MONITOR_WIDTH 127
#define MONITOR_HEIGHT 116

int main(int argc, char* argv[]){
	int size;
	packet_t packet;
	packet.datatype = VOICE_DATA;
	char buff[1024];
	pthread_t audioThread;
//	pthread_t bluetoothThreadS;
//	pthread_t bluetoothThreadR;
	pthread_t playAudioThread;
//	initCapture();
//	initPlayback();
	initBluetooth_Pi3();
//	while(1){
//		size = captureAudio(buff, 1024);
//		playbackAudio(buff, size);
//	}
//	pipe(audioPipeBlue);
//	pipe(audioPipeHead);
//	pthread_create(&audioThread, NULL, handleBluetoothSender, NULL);
	pthread_create(&playAudioThread,NULL, handleBluetoothReceiver, NULL);
//	pthread_create(&bluetoothThreadS, NULL, handleBluetoothSender, NULL);
//	pthread_create(&bluetoothThreadR, NULL, handleBluetoothReceiver, NULL);
//	pthread_create(&bluetoothThread, NULL, handleBluetooth, NULL);
	pthread_exit(NULL);
}
