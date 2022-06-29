#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

// gates
Bounce gateK = Bounce(29,5);
Bounce gateS = Bounce(30,5);
Bounce gateH = Bounce(31,5);

// inputs
#define pot1            A10 // k EnvDecay
#define pot2            A11 // k Waveform 1 Freq
#define pot3            A12 // s EnvDecay
#define pot4            A13 // s Waveform 1 Freq
#define pot5            A16 // h EnvDecay
#define pot6            A17 // h Waveform 1 Freq


// GUItool: begin automatically generated code
AudioSynthWaveformSineModulated snareFM2;       //xy=113,539
AudioSynthNoiseWhite     snareNoise;     //xy=113,577
AudioSynthWaveformSineModulated snareFM1;       //xy=120,479
AudioSynthWaveformSineModulated HHSineMod1;     //xy=130,231
AudioSynthWaveformSineModulated HHSineMod2;     //xy=154,283
AudioEffectEnvelope      snareNoiseEnv;  //xy=276,576
AudioEffectEnvelope      snareFMEnv;     //xy=278,534
AudioEffectEnvelope      HHModEnv;       //xy=308,281
AudioSynthWaveformSineModulated snareClickCarrier; //xy=329,487
AudioSynthNoiseWhite     HHNoise;        //xy=335,373
AudioEffectEnvelope      snareClickEnv;  //xy=362,441
AudioSynthWaveformSineModulated snareBody;      //xy=454,528
AudioSynthWaveformSineModulated HHSineCarrier;  //xy=467,281
AudioFilterStateVariable snareNoiseHPF;  //xy=467,580
AudioEffectEnvelope      HHModAMpEnv;    //xy=516,329
AudioEffectEnvelope      HHnoiseEnv;     //xy=518,373
AudioFilterStateVariable snareClickFilter; //xy=544,464
AudioFilterStateVariable HHfilter;       //xy=676,289
AudioSynthWaveform       waveform2;      //xy=684,670
AudioSynthWaveform       waveform1;      //xy=684,714
AudioMixer4              HHMixer;        //xy=686,372
AudioMixer4              snareMixer;     //xy=723,533
AudioFilterStateVariable filter1;        //xy=833,679
AudioFilterStateVariable filter2;        //xy=836,742
AudioEffectEnvelope      envelope1;      //xy=854,814
AudioEffectEnvelope      snareAmpEnv;    //xy=889,570
AudioAnalyzePeak         snarePeak;      //xy=891,502
AudioMixer4              mixer1;         //xy=983,704
AudioEffectEnvelope      HHAmpEnv;       //xy=1012,386
AudioFilterStateVariable finalSnareFilter; //xy=1068,543
AudioEffectMultiply      multiply1;      //xy=1120,734
AudioMixer4              masterMix;         //xy=1284,477
AudioOutputI2S           i2s1;           //xy=1419,477
AudioConnection          patchCord1(snareFM2, snareFMEnv);
AudioConnection          patchCord2(snareNoise, snareNoiseEnv);
AudioConnection          patchCord3(snareFM1, snareFM2);
AudioConnection          patchCord4(HHSineMod1, HHSineMod2);
AudioConnection          patchCord5(HHSineMod2, HHModEnv);
AudioConnection          patchCord6(snareNoiseEnv, 0, snareNoiseHPF, 0);
AudioConnection          patchCord7(snareFMEnv, snareBody);
AudioConnection          patchCord8(HHModEnv, HHSineCarrier);
AudioConnection          patchCord9(snareClickCarrier, snareClickEnv);
AudioConnection          patchCord10(HHNoise, HHnoiseEnv);
AudioConnection          patchCord11(snareClickEnv, snareClickCarrier);
AudioConnection          patchCord12(snareClickEnv, 0, snareClickFilter, 0);
AudioConnection          patchCord13(snareBody, 0, snareMixer, 1);
AudioConnection          patchCord14(HHSineCarrier, HHModAMpEnv);
AudioConnection          patchCord15(snareNoiseHPF, 2, snareMixer, 2);
AudioConnection          patchCord16(HHModAMpEnv, 0, HHMixer, 0);
AudioConnection          patchCord17(HHModAMpEnv, 0, HHfilter, 1);
AudioConnection          patchCord18(HHnoiseEnv, 0, HHMixer, 1);
AudioConnection          patchCord19(snareClickFilter, 1, snareMixer, 0);
AudioConnection          patchCord20(HHfilter, 2, HHAmpEnv, 0);
AudioConnection          patchCord21(waveform2, 0, filter1, 0);
AudioConnection          patchCord22(waveform1, envelope1);
AudioConnection          patchCord23(waveform1, 0, filter2, 0);
AudioConnection          patchCord24(HHMixer, 0, HHfilter, 0);
AudioConnection          patchCord25(snareMixer, snareAmpEnv);
AudioConnection          patchCord26(filter1, 1, mixer1, 1);
AudioConnection          patchCord27(filter2, 2, mixer1, 2);
AudioConnection          patchCord28(envelope1, 0, multiply1, 1);
AudioConnection          patchCord29(snareAmpEnv, snarePeak);
AudioConnection          patchCord30(snareAmpEnv, 0, finalSnareFilter, 0);
AudioConnection          patchCord31(mixer1, 0, multiply1, 0);
AudioConnection          patchCord32(HHAmpEnv, 0, masterMix, 0);
AudioConnection          patchCord33(finalSnareFilter, 1, masterMix, 1);
AudioConnection          patchCord34(multiply1, 0, masterMix, 2);
AudioConnection          patchCord35(masterMix, 0, i2s1, 0);
AudioConnection          patchCord36(masterMix, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000;       //xy=171,65
// GUItool: end automatically generated code


void setup() {
  
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000.enable();
  sgtl5000.volume(0.9);

  // Pins
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);

  // Master Mixer 
  masterMix.gain(0, 0.5);
  masterMix.gain(1, 0.5);
  masterMix.gain(2, 0.5);
  masterMix.gain(3, 0.5);

  /////////////////////////
  //       kick          //
  /////////////////////////
  
  // Mixer 
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3, 0.5);
  
  // Waveform 1
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(1.5);
  waveform1.frequency(50);
  //waveform1.pulseWidth(.5);

  // Waveform 2
  waveform2.begin(WAVEFORM_SINE);
  waveform2.amplitude(1.5);
  waveform2.frequency(50);
  //waveform2.pulseWidth(.5);
  
  //envelope
  envelope1.attack(0);
  envelope1.hold(5);
  envelope1.delay(0);
  envelope1.sustain(0);
  envelope1.release(70);

  // Filter Resonance
  filter1.resonance(1);
  filter2.resonance(1);
  filter1.frequency(300);
  filter1.frequency(300);
  
  /////////////////////////
  //       snare         //
  /////////////////////////

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
  
  /////////////////////////
  //       hat           //
  /////////////////////////
  
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
  float knob1 = (float)analogRead(pot1)/2;   // k EnvDecay
  float knob2 = (float)analogRead(pot2)/4;   // k Waveform Freq
  float knob3 = (float)analogRead(pot3)/2;   // s EnvDecay
  float knob4 = (float)analogRead(pot4)/4;   // s Waveform Freq
  float knob5 = (float)analogRead(pot5)/2;   // h EnvDecay
  float knob6 = (float)analogRead(pot6)/4;   // h Waveform Freq

  gateK.update();
  gateS.update();
  gateH.update();

  // kick knobs
  envelope1.decay(knob1);
  waveform1.frequency(knob2);
  waveform2.frequency(knob2);

  // snare knobs
  snareAmpEnv.decay(knob3);
  snareFM1.frequency(knob4);
  snareFM2.frequency(knob4);
  snareBody.frequency(knob4);
  snareClickCarrier.frequency(knob4);

 // hat knobs
  HHAmpEnv.decay(knob5);
  HHSineMod1.frequency(knob6);
  HHSineMod2.frequency(knob6);

  if (gateK.fallingEdge()) {
    envelope1.noteOn();
    timeout = 0;
  }
  if (gateS.fallingEdge()) {
    snareBody.phase(0);
    snareFM1.phase(180);
    snareFM2.phase(180);
    snareFMEnv.noteOn();
    snareClickEnv.noteOn();
    snareNoiseEnv.noteOn();
    snareAmpEnv.noteOn();
    timeout = 0;
  }
  if (gateH.fallingEdge()) {
    HHnoiseEnv.noteOn();
    HHAmpEnv.noteOn();
    HHModAMpEnv.noteOn();
    HHModEnv.noteOn();
    timeout = 0;
  }
}
  
