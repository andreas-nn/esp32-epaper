# e-Paper image loader (GIF) for ESP32

For programming of e-papers, alternatively, you can use a webserver at LAN to create and serve the image.
I use at this point apache with php.<BR>
If the EPD make a call to the webserver, the file will instant been generated.<BR>
You can check the image by every browser.

There is on the epaper-device an ESP32 to put the image on th EPD.
Some header-information organize the administration information.

The original library no longer contains all current screens. That is why I changed to GxEPD2. 

# Used header information
from EPD to Webserver:<BR>
- "X-Battery"  : battery voltage in "V"<BR>
- "X-Dim-X"    : Width in pixel<BR>
- "X-DIM_Y"    : Height in pixel<BR>

from Webserver to EPD:<BR>
- "X-Expire"  : seconds to predicted next contact<BR>
- "Content-Type : "image/gif"
- "Size"      : Size of gif-file<BR>
Only the last two are necessary.

If you do not want to generate the image on the fly, you can also call a fixed gif-file

# Restrictions
The used GIF-Decoder from binzume is simple but sufficient. But there are some restrictions / solutions:
- the gif must be in GIF89 -> use transparency
- the gif must have almost 3 colors -> i.e. solve it with one dot with light gray)
- the color-palette will be ignored -> use a fixed palette with the order white,black,red,yellow,lightgray
If you don't follow these conditions, some things will happen (inverted display, no picture)

# Hardware
I have four compilations on ESP32 and EPD display
- Waveshare 32-driver board + EPD 2.9
- Lolin32 + EPD 2.13c
- Lilygo T7 V1.5 + EPD 7.5
- AZSMZ epaper board + EPD 2.9 (from 2017 - processor changed from ESP8266 to ESP32C3-12F - old, but it works)

For the Waveshare Universal e-Paper Raw Panel Driver HAT you must set the 9th pin "PWR" to high. At the config is the GPIO-definition EPD_PWR.

If the board has a controlled LED, you can serve it by EPD_LED. Negative GPIO means here an inverted output.
Unfortunately the LED at "Universal e-Paper Raw Panel Driver Board, ESP32" is constantly on. You can only cut it hard to save power.

## ESP32
Following ESP32 were tested by me:
- ESP32<BR>
- ESP32C3<BR>
for these processor, ´I have to change the SPI to fspi instead of hspi.<BR>
- ESP32S3<BR>
for epaper > 4.2 inch you need PSRAM. Please activate it on platformio.ini<BR>

## e-Paper Module
- All module supported by GxEPD2

# Build with Platform.IO
modify src/project_xxx.h<BR>
Fill in the correct GPIO-numbers for the six EPD-lines.
> bash<BR>
> cd esp32-epaper<BR>
> pio run -t upload<BR>

# License
MIT License

# Thanks
A special thank you to binzume and ZingJM for the idea and the realization with GxEPD.
