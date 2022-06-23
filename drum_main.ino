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

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable4;     //xy=80.5,600
AudioSynthNoiseWhite     noise1;         //xy=90,340
AudioSynthWavetable      wavetable3;     //xy=93,458
AudioSynthNoiseWhite     noise2;         //xy=92.5,684
AudioSynthWavetable      wavetable5;     //xy=100.5,760
AudioSynthWavetable      wavetable2;     //xy=104,189
AudioSynthWavetable      wavetable1;     //xy=108,107
AudioSynthNoisePink      pink1;          //xy=105.5,836
AudioEffectMultiply      multiply3; //xy=220.5,639
AudioEffectMultiply      multiply4; //xy=243.5,801
AudioFilterStateVariable filter1;        //xy=270,100
AudioFilterStateVariable filter2; //xy=270,180
AudioEffectEnvelope      envelope1;      //xy=271,237
AudioFilterStateVariable filter3; //xy=278,342
AudioFilterStateVariable filter4; //xy=278,422
AudioEffectEnvelope      envelope2; //xy=284,502
AudioFilterStateVariable filter5; //xy=365.5,611
AudioFilterStateVariable filter6; //xy=366.5,676
AudioFilterStateVariable filter7; //xy=388.5,773
AudioFilterStateVariable filter8; //xy=389.5,838
AudioMixer4              mixer2; //xy=421,379
AudioMixer4              mixer1;         //xy=422,133
AudioMixer4              mixer3; //xy=508.5,638
AudioMixer4              mixer4; //xy=531.5,800
AudioEffectMultiply      multiply1;      //xy=585,140
AudioEffectMultiply      multiply2; //xy=588,382
AudioEffectEnvelope      envelope3; //xy=651.5,638
AudioEffectEnvelope      envelope4; //xy=670.055534362793,798.8888740539551
AudioMixer4              mixer5; //xy=844.4444541931152,464.4444274902344
AudioOutputI2S           i2s1;           //xy=995.5555686950684,465.55557441711426
AudioConnection          patchCord1(wavetable4, 0, multiply3, 0);
AudioConnection          patchCord2(noise1, 0, filter3, 0);
AudioConnection          patchCord3(wavetable3, 0, filter4, 1);
AudioConnection          patchCord4(wavetable3, envelope2);
AudioConnection          patchCord5(noise2, 0, multiply3, 1);
AudioConnection          patchCord6(wavetable5, 0, multiply4, 0);
AudioConnection          patchCord7(wavetable2, 0, filter2, 1);
AudioConnection          patchCord8(wavetable2, envelope1);
AudioConnection          patchCord9(wavetable1, 0, filter1, 1);
AudioConnection          patchCord10(pink1, 0, multiply4, 1);
AudioConnection          patchCord11(multiply3, 0, filter5, 0);
AudioConnection          patchCord12(multiply3, 0, filter6, 1);
AudioConnection          patchCord13(multiply4, 0, filter7, 0);
AudioConnection          patchCord14(multiply4, 0, filter8, 1);
AudioConnection          patchCord15(filter1, 1, mixer1, 1);
AudioConnection          patchCord16(filter2, 2, mixer1, 2);
AudioConnection          patchCord17(envelope1, 0, multiply1, 1);
AudioConnection          patchCord18(filter3, 1, mixer2, 1);
AudioConnection          patchCord19(filter4, 2, mixer2, 2);
AudioConnection          patchCord20(envelope2, 0, multiply2, 1);
AudioConnection          patchCord21(filter5, 1, mixer3, 1);
AudioConnection          patchCord22(filter6, 0, mixer3, 2);
AudioConnection          patchCord23(filter7, 1, mixer4, 1);
AudioConnection          patchCord24(filter8, 0, mixer4, 2);
AudioConnection          patchCord25(mixer2, 0, multiply2, 0);
AudioConnection          patchCord26(mixer1, 0, multiply1, 0);
AudioConnection          patchCord27(mixer3, envelope3);
AudioConnection          patchCord28(mixer4, envelope4);
AudioConnection          patchCord29(multiply1, 0, mixer5, 0);
AudioConnection          patchCord30(multiply2, 0, mixer5, 1);
AudioConnection          patchCord31(envelope3, 0, mixer5, 2);
AudioConnection          patchCord32(envelope4, 0, mixer5, 3);
AudioConnection          patchCord33(mixer5, 0, i2s1, 0);
AudioConnection          patchCord34(mixer5, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=91,35
// GUItool: end automatically generated code



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
