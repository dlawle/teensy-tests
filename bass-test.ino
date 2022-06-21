#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=87,273
AudioSynthWaveformPWM    pwm1;           //xy=90,107
AudioFilterStateVariable filter1;        //xy=254,139
AudioFilterStateVariable filter2;        //xy=261,241
AudioEffectEnvelope      envelope1;      //xy=474,319
AudioMixer4              mixer1;         //xy=478,194
AudioEffectMultiply      multiply1;      //xy=718,259
AudioOutputI2S           i2s1;           //xy=924,260
AudioConnection          patchCord1(waveform1, 0, filter2, 1);
AudioConnection          patchCord2(pwm1, 0, filter1, 0);
AudioConnection          patchCord3(filter1, 1, mixer1, 1);
AudioConnection          patchCord4(filter2, 1, mixer1, 2);
AudioConnection          patchCord5(envelope1, 0, multiply1, 1);
AudioConnection          patchCord6(mixer1, 0, multiply1, 0);
AudioConnection          patchCord7(multiply1, 0, i2s1, 0);
AudioConnection          patchCord8(multiply1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=97,38
// GUItool: end automatically generated code
