// config Lolin32 with connected epd 213 Z98c
// cable like waveshare32

//WiFi-definition and website for image
#define mySSID "mySSID"
#define myPASSWORD "myPASS"
#define IMG_URL "http://192.168.x.y/<path>/screen.php"

//hardware-definition Lolin32
//#define EPD_USE_FSPI                 // use FSPI instead of HSPI
#define EPD_BUSY 25                    // BUSY
#define EPD_CS   15                    // SS / CS
#define EPD_RST  26                    // RST
#define EPD_DC   27                    // DC
#define EPD_SCK  13                    // CLK /SCLK
#define EPD_MISO -1                    // Master-In Slave-OutMISO not needed
#define EPD_MOSI 14                    // DIN / MOSI

//hardware specific - if not used -> disable it
#define EPD_LED -22                    // BUILTIN_LED / negative for inverted output
//#define EPD_PWR 12  // only Waveshare EPD-Hat need a High-Level at PWR (9 Pin Cable)
//#define EPD_BATTERY 35                 // measure battery voltage

#define EPD_BAT_DIVIDER 5800           // Divider for calculation of battery voltage

#define EPD_SLEEP   3600               // standard-time for deepsleep, if not changed by webserver
#define EPD_Rotation 3                 // Rotation for landscape-mode

//define display
#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
#define GxEPD2_DRIVER_CLASS GxEPD2_213_Z98c // GDEY0213Z98c 122x250, SSD1680

//define colors and substitutes for red and yellow
#define EPD_WHITE GxEPD_WHITE
#define EPD_BLACK GxEPD_BLACK
#define EPD_COLOR1 GxEPD_RED           // second Color (mostly red)
#define EPD_COLOR2 GxEPD_WHITE         // third Color (mostly yellow)
