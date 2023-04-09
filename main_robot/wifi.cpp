/* wifi.cpp
 *
 * This file is part of the Epitech Msc2 2023 ESP project.
 * It contains all the helper functions for the wifi module.
 */

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

  WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK, false);

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

int connect_wifi(String ssidName, String ssidPass, Stream *espSerial)
{
  char ssid[ssidName.length() + 1];
  char pass[ssidPass.length() + 1];

  ssidName.toCharArray(ssid, ssidName.length() + 1);
  ssidPass.toCharArray(pass, ssidPass.length() + 1);

  int ret = WiFi.begin(ssid, pass);
  if (ret == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
  }

  return ret;
}

void start_server(int port, Stream *espSerial)
{
  String data;

  WiFiEspServer server(port);

  server.begin();
  Serial.println("Server started");

  while (true)
  {
    WiFiEspClient client = server.available();

    if (client)
    {

      while (client.connected())
      {
        if (client.available())
        {
          char c = client.read();
          data.concat(c);

          if (data.endsWith("\r\n"))
          {
            int index = data.indexOf(',');
            String ssid = data.substring(0, index);
            String pass = data.substring(index + 1, data.length() - 2);
            Serial.print("SSID: " + ssid);
            Serial.println("PASS: " + pass);

            if (connect_wifi(ssid, pass, espSerial) == WL_CONNECTED)
            {
              client.write('OK');
              break;
            }
            else
            {
              client.write('KO');
            }
          }
        }
      }

      Serial.println("client disconnected");
      client.stop();
      break;
    }

    delay(50);
  }
}

void query_url(String host, int port, String url, Stream *espSerial)
{
  WiFiEspClient client;

  if (client.connect(host.c_str(), port))
  {
    Serial.println("connected");
    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: " + host);
    client.println("Connection: close");
    client.println();

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.print(c);
      }
    }

    Serial.println();
    Serial.println("disconnecting.");
  }
  else
  {
    Serial.println("connection failed");
  }
}