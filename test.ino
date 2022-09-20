#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSineModulated HHSineMod1;     //xy=162,320
AudioSynthWaveformSineModulated HHSineMod2;     //xy=186,372
AudioSynthWaveformSineModulated snareFM1;       //xy=233,714
AudioSynthNoiseWhite     snareNoise;     //xy=262,866
AudioEffectEnvelope      HHModEnv;       //xy=340,370
AudioSynthWaveformSineModulated snareFM2;       //xy=366,776
AudioSynthWaveformDc     kickDCClick;    //xy=387,153
AudioSynthWaveformDc     kickDCSwoop;    //xy=413,102
AudioSynthNoiseWhite     HHNoise;        //xy=415,480
AudioEffectEnvelope      snareNoiseEnv;  //xy=491,855
AudioSynthWaveformSineModulated HHSineCarrier;  //xy=499,370
AudioEffectEnvelope      snareFMEnv;     //xy=517,793
AudioEffectEnvelope      kickClickEnv;   //xy=547,153
AudioEffectEnvelope      HHModAMpEnv;    //xy=548,418
AudioEffectEnvelope      HHnoiseEnv;     //xy=559,480
AudioEffectEnvelope      kickSwoopEnv;   //xy=573,102
AudioSynthWaveformSineModulated snareClickCarrier; //xy=573,702
AudioEffectEnvelope      snareClickEnv;  //xy=606,656
AudioFilterStateVariable snareNoiseHPF;  //xy=675,856
AudioSynthWaveformSineModulated snareBody;      //xy=678,792
AudioMixer4              HHMixer;        //xy=725,491
AudioMixer4              kickModMixer;   //xy=747,125
AudioFilterStateVariable snareClickFilter; //xy=788,679
AudioMixer4              snareMixer;     //xy=874,801
AudioFilterStateVariable HHfilter;       //xy=891,440
AudioSynthWaveformSineModulated kickSine;       //xy=897,126
AudioFilterStateVariable finalSnareFilter; //xy=1048,690
AudioEffectEnvelope      snareAmpEnv;    //xy=1048,802
AudioAnalyzePeak         snarePeak;      //xy=1104,752
AudioEffectEnvelope      kickAmpEnv;     //xy=1127,208
AudioEffectEnvelope      HHAmpEnv;       //xy=1144,472
AudioAnalyzePeak         HHPeak;         //xy=1189,416
AudioAnalyzePeak         kickPeak;       //xy=1285,172
AudioPlayMemory          playMemHH;      //xy=1284,877
AudioPlayMemory          playMemKick;    //xy=1285,836
AudioPlayMemory          playMemSnare;   //xy=1291,922
AudioMixer4              sampleMixer;    //xy=1468,872
AudioMixer4              drumVoiceMixer; //xy=1514,704
AudioEffectWaveshaper    waveshaper;     //xy=1673,554
AudioMixer4              driveMixer;     //xy=1803,649
AudioOutputI2S           i2s1;           //xy=1967,646
AudioConnection          patchCord1(HHSineMod1, HHSineMod2);
AudioConnection          patchCord2(HHSineMod2, HHModEnv);
AudioConnection          patchCord3(snareFM1, snareFM2);
AudioConnection          patchCord4(snareNoise, snareNoiseEnv);
AudioConnection          patchCord5(HHModEnv, HHSineCarrier);
AudioConnection          patchCord6(snareFM2, snareFMEnv);
AudioConnection          patchCord7(kickDCClick, kickClickEnv);
AudioConnection          patchCord8(kickDCSwoop, kickSwoopEnv);
AudioConnection          patchCord9(HHNoise, HHnoiseEnv);
AudioConnection          patchCord10(snareNoiseEnv, 0, snareNoiseHPF, 0);
AudioConnection          patchCord11(HHSineCarrier, HHModAMpEnv);
AudioConnection          patchCord12(snareFMEnv, snareBody);
AudioConnection          patchCord13(kickClickEnv, 0, kickModMixer, 1);
AudioConnection          patchCord14(HHModAMpEnv, 0, HHMixer, 0);
AudioConnection          patchCord15(HHModAMpEnv, 0, HHfilter, 1);
AudioConnection          patchCord16(HHnoiseEnv, 0, HHMixer, 1);
AudioConnection          patchCord17(kickSwoopEnv, 0, kickModMixer, 0);
AudioConnection          patchCord18(snareClickCarrier, snareClickEnv);
AudioConnection          patchCord19(snareClickEnv, snareClickCarrier);
AudioConnection          patchCord20(snareClickEnv, 0, snareClickFilter, 0);
AudioConnection          patchCord21(snareNoiseHPF, 2, snareMixer, 2);
AudioConnection          patchCord22(snareBody, 0, snareMixer, 1);
AudioConnection          patchCord23(HHMixer, 0, HHfilter, 0);
AudioConnection          patchCord24(kickModMixer, kickSine);
AudioConnection          patchCord25(snareClickFilter, 1, snareMixer, 0);
AudioConnection          patchCord26(snareMixer, snareAmpEnv);
AudioConnection          patchCord27(HHfilter, 2, HHAmpEnv, 0);
AudioConnection          patchCord28(kickSine, kickAmpEnv);
AudioConnection          patchCord29(finalSnareFilter, 2, drumVoiceMixer, 2);
AudioConnection          patchCord30(snareAmpEnv, snarePeak);
AudioConnection          patchCord31(snareAmpEnv, 0, finalSnareFilter, 0);
AudioConnection          patchCord32(kickAmpEnv, 0, drumVoiceMixer, 0);
AudioConnection          patchCord33(kickAmpEnv, kickPeak);
AudioConnection          patchCord34(HHAmpEnv, HHPeak);
AudioConnection          patchCord35(HHAmpEnv, 0, drumVoiceMixer, 1);
AudioConnection          patchCord36(playMemHH, 0, sampleMixer, 1);
AudioConnection          patchCord37(playMemKick, 0, sampleMixer, 0);
AudioConnection          patchCord38(playMemSnare, 0, sampleMixer, 2);
AudioConnection          patchCord39(sampleMixer, 0, drumVoiceMixer, 3);
AudioConnection          patchCord40(drumVoiceMixer, waveshaper);
AudioConnection          patchCord41(drumVoiceMixer, 0, driveMixer, 1);
AudioConnection          patchCord42(waveshaper, 0, driveMixer, 0);
AudioConnection          patchCord43(driveMixer, 0, i2s1, 0);
AudioConnection          patchCord44(driveMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1979,550
// GUItool: end automatically generated code


#include "AudioSampleKick.h"
#include "AudioSampleHh.h"
#include "AudioSampleSnare.h"

elapsedMillis printTime;

#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
int midiChannel = 5;

#include <ResponsiveAnalogRead.h>
ResponsiveAnalogRead pots[7] = {
  //pots
  ResponsiveAnalogRead (A10, true),
  ResponsiveAnalogRead (A11, true),
  ResponsiveAnalogRead (A0, true),
  ResponsiveAnalogRead (A1, true),
  ResponsiveAnalogRead (A2, true),
  ResponsiveAnalogRead (A3, true),
  ResponsiveAnalogRead (A8, true),
};

//test cv responsive?
ResponsiveAnalogRead pitchCV(A9, true);
float pitchVal;

int cvInputs[7] = {
  A12,A13,A14,A15,A16,A17,A9
};
float rawCvVals[7];
float scaledCvVals[7];

#include <Bounce.h>
Bounce gateIn[3] = {
  Bounce(2,5),
  Bounce(3,5),
  Bounce(4,5),
};
bool btnDown;

int kickPitch = 50;
int kickDecay = 300;
int kickPitchCV;
int kickDecayCV;
int kickPitchSum;
int kickDecaySum;

int HHPitch = 100;
int HHDecay = 50;
int HHPitchCV;
int HHDecayCV;
int HHPitchSum;
int HHDecaySum;

int snarePitch = 100;
int snareDecay = 50;
int snarePitchCV;
int snareDecayCV;
int snarePitchSum;
int snareDecaySum;

float velocities[3] = {1,1,1};
float sampVelocities[3] = {0,0,0};

float punchVal[3] = {1,1,1};

float driveMix;
float driveMixMod;

bool firstRun = true;;

float WaveShapeArray[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.320,
  -0.488,
  -0.228,
  -0.122,
  -0.396,
  0,
  0.122,
  0.320,
  0.396,
  0.228,
  0.549,
  0.488,
  0.588,
  0.579,
};


void setup() {
  // Main setup
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);
  MIDI.begin(midiChannel);

  analogWriteResolution(12);
  AudioMemory(48);
  //kick////////////////////////////////////
  kickSine.frequency(10);
  kickSine.mod_index(16383.75);

  kickAmpEnv.attack(1);
  kickAmpEnv.sustain(0);
  kickAmpEnv.decay(250);
  kickAmpEnv.release(1);

  kickClickEnv.attack(1);
  kickClickEnv.sustain(0);
  kickClickEnv.decay(10);
  kickClickEnv.release(1);

  kickSwoopEnv.attack(1);
  kickSwoopEnv.sustain(0);
  kickSwoopEnv.decay(150);
  kickSwoopEnv.release(1);

  kickDCClick.amplitude(0.04);
  kickDCSwoop.amplitude(0.01);

  //snare////////////////////////////////////
  snareAmpEnv.attack(1);
  snareAmpEnv.sustain(0);
  snareAmpEnv.decay(100);
  snareAmpEnv.release(1);

  snareNoiseEnv.delay(10);
  snareNoiseEnv.attack(150);
  snareNoiseEnv.sustain(1);
  snareNoiseEnv.release(1);



  snareBody.mod_index(65535);
  snareBody.frequency(50);
  snareNoise.amplitude(1);

  snareNoiseHPF.frequency(1000);;

  snareClickCarrier.mod_index(65535);
  snareClickCarrier.frequency(1500);
  snareClickEnv.attack(0);
  snareClickEnv.sustain(0);
  snareClickEnv.decay(500);
  snareClickEnv.release(1);
  snareClickFilter.frequency(1500);
  snareClickFilter.resonance(5);

  snareFM1.mod_index(65535);
  snareFM1.frequency(1500);
  snareFM2.mod_index(65535);
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


  //HiHat////////////////////////////////////
  HHModAMpEnv.attack(1);
  HHModAMpEnv.decay(50);
  HHModAMpEnv.sustain(0);
  HHModAMpEnv.release(10);

  HHSineCarrier.amplitude(0.75);
  HHSineCarrier.mod_index(65535);
  HHSineCarrier.frequency(4000);

  HHSineMod1.frequency(2500);
  HHSineMod2.mod_index(65535);
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


  //VoiceMix////////////////////////////////////
  // drumVoiceMixer.gain(0,1);
  // drumVoiceMixer.gain(1,1);
  // drumVoiceMixer.gain(2,0.5);
  //

  //SampleMixer
  sampleMixer.gain(0,0);
  sampleMixer.gain(1,0);
  sampleMixer.gain(2,0);
  waveshaper.shape(WaveShapeArray, 17);

  //gate in pins
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  //btn in
  pinMode(8,INPUT_PULLUP);

  analogReadResolution(12);
  for (size_t i = 0; i < 7; i++) {
    pots[i].setAnalogResolution(4096);
    pots[i].setActivityThreshold(50);
    pots[i].enableEdgeSnap();
  }
}

