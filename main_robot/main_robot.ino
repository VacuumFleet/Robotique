/* main_robot.ino
 *
 * This file is part of the Epitech Msc2 2023 ESP project.
 * This is the sketch file for the main robot. It handles all the robot logic, wifi configuration as well as movement
 */

#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include "wifi.h"
#include "movement.h"

SoftwareSerial Serial1(12, 13); // RX, TX
String serial = "8488B";
String name = "robot-8488B";

void setup()
{
  Serial.begin(115200); // initialize serial for debugging

  Serial1.begin(9600); // initialize serial for ESP module

  setup_movement();

  init_wifi(&Serial1);
  setup_ap(name, "123456789", &Serial1);
  start_server(8080, &Serial1, serial, name);

  query_url("192.168.1.42", 8000, "/docs", &Serial1);

  Serial.println("Setup done");
}

void loop()
{
  movement_tick();
}
