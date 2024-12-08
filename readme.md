# Home Assistant Pressure and Temperature Sensor using ESP32 and BMP280

## Installation

#### Clone this repository
'git clone www.github.com/Ogurrr/ESP32BMP280-HomeAssistant.git'

#### Build using PlatformIO
'pio run'

#### Upload to ESP32 
'pio run --upload-port (PORT)'

#### Connect sensor to ESP
Use this scheme to connect sensor <br>
BMP280 Pin	ESP32 Pin <br>
VIN&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3V <br>
GND&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;GND  <br>
SDA&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;GPIO21 <br>
SCL&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;GPIO22 <br>

