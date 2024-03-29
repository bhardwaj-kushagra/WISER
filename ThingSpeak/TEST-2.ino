#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHT_PIN D3
#define DHT_TYPE DHT11
#define MQ7_PIN A0
#define BUZZER_PIN D5
#define LDR_PIN D0
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";
const unsigned long channelId = YOUR_CHANNEL_ID;
const char *writeAPIKey = "YourWriteAPIKey";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHT_PIN, DHT_TYPE);
float temperature = 0;
float humidity = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MQ7_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  ThingSpeak.begin(client);
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  int status = ThingSpeak.writeFields(channelId, writeAPIKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.println("Failed to send data to ThingSpeak");
  }
  delay(2000);
}
