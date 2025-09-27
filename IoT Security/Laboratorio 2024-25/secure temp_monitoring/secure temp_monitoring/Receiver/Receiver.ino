#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <AES.h>

AES aes ;

byte key [N_BLOCK] ;

byte cipher [N_BLOCK] ;
byte check [N_BLOCK] ;

#define PIN_EN 6
#define BUTTON 13

SoftwareSerial btSerial(4, 5);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String msg = "";
bool isConnected = false;

String readString = "";
byte msg_received[16];
char final_str[16];

void setup( )
{
  Serial.begin(9600);
  Serial.print("Receiving Application\n\n");
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Receiving App");

  int bits = 128;
  set_bits (bits, key, 0) ;  // all zero key
  byte succ;
  succ = aes.set_key (key, bits) ;
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
  if(isConnected) { 
    getBTReply();
    if(msg.length() > 0) {
      Serial.println("Received msg: " + msg);
      lcd.clear();
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      lcd.print("Receiving App");
      lcd.setCursor(0, 1);
      lcd.print("Temp. > ");
      lcd.print(msg);
      lcd.setCursor(13, 1);
      lcd.print(" C");
    } else {
      Serial.println("Received no msg");
      lcd.clear();
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      lcd.print("Receiving App");
      lcd.setCursor(0, 1);
      lcd.print("no message received");
    }
  }
  delay(4000);
}

void getBTReply() {
  msg = "";
  int i = 0;
  while (btSerial.available()) {
    msg_received[i] = btSerial.read();
    i++;
  }
  if (i==16) {
    byte succ;
    succ = aes.decrypt (msg_received, check) ;
    if (succ != SUCCESS) Serial.println ("Failure decrypt") ;
    String x = prs_byte_hex(check, 128);
    textFromHexString(x.c_str(), final_str);
    msg = String(final_str);
    memset(final_str,0,strlen(final_str));
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


char * hex = "0123456789abcdef" ;


void print_value (byte * a, int bits)
{
  bits >>= 3 ;
  for (int i = 0 ; i < bits ; i++)
    {
      byte b = a[i] ;
      // test purpose only
      Serial.print (hex [b >> 4]) ;
      Serial.print (hex [b & 15]) ;
    }
  Serial.println () ;
}

String prs_byte_hex (byte * a, int bits)
{
  bits >>= 3 ;
  String str_toparse;
  for (int i = 0 ; i < bits ; i++)
    {
      byte b = a[i] ;
      str_toparse += hex [b >> 4];
      str_toparse += hex [b & 15];
    }
  return str_toparse;
}

void textFromHexString(char *hex, char *result)
{
    char temp[3];
    int index = 0;

    temp[2] = '\0';
    while (hex[index])
    {
        strncpy(temp, &hex[index], 2);
        *result = (char)strtol(temp, NULL, 16);
        result++;
        index += 2;
    }
    *result = '\0';
}
