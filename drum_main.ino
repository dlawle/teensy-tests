#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

Bounce button0 = Bounce(33,15);

// inputs
#define pot1            A13 // EnvDecay
#define pot2            A14 // Filter 1
#define pot3            A15 // Filter 2
#define pot4            A16 // Tone 1
#define pot5            A17 // Tone 2

// Audio Processing Nodes
AudioSynthWaveform              hatPulse; //xy=90,715
AudioSynthWaveform              cymPulse; //xy=90,925
AudioSynthWaveform              bassSine1; //xy=125,240
AudioSynthWaveform              bassSine2; //xy=120,310
AudioSynthNoiseWhite            snareNoise; //xy=120,455
AudioSynthWaveform              snareSaw; //xy=120,615
AudioSynthNoiseWhite            hatNoise; //xy=100,825
AudioSynthNoiseWhite            cymNoise; //xy=100,1035
AudioFilterStateVariable        bassBP; //xy=290,245
AudioFilterStateVariable        bassLP; //xy=295,315
AudioEffectEnvelope             bassEnv; //xy=295,380
AudioFilterStateVariable        snareBP; //xy=265,465
AudioFilterStateVariable        snareLP; //xy=265,530
AudioEffectMultiply             hatVCA; //xy=245,765
AudioEffectMultiply             cymVCA; //xy=245,975
AudioMixer4                     bassMixer; //xy=430,280
AudioMixer4                     snareMixer; //xy=410,490
AudioEffectEnvelope             snareEnv; //xy=405,615
AudioFilterStateVariable        hatBP; //xy=400,720
AudioFilterStateVariable        hatLP; //xy=400,805
AudioFilterStateVariable        cymBP; //xy=400,930
AudioFilterStateVariable        cymLP; //xy=400,1015
AudioMixer4                     hatMixer; //xy=530,755
AudioMixer4                     cymMixer; //xy=530,965
AudioEffectMultiply             bassVCA; //xy=675,375
AudioEffectMultiply             snareVCA; //xy=685,540
AudioEffectEnvelope             hatEnv; //xy=680,755
AudioEffectEnvelope             cymEnv; //xy=680,965
AudioMixer4                     masterMixer; //xy=909,561
AudioOutputI2S                  i2s; //xy=1070,560

// Audio Connections (all connections (aka wires or links))
AudioConnection        patchCord1(hatPulse, 0, hatVCA, 0);
AudioConnection        patchCord2(cymPulse, 0, cymVCA, 0);
AudioConnection        patchCord3(bassSine1, 0, bassBP, 0);
AudioConnection        patchCord4(bassSine2, 0, bassEnv, 0);
AudioConnection        patchCord5(bassSine2, 0, bassLP, 0);
AudioConnection        patchCord6(snareNoise, 0, snareBP, 0);
AudioConnection        patchCord7(snareSaw, 0, snareLP, 1);
AudioConnection        patchCord8(snareSaw, 0, snareEnv, 0);
AudioConnection        patchCord9(hatNoise, 0, hatVCA, 1);
AudioConnection        patchCord10(cymNoise, 0, cymVCA, 1);
AudioConnection        patchCord11(bassBP, 1, bassMixer, 1);
AudioConnection        patchCord12(bassLP, 2, bassMixer, 2);
AudioConnection        patchCord13(bassEnv, 0, bassVCA, 1);
AudioConnection        patchCord14(snareBP, 1, snareMixer, 1);
AudioConnection        patchCord15(snareLP, 2, snareMixer, 2);
AudioConnection        patchCord16(hatVCA, 0, hatBP, 0);
AudioConnection        patchCord17(hatVCA, 0, hatLP, 1);
AudioConnection        patchCord18(cymVCA, 0, cymBP, 0);
AudioConnection        patchCord19(cymVCA, 0, cymLP, 1);
AudioConnection        patchCord20(bassMixer, 0, bassVCA, 0);
AudioConnection        patchCord21(snareMixer, 0, snareVCA, 0);
AudioConnection        patchCord22(snareEnv, 0, snareVCA, 1);
AudioConnection        patchCord23(hatBP, 1, hatMixer, 1);
AudioConnection        patchCord24(hatLP, 0, hatMixer, 2);
AudioConnection        patchCord25(cymBP, 1, cymMixer, 1);
AudioConnection        patchCord26(cymLP, 0, cymMixer, 2);
AudioConnection        patchCord27(hatMixer, 0, hatEnv, 0);
AudioConnection        patchCord28(cymMixer, 0, cymEnv, 0);
AudioConnection        patchCord29(bassVCA, 0, masterMixer, 0);
AudioConnection        patchCord30(snareVCA, 0, masterMixer, 1);
AudioConnection        patchCord31(hatEnv, 0, masterMixer, 2);
AudioConnection        patchCord32(cymEnv, 0, masterMixer, 3);
AudioConnection        patchCord33(masterMixer, 0, i2s, 0);
AudioConnection        patchCord34(masterMixer, 0, i2s, 1);

