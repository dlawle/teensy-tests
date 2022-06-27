#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

Bounce button0 = Bounce(25,15);

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       snareSquare;      //xy=127,180
AudioSynthWaveform       snareTri;      //xy=128,231
AudioSynthNoiseWhite     snareNoise;         //xy=128,275
AudioMixer4              snareMix;         //xy=280,221
AudioSynthWaveformSine   snareContour;          //xy=287,130
AudioAmplifier           snareAmp;           //xy=410,70
AudioFilterStateVariable snareLP;        //xy=427,224
AudioEffectMultiply      snareVCA;      //xy=593,223
AudioOutputI2S           i2s1;           //xy=759,222
AudioConnection          patchCord1(snareSquare, 0, snareMix, 1);
AudioConnection          patchCord2(snareTri, 0, snareMix, 2);
AudioConnection          patchCord3(snareNoise, 0, snareMix, 3);
AudioConnection          patchCord4(snareMix, 0, snareLP, 0);
AudioConnection          patchCord5(snareContour, snareAmp);
AudioConnection          patchCord6(snareAmp, 0, snareLP, 1);
AudioConnection          patchCord7(snareAmp, 0, snareVCA, 0);
AudioConnection          patchCord8(snareLP, 2, snareVCA, 1);
AudioConnection          patchCord9(snareVCA, 0, i2s1, 0);
AudioConnection          patchCord10(snareVCA, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=132,73
// GUItool: end automatically generated code


// inputs
#define pot1            A15 // EnvDecay
#define pot2            A16 // Waveform 1 Freq
#define pot3            A17 // Noise Amplitude
#define pot4            A12 // BP Freq
#define pot5            A13 // LP Freq

void setup() {
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  
  // Pins
  pinMode(25, INPUT_PULLUP);
  
  // Set Waveforms
  waveform1.begin(WAVEFORM_SAWTOOTH_REVERSE);
  waveform1.frequency(180);
  waveform1.amplitude(.75);
  //sine1.frequency(111);
  //sine1.amplitude(.75);
  noise1.amplitude(.75);
  
  // Set Mixer 
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3 , 0.5);

  //envelope
  envelope1.attack(0);
  envelope1.hold(5);
  envelope1.delay(0);
  envelope1.sustain(0);
  envelope1.release(70);

  // Filter Resonance
  filter1.resonance(0.7);
  filter2.resonance(0.7);

}

elapsedMillis timeout = 0;

void loop() { 
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // Waveform 1 Freq
  float knob3 = (float)analogRead(pot3)/4;   // Noise Amplitude
  float knob4 = (float)analogRead(pot4)/4;     // BP Freq
  float knob5 = (float)analogRead(pot5)/2;     // LP Freq

  envelope1.decay(knob1);
  waveform1.frequency(knob2);
  noise1.amplitude(knob2);
  filter1.frequency(knob4);
  filter2.frequency(knob5);
  

  button0.update();
  if (button0.fallingEdge()) {
    envelope1.noteOn();
      Serial.println("Button Released, sending NoteOn");
      Serial.print("Decay Value read: ");
      Serial.println(knob1);
      Serial.print("Waveform 1 Freq Value read: ");
      Serial.println(knob2);
      Serial.print("Noise Amplitude Value read: ");
      Serial.println(knob3);
      Serial.print("BP Freq Value read: ");
      Serial.println(knob4);
      Serial.print("LP Freq Value read: ");
      Serial.println(knob5);
      timeout = 0;
    timeout = 0;
  }
  
  if (button0.risingEdge()) {
    envelope1.noteOff();
    Serial.println("Button Released, sending NoteOff");
    Serial.println();
    timeout = 0;
  }
}
