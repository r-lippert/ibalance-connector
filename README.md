# ibalance-connector
Connect the _JUDO i-balance_ limescale protection system to home automation systems via MQTT

This firmware allows an ESP8266 microcontroller to listen to the serial communication from the main controller board to the display inside the _i-balance_ device. The displayed strings are forwarded to an MQTT broker for use in a home automation system such as Home Assistant.

## Please note
_This is an independent, unofficial open-source project and is not affiliated with, endorsed by, or supported by JUDO._

_i-balance and JUDO are trademarks of their respective owners. The names are used solely to describe compatibility with the corresponding device._

_**Warning:** Manipulating electric connections inside the device may void your warranty, damage or destroy the device, or cause serious injury or death._

## How to build
I use PlatformIO and Visual Studio Code to build this firmware. The main program uses a `config.h` for configuration values. Copy the existing `config_example.h` and enter your Wifi and MQTT connection data.

## Hardware setup
Use an ESP8266 board and connect the GND pin to the brown wire of the _i-balance_ display, the software serial RX pin to the green wire.
Do NOT attempt to steal the 5V for the ESP8266 power supply from the display. It won't sustain the microcontroller. The easiest way to power the ESP8266 is an external USB power supply. You may also use a DC-DC buck converter to change the 24V supply of the _i-balance_ to 5V for the ESP8266. If you do it wrong, be prepared for blue smoke damage!
