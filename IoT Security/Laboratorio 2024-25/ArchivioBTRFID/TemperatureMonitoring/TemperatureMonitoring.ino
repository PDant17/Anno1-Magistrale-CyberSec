#include "DHT.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9   
#define SS_PIN    10

#define DHTPIN 2
#define DHTTYPE DHT22
#define LED 3

SoftwareSerial btSerial(4, 5);

DHT dht(DHTPIN, DHTTYPE);

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Card UUID 77 E8 53 62
// Tag UUID  E9 38 14 C2

String msg = ""; 

bool lockOn;

void setup( )
{
  Serial.begin( 9600);
  pinMode(LED, OUTPUT);
  Serial.print("Temperature and Humidity Monitoring Application\n\n");
  dht.begin();
  delay(1000);

  btSerial.begin(9600);  
  //btSerial.println("AT");
  //getBTReply();
  //btSerial.println("AT+ROLE0");
  //getBTReply();
  //btSerial.println("AT+NAMEtempSens");  
  //Serial.println("Check if name is assigned");
  //getBTReply();

  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.println("Lock initialised");

  lockOn = true;
}

void loop( )
{
  if(lockOn == true) {
    if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
      Serial.println("Application locked, waiting for RFID key to unlock");
    } else {
      if(checkRFID("E9 38 14 C2")) {
        Serial.println("RFID Tag detected");
        Serial.println("Application unlocked, performing monitoring");
        digitalWrite(LED, HIGH);
        lockOn=false;
      }
    }
  } else {
    if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
      if (isnan(h) || isnan(t) ) {
        Serial.print(F("Failed to read from DHT sensor! "));
        Serial.print(t);
        Serial.print(" ");
        Serial.println(h);
      } else {
        float hic = dht.computeHeatIndex(t, h, false);
        Serial.print(F(" Humidity: "));
        Serial.print(h);
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F("C "));
        Serial.print(F("  Heat index: "));
        Serial.print(hic);
        Serial.print(F("C \n"));
      }
        
      if(btSerial.available()) {
        btSerial.print("Temperature: ");
        btSerial.print(t);
        btSerial.println("");
        Serial.print(" Message sent on Bluetooth! ");
      }
    } else {
      if(checkRFID("E9 38 14 C2")) {
        Serial.println("RFID Tag detected");
        Serial.println("Application locked, stopping monitoring");
        digitalWrite(LED, LOW);
        lockOn=true;
      }
    }
  }

  delay(5000);
}

boolean checkRFID(String rightID) {
  Serial.print("Detected RFID with UUID = ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  return (content.substring(1) == rightID);
}
