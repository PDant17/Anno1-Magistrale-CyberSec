#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <Arduino_LSM6DSOX.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <SSLClient.h>
#include "trustanchors.h"

#define flame_sensor A1
#define current_sensor A2
#define debug 1
    
SensirionI2CScd4x scd4x;

char ssid[] = "ChristianWiFi"; //  your network SSID (name)
char pass[] = "abcdefgh";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

const unsigned char cert[] = \
                             "-----BEGIN CERTIFICATE-----\n" \
                             "MIIDtjCCAp4CCQDw8o5eUMLmozANBgkqhkiG9w0BAQsFADCBnDELMAkGA1UEBhMC\n" \
                             "SVQxEDAOBgNVBAgMB1NBTEVSTk8xETAPBgNVBAcMCEZJU0NJQU5PMQ4wDAYDVQQK\n" \
                             "DAVVTklOQTELMAkGA1UECwwCREkxKTAnBgNVBAMMIERpcGFydGltZW50byBJbmZv\n" \
                             "cm1hdGljYSBAIFVOSVNBMSAwHgYJKoZIhvcNAQkBFhFlc3Bvc2l0b0B1bmlzYS5p\n" \
                             "dDAeFw0yMjAzMTExMDE3MjNaFw0yMzAzMTExMDE3MjNaMIGcMQswCQYDVQQGEwJJ\n" \
                             "VDEQMA4GA1UECAwHU0FMRVJOTzERMA8GA1UEBwwIRklTQ0lBTk8xDjAMBgNVBAoM\n" \
                             "BVVOSU5BMQswCQYDVQQLDAJESTEpMCcGA1UEAwwgRGlwYXJ0aW1lbnRvIEluZm9y\n" \
                             "bWF0aWNhIEAgVU5JU0ExIDAeBgkqhkiG9w0BCQEWEWVzcG9zaXRvQHVuaXNhLml0\n" \
                             "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAxBbYm3zI3gvbp5cW4Djb\n" \
                             "Urv9sxeiQ4dRP+ghz0hW4VEi/DVh9N2QJvqOCz+sOnA0+UTl+jRKAkuIr1goMpRX\n" \
                             "/cUBEouCIh/uTHsj6i8wrbUL8Oqplu8W9Ms/7+FneGxF2chQ6cebJJWld864jqHm\n" \
                             "C/cPE5YXRzZf5AXW33YGjlsvNALA6kWhpIhQ6cyKlwniNV9+wcCVSxae3oU11f4V\n" \
                             "jnC5lfzdxzWSh11wQbHhcwKgnQlK2+F4rLOTehQs+DT3L1F/iFRM9dMSvJIWXbjg\n" \
                             "OWW6Cty579+Pv/IK8Za9HPmj7Fbi3wzrC2m6SPpalCflxCiIx62pZ7XyPZrpIfxi\n" \
                             "gwIDAQABMA0GCSqGSIb3DQEBCwUAA4IBAQB6zuAo9Ey28KIhPxxmvesoTk0qeRyK\n" \
                             "DRoH3KaKlQ3ITs1Bsq9sGdPSM6+gMRfL267fQ7pr1HYsRa6h9+MlMMF9gxt5YAo2\n" \
                             "gr1U2LBFJhSSV6tTrz9ykZ/tM7vOBHh1DjhhZsXE10AvGGFyCCrIoYDRrECXBLxm\n" \
                             "XwrCnDrEQ15Y7pMvqrGe2o+Pv/UCO7FNPMqBRgeUKy2QszS1Pj9zjQZB4PRXQNPh\n" \
                             "VXBqwKU1CXuwu5/dEZpL5WYyUHCA9dPgHszJv35/WIdV43J2mbPSBiEhyfloVP7Y\n" \
                             "uU0LcCERChrWGsn5gEdtwqZtMv9KwrUUwdL/hR+VyKlFZpXJx6DfMLxS\n" \
                             "-----END CERTIFICATE-----\n";


char idNode[] = "Monitor_01";
int seq_msg = 0;

int status = WL_IDLE_STATUS;
IPAddress server(192,168,103,229);
const int port = 60000;

// Initialize the Wifi client library
// with the IP addressSensirionI2CCommunication and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient baseClient;
SSLClient client(baseClient, TAs, (size_t)2, 14);

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}
int init_LSM6DSOXTR()
{
    if (!IMU.begin()) 
    {
      if(debug)
        Serial.println("Failed to initialize LSM6DSOXTR");
      return 0;
    }
    if(debug)
    {
    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println(" Hz");
    Serial.println("Acceleration in g's");
    Serial.println("X\tY\tZ");
    }
  return 1;
}
int LSM6DSOXTR_write()
{
  char nByte=0;
  float acc[3]={0,0,0};
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(acc[0], acc[1], acc[2]);
  if(debug)
  {
      Serial.print("LSM6DSOXTR x= ");
      Serial.print(acc[0]);
      Serial.print(" LSM6DSOXTR y= ");
      Serial.print(acc[1]);
      Serial.print(" LSM6DSOXTR z= ");
      Serial.println(acc[2]);
  }
  return nByte;
  }
return -1;
}

