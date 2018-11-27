// BOARD: Adafruit ESP32 Feather
// BAUDRATE: 921600 
// CPU Frecuency: 80 MHz
// Programmer: AVRISP mkll

#include <WiFi.h>
#include <ArduinoJson.h>
/* Gyro Sensor */
#include <Wire.h> 
#include "Adafruit_L3GD20.h"

/* LED */
#define LED_PIN 13

// Comment this next line to use SPI
#define USE_I2C

#ifdef USE_I2C
  // The default constructor uses I2C
  Adafruit_L3GD20 gyro;
#else
  // To use SPI, you have to define the pins
  #define GYRO_CS 22 // labeled CS - 4 (UNO)
  #define GYRO_DO 21 // labeled SA0 - 5 (UNO)
  #define GYRO_DI 18  // labeled SDA - 6 (UNO)
  #define GYRO_CLK 19 // labeled SCL - 7 (UNO)
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif
const char* ssid     = "EMBAJADADA";
const char* password = "embajadada";
const char* host = "192.168.1.114";
const int port = 8088;

void setup()
{
    
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* connect to your WiFi */
    WiFi.begin(ssid, password);
    /* wait until ESP32 connect to WiFi*/
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());

      delay(1000);
  // Try to initialise and warn if we couldn't detect the chip
   if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    while (1)
      {
        Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
      }
  }
}


void loop()
{
  
    delay(10);
    Serial.print("connecting to ");
    Serial.println(host);
    /* Use WiFiClient class to create TCP connections */
    WiFiClient client;
    
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        return;
    }
    /* This will send the data to the server */
    gyro.read();
  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); Serial.print(" ");
  delay(1000);
  
  int jX = (int)gyro.data.x;
  int jY = (int)gyro.data.y;
  int jZ = (int)gyro.data.z;

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["X"] = jX; root["Y"] = jY;root["Z"] = jZ;
  root.printTo(Serial); root.printTo(client);

  /*
  JsonObject& data = root.createObject("data");
data.set("temperature", "30.1");
data.set("humidity", "70.1");*/





/*
 char json[] =
      "{\"X\":\"(int)gyro.data.x\",\"Y\":\"(int)gyro.data.y\",\"Z\":\"(int)gyro.data.z\"}";
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

  const char* X = root["X"];
  const char* Y = root["Y"];
  const char* Z = root["Z"];

    Serial.println(X);
    Serial.println(Y);
    Serial.println(Z); */
    
    /*
              client.print("X: ");
              client.print((int)gyro.data.x);
              client.print(" ");
              client.print("Y: ");
              client.print((int)gyro.data.y);
              client.print(" ");
              client.print("Z: ");
              client.print((int)gyro.data.z);
              client.print(" ");
*/
               
 

             
    
}
