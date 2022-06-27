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
AudioSynthWaveformSineModulated HHSineMod1;     //xy=111,284
AudioSynthWaveformSineModulated HHSineMod2;     //xy=135,336
AudioEffectEnvelope      HHModEnv;       //xy=289,334
AudioSynthNoiseWhite     HHNoise;        //xy=364,444
AudioSynthWaveformSineModulated HHSineCarrier;  //xy=448,334
AudioEffectEnvelope      HHModAMpEnv;    //xy=497,382
AudioEffectEnvelope      HHnoiseEnv;     //xy=508,444
AudioMixer4              HHMixer;        //xy=674,455
AudioFilterStateVariable HHfilter;       //xy=840,404
AudioEffectEnvelope      HHAmpEnv;       //xy=1093,436
AudioOutputI2S           i2s1;           //xy=1267,436
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
AudioConnection          patchCord11(HHAmpEnv, 0, i2s1, 0);
AudioConnection          patchCord12(HHAmpEnv, 0, i2s1, 1);
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
}

elapsedMillis timeout = 0;

void loop() {
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // Waveform 1 Freq
  
  HHAmpEnv.decay(knob1);
  HHSineMod1.frequency(knob2);
  HHSineMod2.frequency(knob2);
  
  button0.update();
  if (button0.fallingEdge()) {
      HHnoiseEnv.noteOn();
      HHAmpEnv.noteOn();
      HHModAMpEnv.noteOn();
      HHModEnv.noteOn();
    timeout = 0;
  }
  
  if (button0.risingEdge()) {
    //envelope1.noteOff();
    Serial.println("Button Released, sending NoteOff");
    Serial.println();
    timeout = 0;
}
}
