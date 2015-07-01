#include <ArduinoJson.h>

#include <VirtualShield.h>
#include <Text.h>

#include "DHT.h"
#define DHTPIN 7     
#define DHTTYPE DHT11

#define ECHO 5
#define TRIGER 4
#define RED A2
#define GREEN A3
#define BLUE A4
#define LED 6

VirtualShield shield;	         
DHT dht(DHTPIN, DHTTYPE);
Text screen = Text(shield);	 

void setup()
{
  pinMode(TRIGER, OUTPUT); 
  pinMode(ECHO, INPUT); 
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(LED, OUTPUT);
  dht.begin();
  shield.begin(9600);
}

void reportState() {
  unsigned long d;
  digitalWrite(TRIGER, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGER, LOW); 
  d = pulseIn(ECHO, HIGH);
  float cm;
  cm = d / 58.0;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  screen.clear();
  screen.printAt(0,"Humidity: " + String(h));
  screen.printAt(1,"Temperature:"+ String(t));
  screen.printAt(2,"Distance:"+String(cm)+" cm");
  screen.printAt(8,"RGB");

  setRGB(cm);
  delay(1000);
}

void setRGB(float val){
   if(val <= 0.0) {
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
  }
  else if(val < 10.0) {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
  } else if (val < 50.0) {
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,LOW);
  } else {
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
  }
}

void loop()
{
  reportState();  
}								
