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
AudioSynthWaveformSineModulated snareFM1;       //xy=194,807
AudioSynthNoiseWhite     snareNoise;     //xy=223,959
AudioSynthWaveformSineModulated snareFM2;       //xy=327,869
AudioEffectEnvelope      snareNoiseEnv;  //xy=452,948
AudioEffectEnvelope      snareFMEnv;     //xy=478,886
AudioSynthWaveformSineModulated snareClickCarrier; //xy=534,795
AudioEffectEnvelope      snareClickEnv;  //xy=567,749
AudioFilterStateVariable snareNoiseHPF;  //xy=636,949
AudioSynthWaveformSineModulated snareBody;      //xy=639,885
AudioFilterStateVariable snareClickFilter; //xy=749,772
AudioMixer4              snareMixer;     //xy=835,894
AudioEffectEnvelope      snareAmpEnv;    //xy=1009,895
AudioAnalyzePeak         snarePeak;      //xy=1065,845
AudioFilterStateVariable finalSnareFilter; //xy=1262,875
AudioOutputI2S           i2s1;           //xy=1523,873
AudioConnection          patchCord1(snareFM1, snareFM2);
AudioConnection          patchCord2(snareNoise, snareNoiseEnv);
AudioConnection          patchCord3(snareFM2, snareFMEnv);
AudioConnection          patchCord4(snareNoiseEnv, 0, snareNoiseHPF, 0);
AudioConnection          patchCord5(snareFMEnv, snareBody);
AudioConnection          patchCord6(snareClickCarrier, snareClickEnv);
AudioConnection          patchCord7(snareClickEnv, snareClickCarrier);
AudioConnection          patchCord8(snareClickEnv, 0, snareClickFilter, 0);
AudioConnection          patchCord9(snareNoiseHPF, 2, snareMixer, 2);
AudioConnection          patchCord10(snareBody, 0, snareMixer, 1);
AudioConnection          patchCord11(snareClickFilter, 1, snareMixer, 0);
AudioConnection          patchCord12(snareMixer, snareAmpEnv);
AudioConnection          patchCord13(snareAmpEnv, snarePeak);
AudioConnection          patchCord14(snareAmpEnv, 0, finalSnareFilter, 0);
AudioConnection          patchCord15(finalSnareFilter, 2, i2s1, 0);
AudioConnection          patchCord16(finalSnareFilter, 2, i2s1, 1);
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

  snareAmpEnv.attack(1);
  snareAmpEnv.sustain(0);
  snareAmpEnv.decay(100);
  snareAmpEnv.release(1);

  snareNoiseEnv.delay(10);
  snareNoiseEnv.attack(150);
  snareNoiseEnv.sustain(1);
  snareNoiseEnv.release(1);

  snareBody.frequency(50);
  snareNoise.amplitude(1);

  snareNoiseHPF.frequency(1000);;

  snareClickCarrier.frequency(1500);
  snareClickEnv.attack(0);
  snareClickEnv.sustain(0);
  snareClickEnv.decay(500);
  snareClickEnv.release(1);
  snareClickFilter.frequency(1500);
  snareClickFilter.resonance(5);

  snareFM1.frequency(1500);
  snareFM2.frequency(400);

  snareFMEnv.attack(0);
  snareFMEnv.sustain(0);
  snareFMEnv.decay(50);
  snareFMEnv.release(1);

  finalSnareFilter.frequency(100);
  finalSnareFilter.resonance(1);
  finalSnareFilter.octaveControl(7);

  snareMixer.gain(0,0.5);
  snareMixer.gain(1,0.5);
  snareMixer.gain(2,0.3);

}

elapsedMillis timeout = 0;

void loop() {
  float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // Waveform 1 Freq
  
  snareAmpEnv.decay(knob1);
  snareFM1.frequency(knob2);
  snareFM2.frequency(knob2);
  snareBody.frequency(knob2);
  snareClickCarrier.frequency(knob2);
  
  button0.update();
  if (button0.fallingEdge()) {
      snareBody.phase(0);
      snareFM1.phase(180);
      snareFM2.phase(180);
      snareFMEnv.noteOn();
      snareClickEnv.noteOn();
      snareNoiseEnv.noteOn();
      snareAmpEnv.noteOn();
    timeout = 0;
  }
  
  if (button0.risingEdge()) {
    //envelope1.noteOff();
    Serial.println("Button Released, sending NoteOff");
    Serial.println();
    timeout = 0;
}

}
