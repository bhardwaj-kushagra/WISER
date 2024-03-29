#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Constants for pin configurations
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHT_PIN D3
#define DHT_TYPE DHT11
#define MQ7_PIN A0
#define BUZZER_PIN D5
#define LDR_PIN D0
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Global variables
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED display object
DHT dht(DHT_PIN, DHT_TYPE); // DHT sensor object
float temperature = 0; // Variable to store temperature
float humidity = 0; // Variable to store humidity

void setup() {
  // Initialize components
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  pinMode(MQ7_PIN, INPUT); // Set MQ7 sensor pin as input
  pinMode(LDR_PIN, INPUT); // Set LDR sensor pin as input
  dht.begin(); // Initialize DHT sensor
  Serial.begin(115200); // Initialize serial communication

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Start OLED display
    Serial.println(F("SSD1306 allocation failed")); // Print error message if OLED allocation failed
    for (;;); // Infinite loop if allocation failed
  }
}

void loop() {
  // Read temperature and humidity
  temperature = dht.readTemperature(); // Read temperature from DHT sensor
  humidity = dht.readHumidity(); // Read humidity from DHT sensor

  // Display temperature and humidity
  display.clearDisplay(); // Clear previous display
  display.setTextSize(2); // Set text size
  display.setTextColor(WHITE); // Set text color
  display.setCursor(0, 0); // Set cursor position
  display.print("Temp: "); // Print temperature label
  display.println(temperature); // Print temperature value
  display.print("Humidity: "); // Print humidity label
  display.println(humidity); // Print humidity value
  display.display(); // Display content on OLED
  delay(2000); // Delay for 2 seconds

  // Read and display MQ7 sensor value
  int mq7Value = analogRead(MQ7_PIN); // Read MQ7 sensor value
  display.clearDisplay(); // Clear previous display
  display.setCursor(0, 0); // Set cursor position
  display.println("MQ7 Value: "); // Print MQ7 sensor label
  display.println(mq7Value); // Print MQ7 sensor value
  display.display(); // Display content on OLED
  delay(2000); // Delay for 2 seconds

  // Read and display LDR value
  int ldrValue = analogRead(LDR_PIN); // Read LDR sensor value
  display.clearDisplay(); // Clear previous display
  display.setCursor(0, 0); // Set cursor position
  display.println("Light Intensity: "); // Print LDR sensor label
  display.println(ldrValue ? "LOW" : "HIGH"); // Print LDR sensor value
  display.display(); // Display content on OLED
  delay(2000); // Delay for 2 seconds

  // Check for abnormal sensor readings and trigger buzzer
  if (ldrValue == 1023) { // If light intensity is high
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  } else { // If light intensity is not high
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }
}
