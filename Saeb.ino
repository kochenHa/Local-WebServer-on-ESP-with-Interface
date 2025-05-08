#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <U8g2lib.h>
#include <Wire.h>

#ifndef STASSID
#define STASSID "Your SSID"
#define STAPSK "Your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

int Status = 1;
#define ButtonPin 2

ESP8266WebServer server(80);  //port?

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const int led = 13;

const char* statusMessages[] = {
  "Säb + Svea",        // Status 1
  "Säb ohne Svea",     // Status 2
  "Vielleicht",        // Status 3
  "Nur Ficken",        // Status 4
  "Mit Philipp verheiratet",        // Status 5
  "Am WixXxen",       // Status 6
  "Am Inten",         // Status 7
  "Lost",             // Status 8
  "Mit Lukas beefen", // Status 9
  "Saufen",           // Status 10
  "Lernen",           // Status 11
  "Hannes"            // Status 12
};
const int maxStatus = sizeof(statusMessages) / sizeof(statusMessages[0]); // Anzahl der Status

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

int currentPage = 0; // Aktuelle Seite (global)
void displayStatus() {
    u8g2.clearBuffer(); // Display löschen

  // IP-Adresse anzeigen
  String myIP = WiFi.localIP().toString();
  u8g2.drawStr(0, 0, myIP.c_str());

  // Anzahl der Seiten berechnen
  int totalPages = (maxStatus + 3) / 4; // 4 Zeilen pro Seite

  // Statusmeldungen für die aktuelle Seite anzeigen
  for (int i = 0; i < 4; i++) {
    int statusIndex = currentPage * 4 + i;
    if (statusIndex >= maxStatus) break; // Keine weiteren Statusmeldungen

    String statusText = (statusIndex + 1 == Status) 
                        ? "- " + String(statusMessages[statusIndex]) 
                        : "  " + String(statusMessages[statusIndex]);
    u8g2.drawStr(0, 10 + (i * 10), statusText.c_str()); // Zeilenweise anzeigen
  }

  // Seitenanzeige unten hinzufügen
  String pageInfo = "Seite " + String(currentPage + 1) + "/" + String(totalPages);
  u8g2.drawStr(0, 54, pageInfo.c_str());

  u8g2.sendBuffer(); // Buffer an das Display senden
}

void handleRoot() {
  digitalWrite(led, 1);
  //server.send(200, "text/plain", "hello from esp8266!\r\n");
  digitalWrite(led, 0);
  switch (Status) {
    case 1:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Säb + Svea</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ffe6e6;"
                  "  font-family: Arial, sans-serif;"
                  "}"
                  "h1 {"
                  "  position: absolute;"
                  "  top: 10%;"
                  "  font-size: 3rem;"
                  "  color: #ff3366;"
                  "}"
                  ".heart {"
                  "  width: 200px;"
                  "  height: 200px;"
                  "  background-color: #ff3366;"
                  "  position: relative;"
                  "  transform: rotate(-45deg);"
                  "}"
                  ".heart::before,"
                  ".heart::after {"
                  "  content: \"\";"
                  "  width: 200px;"
                  "  height: 200px;"
                  "  background-color: #ff3366;"
                  "  border-radius: 50%;"
                  "  position: absolute;"
                  "}"
                  ".heart::before {"
                  "  top: -100px;"
                  "  left: 0;"
                  "}"
                  ".heart::after {"
                  "  left: 100px;"
                  "  top: 0;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "<h1>Säb + Svea</h1>"
                  "<div class=\"heart\"></div>"
                  "</body>"
                  "</html>");
      break;

    case 2:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Gebrochenes Herz</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #f2f2f2;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #ff3366;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "&#128148; <!-- Unicode für gebrochenes Herz -->"
                  "</body>"
                  "</html>");
      break;
    case 3:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Vielleicht</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #e6f7ff;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #007acc;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Vielleicht"
                  "</body>"
                  "</html>");
      break;
    case 4:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Nur Ficken</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ffe6cc;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #cc6600;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Nur Ficken"
                  "</body>"
                  "</html>");

      break;
    case 5:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Mit Philipp verheiratet</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #e6ffe6;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #33cc33;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Mit Philipp verheiratet"
                  "</body>"
                  "</html>");
      break;
    case 6:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Am WixXxen</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ffccff;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #990099;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "&#128166; &#127814;"  // Wassertropfen und Aubergine
                  "</body>"
                  "</html>");
      break;
    case 7:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Am Inten</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ccffff;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #006666;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Am Inten"
                  "</body>"
                  "</html>");
      break;
    case 8:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Lost</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #f2f2f2;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 3rem;"
                  "  color: #808080;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Lost"
                  "</body>"
                  "</html>");
      break;
    case 9:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Mit Lukas beefen</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ffcccc;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 10rem;"
                  "  color: #cc0000;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "Mit Lukas beefen"
                  "</body>"
                  "</html>");
      break;
    case 10:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Saufen</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #ffffcc;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 10rem;"
                  "  color: #ffcc00;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "&#127866;"  // Bier Emoji
                  "</body>"
                  "</html>");
      break;
    case 11:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Lernen</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: #e6f7ff;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 10rem;"
                  "  color: #007acc;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "&#128218;"  // Buch Emoji
                  "</body>"
                  "</html>");
      break;
          case 12:
      server.send(200, "text/html",
                  "<!DOCTYPE html>"
                  "<html lang=\"de\">"
                  "<head>"
                  "<meta charset=\"UTF-8\">"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<title>Lernen</title>"
                  "<style>"
                  "body {"
                  "  display: flex;"
                  "  justify-content: center;"
                  "  align-items: center;"
                  "  height: 100vh;"
                  "  margin: 0;"
                  "  background-color: ##2d2b9e;"
                  "  font-family: Arial, sans-serif;"
                  "  font-size: 12rem;"
                  "  color: ##2f9e2b;"
                  "}"
                  "</style>"
                  "</head>"
                  "<body>"
                  "HANNES ist der beste"  // Buch Emoji
                  "</body>"
                  "</html>");
      break;
  }
}



