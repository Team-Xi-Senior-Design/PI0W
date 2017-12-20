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
#include <ncurses.h>
#include <stdio.h>
#include "Bluetooth_Pi3.h"

#define MONITOR_WIDTH 127
#define MONITOR_HEIGHT 116

int main(int argc, char* argv[]){
	initscr();
	initBluetooth_Pi3();
	int size;
	char dataBoi[256];

	while(1){
		size = 0;
		size = getAudio(dataBoi, 255);
		dataBoi[size] = 0;
		printf("%s",dataBoi);
		refresh();
	}

	closeBluetooth_Pi0W();
	endwin();
	return 0;
}
