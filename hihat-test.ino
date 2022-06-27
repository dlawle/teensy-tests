#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

Bounce button0 = Bounce(31,15);

// inputs
#define pot1            A10 // EnvDecay
#define pot2            A11 // Waveform 1 Freq

// GUItool: begin automatically generated code
AudioSynthWaveform       hatPulseMod;      //xy=182,202
AudioSynthWaveformModulated hatPulse;   //xy=352,201
AudioFilterStateVariable hatHP;        //xy=490,235
AudioFilterStateVariable hatBP;        //xy=492,181
AudioEffectEnvelope      hatBPEnv;      //xy=618,187
AudioEffectEnvelope      hatHPEnv;      //xy=618,222
AudioAmplifier           hatHPAmp; //xy=755,222
AudioAmplifier           hatBPAmp;           //xy=756,187
AudioMixer4              hatMixer;         //xy=893,204
AudioEffectEnvelope      hatEnv;      //xy=1026,204
AudioOutputI2S           i2s1;           //xy=1161,206
AudioConnection          patchCord1(hatPulseMod, 0, hatPulse, 0);
AudioConnection          patchCord2(hatPulseMod, 0, hatPulse, 1);
AudioConnection          patchCord3(hatPulse, 0, hatBP, 0);
AudioConnection          patchCord4(hatPulse, 0, hatHP, 0);
AudioConnection          patchCord5(hatHP, 0, hatHPEnv, 0);
AudioConnection          patchCord6(hatBP, 1, hatBPEnv, 0);
AudioConnection          patchCord7(hatBPEnv, hatBPAmp);
AudioConnection          patchCord8(hatHPEnv, hatHPAmp);
AudioConnection          patchCord9(hatHPAmp, 0, hatMixer, 2);
AudioConnection          patchCord10(hatBPAmp, 0, hatMixer, 1);
AudioConnection          patchCord11(hatMixer, hatEnv);
AudioConnection          patchCord12(hatEnv, 0, i2s1, 0);
AudioConnection          patchCord13(hatEnv, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=306,129
// GUItool: end automatically generated code


void setup() {
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  
  // Pins
  pinMode(31, INPUT_PULLUP);

  
}

elapsedMillis timeout = 0;

void loop() {
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // Waveform 1 Freq
  
  snareEnv.decay(knob1);
  snareTri.frequency(knob2);
  snareSquare.frequency(knob2);
  snareContour.frequency(knob2);
  
  button0.update();
  if (button0.fallingEdge()) {
    snareEnv.noteOn();
    timeout = 0;
  }
  
  if (button0.risingEdge()) {
    //envelope1.noteOff();
    Serial.println("Button Released, sending NoteOff");
    Serial.println();
    timeout = 0;
}
}
