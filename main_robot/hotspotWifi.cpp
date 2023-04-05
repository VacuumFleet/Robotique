#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>

/*
  WiFiEsp example: WebServerAP

  A simple web server that shows the value of the analog input
  pins via a web page using an ESP8266 module.
  This sketch will start an access point and print the IP address of your
  ESP8266 module to the Serial monitor. From there, you can open
  that address in a web browser to display the web page.
  The web page will be automatically refreshed each 20 seconds.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

int status = WL_IDLE_STATUS; // the Wifi radio's status
int reqCount = 0;            // number of requests received

WiFiEspServer server(80);

// use a ring buffer to increase speed and reduce memory allocation
RingBuffer buf(8);

void setupHotspot(String ssidName, String ssidPassword, Stream *espSerial)
{
  WiFi.init(espSerial); // initialize ESP module

  char ssid[ssidName.length() + 1];
  char pass[ssidPassword.length() + 1];

  ssidName.toCharArray(ssid, ssidName.length() + 1);
  ssidPassword.toCharArray(pass, ssidPassword.length() + 1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true)
      ; // don't continue
  }

  // uncomment these two lines if you want to set the IP address of the AP
  // IPAddress localIp(192, 168, 111, 111);
  // WiFi.configAP(localIp);

  // start access point
  status = WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);
  // status = WiFi.begin("Livebox-5840", "swept0-security-quotation-rocker");
  Serial.println("Access point started");

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, connect to ");
  Serial.print(ssid);
  Serial.print(" and open a browser to http://");
  Serial.println(ip);
  Serial.println();

  // start the web server on port 80
  server.begin();
  Serial.println("Server started");
}

void sendHttpResponse(WiFiEspClient client)
{
  client.print(
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html\r\n"
      "Connection: close\r\n" // the connection will be closed after completion of the response
      "Refresh: 20\r\n"       // refresh the page automatically every 20 sec
      "\r\n");
  client.print("<!DOCTYPE HTML>\r\n");
  client.print("<html>\r\n");
  client.print("<h1>Hello World!</h1>\r\n");
  client.print("Requests received: ");
  client.print(++reqCount);
  client.print("<br>\r\n");
  client.print("Analog input A0: ");
  client.print(analogRead(0));
  client.print("<br>\r\n");
  client.print("</html>\r\n");
}

void srvLoop()
{
  WiFiEspClient client = server.available(); // listen for incoming clients

  if (client)
  {                               // if you get a client,
    Serial.println("New client"); // print a message out the serial port
    buf.init();                   // initialize the circular buffer
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        buf.push(c);            // push it to the ring buffer

        // you got two newline characters in a row
        // that's the end of the HTTP request, so send a response
        if (buf.endsWith("\r\n\r\n"))
        {
          Serial.print("Sending response to client...");
          sendHttpResponse(client);
          break;
        }
      }
    }

    // give the web browser time to receive the data
    delay(10);

    // close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
