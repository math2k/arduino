#include <WiFi.h>
#include <WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "xxx";  // Enter SSID here
const char* password = "xxx";  //Enter Password here

WebServer server(80);

// GPIO2, pin 4
const int relay = 2;

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, 0);
  
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  
  server.on("/open",[]() {
    Serial.println("Opening...");
    digitalWrite(relay, 1);
    delay(2000);
    digitalWrite(relay, 0);

    server.send(200, "text/plain", "garage is opening");
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  Serial.println("/");
  server.send(200, "text/html", ":)"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
