#include <synth_simple_drum.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

// gates
Bounce gate1 = Bounce(24,5);
Bounce gate2 = Bounce(25,5);
Bounce gate3 = Bounce(26,5);
Bounce gate4 = Bounce(27,5);

// inputs
#define pot1            A17 // frequency
#define pot2            A16 // length
#define pot3            A15 // secondMix
#define pot4            A14 // pitchMod

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=399,244
AudioSynthSimpleDrum     drum3;          //xy=424,310
AudioSynthSimpleDrum     drum1;          //xy=431,197
AudioSynthSimpleDrum     drum4;          //xy=464,374
AudioMixer4              mixer1;         //xy=737,265
AudioOutputI2S           i2s1;           //xy=979,214
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=930,518
// GUItool: end automatically generated code

// https://forum.arduino.cc/t/use-a-single-knob-for-mutli-variables/311022/14 
// handling multiple variables with single pot 
enum modes {d1, d2, d3, d4 };
modes mode; //the current mode must be stored in a global variable

const int buttonPin = 33;    // the number of the pushbutton pin
const unsigned long debounceDelay = 50;    // the debounce time milliseconds; increase if the output flickers

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // audio library init
  AudioMemory(20);
  
  // Pins
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  mode = d1;
  
  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);
  
  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);
  
  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);

  drum4.frequency(1200);
  drum4.length(150);
  drum4.secondMix(0.0);
  drum4.pitchMod(0.0);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  AudioInterrupts();

}

elapsedMillis timeout = 0;

void loop() {
    readButtons();
    readPots();
    playDrums();
    
    Serial.print("Diagnostics: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.print(" ");
    Serial.println(AudioMemoryUsageMax());
    AudioProcessorUsageMaxReset();
}

void readButtons() {
  //read the button(s) in and change modes accordingly
  //currently this example only shows one button
  
  //store some static variables that we need to remember over the long term
  static bool lastButtonState = LOW;   // the previous reading from the input pin
  static bool buttonState = HIGH;     // the current state of the button
  static unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

  // read the state of the switch into a local variable:
  bool reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      //Only change mode if the new button state is LOW (pressed)
      //depending on which mode we are in, we may jump to a different one
      if (buttonState == LOW) {
        switch (mode) {
          case d1:
            mode = d2;
            break;
          case d2:
            mode = d3;
            break;
          case d3:
            mode = d4;
            break;
          case d4:
            mode = d1;
            break;
          default:
            //something random changed mode to an invalid value? Get it back on track.
            mode = d1;
            break;
        }
      }
    }
  }

  // save the button reading
  lastButtonState = reading;
}

void readPots() {
  //read in the potentiometer values.
  //Depending on the mode, this will update different global variables

  float knob1 = (float)analogRead(pot1)/2;   // frequency
  float knob2 = (float)analogRead(pot2)/2;   // length
  float knob3 = (float)analogRead(pot3)/2;   // secondMix
  float knob4 = (float)analogRead(pot4)/2;   // pitchMod

  switch (mode) {
    case d1:
      drum1.frequency(knob1);
      drum1.length(knob2);
      drum1.secondMix(knob3);
      drum1.pitchMod(knob4);
      break;
    case d2:
      drum2.frequency(knob1);
      drum2.length(knob2);
      drum2.secondMix(knob3);
      drum2.pitchMod(knob4);
      break;
    case d3:
      drum3.frequency(knob1);
      drum3.length(knob2);
      drum3.secondMix(knob3);
      drum3.pitchMod(knob4);
      break;
    case d4:
      drum4.frequency(knob1);
      drum4.length(knob2);
      drum4.secondMix(knob3);
      drum4.pitchMod(knob4);
      break;
  }
}

void playDrums() {
    
  gate1.update();
  gate2.update();
  gate3.update();
  gate4.update();
  
  if (gate1.fallingEdge()) {
    drum1.noteOn();
    timeout = 0;
  }
  if (gate2.fallingEdge()) {
    drum2.noteOn();
    timeout = 0;
  }
  if (gate3.fallingEdge()) {
    drum3.noteOn();
    timeout = 0;
  }
  if (gate4.fallingEdge()) {
    drum4.noteOn();
    timeout = 0;
  }
}
