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

int main(int argc, char* argv[]){
//	printf("Hello\n");
	initscr();
	addstr("Hello World");
	refresh();
	getch();

	endwin();
	return 0;
}
