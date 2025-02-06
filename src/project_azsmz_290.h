//project AZSMZ-board with 2.9 inch epd (2017)
// esp8266 exchanged by esp32c3 12f !!!


//WiFi-definition and website for image
#define mySSID "mySSID"
#define myPASSWORD "myPASS"
#define IMG_URL "http://192.168.x.y/<path>/screen.php"

//hardware-definition old azsmz-board modded with ESP32C3 12F
#define EPD_USE_FSPI                   // set FSPI instead of HSPI i.e. esp32c3
#define EPD_BUSY 10                    // BUSY
#define EPD_CS   7                     // SS / CS
#define EPD_RST  8                     // RST
#define EPD_DC   3                     // DC
#define EPD_SCK  4                     // CLK
#define EPD_MISO -1                    // MISO not needed
#define EPD_MOSI 6                     // DIN

//hardware specific - if not used -> disable it
//#define EPD_LED -22                  // BUILTIN_LED / negative for inverted output
//#define EPD_PWR 12                   // only Waveshare EPD-Hat need a High-Level at PWR (9 Pin Cable)
#define EPD_BATTERY 1                  // Battery-Pin (Divider 300k/100k)

#define EPD_BAT_DIVIDER 2820           // Divider for calculation of battery voltage

#define EPD_SLEEP   3600               // standard-time for deepsleep, if not changed by webserver
#define EPD_Rotation 1                 // Rotation for landscape-mode

//define display
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_290 // GDEY0213Z98c 122x250, SSD1680

//define colors and substitutes for red and yellow
#define EPD_BLACK GxEPD_BLACK
#define EPD_WHITE GxEPD_WHITE
#define EPD_COLOR1 GxEPD_BLACK
#define EPD_COLOR2 GxEPD_WHITE
