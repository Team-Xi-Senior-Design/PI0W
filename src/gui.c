#include <ncurses.h>
#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <wchar.h>
#include "main.h"
#include "gui.h"

#define  USER_NAME_MAX 10

#define  X_MID_POINT     24
#define  Y_MID_POINT     10

#define  WIN_HIGHT     20
#define  WIN_WIDTH     50

#define  SPEED_Y       17

#define  RPM_Y         18

#define  FUEL_Y        17 
#define  FUEL_X        40

#define  PACK_Y        0
    
#define  ROOM_Y        1

#define  USERS_Y_START 6
#define  USERS_X       40

#define LEFT_X		   17
#define LEFT_Y         10

#define RIGHT_X        31
#define RIGHT_Y        10

#define STRIGHT_X      22
#define STRIGHT_Y      8

#define SILVER_RGB  192  // all values are the same

void createMainDisp(){
	initscr();
	win = newwin(WIN_HIGHT,WIN_WIDTH,0,0);
	//bkrgrnd(COLOR_WHITE);
	start_color();
	init_pair(1, COLOR_WHITE,  COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	curs_set(0);
//	wborder(win, ACS_VLINE,ACS_VLINE, ACS_HLINE,ACS_HLINE,ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	//keypad()
	refresh();
}
void dispSpeedMph(const int32_t speedKph){
	int speedMph;
	//convets form kphto mph
	speedMph = (speedKph * 0.621);
	char speedBuff[10];
	sprintf(speedBuff,"%d Mph",speedMph);
	mvwprintw(win,SPEED_Y,20,"           ");
	int xCord = calcCentered(speedBuff);
	mvwprintw(win,SPEED_Y,xCord,speedBuff);
	wrefresh(win);
	
}

void dispSpeedKph(const int32_t speedKph){
	char speedBuff[10];
	sprintf(speedBuff,"%d Kph",speedKph);
	mvwprintw(win,SPEED_Y,20,"           ");
	int xCord = calcCentered(speedBuff);
	mvwprintw(win,SPEED_Y,xCord,speedBuff);
	wrefresh(win);
}

void dispFuelLevel(const int32_t levelPersent){
	char persentBuff[7];
	sprintf(persentBuff,"%d%s",levelPersent,"%%");
	mvwprintw(win,FUEL_Y,FUEL_X,"      ");
	mvwprintw(win,FUEL_Y,FUEL_X,persentBuff);
	wrefresh(win);
}

void dispRpm(const int32_t rpm){
	char rpmBuff[11];
	sprintf(rpmBuff,"%d RPM",rpm);
    int xCord = calcCentered(rpmBuff);
	mvwprintw(win,RPM_Y,20,"           ");
	mvwprintw(win,RPM_Y,xCord,rpmBuff);
	wrefresh(win);
}

void dispPackName(const char* packName){
	if(packName!=NULL){
		wmove(win,PACK_Y,0);
		wclrtoeol(win);
    	int xCord = calcCentered(packName);
		mvwprintw(win,PACK_Y,xCord,packName);
		wrefresh(win);
	}
}
void dispChatRoomName(const char* roomName){
	if(roomName!=NULL){
		wmove(win,ROOM_Y,0);
		wclrtoeol(win);
		int xCord = calcCentered(roomName);
		mvwprintw(win,ROOM_Y,xCord,roomName);
		wrefresh(win);
	}
}

void dispRoomMembers(){
	if(roomMembers!=NULL){
		for (int i = 0; i< numbMembers;i++){
			if (numbMembers<(FUEL_Y - USERS_Y_START)){
				mvwprintw(win,USERS_Y_START+(i-1),USERS_X,"            ");
				mvwprintw(win,USERS_Y_START+(i-1),USERS_X,roomMembers[i]);
			}
		}
		for (int i = (numbMembers-1); i < ((FUEL_Y - USERS_Y_START)-numbMembers); i++){
				mvwprintw(win,USERS_Y_START+i,USERS_X-1,"            ");
		}
		wrefresh(win);
	}
}

void addMember(const char* name){
	if(name != NULL){
		int length = sizeof(name);
		if(roomMembers != NULL){
			if((length!=0)&&(length<=32)){
				numbMembers++;
				roomMembers = (char**) realloc(roomMembers,sizeof(char*)*(numbMembers));
				char* newMember = (char*)malloc(length);
				strcpy(newMember,name);
				roomMembers[numbMembers-1] = newMember;
			}
		}else{
			roomMembers = (char**) malloc(sizeof(char**));
			char* newMember = (char*)malloc(length);
			numbMembers++;
			strcpy(newMember,name);
			roomMembers[0] = newMember;
		}
	}
}


void removeMember (char* member) {
	int tmpInt;
	int tmpNumb = numbMembers;
	if(member!=NULL){
		for (int i = 0; i < tmpNumb; i++){
			if (strcmp(roomMembers[i],member)==0){
				//attron(COLOR_PAIR(2));
				tmpInt = i;
				numbMembers--;
				free(roomMembers[tmpInt]);
				char** tmpList = (char**)malloc(sizeof(char*)*(tmpNumb-1));
				for(int i = 0; i < tmpNumb-1; i++){
					if (i<tmpInt){
						tmpList[i]=roomMembers[i];
					}else if (i>=tmpInt){
						tmpList[i]=roomMembers[i+1];
					}
				}
				free(roomMembers);
				roomMembers = tmpList;
				break; 
			}
		}

	}
}

void cleanUp(){
	if(roomMembers!=NULL){
		if(numbMembers!=0){
			for (int i = 0; i < numbMembers; i++){
				free(roomMembers[i]);
			}
		}
		free(roomMembers);
	}
}

void setRoomMembers(char** newRoomMembers, const int newNumbMembers){
	if(newRoomMembers != NULL){
		roomMembers = newRoomMembers;
		numbMembers = newNumbMembers;
	}
}



// void setLowFuel( char** isTalking, const uint8_t numbTalking){
// 	if (isTalking != NULL){
// 		for (int i = 0; i < numbMembers; i++){
// 			for(int j = 0; j < numbTalking; j++){
// 				if (strcmp(isTalking[j],roomMembers[i])==0){
// 				//attron(COLOR_PAIR(2));
// 					mvwaddch(win,USERS_Y_START+i,USERS_X-1,ACS_BULLET);
// 					break;
// 				////	attroff(COLOR_PAIR(2));
// 				}else{
// 				///	attron(COLOR_PAIR(1));
// 					mvwaddstr(win,USERS_Y_START+i,USERS_X-1," ");
// 				///mvwaddch(win,USERS_Y_START+i,USERS_X-1,ACS_BULLET);
// 				///	attroff(COLOR_PAIR(1));
// 				}
// 			}
// 			wrefresh(win);
// 		}
// 	} else{
// 		for (int i = 0; i < numbMembers; i++){
// 			mvwaddstr(win,USERS_Y_START+i,USERS_X-1," ");
// 			wrefresh(win); 
// 		}
// 	}
// }

void setLowFuel(char* isTalking){
	if (isTalking != NULL){
		for (int i = 0; i < numbMembers; i++){
			if (strcmp(roomMembers[i],isTalking)==0){
			//attron(COLOR_PAIR(2));
				mvwaddch(win,(USERS_Y_START+i)-1,USERS_X-1,ACS_BULLET);
				break;
				////	attroff(COLOR_PAIR(2));
			}
			wrefresh(win);
		}
	}
}
void removeLowFuel(char* isTalking){
	if (isTalking != NULL){
		for (int i = 0; i < numbMembers; i++){
			if (strcmp(roomMembers[i],isTalking)==0){
			//attron(COLOR_PAIR(2));
				mvwaddstr(win,(USERS_Y_START+i)-1,USERS_X-1," ");
				break;
				////	attroff(COLOR_PAIR(2));
			}
			wrefresh(win);
		}
	}
}
void leftArrowOn(){
 
	mvwaddch(win,Y_MID_POINT  ,LEFT_X  ,0x2F);
	mvwaddch(win,Y_MID_POINT  ,LEFT_X-2,0x2F);
	mvwaddch(win,Y_MID_POINT-1,LEFT_X+1,0x2F);
	mvwaddch(win,Y_MID_POINT-1,LEFT_X-1,0x2F);

	mvwaddch(win,Y_MID_POINT,LEFT_X+1,'-');
	mvwaddch(win,Y_MID_POINT+1,LEFT_X+1,'-');

	mvwaddch(win,Y_MID_POINT,LEFT_X+2,'-');
	mvwaddch(win,Y_MID_POINT+1,LEFT_X+2,'-');

	mvwaddch(win,Y_MID_POINT+1,LEFT_X  ,0x5c);
	mvwaddch(win,Y_MID_POINT+1,LEFT_X-2,0x5c);
	mvwaddch(win,Y_MID_POINT+2,LEFT_X+1,0x5c);
	mvwaddch(win,Y_MID_POINT+2,LEFT_X-1,0x5c);
	wrefresh(win); 

}
void leftArrowOff(){
	mvwaddstr(win,Y_MID_POINT,  LEFT_X-2,"     ");
	mvwaddstr(win,Y_MID_POINT-1,LEFT_X-1,"   ");;
	mvwaddstr(win,Y_MID_POINT+1,LEFT_X-2,"     ");
	mvwaddstr(win,Y_MID_POINT+2,LEFT_X-1,"   ");
	wrefresh(win);
}
void rightArrowOn(){
	mvwaddch(win,Y_MID_POINT  ,RIGHT_X  ,0x5c);
	mvwaddch(win,Y_MID_POINT  ,RIGHT_X+2,0x5c);
	mvwaddch(win,Y_MID_POINT-1,RIGHT_X-1,0x5c);
	mvwaddch(win,Y_MID_POINT-1,RIGHT_X+1,0x5c);


	mvwaddch(win,Y_MID_POINT,RIGHT_X-1,'-');
	mvwaddch(win,Y_MID_POINT+1,RIGHT_X-1,'-');

	mvwaddch(win,Y_MID_POINT,RIGHT_X-2,'-');
	mvwaddch(win,Y_MID_POINT+1,RIGHT_X-2,'-');


	mvwaddch(win,Y_MID_POINT+1,RIGHT_X  ,0x2F);
	mvwaddch(win,Y_MID_POINT+1,RIGHT_X+2,0x2F);
	mvwaddch(win,Y_MID_POINT+2,RIGHT_X-1,0x2F);
	mvwaddch(win,Y_MID_POINT+2,RIGHT_X+1,0x2F);
	wrefresh(win);
}
void rightArrowOff(){
	mvwaddstr(win,Y_MID_POINT,RIGHT_X-3,"      ");
	mvwaddstr(win,Y_MID_POINT-1,RIGHT_X-1,"   ");;
	mvwaddstr(win,Y_MID_POINT+1,RIGHT_X-3,"      ");
	mvwaddstr(win,Y_MID_POINT+2,RIGHT_X-1,"   ");;
	wrefresh(win);
}
void strightArrowOn(){



	mvwaddch(win,STRIGHT_Y-1,X_MID_POINT-1,0x2F);
	mvwaddch(win,STRIGHT_Y,X_MID_POINT-1,0x2F);
	mvwaddch(win,STRIGHT_Y,X_MID_POINT-2,0x2F);
	mvwaddch(win,STRIGHT_Y-1,X_MID_POINT+1,0x5c);
	mvwaddch(win,STRIGHT_Y,X_MID_POINT+1,0x5c);

	mvwaddch(win,STRIGHT_Y,X_MID_POINT+2,0x5c);

	mvwaddch(win,STRIGHT_Y-2,X_MID_POINT,'^');
	mvwaddch(win,STRIGHT_Y-1,X_MID_POINT,120|A_ALTCHARSET);

    mvwaddch(win,STRIGHT_Y,X_MID_POINT,120|A_ALTCHARSET);

	mvwaddch(win,STRIGHT_Y+1,X_MID_POINT+1,120|A_ALTCHARSET);
	mvwaddch(win,STRIGHT_Y+1,X_MID_POINT,120|A_ALTCHARSET);
	mvwaddch(win,STRIGHT_Y+1,X_MID_POINT-1,120|A_ALTCHARSET);

	wrefresh(win);
}
void strightArrowOff(){

	mvwaddstr(win,STRIGHT_Y,X_MID_POINT-2,"      ");
    mvwaddstr(win,STRIGHT_Y-1,X_MID_POINT-3,"        ");
     mvwaddstr(win,STRIGHT_Y+1,X_MID_POINT-3,"        ");

	wrefresh(win);
}

	
int calcCentered(const char* str){
	int x_start;
	if(str != NULL){
		int halfLng, length;
		length = strlen(str);
		halfLng = length/2;
		x_start =  X_MID_POINT-halfLng; 
	}
	return x_start;
}

void setMicIcon(const uint8_t micState){

}

void setSpkrMuteIcon(const uint8_t spkrState){

}
void endWindow(){
	if (win!=NULL){
		curs_set(1);
    	delwin(win);
		if(roomMembers != NULL) cleanUp();
		endwin();
	}
}