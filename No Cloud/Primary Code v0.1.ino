//First code that was errorfree and ran smoothly.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHTPIN D3
#define DHTTYPE DHT11
#define MQ7PIN A0
#define BUZZER D5
#define LDR_PIN D0
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

float btemp = 12.6;
float bhumid = 24;
int count = 0;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(MQ7PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  dht.begin();
  Serial.begin(115200);


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
}

void loop() {
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
   
  float temperature = dht.readTemperature();

  display.display();
  delay(2000);
  display.clearDisplay();

  if(!isnan(temperature))
    btemp = temperature;

  int mq7Value = analogRead(MQ7PIN);
  int ldrValue = analogRead(LDR_PIN);


  display.setCursor(0, 0);
  display.println("Temp: ");
  Serial.println(btemp);
  display.print(btemp);
  display.print("C");
  display.display();
  delay(2000);
  display.clearDisplay();

  float humidity = dht.readHumidity();

  if(!isnan(humidity))
    bhumid = humidity;
    
  //display.setTextSize(2);
  display.setCursor(0, 28);
  display.println("Hmdty: ");
  display.print(bhumid);
  Serial.println(bhumid);
  display.print("%");
  display.display();
  delay(2000);
  display.clearDisplay();

  //display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("MQ7 Value: ");                                                
  display.print(mq7Value);
 
  display.display();
  delay(2000);
  display.clearDisplay();

  //display.setTextSize(2);
  display.setCursor(0,0);
  display.println(F("Light Int: "));
  display.print(ldrValue?"LOW":"HIGH");
  if(ldrValue == 1023)
    digitalWrite(BUZZER, HIGH);
  else
    digitalWrite(BUZZER, LOW);

  display.display();
  delay(2000);
  display.clearDisplay();

  delay(2000);

}
