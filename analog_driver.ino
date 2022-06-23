
#include <SPI.h>
#include <Wire.h>

// inputs
#define pot1            A0 // Decay
#define pot2            A1 // Filter 1
#define pot3            A2 // Filter 2
#define pot4            A3 // Tone 1 
#define pot5            A4 // Tone 2 


void setup() {
  Serial.begin(9600);
  pinMode(PIN_D8, INPUT_PULLUP); // Drum Voice 1 
  pinMode(PIN_D9, INPUT_PULLUP); // Drum Voice 2
  pinMode(PIN_D10, INPUT_PULLUP); // Drum Voice 3
  pinMode(PIN_D11, INPUT_PULLUP); // Drum Voice 4
}

void loop() {
//  float knob1 = (float)analogRead(pot1)/2; // Decay 
//  float knob2 = (float)analogRead(pot2)/4; // Filter 1 
//  float knob3 = (float)analogRead(pot3)/4; // Filter 2  
//  float knob4 = (float)analogRead(pot4)/4; // Tone 1  
//  float knob5 = (float)analogRead(pot5)/2; // Tone 2  
  
// Serial.print("Decay Value read: ");
// Serial.println(knob1);
// Serial.print("Filter 1 Value read: ");
// Serial.println(knob2);
// Serial.print("Filter 2 Value read: ");
// Serial.println(knob3);
// Serial.print("Tone 1 Value read: ");
// Serial.println(knob4);
// Serial.print("Tone 2 Value read: ");
// Serial.println(knob5);
  for (int i = 9; i <= 11; i++) {
  	if (digitalRead(i)) {
  		Serial.print("Current selection: ");
  		Serial.println(i);
  	}
  }
}