int LSM6DSOXTR_writeXML( boolean flag)
{
  char nByte=0;
  float acc[3]={0,0,0};
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(acc[0], acc[1], acc[2]);
  if(debug)
  {
    if(flag)
    {
      client.println("\t<LSM6DSOXTR>");
      client.println("\t \t<x>");
      client.print("\t \t \t "); client.print(acc[0]); client.println("");
      client.println("\t \t</x>");
      client.println("\t \t<y>");
      client.print("\t \t \t "); client.print(acc[1]); client.println("");
      client.println("\t \t</y>");
      client.println("\t \t<z>");
      client.print("\t \t \t "); client.print(acc[2]); client.println("");
      client.println("\t \t</z>");
      client.println("\t</LSM6DSOXTR>");
    } else {
      Serial.println("\t<LSM6DSOXTR>");
      Serial.println("\t \t<x>");
      Serial.print("\t \t \t "); Serial.print(acc[0]); Serial.println("");
      Serial.println("\t \t</x>");
      Serial.println("\t \t<y>");
      Serial.print("\t \t \t "); Serial.print(acc[1]); Serial.println("");
      Serial.println("\t \t</y>");
      Serial.println("\t \t<z>");
      Serial.print("\t \t \t "); Serial.print(acc[2]); Serial.println("");
      Serial.println("\t \t</z>");
      Serial.println("\t</LSM6DSOXTR>");
    }
  }
  return nByte;
  }
return -1;
}
void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }
    init_LSM6DSOXTR();
    Wire.begin();
    uint16_t error;
    char errorMessage[256];
    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage); 
    }

    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }

    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);
  
      // wait 10 seconds for connection:
      delay(10000);
    }
    Serial.print("Connected to wifi ");
    Serial.println(WiFi.localIP());

    Serial.println("Waiting for the first measurement...");

    /*Serial.println("rng_seeds - INIT");
    Serial.println(A0);
    uint8_t rng_seeds[16];
    // take the bottom 8 bits of the analog read
    for (uint8_t i = 0; i < sizeof rng_seeds; i++) {
        rng_seeds[i] = static_cast<uint8_t>(analogRead(A0));
        Serial.println(rng_seeds[i]);
    }
    Serial.println("rng_seeds - FINIT");*/
}

void loop() {
    uint16_t error;
    char errorMessage[256];
    delay(1000);

    // Read Measurement
    uint16_t co2;
    float temperature;
    float humidity;
    Serial.print("flame= ");
    Serial.println(analogRead(flame_sensor));
    Serial.print("corrente assorbita= ");
    Serial.println(analogRead(current_sensor));
    LSM6DSOXTR_write();
    scd4x.getDataReadyStatus(error);
    if((error&2047)>0)
    {
      error = scd4x.readMeasurement(co2, temperature, humidity);
      if (error) {
          Serial.print("Error trying to execute readMeasurement(): ");
          errorToString(error, errorMessage, 256);
          Serial.println(errorMessage);
      } else if (co2 == 0) {
          Serial.println("Invalid sample detected, skipping.");
      } else {
          Serial.print("Co2:");
          Serial.print(co2);
          Serial.print("ppm\t");
          Serial.print("Temperature:");
          Serial.print(temperature);
          Serial.print("°C\t");
          Serial.print("Humidity:");
          Serial.print(humidity);
          Serial.println("%RH");

          Serial.println("\nStarting connection to SSL server...");
          // if you get a connection, report back via serial:
          Serial.print("IP: " );Serial.print(server);
          Serial.println(" port: 60000" );
          client.connect(server, port);
          if (client.connected()) {
            Serial.print("Sent message: ");
            Serial.println("<?xml version=\"1.0\"?>");
            Serial.print("<sensorData id=\"");Serial.print(seq_msg++);Serial.println("\">");
            Serial.println("\t<Flame>");
            Serial.print("\t \t "); Serial.print(analogRead(flame_sensor)); Serial.println("");
            Serial.println("\t</Flame>");
            Serial.println("\t<Current>");
            Serial.print("\t \t "); Serial.print(analogRead(current_sensor)); Serial.println("");
            Serial.println("\t</Current>");
            LSM6DSOXTR_writeXML(false);
            Serial.println("\t<Co2>");
            Serial.print("\t \t "); Serial.print(co2); Serial.println("");
            Serial.println("\t</Co2>");
            Serial.println("\t<Temperature>");
            Serial.print("\t \t "); Serial.print(temperature); Serial.println("");
            Serial.println("\t</Temperature>");
            Serial.println("\t<Humidity>");
            Serial.print("\t \t "); Serial.print(humidity); Serial.println("");
            Serial.println("\t</Humidity>");
            Serial.println("</sensorData>");
            client.println("<?xml version=\"1.0\"?>");
            client.print("<sensorData id=\"");client.print(seq_msg++);client.println("\">");
            client.println("\t<Flame>");
            client.print("\t \t "); client.print(analogRead(flame_sensor)); client.println("");
            client.println("\t</Flame>");
            client.println("\t<Current>");
            client.print("\t \t "); client.print(analogRead(current_sensor)); client.println("");
            client.println("\t</Current>");
            LSM6DSOXTR_writeXML(true);
            client.println("\t<Co2>");
            client.print("\t \t "); client.print(co2); client.println("");
            client.println("\t</Co2>");
            client.println("\t<Temperature>");
            client.print("\t \t "); client.print(temperature); client.println("");
            client.println("\t</Temperature>");
            client.println("\t<Humidity>");
            client.print("\t \t "); client.print(humidity); client.println("");
            client.println("\t</Humidity>");
            client.println("</sensorData>");
            client.flush();
          } else {
            Serial.println("Connessione Fallita");
          }
        
          // if the server's disconnected, stop the client:
          if (!client.connected()) {
            Serial.println();
            Serial.println("disconnecting from server.");
            client.stop();
          }
      }
    }
}