void loop() {

  int type, note, velocity;
  if (MIDI.read()) {
    type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();

        triggerDrum(note%3);
        velocities[note%3] = float(velocity)/127;
        // Serial.println("Engine: "+String(note%3)+" velocity: "+String(velocities[note%3]));
        break;
      case 176:
        //MIDI Mod
        if(MIDI.getData1() == 1) {
          driveMix = float(MIDI.getData2())/127;
          Serial.println(driveMix);
        }
        break;
    }
  }

  //leds pins 9,10,25 PWM
  if (kickPeak.available()) {
    analogWrite(9,255*kickPeak.read());
  }
  if (HHPeak.available()) {
    analogWrite(10,255*HHPeak.read());
  }
  if (snarePeak.available()) {
    analogWrite(25,255*snarePeak.read());
  }

  btnDown = !digitalRead(8);



  for (size_t i = 0; i < 3; i++) {
    gateIn[i].update();
    if (gateIn[i].fallingEdge()) {
      triggerDrum(i);
    }
  }

  for (size_t i = 0; i < 7; i++) {
    pots[i].update();
    if(pots[i].hasChanged() || firstRun) {
      if (i<7) {
        switch (i) {
          case 0:
            driveMix = pots[i].getValue();
            driveMix /= 4095;
            break;
          case 1:
            if(btnDown){
              velocities[2] = (float)pots[i].getValue() / 4095;
            }else{
              snarePitch = pots[i].getValue()/10;
            }
            break;
          case 2:
            if(btnDown){
              velocities[1] = (float)pots[i].getValue() / 4095;
            }else{
              HHPitch = pots[i].getValue();
            }
            break;
          case 3:
            if(btnDown){
              velocities[0] = (float)pots[i].getValue() / 4095;
            }else{
              kickPitch = pots[i].getValue()/15;
            }
            break;
          case 4:
            if(btnDown){
              sampVelocities[2] = (float)pots[i].getValue()/4095;
            }else{
              snareDecay = pots[i].getValue()/4;
            }
            break;
          case 5:
            if(btnDown){
              sampVelocities[1] = (float)pots[i].getValue()/4095;
            }else{
              HHDecay = pots[i].getValue()/3;
            }
            break;
          case 6:
            if(btnDown){
              sampVelocities[0] = (float)pots[i].getValue()/4095;
            }else{
              kickDecay = pots[i].getValue()/3;
            }
            break;
        }
      }
    }
  }

  for (size_t i = 0; i < 7; i++) {
    rawCvVals[i] = analogRead(cvInputs[i]);
    switch (i) {
      case 2:
        kickPitchCV = map(rawCvVals[i],1250,3670,118,-118);
        break;
      case 3:
        kickDecayCV = map(rawCvVals[i],1250,3670,682,-682);
        break;
      case 4:
        HHPitchCV = map(rawCvVals[i],1250,3670,2047,-2047);
        break;
      case 1:
        HHDecayCV = map(rawCvVals[i],1250,3670,682,-682);
        break;
      case 0:
        snarePitchCV = map(rawCvVals[i],1250,3670,204,-204);
        break;
      case 5:
        snareDecayCV =  map(rawCvVals[i],1250,3670,511,-511);
        break;
      case 6:
        float tmpMix;
        tmpMix = mapfloat(rawCvVals[i],1250,3670,0.75,-0.75);
        driveMixMod = tmpMix; //overdirve
        break;
    }
  }



  AudioNoInterrupts();
  //KICK
  kickPitchSum = kickPitch + kickPitchCV;
  kickPitchSum = constrain(kickPitchSum,0,546);

  kickDecaySum = kickDecay + kickDecayCV;
  kickDecaySum = constrain(kickDecaySum,0,2730);

  kickSine.frequency(kickPitchSum);
  kickAmpEnv.decay(kickDecaySum);
  kickSwoopEnv.decay(kickDecaySum/4);
  kickDCClick.amplitude(0.05);

  //============================================================================

  //HH
  HHPitchSum = HHPitch + HHPitchCV;
  HHPitchSum = constrain(HHPitchSum,0,8190);

  HHDecaySum = HHDecay + HHDecayCV;
  HHDecaySum = constrain(HHDecaySum,0,2730);

  HHAmpEnv.decay( HHDecaySum );
  HHnoiseEnv.decay( HHDecaySum );
  HHModEnv.decay( HHDecaySum / 2);
  HHModAMpEnv.decay(HHDecaySum);

  HHSineCarrier.frequency( HHPitchSum/2 );
  HHSineMod1.frequency( HHPitchSum * 2 );
  HHSineMod2.frequency( HHPitchSum );

  //============================================================================

  //snare
  snarePitchSum = snarePitch + snarePitchCV;
  snarePitchSum = constrain(snarePitchSum,0,800);

  snareDecaySum = snareDecay + snareDecayCV;
  snareDecaySum = constrain(snareDecaySum,0, 2046);

  snareAmpEnv.decay( snareDecaySum );
  snareFMEnv.decay( snareDecaySum / 12 );

  snareBody.frequency( snarePitchSum );
  snareFM1.frequency( snarePitchSum*5 );
  snareFM2.frequency( snarePitchSum*15 );

  snareNoiseHPF.frequency( snarePitchSum*1.5 );

  //============================================================================

  //drive
  float driveMixFinal = driveMix+driveMixMod;
  driveMixFinal = constrain(driveMixFinal,0,1);

  driveMixer.gain(0,driveMixFinal);
  driveMixer.gain(1,1-(driveMixFinal));

  //============================================================================

  //final mix
  drumVoiceMixer.gain(0,velocities[0]);
  drumVoiceMixer.gain(1,velocities[1]);
  drumVoiceMixer.gain(2,velocities[2]);

  sampleMixer.gain(0,sampVelocities[0]);
  sampleMixer.gain(1,sampVelocities[1]);
  sampleMixer.gain(2,sampVelocities[2]);

  AudioInterrupts();

  firstRun = false;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void triggerDrum(int drumVoice){

  switch (drumVoice) {
    case 0:
      if (kickAmpEnv.isActive()) {
        kickClickEnv.noteOff();
        kickSwoopEnv.noteOff();
        kickAmpEnv.noteOff();
        delay(5);
      }
      // Serial.println("kick Pitch: "+String(kickPitch)+" | kick Pitch CV: "+String(kickPitchCV)+" | Total: "+String(kickPitchSum));
      // Serial.println("kick Decay: "+String(kickDecay)+" | kick Decay CV: "+String(kickDecayCV)+" | Total: "+String(kickDecaySum));
      kickSine.phase(0);
      kickClickEnv.noteOn();
      kickSwoopEnv.noteOn();
      kickAmpEnv.noteOn();
      playMemKick.play(AudioSampleKick);
      break;
    case 1:
      // Serial.println("HH Pitch: "+String(HHPitch)+" | HH Pitch CV: "+String(HHPitchCV)+" | Total: "+String(HHPitchSum));
      // Serial.println("HH Decay: "+String(HHDecay)+" | HH Decay CV: "+String(HHDecayCV)+" | Total: "+String(HHDecaySum));
      HHnoiseEnv.noteOn();
      HHAmpEnv.noteOn();
      HHModAMpEnv.noteOn();
      HHModEnv.noteOn();
      playMemHH.play(AudioSampleHh);
      break;
    case 2:
      // Serial.println("snare Pitch: "+String(snarePitch)+" | snare Pitch CV: "+String(snarePitchCV)+" | Total: "+String(snarePitchSum));
      // Serial.println("snare Decay: "+String(snareDecay)+" | snare Decay CV: "+String(snareDecayCV)+" | Total: "+String(snareDecaySum));
      snareBody.phase(0);
      snareFM1.phase(180);
      snareFM2.phase(180);
      snareFMEnv.noteOn();
      snareClickEnv.noteOn();
      snareNoiseEnv.noteOn();
      snareAmpEnv.noteOn();
      playMemSnare.play(AudioSampleSnare);
    break;
  }
}
