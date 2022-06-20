#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "FS.h"
#endif

// Replace with your network credentials
const char* ssid = "AndroidAPRicardo";
const char* password = "oqkg9662";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>ESP Image Web Server</h2>
  <img src="cat">
  <img src="cat2">
</body>  
</html>)rawliteral";


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/cat", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/cat.jpeg", "image/jpeg");
  });
  server.on("/cat2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/cat2.jpg", "image/jpg");
  });
  // Start server
  server.begin();
}
 
void loop(){
  
}
