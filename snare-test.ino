#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

Bounce button0 = Bounce(31,15);

// inputs
#define pot1            A10 // EnvDecay
#define pot2            A11 // Waveform 1 Freq

// GUItool: begin automatically generated code
AudioSynthWaveform       snareSquare;      //xy=127,180
AudioSynthWaveform       snareTri;      //xy=128,231
AudioSynthNoiseWhite     snareNoise;         //xy=128,275
AudioMixer4              snareMix;         //xy=280,221
AudioSynthWaveformSine   snareContour;          //xy=287,130
AudioAmplifier           snareAmp;           //xy=410,70
AudioFilterStateVariable snareLP;        //xy=427,224
AudioEffectMultiply      snareVCA;      //xy=593,223
AudioEffectEnvelope      snareEnv;      //xy=763,221
AudioOutputI2S           i2s1;           //xy=914,220
AudioConnection          patchCord1(snareSquare, 0, snareMix, 1);
AudioConnection          patchCord2(snareTri, 0, snareMix, 2);
AudioConnection          patchCord3(snareNoise, 0, snareMix, 3);
AudioConnection          patchCord4(snareMix, 0, snareLP, 0);
AudioConnection          patchCord5(snareContour, snareAmp);
AudioConnection          patchCord6(snareAmp, 0, snareLP, 1);
AudioConnection          patchCord7(snareAmp, 0, snareVCA, 0);
AudioConnection          patchCord8(snareLP, 2, snareVCA, 1);
AudioConnection          patchCord9(snareVCA, snareEnv);
AudioConnection          patchCord10(snareEnv, 0, i2s1, 0);
AudioConnection          patchCord11(snareEnv, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=132,73
// GUItool: end automatically generated code

void setup() {
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  
  // Pins
  pinMode(31, INPUT_PULLUP);

  // Snare 
  snareSquare.begin(WAVEFORM_SQUARE);
  snareSquare.frequency(50);
  snareSquare.amplitude(1.5);

  snareTri.begin(WAVEFORM_TRIANGLE);
  snareTri.frequency(50);
  snareTri.amplitude(1.5);

  snareNoise.amplitude(1);

  snareContour.frequency(50);
  snareContour.amplitude(1.5);
  snareAmp.gain(1);

  snareLP.resonance(1);
  snareLP.frequency(300);

  snareMix.gain(0, 0.5);
  snareMix.gain(1, 0.5);
  snareMix.gain(2, 0.5);
  snareMix.gain(3, 0.5);

  snareEnv.attack(0);
  snareEnv.hold(5);
  snareEnv.delay(0);
  snareEnv.sustain(0);
  snareEnv.release(70);

}

void loop() {
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // Waveform 1 Freq
  
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
