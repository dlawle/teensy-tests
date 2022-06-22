#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

Bounce button0 = Bounce(25,15);

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=106,404
AudioSynthWaveform       waveform1;      //xy=108,595
AudioSynthNoiseWhite     noise1;         //xy=111,296
AudioFilterStateVariable filter2;        //xy=298,493
AudioFilterStateVariable filter1;        //xy=302,356
AudioMixer4              mixer1;         //xy=547,385
AudioEffectEnvelope      envelope1;      //xy=639,625
AudioEffectMultiply      multiply1;      //xy=813,384
AudioOutputI2S           i2s2;           //xy=1019,385
AudioConnection          patchCord1(sine1, 0, filter1, 1);
AudioConnection          patchCord2(waveform1, 0, filter2, 1);
AudioConnection          patchCord3(waveform1, envelope1);
AudioConnection          patchCord4(noise1, 0, filter1, 0);
AudioConnection          patchCord5(filter2, 2, mixer1, 2);
AudioConnection          patchCord6(filter1, 1, mixer1, 1);
AudioConnection          patchCord7(mixer1, 0, multiply1, 0);
AudioConnection          patchCord8(envelope1, 0, multiply1, 1);
AudioConnection          patchCord9(multiply1, 0, i2s2, 0);
AudioConnection          patchCord10(multiply1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=102,222
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
