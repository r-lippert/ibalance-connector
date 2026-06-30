# ibalance-connector

Connect a JUDO i-balance limescale protection system to a home automation system via MQTT.

This firmware allows an ESP8266 microcontroller to passively monitor the serial communication between the main controller board and the display of an i-balance device. Text shown on the display is forwarded to an MQTT broker for use with a home automation system such as Home Assistant.

## Project status and trademarks

This is an independent, unofficial open-source project. It is not affiliated with, endorsed by, authorized by, or supported by JUDO.

The names JUDO and i-balance are used solely to identify the product with which this project is intended to interoperate. All trademarks and trade names remain the property of their respective owners.

Use of this project does not imply that the connected device, firmware version, or hardware revision is supported or approved by its manufacturer.

## Safety warning

**Working inside an electrical appliance can cause electric shock, fire, damage to property, serious injury, or death. It may also void the manufacturer's warranty.**

Disconnect the device completely from the mains supply before opening it or making any electrical connection. Do not work on the device while it is powered or connected to the mains.

Only carry out this modification if you have the necessary knowledge and qualifications to work safely on electrical and electronic equipment. Otherwise, consult a qualified professional.

Do not assume that wire colours, connector pinouts, signal levels, or supply voltages are identical across all models and hardware revisions. Verify all connections and voltages before connecting the ESP8266.

This project is intended only for passive monitoring. Do not use it for safety-related functions or as a replacement for any original protection, warning, control, or maintenance function of the device.

The project is provided without any warranty. You are responsible for assessing the suitability and safety of the hardware setup and for any modifications made to your device.

## How to build

This firmware can be built using PlatformIO, for example with Visual Studio Code.

The main program reads configuration values from `config.h`. Copy `config_example.h` to `config.h` and enter your Wi-Fi and MQTT connection details.

Do not commit `config.h` if it contains passwords or other credentials.

## Hardware setup

The current prototype uses an ESP8266 board.

For the tested hardware revision:

* Connect the ESP8266 ground to the brown display wire.
* Connect the configured software-serial RX input to the green display wire.

**Verify these connections on your own device before proceeding. Wire colours and pin assignments may differ between models or hardware revisions.**

Do not power the ESP8266 from the display's 5 V connection. In the tested device, this supply was not able to provide the current required by the microcontroller.

The safest option is to use a separate, suitable USB power supply. A properly rated and installed DC-DC converter may alternatively be used to convert the device's 24 V supply to 5 V. Verify the input voltage, output voltage, polarity, current rating, insulation requirements, and common-ground arrangement before connecting it.

Incorrect wiring or an unsuitable power supply may damage the ESP8266, the display, or the main controller board.
