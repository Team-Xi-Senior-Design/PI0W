#include <ncurses.h>
#include <stdtype.h>

#include <main.h>


static uint8_t  micOpen = 1;

static uint8_t  mute    = 0;

void setConfig(){
	//set cursor to invisibil
	curs_set(0);
	

}
void dispSpeedMph(const int32_t speedKph){

}

void dispSpeedKph(const int32_t speedKph){

}

void dispFuelLevel(const int32_t levelPersent){

}

void dispRpm(const int32_t rpm){

}

void dispPackName(const char* packname){

}
void dispChatRoomName(const char* roomName){

}

void dispRoomMembers(const char** roomMembers){

}

void setMicIcon(const uint8_t micState){

}

void setSpkrMuteIcon(const uint8_t spkrState){

}