void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();

  displayStatus();

  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  u8g2.clearBuffer();  //print IP on screen
  u8g2_prepare();
  String myIP = WiFi.localIP().toString();
  u8g2.drawStr(0, 0, myIP.c_str());
  u8g2.sendBuffer();


  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  /////////////////////////////////////////////////////////
  // Hook examples

  server.addHook([](const String& method, const String& url, WiFiClient* client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method;       // GET, PUT, ...
    (void)url;          // example: /root/myfile.html
    (void)client;       // the webserver tcp client connection
    (void)contentType;  // contentType(".html") => "text/html"
    Serial.printf("A useless web hook has passed\n");
    Serial.printf("(this hook is in 0x%08x area (401x=IRAM 402x=FLASH))\n", esp_get_program_counter());
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String& url, WiFiClient*, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/fail")) {
      Serial.printf("An always failing web hook has been triggered\n");
      return ESP8266WebServer::CLIENT_MUST_STOP;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String& url, WiFiClient* client, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/dump")) {
      Serial.printf("The dumper web hook is on the run\n");

      // Here the request is not interpreted, so we cannot for sure
      // swallow the exact amount matching the full request+content,
      // hence the tcp connection cannot be handled anymore by the
      // webserver.
#ifdef STREAMSEND_API
      // we are lucky
      client->sendAll(Serial, 500);
#else
      auto last = millis();
      while ((millis() - last) < 500) {
        char buf[32];
        size_t len = client->read((uint8_t*)buf, sizeof(buf));
        if (len > 0) {
          Serial.printf("(<%d> chars)", (int)len);
          Serial.write(buf, len);
          last = millis();
        }
      }
#endif
      // Two choices: return MUST STOP and webserver will close it
      //                       (we already have the example with '/fail' hook)
      // or                  IS GIVEN and webserver will forget it
      // trying with IS GIVEN and storing it on a dumb WiFiClient.
      // check the client connection: it should not immediately be closed
      // (make another '/dump' one to close the first)
      Serial.printf("\nTelling server to forget this connection\n");
      static WiFiClient forgetme = *client;  // stop previous one if present and transfer client refcounter
      return ESP8266WebServer::CLIENT_IS_GIVEN;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  // Hook examples
  /////////////////////////////////////////////////////////

  server.begin();
  Serial.println("HTTP server started");
}

bool lastButtonState = HIGH;
bool currentButtonState;

void loop(void) {
  server.handleClient();
  MDNS.update();
  
  currentButtonState = digitalRead(ButtonPin);

  // Flankenerkennung: Prüfen, ob der Taster gedrückt wurde
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Status++; // Status erhöhen
    if (Status > 12) {
      Status = 1; // Rollover zu 1
    }
    Serial.print("Status aktualisiert: ");
    Serial.println(Status);

    // Seite basierend auf dem Status berechnen
    currentPage = (Status - 1) / 4;
    // Aktualisiere die Anzeige auf dem Display
    displayStatus();
    delay(100);
  }

  lastButtonState = currentButtonState; // Aktuellen Zustand speichern





  // Prüfen, ob Daten im seriellen Puffer verfügbar sind
  /*
  if (Serial.available() > 0) {
    int newStatus = Serial.parseInt();      // Neue Eingabe lesen
    if (newStatus > 0 && newStatus <= 11) {  // Optional: Gültigkeitsprüfung
      Status = newStatus;                   // Status nur aktualisieren, wenn Eingabe gültig ist
      Serial.print("Status aktualisiert: ");
      Serial.println(Status);
    } else {
      Serial.println("Ungültige Eingabe. Bitte eine Zahl zwischen 0 und 4 eingeben.");
    }
  }*/
}
