//project Waveshare32 with 2.9 inch epd.h

//WiFi-definition and website for image
#define mySSID "mySSID"
#define myPASSWORD "myPASS"
#define IMG_URL "http://192.168.x.y/<path>/screen.php"

//hardware-definition waveshare32-board
//#define EPD_USE_FSPI                 // use FSPI instead of HSPI
#define EPD_BUSY 25                    // BUSY
#define EPD_CS   15                    // SS
#define EPD_RST  26                    // RST
#define EPD_DC   27                    // DC
#define EPD_SCK  13                    // CLK
#define EPD_MISO 23                    // MISO not needed
#define EPD_MOSI 14                    // DIN

//hardware specific - if not used -> disable it
#define EPD_LED 2                      // BUILTIN_LED / negative for inverted output
//#define EPD_PWR 12      // only Waveshare EPD-Hat need a High-Level at PWR (9 Pin Cable)
//#define EPD_BATTERY 35                 // measure battery voltage

#define EPD_BAT_DIVIDER 5800           // Divider for calculation of battery voltage

#define EPD_SLEEP   3600               // standard-time for deepsleep, if not changed by webserver
#define EPD_Rotation 3                 // Rotation for landscape-mode

//define display
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_290 // GDEY0213Z98c 122x250, SSD1680

//define colors and substitution for red and yellow
#define EPD_WHITE  GxEPD_WHITE
#define EPD_BLACK  GxEPD_BLACK
#define EPD_COLOR1 GxEPD_BLACK         // second Color (mostly red)
#define EPD_COLOR2 GxEPD_WHITE         // third Color (mostly yellow)
