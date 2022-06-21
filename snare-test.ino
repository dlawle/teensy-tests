#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=107,246
AudioSynthNoiseWhite     noise1;         //xy=166,356
AudioEffectEnvelope      envelope1;      //xy=287,246
AudioEffectMultiply      multiply1;      //xy=492,348
AudioMixer4              mixer1;         //xy=670,342
AudioOutputI2S           i2s1;           //xy=866,349
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(noise1, 0, multiply1, 1);
AudioConnection          patchCord3(envelope1, 0, multiply1, 0);
AudioConnection          patchCord4(multiply1, 0, mixer1, 2);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=97,38
// GUItool: end automatically generated code


// inputs
#define pot1            A12 // frequency
#define pot2            A13 // offset
#define pot3            A14 // pulsewidth

void setup() {
  Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);

  // I2S audio init
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);

  AudioInterrupts();

  // Set square wave
  waveform1.begin(square)
}


void loop() {

  // read pot levels
  float knob1 = (float)analogRead(pot1) / 1023.0;  // frequency
  float knob2 = (float)analogRead(pot2) / 1023.0;  // offset
  float knob3 = (float)analogRead(pot3) / 1023.0;  // pulsewidth

  waveform1.frequency(knob1)
  waveform1.offset(knob2)
  waveform1.pulsewidth(knob3)

  Serial.print("Frequency: ");
  Serial.print(knob1 * 100.0);
  Serial.print("%, Offset: ");
  Serial.print(knob2 * 100.0);
  Serial.print("%, Pulse Width: ");
  Serial.print(knob3 * 100.0);
  Serial.print("% / ");

  // determine how much actual memory is needed for the audio processes
  Serial.print("Max audio blocks used: ");
  Serial.println(AudioMemoryUsageMax());
  Serial.println();
  delay(100);}

}
