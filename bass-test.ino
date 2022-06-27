#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=123,317
AudioEffectEnvelope      envelope1;      //xy=328,339
AudioSynthWaveformModulated waveformMod1;   //xy=502,286
AudioFilterStateVariable filter1;        //xy=666,315
AudioOutputI2S           i2s1;           //xy=838,326
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, waveformMod1, 0);
AudioConnection          patchCord3(envelope1, 0, filter1, 1);
AudioConnection          patchCord4(waveformMod1, 0, filter1, 0);
AudioConnection          patchCord5(filter1, 2, i2s1, 0);
AudioConnection          patchCord6(filter1, 2, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=100,46
// GUItool: end automatically generated code

#include <Bounce.h>
Bounce gateIn = Bounce(31,15);

void setup() {
  Serial.begin(9600);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  AudioMemory(48);
  
  //kick////////////////////////////////////

  pinMode(31,INPUT_PULLUP);
}

void loop() {
  AudioNoInterrupts();
  
    gateIn.update();
    if (gateIn.fallingEdge()) {
      kickClickEnv.noteOn();
      kickSwoopEnv.noteOn();
      kickAmpEnv.noteOn();
      Serial.println("Button Released, sending NoteOn");
    }
    
    if (gateIn.risingEdge()) {
      kickClickEnv.noteOff();
      kickSwoopEnv.noteOff();
      kickAmpEnv.noteOff();
      Serial.println("Button Released, sending NoteOff");
      Serial.println();
    }
  
}
