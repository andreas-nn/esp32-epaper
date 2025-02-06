//config.h

//#include "project_lolin_213c.h"
#include "project_wf_290.h"
//#include "project_azsmz_290.h"
//#include "project_t7_15_75.h"

// GxEPD2-main definition
#define MAX_DISPLAY_BUFFER_SIZE 65536ul // e.g.

//make display
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
#define GxEPD_CLASS GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)>
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> disp(GxEPD2_DRIVER_CLASS(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)); // Waveshare ESP32 Driver Board
