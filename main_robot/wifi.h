/* wifi.h
 *
 * This file is part of the Epitech Msc2 2023 ESP project.
 *
 */

void init_wifi(Stream *espSerial);
void setup_ap(String ssidName, String ssidPass, Stream *espSerial);
void connect_wifi(String ssidName, String ssidPass, Stream *espSerial);
void start_server(int port, Stream *espSerial);
void query_url(String host, int port, String url, Stream *espSerial);
