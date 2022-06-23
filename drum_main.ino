#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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



void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP); // mode select
  pinMode(7, INPUT_PULLUP); // mode select
  pinMode(8, INPUT_PULLUP); // mode select
  pinMode(9, INPUT_PULLUP); // mode select

}

void loop() {
 
 if (digitalRead(6) == LOW) {
  Serial.println("drum");
 } else if (digitalRead(7) == LOW) {
  Serial.println("snare");
 }else if (digitalRead(8) == LOW) {
  Serial.println("hat");
 }else if (digitalRead(9) == LOW) {
  Serial.println("cym");
 }



}
