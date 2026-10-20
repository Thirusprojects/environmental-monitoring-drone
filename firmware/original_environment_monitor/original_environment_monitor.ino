// Environmental monitoring project sketch.
// Credentials replaced; formatting and comments cleaned up.
// Original executable logic retained. See docs/code-review.md before reuse.
#include <Wire.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <MQUnifiedsensor.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0
#define type "MQ-135"
#define ADC_Bit_Resolution 10
#define RatioMQ135CleanAir 3.6
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)
Adafruit_BMP280 bmp;

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "DroneProj"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

float temperature = 30.30;
float humidity = 64.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("BMP280 setup start");
  while (!Serial) delay(100);
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  Serial.println("BMP280 setup end");
  Serial.println("setup");
  MQ135.setRegressionMethod(1);
  MQ135.init();
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ135.update();
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");
  if (isinf(calcR0)) {
    Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply");
    while (1);
  }
  if (calcR0 == 0) {
    Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply");
    while (1);
  }
  Serial.println("** Values from MQ-135 ****");
  Serial.println("|    CO   |  Alcohol |   CO2  |  Toluen  |  NH4  |  Aceton  |");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  float airpressure = bmp.readPressure()/100000;
  Serial.print("Air Pressure : ");
  Serial.print(airpressure);
  Serial.println(" Bar");
  Blynk.virtualWrite(V2, airpressure);
  delay(1000);
  MQ135.update();
  MQ135.setA(605.18); MQ135.setB(-3.937);
  float CO = MQ135.readSensor();
  MQ135.setA(77.255); MQ135.setB(-3.18);
  float Alcohol = MQ135.readSensor();
  MQ135.setA(110.47); MQ135.setB(-2.862);
  float CO2 = MQ135.readSensor();
  MQ135.setA(44.947); MQ135.setB(-3.445);
  float Toluen = MQ135.readSensor();
  MQ135.setA(102.2); MQ135.setB(-2.473);
  float NH4 = MQ135.readSensor();
  MQ135.setA(34.668); MQ135.setB(-3.369);
  float Aceton = MQ135.readSensor();
  Serial.print("|   "); Serial.print(CO);
  Serial.print("   |   "); Serial.print(Alcohol);
  Serial.print("   |   "); Serial.print(CO2 + 400);
  Serial.print("   |   "); Serial.print(Toluen);
  Serial.print("   |   "); Serial.print(NH4);
  Serial.print("   |   "); Serial.print(Aceton);
  Serial.println("   |");
  String gasSet1 = "CO:"+String(CO)+" , C02:"+String(CO2+400)+", NH4:"+String(NH4);
  Blynk.virtualWrite(V3, gasSet1);
  String gasSet2 = "Toluen:"+String(Toluen)+", Aceton:"+String(Aceton);
  Blynk.virtualWrite(V4, gasSet2);
  delay(1000);
  float h = dht.readHumidity();
  Serial.print("Humidity(in percentage) = ");
  Serial.print(h);
  Blynk.virtualWrite(V1, h);
  Serial.println("%");
  float t = dht.readTemperature();
  Serial.print("Temparature(in celcius) = ");
  Serial.print(t);
  Blynk.virtualWrite(V0, t);
  Serial.println("celcius");
  delay(1000);
}
