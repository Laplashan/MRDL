
# Datalogger ECM
WEEMOS D1 Mini ESP3266
## Description
Captures and stores real-time data from other vehicle ECM and sensors for diagnostics and performance analysis.

## Folder Structure
- `src/` - Logging and data management code
- `tests/` - Test scripts for data integrity and performance
- `storage/` - Data formats and archival logic

## Dependencies
- ArduinoIoTCloud
- TinyGPSPlus

## Build Instructions
To build code for the ESP8266 using the Arduino IDE, follow these steps:

✅ 1. Install Arduino IDE
Download and install the latest version from arduino.cc.

✅ 2. Add ESP8266 Board Support
Open Arduino IDE.
Go to File > Preferences.
In the Additional Board Manager URLs, add:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
Click OK.
✅ 3. Install ESP8266 Board Package
Go to Tools > Board > Boards Manager.
Search for ESP8266.
Click Install on the package by ESP8266 Community.
✅ 4. Select Your ESP8266 Board
Go to Tools > Board, and choose your specific board (e.g., NodeMCU 1.0, Wemos D1 Mini, etc.).

✅ 5. Connect Your Board
Plug in your ESP8266 via USB.
Select the correct Port under Tools > Port.
✅ 6. Write or Load Your Code

## Versioning
Current version: 0.0.0
Version history is tracked via Git tags: `datalogger-ecm-vX.Y.Z`

## Contact
Ernest
    github.com/Laplashan
    ernesto.ts06@gmail.com
