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

#define MONITOR_WIDTH 127
#define MONITOR_HEIGHT 116

int main(int argc, char* argv[]){
//	printf("Hello\n");
	initscr();
	int i = 1;
	while(i<=MONITOR_HEIGHT){
		printw("%i\n", i);
		i++;
		refresh();
	}
	getch();

	endwin();
	return 0;
}
