#define BLYNK_TEMPLATE_ID "TMPL3c6CPYS0W"
#define BLYNK_TEMPLATE_NAME "weather moniter"
#define BLYNK_AUTH_TOKEN "nSV3UVSbAyS7yr0m4_KUN0LRek9MGPz-"
#define BLYNK_PRINT Serial
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHTPIN D3
#define DHTTYPE DHT11
#define MQ7PIN A0
#define BUZZER D5
#define LDR_PIN D0
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C

#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//WiFiClient client;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Error";  // type your wifi name
char pass[] = "99999998";  // type your wifi password

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

float btemp = 12.6;
float bhumid = 24;
int count = 0;

void sendSensor()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
   
  float temperature = dht.readTemperature();

  if(WiFi.status() == WL_CONNECTED)
    display.print("Cloud ON!");
  else
    display.print("Cloud OFF!");

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

  display.display();
  delay(2000);
  display.clearDisplay();

  delay(2000);

  if( btemp > 30)
    Blynk.logEvent("temperature_change_detected", String("High Temperature Detected! T(in C)" + String(btemp)));

  if(ldrValue == 1023){
    Blynk.logEvent("low_light_intensity");
    digitalWrite(BUZZER, HIGH);
  }
  else
    digitalWrite(BUZZER, LOW);

  if(mq7Value > 550)
    Blynk.logEvent("pollution_alert");

  if( bhumid > 70)
    Blynk.logEvent("high_humidity");
    
  Blynk.virtualWrite(V4, mq7Value);
  Blynk.virtualWrite(V0, ldrValue);
  Blynk.virtualWrite(V3, btemp);
  Blynk.virtualWrite(V1, bhumid);
}


void setup() {
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  Serial.begin(115200);

//    WiFi.begin("Error","99999998");
//    while(WiFi.status() != WL_CONNECTED){
//    delay(200);
//    count++;
//    Serial.print("..");
//    if(count == 50)
//    break;
//  }
//  Serial.println();
//  Serial.println("NodeMCU is connected!");
//  Serial.println(WiFi.localIP());

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  
}

void loop() {
  Blynk.run();
  timer.run();
}
