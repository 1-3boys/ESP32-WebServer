#include <WiFi.h>
#include <WebServer.h>

#define RXD2 16
#define TXD2 17

const char *ssid = "suw0n";
const char *password = "";

WebServer server(80);

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

const char open_door_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Door Opened - &#128522;</h1>
</center>
</body>
</html>
)rawliteral";

const char close_door_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Door Closed - &#128522;</h1>
</center>
</body>
</html>
)rawliteral";

void healthCheck() {
  server.send(200, "text/html", index_html);
}

int openDoorSerialCommand = 1;
void openDoor() {
  Serial2.write(openDoorSerialCommand);
  Serial.println("open door serial command sended");
  server.send(200, "text/html", open_door_html);
}

int closeDoorSerialCommand = 1;
void closeDoor() {
  Serial2.write(closeDoorSerialCommand);
  Serial.println("close door serial command sended");
  server.send(200, "text/html", close_door_html);
}

void InitWebServer() {
  server.on("/", HTTP_GET, healthCheck);
  server.on("/open", HTTP_POST, openDoor);
  server.on("/close", HTTP_POST, closeDoor);

  server.begin();
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Waiting");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
    
  Serial.print("WiFi IP: ");
  Serial.println(WiFi.localIP());

  InitWebServer(); 
    
  Serial.println("HTTP Server Started");
  delay(100); 
}

void loop() {
  server.handleClient();
}
