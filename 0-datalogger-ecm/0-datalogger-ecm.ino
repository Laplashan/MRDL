#include "arduino_secrets.h"
#include "thingProperties.h"
#include <SoftwareSerial.h>

// Comunicación serial con Arduino Uno
SoftwareSerial swSer(D5, D4); // D5 = RX, D4 = TX

String incomingData = "";
float elapsed;

void setup() {
  Serial.begin(9600);
  swSer.begin(9600);

  WiFi_Start();
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void WiFi_Start() {
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoCloud.update();

  while (swSer.available()) {
    char c = swSer.read();
    if (c == '\n') {
      parseData(incomingData);
      incomingData = "";
    } else {
      incomingData += c;
    }
  }
}

void parseData(String data) {
  // Separar por comas
  int p1 = data.indexOf(',');
  int p2 = data.indexOf(',', p1 + 1);
  int p3 = data.indexOf(',', p2 + 1);
  int p4 = data.indexOf(',', p3 + 1);

  if (p1 > 0 && p2 > p1 && p3 > p2 && p4 > p3) {
    String timeStr = data.substring(0, p1);
    String rpmEngStr = data.substring(p1 + 1, p2);
    String rpmGbxStr = data.substring(p2 + 1, p3);
    String latStr = data.substring(p3 + 1, p4);
    String lngStr = data.substring(p4 + 1);

    // Convertir a valores
    elapsed = timeStr.toFloat();
    rpm_eng = rpmEngStr.toFloat();
    rpm_gbx = rpmGbxStr.toFloat();
    latitude = latStr.toFloat();
    longitude = lngStr.toFloat();

    
    gpsLocation = {latStr.toFloat(), lngStr.toFloat()}; // Actualiza el mapa


    // Mostrar en consola
    Serial.print("Tiempo: "); Serial.print(elapsed);
    Serial.print(" ms, RPM Motor: "); Serial.print(rpm_eng);
    Serial.print(", RPM Gearbox: "); Serial.print(rpm_gbx);
    Serial.print(", Lat: "); Serial.print(latitude);
    Serial.print(", Lng: "); Serial.println(longitude);
  }
}