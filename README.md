# NSEMBED-Web-Server
_An ESP32 Web Server for Embedded Platform Development (NSEMBED)._

## Use
This project allows users to learn the morse code equivalent of three different words, NSEMBED, Bernice, and Betito. The morse code equivalent of each words are shown through the blinking LED in the ESP32 board.

## Components
1. ESP32
2. Type C Cable
3. Arduino 1.8.15
4. WiFi.h Arduino Library

## Download
Curl can be used to download the project. To download curl in Linux, use the command `sudo apt-get install curl`. To download curl in windows, check this [website](https://curl.se/windows/). Once curl is downloaded, download the project through the following commands:
* Linux:
``` sudo curl -O https://raw.githubusercontent.com/bernicebetito/NSEMBED-Web-Server/main/CODE.ino ```
* Windows:
``` curl -O https://raw.githubusercontent.com/bernicebetito/NSEMBED-Web-Server/main/CODE.ino ```

Once downloaded, the project can be used through the [Arduino Software](https://www.arduino.cc/en/software).

## Blinking Patterns
Dashes and dots have different durations in order to easily distinguish between the two:
* LED is lit up for 3 seconds for Dashes / " - "
* LED is lit up for 1 second for Dots / " . "

Before the start of any pattern, the LED would be lit up for 5 seconds to signify that the pattern will start. At the end of the pattern, the LED would be off for 5 seconds to signify that the pattern has ended.
