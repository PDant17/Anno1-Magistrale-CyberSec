#include "DHT.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <MFRC522.h>
#include <AES.h>

AES aes ;

byte key [N_BLOCK] ;
byte plain[N_BLOCK];

byte cipher [N_BLOCK] ;
byte check [N_BLOCK] ;

#define RST_PIN   9   
#define SS_PIN    10

#define DHTPIN 2
#define DHTTYPE DHT22
#define LED 3
#define PIN_EN 6

SoftwareSerial btSerial(4, 5);

DHT dht(DHTPIN, DHTTYPE);

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Card UUID 77 E8 53 62
// Tag UUID  E9 38 14 C2

bool isConnected = false;
String msg = ""; 

bool lockOn;


void setup( )
{
  Serial.begin( 9600);
  pinMode(LED, OUTPUT);
  Serial.print("Temperature and Humidity Monitoring Application\n\n");
  dht.begin();
  delay(1000);
  int bits = 128;
  byte succ;
  set_bits (bits, key, 0) ;  // all zero key
  succ = aes.set_key (key, bits);
  if (succ != SUCCESS) Serial.println ("Failure set_key") ;

  checkConnection();
  if(!isConnected) {
    pinMode(PIN_EN, OUTPUT);  // this pin will pull the HC-010 EN HIGH to switch module to AT mode
    digitalWrite(PIN_EN, HIGH);
    Serial.println("Going in AT mode for BLE HC-10");
    btSerial.begin(38400);
    delay(1000);
    pinMode(A0, INPUT);
    while(!isConnected) {
      if (btSerial.available()) {
        char c = btSerial.read();
        Serial.write(c);         
      }
      if (Serial.available()) {  
        char c = Serial.read();  
        btSerial.write(c);       
      }
      checkConnection();
    }  

    btSerial.flush();
    btSerial.end();
    btSerial.begin(9600);
    digitalWrite(PIN_EN, LOW);
    Serial.println("Exiting from AT mode for BLE HC-10");
  }

  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.println("Lock initialised");

  lockOn = true;
}

void checkConnection() {
  int x = analogRead(A0);
    if(x > 700) {
      Serial.println("HC-10 is connected");
      isConnected = true;
    }
}

void loop( )
{
  if(lockOn == true) {
    if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
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
    if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
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
        
      if(isConnected) {
        String string_1 = String(t);
        byte succ;
        string_1.getBytes(plain, 16);
        succ = aes.encrypt (plain, cipher) ;
        print_value(cipher, 16);
        Serial.print(" Message sent on Bluetooth! - ");
        Serial.print(t);
        Serial.print("\r\n");
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

char * hex = "0123456789abcdef" ;


void print_value (byte * a, int bits)
{
  for (int i = 0 ; i < bits ; i++)
    {
      byte b = a[i];
      btSerial.write(b);
    }
}

void print_value_serial (byte * a, int bits)
{
  bits >>= 3 ;
  for (int i = 0 ; i < bits ; i++)
    {
      byte b = a[i] ;
      Serial.print (hex [b >> 4]) ;
      Serial.print (hex [b & 15]) ;
    }
}

void set_bits (int bits, byte * a, int count)
{
  bits >>= 3 ;
  byte bcount = count >> 3 ;
  for (byte i = 0 ; i < bcount ; i++)
    a [i] = 0xFF ;
  if ((count & 7) != 0)
    a [bcount++] = 0xFF & (0xFF00 >> (count & 7)) ;
  for (byte i = bcount ; i < bits ; i++)
    a [i] = 0x00 ;
}