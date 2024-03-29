//Works for newer versions of Blynk or BLYNK2.0 only. 
//May encounter some issues uf you using NodeMCU esp8266, contact me for troubleshooting in this one or use Primary Code v1/v2

#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Blynk authentication token
char auth[] = "YourAuthToken";

// Pin definitions
const int DHT_PIN = D3;
const int MQ7_PIN = A0;
const int LDR_PIN = D0;
const int BUZZER_PIN = D5;

// Display constants
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;
const int SCREEN_ADDRESS = 0x3C;

// DHT sensor setup
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// OLED display setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables for sensor readings
float temperature = 0;
float humidity = 0;
int mq7Value = 0;
int ldrValue = 0;

// Initialize Blynk timer
BlynkTimer timer;

// Function prototypes
void sendSensorData();

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize Blynk
  Blynk.begin(auth, WiFi);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  // Set up Blynk timer for sending sensor data
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  // Run Blynk tasks
  Blynk.run();
  // Run Blynk timer
  timer.run();
}

void sendSensorData() {
  // Read temperature and humidity from DHT sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Read values from MQ7 sensor and LDR
  mq7Value = analogRead(MQ7_PIN);
  ldrValue = analogRead(LDR_PIN);

  // Update OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temp: ");
  display.println(temperature);
  display.print("Humidity: ");
  display.println(humidity);
  display.print("MQ7 Value: ");
  display.println(mq7Value);
  display.print("Light Intensity: ");
  display.println(ldrValue);
  display.display();

  // Send sensor data to Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, mq7Value);
  Blynk.virtualWrite(V3, ldrValue);

  // Check for abnormal sensor readings and trigger notifications
  if (temperature > 30) {
    Blynk.notify("High Temperature Detected!");
  }
  if (ldrValue == 1023) {
    Blynk.notify("Low Light Intensity Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
  if (mq7Value > 550) {
    Blynk.notify("High Pollution Level Detected!");
  }
  if (humidity > 70) {
    Blynk.notify("High Humidity Detected!");
  }
}