// Control Nodes (all control nodes (no inputs or outputs))
AudioControlSGTL5000     sgtl5000_1;     //xy=110,175

// Configure params

//////////////////////////
// BASS DRUM PARAMETERS //
//////////////////////////

//  BASS MIXER
bassMixer.gain(0, 0.5);
bassMixer.gain(1, 0.5);
bassMixer.gain(2, 0.5);
bassMixer.gain(3 , 0.5);

// BASS SINE 1
bassSine1.begin(WAVEFORM_SINE);
bassSine1.amplitude(1.5);
bassSine1.frequency(50);
bassSine1.pulseWidth(.5);

// BASS SINE 2
bassSine2.begin(WAVEFORM_SINE);
bassSine2.amplitude(1.5);
bassSine2.frequency(50);
bassSine2.pulseWidth(.5);

// BASS ENV
bassEnv.attack(0);
bassEnv.hold(5);
bassEnv.delay(0);
bassEnv.sustain(0);
bassEnv.release(70);

// Filter Resonance
bassBP.resonance(0.7);
bassLP.resonance(0.7);



//////////////////////////
// SNARE PARAMETERS     //
//////////////////////////

// SNARE WAVEFORMS
snareSaw.begin(WAVEFORM_SAWTOOTH_REVERSE);
snareSaw.frequency(180);
snareSaw.amplitude(.75);
snareNoise.amplitude(.75);

// SNARE MIXER 
snareMixer.gain(0, 0.5);
snareMixer.gain(1, 0.5);
snareMixer.gain(2, 0.5);
snareMixer.gain(3 , 0.5);

// SNARE ENVELOPE
snareEnv.attack(0);
snareEnv.hold(5);
snareEnv.delay(0);
snareEnv.sustain(0);
snareEnv.release(70);

// SNARE FILTER
snareBP.resonance(0.7);
snareLP.resonance(0.7);

//////////////////////////
// "HIHAT" PARAMETERS   //
//////////////////////////

// HIHAT WAVEFORMS
hatPulse.begin(WAVEFORM_PULSE);
hatPulse.frequency(30000);
hatPulse.amplitude(.75);
hatNoise.amplitude(.75);

// HIHAT MIXER
hatMixer.gain(0, 0.5);
hatMixer.gain(1, 0.5);
hatMixer.gain(2, 0.5);
hatMixer.gain(3 , 0.5);

// HIHAT ENVELOPE
hatEnv.attack(0);
hatEnv.hold(5);
hatEnv.delay(0);
hatEnv.sustain(0);
hatEnv.release(150);

// HIHAT Filter
hatBP.resonance(0.7);
hatLP.resonance(0.7);


//////////////////////////
// "CYMBAL" PARAMETERS   //
//////////////////////////

