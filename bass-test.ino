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
AudioSynthWaveform       kickPulse;      //xy=123,317
AudioEffectEnvelope      kickPulseEnv;      //xy=328,339
AudioSynthWaveformModulated kickSine;   //xy=502,286
AudioFilterStateVariable kickLPF;        //xy=666,315
AudioOutputI2S           i2s1;           //xy=838,326
AudioConnection          patchCord1(kickPulse, kickPulseEnv);
AudioConnection          patchCord2(kickPulseEnv, 0, kickSine, 0);
AudioConnection          patchCord3(kickPulseEnv, 0, kickLPF, 1);
AudioConnection          patchCord4(kickSine, 0, kickLPF, 0);
AudioConnection          patchCord5(kickLPF, 2, i2s1, 0);
AudioConnection          patchCord6(kickLPF, 2, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=100,46
// GUItool: end automatically generated code

#include <Bounce.h>
Bounce gateIn = Bounce(31,15);

void setup() {
  Serial.begin(9600);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  AudioMemory(48);
  
  //kick 
  kickPulse.begin(WAVEFORM_PULSE);
  kickPulse.frequency(10);

  kickPulseEnv.attack(1);
  kickPulseEnv.sustain(0);
  kickPulseEnv.decay(150);
  kickPulseEnv.release(1);

  kickSine.begin(WAVEFORM_SINE)
  kickSine.frequency(10);

  kickLPF.frequency(1500);
  kickLPF.resonance(5);

  pinMode(31,INPUT_PULLUP);
}

void loop() {
  AudioNoInterrupts();
  
    gateIn.update();
    if (gateIn.fallingEdge()) {
      kickPulseEnv.noteOn();
      Serial.println("Button Released, sending NoteOn");
      Serial.println();
    }
    
    if (gateIn.risingEdge()) {
      kickPulseEnv.noteOff();
      Serial.println("Button Released, sending NoteOff");
      Serial.println();
    }
  
}
