# e-Paper image loader for ESP32

For programming of e-papers you can use a webserver at home to processing the image.
I use at this point php.
You can control the image by a browser.

There is on the epaper-device an ESP32 for showing the image.
Some header-information organize the administration information.

# Used header information
from EPD to Webserver:
"X-Battery"  : battery voltage in "V"
"X-Dim-X"    : Width in pixel
"X-DIM_Y"    : Height in pixel
from Webserver to EPD:
"X-Expire"  : seconds to predicted next contact
"Size"      : Size of gif-file

# ESP32

- ESP32
- ESP32C3
- ESP32S3
w/o PSRAM

## e-Paper Module

All module served by GxEPD2

## Build with Platform.IO

modify src/project_xxx.h
bash
cd esp32-epaper
pio run -t upload


# License

MIT License
