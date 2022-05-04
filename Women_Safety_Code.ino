#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t gps_baudrate = 9600;
TinyGPSPlus gps;
SoftwareSerial soft(RXPin, TXPin);
String textMessage;
float Lat, Lon;
int pushbutton1 = 6; 
int pushbutton2 = 5;
int buzzpin = 7;
int halogenbulb = 10;
int shockcircuit = 9;
int x = 0;
int y = 0; 
void setup()
{
  soft.begin(gps_baudrate);
  Serial.begin(19200);
  pinMode(12, INPUT);
  pinMode(4, OUTPUT);
  pinMode(pushbutton1, INPUT);
  pinMode(pushbutton2, INPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(halogenbulb, OUTPUT);
  pinMode(shockcircuit, OUTPUT);
}
void loop()
{
  x = digitalRead(pushbutton1);
  y = digitalRead(pushbutton2);
  if (x == 1)
  {
    digitalWrite(shockcircuit, HIGH);
    digitalWrite(halogenbulb, HIGH);
  }
  if (y == 1)
  { digitalWrite(buzzpin, HIGH);
    int key = digitalRead(12);
    while (soft.available() > 0)
    {
      gps.encode(soft.read());
      if (gps.location.isUpdated())
      {
        Lat = gps.location.lat();
        Lon = gps.location.lng();
      }
      else;
    }
    if (key == 1)
    {
      digitalWrite(4, HIGH);
      sendsms();
      digitalWrite(4, LOW);
    }
  }
}
  void sendsms()
  {
    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.println("AT+CMGS =\"+91XXXXXXXXXX\"");
    delay(100);
    Serial.println("I want Help !!!Location:" + String("Lat: ") + String(Lat) + " " + String("Lon: ") + String(Lon));
    delay(100);
    Serial.println((char)26);
    delay(100);
    Serial.println();
    delay(5000);
  }
