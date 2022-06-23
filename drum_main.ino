#include <SPI.h>
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP); // mode select
  pinMode(7, INPUT_PULLUP); // mode select
  pinMode(8, INPUT_PULLUP); // mode select
  pinMode(9, INPUT_PULLUP); // mode select

}

void loop() {
 
 if (digitalRead(6) == LOW) {
  Serial.println("drum");
 } else if (digitalRead(7) == LOW) {
  Serial.println("snare");
 }else if (digitalRead(8) == LOW) {
  Serial.println("hat");
 }else if (digitalRead(9) == LOW) {
  Serial.println("cym");
 }



}
