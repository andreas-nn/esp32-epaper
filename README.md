# e-Paper image loader for ESP32

For programming of e-papers you can use a webserver at home to create the image.
I use at this point php.
You can control the image by every browser.

There is on the epaper-device an ESP32 for showing the image.
Some header-information organize the administration information.

# Used header information
from EPD to Webserver:<BR>
- "X-Battery"  : battery voltage in "V"<BR>
- "X-Dim-X"    : Width in pixel<BR>
- "X-DIM_Y"    : Height in pixel<BR>

from Webserver to EPD:<BR>
- "X-Expire"  : seconds to predicted next contact<BR>
- "Size"      : Size of gif-file<BR>

# ESP32

- ESP32<BR>
- ESP32C3<BR>
- ESP32S3<BR>
for epaper > 4.2 inch you need PSRAM. Please activate it on platformi.ini<BR>

## e-Paper Module

All module served by GxEPD2

## Build with Platform.IO

modify src/project_xxx.h<BR>
bash<BR>
cd esp32-epaper<BR>
pio run -t upload<BR>


# License

MIT License
