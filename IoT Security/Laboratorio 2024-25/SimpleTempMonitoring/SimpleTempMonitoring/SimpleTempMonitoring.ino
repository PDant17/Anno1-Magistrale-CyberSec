#include "DHT.h"

#define DHT11PIN 4
#define DHTTYPE DHT11

DHT dht(DHT11PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.print("Setup....");
  delay(1000);
  dht.begin();
  Serial.println("....Done");
}

void loop() {
  Serial.println();

  Serial.print("Humidity (%): ");
  float h = dht.readHumidity();
  Serial.println(h, 2);
  Serial.print("Temperature (C): ");
  float t = dht.readTemperature();
  Serial.println(t, 2);

  delay(5000);
}
