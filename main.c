#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Create a WebServer object
WebServer server(80);

// Define the LED pin
const int ledPin = 2;

// Function to handle root URL
void handleRoot() {
  server.send(200, "text/html", 
              "<h1>ESP32 Home Automation</h1>"
              "<p><a href=\"/on\">Turn ON LED</a></p>"
              "<p><a href=\"/off\">Turn OFF LED</a></p>");
}

// Function to turn LED on
void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "<h1>LED is ON</h1><p><a href=\"/\">Back</a></p>");
}

// Function to turn LED off
void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "<h1>LED is OFF</h1><p><a href=\"/\">Back</a></p>");
}

// Setup function
void setup() {
  Serial.begin(115200);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Make sure LED is off initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define the routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
}
