#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//Auther:Quwan Powell
//Purpose of code: The ESP32 connects to a Wi-Fi network and serves a webpage that displays the current
// temperature and humidity values retrieved from the sensor. The project uses the ESPAsyncWebServer library to host the webpage


const char *ssid = "Distributel11626";
const char *password = "6y74xxzbqz9x";

// Create an instance of the SHT31 sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// Create an instance of the server
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 


  // Initialize the sensor
  if (!sht31.begin(0x44)) {
    Serial.println("Couldn't find SHT31 sensor");
    while (1);
  }

  // Serve a web page with sensor data
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();
    
    String html = "<html><body><h1>Temperature: " + String(temperature) + " °C</h1><h1>Humidity: " + String(humidity) + " %</h1></body></html>";
    request->send(200, "text/html", html);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing to do here
}
