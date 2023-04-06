#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

void setup_ap(String ssidName, String ssidPass, Stream *espSerial)
{
  WiFi.init(espSerial);

  char ssid[ssidName.length() + 1];
  char pass[ssidPass.length() + 1];

  ssidName.toCharArray(ssid, ssidName.length() + 1);
  ssidPass.toCharArray(pass, ssidPass.length() + 1);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true)
      ; // don't continue
  }

  WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);
  Serial.println("Access point started");

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}