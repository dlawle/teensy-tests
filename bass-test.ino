#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

Bounce button0 = Bounce(25,15);

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=168,195
AudioSynthWaveform       waveform1;      //xy=178,396
AudioFilterStateVariable filter1;        //xy=356,131
AudioFilterStateVariable filter2;        //xy=356,323
AudioEffectEnvelope      envelope1;      //xy=561,505
AudioMixer4              mixer1;         //xy=570,216
AudioEffectMultiply      multiply1;      //xy=829,310
AudioOutputI2S           i2s2;           //xy=1035,311
AudioConnection          patchCord1(waveform2, 0, filter1, 0);
AudioConnection          patchCord2(waveform1, envelope1);
AudioConnection          patchCord3(waveform1, 0, filter2, 0);
AudioConnection          patchCord4(filter1, 1, mixer1, 1);
AudioConnection          patchCord5(filter2, 2, mixer1, 2);
AudioConnection          patchCord6(envelope1, 0, multiply1, 1);
AudioConnection          patchCord7(mixer1, 0, multiply1, 0);
AudioConnection          patchCord8(multiply1, 0, i2s2, 0);
AudioConnection          patchCord9(multiply1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=208,89
// GUItool: end automatically generated code


// inputs
#define pot1            A15 // EnvDecay
#define pot2            A16 // Waveform 1 Freq
#define pot3            A17 // Waveform 2 Freq
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
  
  // Mixer 
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3 , 0.5);
  
  // Waveform 1
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(1.5);
  waveform1.frequency(50);
  waveform1.pulseWidth(.5);

  // Waveform 2
  waveform2.begin(WAVEFORM_SINE);
  waveform2.amplitude(1.5);
  waveform2.frequency(50);
  waveform2.pulseWidth(.5);
  
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
  float knob3 = (float)analogRead(pot3)/4;   // Waveform 2 Freq
  float knob4 = (float)analogRead(pot4)/4;     // BP Freq
  float knob5 = (float)analogRead(pot5)/2;     // LP Freq

  envelope1.decay(knob1);
  waveform1.frequency(knob2);
  waveform2.frequency(knob2);
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
      Serial.print("Waveform 2 Freq Value read: ");
      Serial.println(knob2);
      Serial.print("BP Freq Value read: ");
      Serial.println(knob4);
      Serial.print("LP Freq Value read: ");
      Serial.println(knob5);
      timeout = 0;
    }
    
    if (button0.risingEdge()) {
      envelope1.noteOff();
      Serial.println("Button Released, sending NoteOff");
      Serial.println();
      timeout = 0;
    }
}
