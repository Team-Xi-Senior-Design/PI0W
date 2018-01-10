#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "gui.h"

#define  USER_NAME_MAX 10

#define  WIN_HIGHT     20
#define  WIN_WIDTH     50

#define  SPEED_Y       17
#define  SPEED_X       23

#define  RPM_Y         18
#define  RPM_X         22

#define  FUEL_Y        17 
#define  FUEL_X        40

#define  PACK_Y        0
#define  PACK_X        22
    
#define  ROOM_Y        1
#define  ROOM_X        23

#define  USERS_Y_START 6
#define  USERS_X       40

static uint8_t  micOpen = 1;

static uint8_t  mute    = 0;
WINDOW *win;

void createMainDisp(){
	initscr();
	win = newwin(WIN_HIGHT,WIN_WIDTH,0,0);
	//bkrgrnd(COLOR_WHITE);
	curs_set(0);
	wborder(win, ACS_VLINE,ACS_VLINE, ACS_HLINE,ACS_HLINE,ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	refresh();
}
void dispSpeedMph(const int32_t speedKph){
	int speedMph;
	//convets form kphto mph
	speedMph = (speedKph * 0.621);
	char speedBuff[7];
	sprintf(speedBuff,"%d Mph",speedMph);
	mvwprintw(win,SPEED_Y,SPEED_X,speedBuff);
	wrefresh(win);
	
}

void dispSpeedKph(const int32_t speedKph){
	char speedBuff[7];
	sprintf(speedBuff,"%d Kph",speedKph);
	mvwprintw(win,SPEED_Y,SPEED_X,speedBuff);
	wrefresh(win);
}

void dispFuelLevel(const int32_t levelPersent){
	char persentBuff[7];
	sprintf(persentBuff,"%d%s",levelPersent,"%%");
	mvwprintw(win,FUEL_Y,FUEL_X,persentBuff);
	wrefresh(win);
}

void dispRpm(const int32_t rpm){
	char rpmBuff[9];
	sprintf(rpmBuff,"%d RPM",rpm);
	mvwprintw(win,RPM_Y,RPM_X,rpmBuff);
	wrefresh(win);
}

void dispPackName(const char* packName){
	if(packName!=NULL){
		mvwprintw(win,PACK_Y,PACK_X,packName);
		wrefresh(win);
	}
}
void dispChatRoomName(const char* roomName){
	if(roomName!=NULL){
		mvwprintw(win,ROOM_Y,ROOM_X,roomName);
		wrefresh(win);
	}
}

void dispRoomMembers(char** roomMembers,const int numbMembers){
	if(roomMembers!=NULL){
		for (int i = 0; i< numbMembers;i++){
			if (numbMembers<(FUEL_Y - USERS_Y_START)){
				mvwprintw(win,USERS_Y_START+i,USERS_X,roomMembers[i]);
				wrefresh(win);
			}
		}
	}
}

void setMicIcon(const uint8_t micState){

}

void setSpkrMuteIcon(const uint8_t spkrState){

}
