#include <ncurses.h>
#include <stdint.h>
#include "main.h"



static char** roomMembers;

static int numbMembers;


static WINDOW *win;

//cairo_surface_t *mainSurface;

//cairo_t *mainDisp;

void createMainDisp();

void dispSpeedMph(const int32_t speedKph);

void dispSpeedKph(const int32_t speedKph);

void dispFuelLevel(const int32_t levelPersent);

void dispRpm(const int32_t rpm);

void dispPackName(const char* packname);

void dispChatRoomName(const char* roomName);

void dispRoomMembers();

void setRoomMembers(char** newRoomMembers, const int newNumbMembers);

//void setLowFuel( char** isTalking, const uint8_t numbTalking);

void setLowFuel(char* isTalking);

void removeLowFuel(char* isTalking);

void addMember(const char* name);

void removeMember(char* member);

void cleanUp();

void leftArrowOn();
void leftArrowOff();
void rightArrowOn();
void rightArrowOff();
void strightArrowOn();
void strightArrowOff();
int calcCentered(const char* str);
void setMicIcon(const uint8_t micState);

void setSpkrMuteIcon(const uint8_t spkrState);

void endWindow();

