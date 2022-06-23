
#include <SPI.h>
#include <Wire.h>

// inputs
#define pot1            A0  Decay
#define pot2            A1  Filter 1
#define pot3            A2  Filter 2
#define pot4            A3  Tone 1 
#define pot5            A4  Tone 2 

void setup() {
  Serial.begin(9600);

}

void loop() {
  float knob1 = (float)analogRead(pot1)/2;  Decay 
  float knob2 = (float)analogRead(pot2)/4;  Filter 1 
  float knob3 = (float)analogRead(pot3)/4;  Filter 2  
  float knob4 = (float)analogRead(pot4)/4;  Tone 1  
  float knob5 = (float)analogRead(pot5)/2;  Tone 2  
  
  Serial.print("Decay Value read: ");
  Serial.println(knob1);
  Serial.print("Filter 1 Value read: ");
  Serial.println(knob2);
  Serial.print("Filter 2 Value read: ");
  Serial.println(knob3);
  Serial.print("Tone 1 Value read: ");
  Serial.println(knob4);
  Serial.print("Tone 2 Value read: ");
  Serial.println(knob5);
 }
