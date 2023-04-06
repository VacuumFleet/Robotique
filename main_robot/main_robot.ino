#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include "lib/wifi.h"
#include "lib/movement.h"

SoftwareSerial Serial1(12, 13); // RX, TX

char bluetooth_tick()
{
  char data = 0;
  if (Serial.available() > 0)
  {
    data = Serial.read();
  }

  return data;
}

void setup()
{
  Serial.begin(115200); // initialize serial for debugging

  Serial1.begin(9600); // initialize serial for ESP module

  setup_movement();

  init_wifi(&Serial1);

  Serial.println("Setup done");
}

void loop()
{
}
