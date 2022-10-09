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
AudioSynthWaveformSineModulated HHSineMod1;     //xy=355.00001525878906,299.50000190734863
AudioSynthWaveformSineModulated HHSineMod2;     //xy=523.0000152587891,301.50000190734863
AudioEffectEnvelope      HHModEnv;       //xy=677.0000152587891,299.50000190734863
AudioSynthNoiseWhite     HHNoise;        //xy=752.0000152587891,409.50000190734863
AudioSynthWaveformSineModulated HHSineCarrier;  //xy=836.0000152587891,299.50000190734863
AudioEffectEnvelope      HHModAMpEnv;    //xy=885.0000152587891,347.50000190734863
AudioEffectEnvelope      HHnoiseEnv;     //xy=896.0000152587891,409.50000190734863
AudioMixer4              HHMixer;        //xy=1062.000015258789,420.50000190734863
AudioFilterStateVariable HHfilter;       //xy=1228.000015258789,369.50000190734863
AudioSynthSimpleDrum     drum3;          //xy=1358,184
AudioSynthSimpleDrum     drum2;          //xy=1360,149
AudioSynthSimpleDrum     drum1;          //xy=1361,114
AudioEffectEnvelope      HHAmpEnv;       //xy=1373.000015258789,387.50000190734863
AudioAnalyzePeak         HHPeak;         //xy=1400.000015258789,327.50000190734863
AudioMixer4              mixer1;         //xy=1595,182
AudioOutputI2S           i2s1;           //xy=1900,131
AudioConnection          patchCord1(HHSineMod1, HHSineMod2);
AudioConnection          patchCord2(HHSineMod2, HHModEnv);
AudioConnection          patchCord3(HHModEnv, HHSineCarrier);
AudioConnection          patchCord4(HHNoise, HHnoiseEnv);
AudioConnection          patchCord5(HHSineCarrier, HHModAMpEnv);
AudioConnection          patchCord6(HHModAMpEnv, 0, HHMixer, 0);
AudioConnection          patchCord7(HHModAMpEnv, 0, HHfilter, 1);
AudioConnection          patchCord8(HHnoiseEnv, 0, HHMixer, 1);
AudioConnection          patchCord9(HHMixer, 0, HHfilter, 0);
AudioConnection          patchCord10(HHfilter, 2, HHAmpEnv, 0);
AudioConnection          patchCord11(drum3, 0, mixer1, 2);
AudioConnection          patchCord12(drum2, 0, mixer1, 1);
AudioConnection          patchCord13(drum1, 0, mixer1, 0);
AudioConnection          patchCord14(HHAmpEnv, HHPeak);
AudioConnection          patchCord15(HHAmpEnv, 0, mixer1, 3);
AudioConnection          patchCord16(mixer1, 0, i2s1, 0);
AudioConnection          patchCord17(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1600,33
// GUItool: end automatically generated code



// https://forum.arduino.cc/t/use-a-single-knob-for-mutli-variables/311022/14 
// handling multiple variables with single pot 
enum modes {d1, d2, d3, d4};
modes mode; //the current mode must be stored in a global variable

const int switchPin = 32;    // the number of the pushbutton pin
int led1 = 31;
int led2 = 30;
int led3 = 29;
int led4 = 28;

const unsigned long debounceDelay = 50;    // the debounce time milliseconds; increase if the output flickers

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // audio library init
  AudioMemory(40);
  
  // Pins
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

//  mode = d1;
//  digitalWrite(led2, LOW);
//  digitalWrite(led3, LOW);
//  digitalWrite(led4, LOW);
//  digitalWrite(led1, HIGH);
  
  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);
  
  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);
  
  drum3.frequency(60);
  drum3.length(800);
  drum3.secondMix(0.0);
  drum3.pitchMod(1.0);
  

  // from https://github.com/otem/Eurorack/tree/master/TeensyDrumV2
  //HiHat 1 ////////////////////////////////////
  HHModAMpEnv.attack(1);
  HHModAMpEnv.decay(50);
  HHModAMpEnv.sustain(0);
  HHModAMpEnv.release(10);

  HHSineCarrier.amplitude(0.75);  
  HHSineCarrier.frequency(4000);

  HHSineMod1.frequency(2500);
  HHSineMod2.frequency(1250);

  HHModEnv.attack(0);
  HHModEnv.decay(50);
  HHModEnv.sustain(0);
  HHModEnv.release(10);

  HHfilter.frequency(2000);
  HHNoise.amplitude(0.5);

  HHnoiseEnv.attack(2);
  HHnoiseEnv.decay(250);
  HHnoiseEnv.sustain(0);
  HHnoiseEnv.release(10);

  HHMixer.gain(0,0.3);
  HHMixer.gain(1,0.5);

  HHAmpEnv.attack(1);
  HHAmpEnv.decay(300);
  HHAmpEnv.sustain(0);
  HHAmpEnv.release(10);

  sgtl5000_1.enable();
  sgtl5000_1.unmuteLineout();
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
  bool reading = digitalRead(switchPin);

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
          digitalWrite(led1, LOW);
          digitalWrite(led2, HIGH);
          break;
        case d2:
          mode = d3;
          digitalWrite(led2, LOW);
          digitalWrite(led3, HIGH);
          break;
        case d3:
          mode = d4;
          digitalWrite(led3, LOW);
          digitalWrite(led4, HIGH);
          break;
        case d4:
          mode = d1;
          digitalWrite(led4, LOW);
          digitalWrite(led1, HIGH);
          break;
        default:
          //something random changed mode to an invalid value? Get it back on track.
          mode = d1;
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          digitalWrite(led1, HIGH);
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
      HHAmpEnv.decay(knob1);
      HHModEnv.decay(knob2);
      HHfilter.frequency(knob3);
      HHModAMpEnv.decay(knob4);
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
      HHnoiseEnv.noteOn();
      HHAmpEnv.noteOn();
      HHModAMpEnv.noteOn();
      HHModEnv.noteOn();
    timeout = 0;
  }
}
