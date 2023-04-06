#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

void init_wifi(Stream *espSerial)
{
  WiFi.init(espSerial);
}

void setup_ap(String ssidName, String ssidPass, Stream *espSerial)
{
  char ssid[ssidName.length() + 1];
  char pass[ssidPass.length() + 1];

  ssidName.toCharArray(ssid, ssidName.length() + 1);
  ssidPass.toCharArray(pass, ssidPass.length() + 1);

  WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void connect_wifi(String ssidName, String ssidPass, Stream *espSerial)
{
  char ssid[ssidName.length() + 1];
  char pass[ssidPass.length() + 1];

  ssidName.toCharArray(ssid, ssidName.length() + 1);
  ssidPass.toCharArray(pass, ssidPass.length() + 1);

  WiFi.begin(ssid, pass);

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}