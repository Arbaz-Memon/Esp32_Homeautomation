#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Your Ssid";
const char* password = "Your Password";

// Create a WebServer object on port 80
WebServer server(80);

// GPIO pins connected to relay modules
const int relayPin1 = 16;  // Control for Appliance 1


// HTML code to display buttons for controlling appliances
String htmlPage = "<html>\
  <head><title>ESP32 Home Automation</title></head>\
  <body>\
    <h1>ESP32 Home Automation</h1>\
    <button onclick=\"location.href='/on1'\">Turn On Appliance 1</button>\
    <button onclick=\"location.href='/off1'\">Turn Off Appliance 1</button>\
    <br><br>\
  </body>\
</html>";

// Functions to handle web requests
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleOn1() {
  digitalWrite(relayPin1, LOW);  // Turn on Appliance 1
  server.send(200, "text/html", "Appliance 1 is ON<br><a href='/'>Back</a>");
}

void handleOff1() {
  digitalWrite(relayPin1, HIGH);  // Turn off Appliance 1
  server.send(200, "text/html", "Appliance 1 is OFF<br><a href='/'>Back</a>");
}

void setup() {
  // Set up serial communication
  Serial.begin(115200);

  // Set relay pins as output and turn appliances off initially
  pinMode(relayPin1, OUTPUT);
  digitalWrite(relayPin1, HIGH);  // OFF position for relay
  

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to Wi-Fi! IP address: ");
  Serial.println(WiFi.localIP());

  // Define URL routes
  server.on("/", handleRoot);
  server.on("/on1", handleOn1);
  server.on("/off1", handleOff1);


  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
