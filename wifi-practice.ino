#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char *ssid = "suw0n";
const char *password = "";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>ESP32 Simple Web Server - &#128522;</h1>
</center>
</body>
</html>
)rawliteral";
const char open_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Door Opened - &#128522;</h1>
</center>
</body>
</html>
)rawliteral";

void handleHealthCheckRequest() {
  server.send(200, "text/html", index_html);
}

void handleOpenDoorRequest() {
  server.send(200, "text/html", open_html);
}

void InitWebServer() {
  server.on("/", HTTP_GET, handleHealthCheckRequest);
  server.on("/open", HTTP_POST, handleOpenDoorRequest);

  server.begin();
}

void setup() {
  Serial.begin(115200);
  
  Serial.print("ssid : ");
  Serail.println(ssid);
  Serial.print("password : ");
  Serail.println(password);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  InitWebServer(); 
  
  Serial.print("Wifi IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("HTTP Server Started");

  delay(100); 
}

void loop() {
  server.handleClient();
}
