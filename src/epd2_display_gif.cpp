// E-Paper for download and display GIF-file
//
// restrictions by the GIF-decoder:
// GIF-File must have:
// GIF89 - format (set it with transparency)
// almost 3 colors (i.e. set it with a dot with light gray)
// the GIF-palette should be: white,black,red,yellow
// the content of the palette will be ignored. 
//
// The program download it from a given http-server.
// The file can be created on the fly with php
// For the communication of parameters will be used the headers

#include <Arduino.h>
#include <GIFDecoder.h>

#include <GxEPD2.h>
#include "epd3c/GxEPD2_213_Z98c.h"  // 2.13" b/w/r 250x128
#include "GxEPD2.h"
#include "GxEPD2_EPD.h"
#include "GxEPD2_BW.h"
#include "GxEPD2_3C.h"
#include "GxEPD2_4C.h"
#include "GxEPD2_7C.h"

#include "config.h"

#include <HTTPClient.h>
#include <WiFi.h>

#include "hardware.h"
#define LOG Serial

// use Struct from GxEPD2 declared as GxEPD
#define GxEPD_Class GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)>

struct PixelWriter {
    PixelWriter(GxEPD_Class *d) : display(d) {};
    GxEPD_Class *display;
    int width, height, pos;
    void setSize(uint16_t w, uint16_t h) {
      width = w;
      height = h;
      pos = 0;
    }
    void setPalette(uint8_t c, uint8_t r, uint8_t g, uint8_t b) {}
    void writePixel(uint8_t c) {
      //Colors as in order of gif-palette
      uint16_t p[] = {GxEPD_WHITE, GxEPD_BLACK, EPD_COLOR1, EPD_COLOR2, GxEPD_WHITE};
      display->drawPixel(pos % width, pos / width, p[c % 5]);
      pos++;
    }
};

struct ByteReader {
    WiFiClient *stream;
    int size;
    ByteReader(WiFiClient *s, int sz) : stream(s), size(sz) {}
    bool eof() { return size <= 0; }
    uint8_t readByte() {
    int l;
    while (size > 0 && ((l = stream->available()) || stream->connected())) {
      if (l == 0) {
        delay(1);
        continue;
        }
      size--;
      return stream->read();
      }
    size = 0;  // set eof
    return 0;
    }
};

void loadBitmap(GxEPD_Class *display, WiFiClient *stream, int size) {
    int l, p = 0;
    int16_t x = 0, y = 0;
    while (((l = stream->available()) || stream->connected()) && p < size) {
      if (l == 0) {
        delay(1);
        continue;
      }
    int b = stream->read();
    p++;
    if (p <= 0x36 + 4 * 2) {
      continue;
    }
    for (int i = 0; i < 8; i++) {
      if (((b << i) & 0x80) == 0) {
        display->drawPixel(x, y, GxEPD_BLACK);
      } else {
        display->drawPixel(x, y, GxEPD_WHITE);
      }
      x++;
      if (x >= 800) {
        x = 0;
        y++;
        }
      }
    }

    LOG.print("Received: ");
    LOG.println(p);
}

void loadGif(GxEPD_Class *display, WiFiClient *stream, int size) {
    ByteReader reader(stream, size);
    PixelWriter writer(display);

    auto decoder = new GIFDecoder<ByteReader, PixelWriter>(reader, writer);
    decoder->decode();
    delete decoder;
}

int loadImage(GxEPD_Class *display) {

    //measure battery voltage and put it to the headers
    float bat=0.0;
#if defined(EPD_BATTERY)
    bat = read_battery_voltage(EPD_BATTERY);
#endif

    // prepare width and height by EPD-Rotation
    uint16_t epd_x,epd_y;
    uint16_t expire = EPD_SLEEP;               //standard-time for deepsleep
    if (EPD_Rotation%2 == 0)
      {epd_x = disp.epd2.WIDTH;epd_y = disp.epd2.HEIGHT;}
    else
      {epd_x = disp.epd2.HEIGHT;epd_y = disp.epd2.WIDTH;}
    //open http-connection
    HTTPClient *client = new HTTPClient();
    client->begin(IMG_URL);
    LOG.println(IMG_URL);
  
    //send the parameter to the webserver
    client->addHeader("X-Battery",String(bat));
    client->addHeader("X-DimX",String(epd_x));
    client->addHeader("X-DimY",String(epd_y));
    LOG.println(">> sent headers:");
    LOG.print("X-Battery: ");LOG.println(bat);
    LOG.print("X-DimX: ");LOG.println(epd_x);
    LOG.print("X-DimY: ");LOG.println(epd_y);
    //get headers from webserver
    const char *headerKeys[] = {"X-Expire"};
    //get time to wait after start deepsleep
    client->collectHeaders(headerKeys, 1);
    long startTime = millis();
    uint16_t http_state = client->GET();
    LOG.println("Retrieve file from webserver");
    LOG.print("http-state: ");LOG.println(http_state);
    if (http_state == 200) {
    //try to decode gif only, if found
    WiFiClient *stream = client->getStreamPtr();
    int size = client->getSize();
    LOG.println("<< received headers:");
    LOG.print("FileSize: ");LOG.println(size);
    expire = client->header("X-Expire").toInt();
    LOG.print("X-Expire: ");LOG.println(expire);

    loadGif(display, stream, size);
    delete client;

    // disable wifi ASAP
    WiFi.enableSTA(false);
    display->display();
    LOG.println("Display updated");
    } else {
    LOG.println("GIF-Image not found!");
    }
    long elapsedTime = (int)((millis() - startTime) / 1000);
    return expire == 0 ? 300 : constrain(expire - elapsedTime, 5, 86400);
}

void setup() {
    LOG.begin(115200);
//  delay(3000);  // for testing
#if defined(EPD_LED)
    set_builtin_led(EPD_LED,true);
#endif

    // Wait for connection
    WiFi.begin(mySSID, myPASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      LOG.print(".");
    }

    LOG.println("");
    LOG.print("Connected to ");
    LOG.println(mySSID);
    LOG.print("my IP address: ");
    LOG.println(WiFi.localIP());

    //activate SPI with given pins
#if defined(EPD_USE_FSPI)
    SPIClass spi(FSPI);
#else
    SPIClass spi(HSPI);
#endif
    spi.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS); // remap spi for EPD (swap pins)
    //activate display
    disp.epd2.selectSPI(spi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
 
    //use declared display and make a pointer from declared disp
    GxEPD_Class *display;
    display = &disp;

    display->init();
    display->setRotation(EPD_Rotation);
    int time_to_sleep = loadImage(display);

    if (time_to_sleep < (EPD_SLEEP /10)) time_to_sleep = EPD_SLEEP/10;  //not to fast
    if (time_to_sleep > (EPD_SLEEP *10)) time_to_sleep = EPD_SLEEP*10;  //not to slow
    esp_sleep_enable_timer_wakeup(time_to_sleep * 1000000LL);
    LOG.println(time_to_sleep);

#if defined(EPD_LED)
    set_builtin_led(EPD_LED,false);
#endif

    esp_deep_sleep_start();
}

void loop() {}
