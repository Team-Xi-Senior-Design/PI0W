#include <cairo/cairo.h>
#include <stdint.h>
#include "main.h"


static uint8_t  micOpen;

static uint8_t  mute;

//cairo_surface_t *mainSurface;

//cairo_t *mainDisp;

void createMainDisp();

void dispSpeedMph(const int32_t speedKph);

void dispSpeedKph(const int32_t speedKph);

void dispFuelLevel(const int32_t levelPersent);

void dispRpm(const int32_t rpm);

void dispPackName(const char* packname);

void dispChatRoomName(const char* roomName);

void dispRoomMembers(char** roomMembers, const int numbMembers);

void setMicIcon(const uint8_t micState);

void setSpkrMuteIcon(const uint8_t spkrState);
