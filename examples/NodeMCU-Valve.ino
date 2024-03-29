#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

// D7 = Relay

/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "SSID"; // Name of your network
const char* password = "PASSWORD"; // Password for your network
const String relay = "HIGH"; // Relay type (`HIGH` or `LOW`)
const char* mdns = "valve"; // mDNS name
//////////////////////////////////////////////////////////////

const int relayPin = 13;
int state = 0;

int relayOn, relayOff;

ESP8266WebServer server(80);

void setup() {
  if (relay.equals("LOW")) {
    relayOn = 0;
    relayOff = 1;
  } else {
    relayOn = 1;
    relayOff = 0;
  }

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayOff);

  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to \"" + String(ssid) + "\"");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(String(++i) + " ");
  }
  Serial.println();
  Serial.println("Connected successfully");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(mdns)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS address: " + String(mdns) + ".local");

  server.on("/setState", []() {
    state = server.arg("value").toInt();
    if (state) {
      digitalWrite(relayPin, relayOn);
    } else {
      digitalWrite(relayPin, relayOff);
    }
    server.send(200);
  });

  server.on("/status", []() {
    size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    doc["currentState"] = state;

    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
  });

  // Start the server
  server.begin();
}

//Main loop
void loop() {
  server.handleClient();
  MDNS.update();
}
