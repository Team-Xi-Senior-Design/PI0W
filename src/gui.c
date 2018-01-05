#include <cairo.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "gui.h"

#define  SPEED_F_SIZE 20.0
static uint8_t  micOpen = 1;

static uint8_t  mute    = 0;
cairo_surface_t *mainSurface;
cairo_t *mainDisp;

void createMainDisp(){
	mainSurface = cairo_image_surface_create(CAIRO_FORMAT_RGB24,
						127.0,
						116.0);
	mainDisp = cairo_create(mainSurface);
}
void dispSpeedMph(const int32_t speedKph){
	
}

void dispSpeedKph(const int32_t speedKph){
	char speedBuff[7];
	sprintf(speedBuff,"%d Kph",speedKph);
	printf("%s",speedBuff);

	cairo_select_font_face(mainDisp,"Sans",
				CAIRO_FONT_SLANT_NORMAL,
				CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(mainDisp, SPEED_F_SIZE);
	cairo_move_to(mainDisp, 2.0, 40.0);
	cairo_show_text(mainDisp,"100 Kph");
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