// CYMBAL WAVEFORMS
cymPulse.begin(WAVEFORM_PULSE);
cymPulse.frequency(30000);
cymPulse.amplitude(.75);
cymNoise.amplitude(.75);

// CYMBAL MIXER
cymMixer.gain(0, 0.5);
cymMixer.gain(1, 0.5);
cymMixer.gain(2, 0.5);
cymMixer.gain(3 , 0.5);

// CYMBAL ENVELOPE
cymEnv.attack(0);
cymEnv.hold(5);
cymEnv.delay(0);
cymEnv.sustain(0);
cymEnv.release(150);

// CYMBAL Filter
cymBP.resonance(0.7);
cymLP.resonance(0.7);


void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  
  // Pins
  pinMode(25, INPUT_PULLUP); // test trigger
  pinMode(28, INPUT_PULLUP); // mode select
  pinMode(29, INPUT_PULLUP); // mode select
  pinMode(30, INPUT_PULLUP); // mode select
  pinMode(31, INPUT_PULLUP); // mode select
}

elapsedMillis timeout = 0;

void loop() {
 
 float knob1 = (float)analogRead(pot1)/2;   // EnvDecay
 float knob2 = (float)analogRead(pot2)/2;   // Filter 1 
 float knob3 = (float)analogRead(pot3)/2;   // Filter 2
 float knob4 = (float)analogRead(pot4)/2;   // Tone 1 
 float knob5 = (float)analogRead(pot5)/2;   // Tone 2 

 if (digitalRead(6) == LOW) {
	  bassEnv.decay(knob1);
	  bassBP.frequency(knob2);
	  bassLP.frequency(knob2);
	  bassSine1.frequency(knob4);
	  bassSine2.frequency(knob5);
	  if (button0.fallingEdge()) {
		Serial.println("Sending Drum Trigger");
		envelope1.noteOn();
		timeout = 0;
	  }
	  if (button0.risingEdge()) {
		bassEnv.noteOff();
		Serial.println("Trigger Released, sending NoteOff");
		Serial.println();
		timeout = 0;
   	  }
 } else if (digitalRead(7) == LOW) {
	  snareEnv.decay(knob1);
	  snareBP.frequency(knob2);
	  snareLP.frequency(knob2);
	  snareSaw.frequency(knob4);
	  snareNoise.frequency(knob5); 
	  if (button0.fallingEdge()) {
		Serial.println("Sending Snare Trigger");
		snareEnv.noteOn();
		timeout = 0;
	  }
	  if (button0.risingEdge()) {
		snareEnv.noteOff();
		Serial.println("Trigger Released, sending NoteOff");
		Serial.println();
		timeout = 0;
   	  }
 }else if (digitalRead(8) == LOW) {
  	  hatEnv.decay(knob1);
	  hatBP.frequency(knob2);
	  hatLP.frequency(knob2);
	  hatPulse.frequency(knob4);
	  hatNoise.frequency(knob5); 
	  if (button0.fallingEdge()) {
		Serial.println("Sending hat Trigger");
		hatEnv.noteOn();
		timeout = 0;
	  }
	  if (button0.risingEdge()) {
		hatEnv.noteOff();
		Serial.println("Trigger Released, sending NoteOff");
		Serial.println();
		timeout = 0;
   	  }
 }else if (digitalRead(9) == LOW) {
          cymEnv.decay(knob1);
	  cymBP.frequency(knob2);
	  cymLP.frequency(knob2);
	  cymPulse.frequency(knob4);
	  cymNoise.frequency(knob5); 
 	  if (button0.fallingEdge()) {
		Serial.println("Sending cymble Trigger");
		cymEnv.noteOn();
		timeout = 0;
	  }
	  if (button0.risingEdge()) {
		cymEnv.noteOff();
		Serial.println("Trigger Released, sending NoteOff");
		Serial.println();
		timeout = 0;
   	  }
 }


}
