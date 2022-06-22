#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

Bounce button0 = Bounce(25,15);

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=102,388
AudioSynthNoiseWhite     noise1;         //xy=108,506
AudioEffectMultiply      multiply1;      //xy=292,447
AudioFilterStateVariable filter1;        //xy=492,407
AudioFilterStateVariable filter2;        //xy=494,489
AudioMixer4              mixer1;         //xy=723,450
AudioEffectEnvelope      envelope1;      //xy=913,450
AudioOutputI2S           i2s1;           //xy=1085,450
AudioConnection          patchCord1(waveform1, 0, multiply1, 0);
AudioConnection          patchCord2(noise1, 0, multiply1, 1);
AudioConnection          patchCord3(multiply1, 0, filter1, 0);
AudioConnection          patchCord4(multiply1, 0, filter2, 1);
AudioConnection          patchCord5(filter1, 1, mixer1, 1);
AudioConnection          patchCord6(filter2, 0, mixer1, 2);
AudioConnection          patchCord7(mixer1, envelope1);
AudioConnection          patchCord8(envelope1, 0, i2s1, 0);
AudioConnection          patchCord9(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=102,222
// GUItool: end automatically generated code

// inputs
#define pot1            A15 // EnvDecay
#define pot2            A16 // Waveform 1 Freq
#define pot3            A17 // Noise Amplitude
#define pot4            A12 // BP Freq
#define pot5            A13 // HP Freq

void setup() {
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  
  // Pins
  pinMode(25, INPUT_PULLUP);
  
  // Set Waveforms
  waveform1.begin(WAVEFORM_PULSE);
  waveform1.frequency(30000);
  waveform1.amplitude(.75);
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
  envelope1.release(150);

  // Filter Resonance
  filter1.resonance(0.7);
  filter2.resonance(0.7);

}

elapsedMillis timeout = 0;

void loop() { 
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  //float knob2 = (float)analogRead(pot2);   // Waveform 1 Freq
  float knob3 = (float)analogRead(pot3);   // Noise Amplitude
  float knob4 = (float)analogRead(pot4);     // BP Freq
  float knob5 = (float)analogRead(pot5);     // HP Freq

  envelope1.decay(knob1);
  //waveform1.frequency(knob2);
  noise1.amplitude(knob3);
  filter1.frequency(knob4);
  filter2.frequency(knob5);
  

  button0.update();
  if (button0.fallingEdge()) {
    envelope1.noteOn();
      Serial.println("Button Released, sending NoteOn");
      Serial.print("Decay Value read: ");
      Serial.println(knob1);
      //Serial.print("Waveform 1 Freq Value read: ");
      //Serial.println(knob2);
      Serial.print("Noise Amplitude Value read: ");
      Serial.println(knob3);
      Serial.print("BP Freq Value read: ");
      Serial.println(knob4);
      Serial.print("HP Freq Value read: ");
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









