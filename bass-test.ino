#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h> 

Bounce button0 = Bounce(0,15);

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

void setup() {
  // Main setup
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  
  // Pins
  pinMode(32, INPUT_PULLUP);
  
  // Mixer 
  mixer1.gain(0, 0.1);
  mixer1.gain(1, 0.1);
  mixer1.gain(2, 0.1);
  mixer1.gain(3 , 0.1);
  
  // Waveform
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.amplitude(.75);
  waveform1.frequency(50);
  waveform1.pulseWidth(.15);
  
  //envelope
  envelope1.attack(10);
  envelope1.hold(10);
  envelope1.decay(25);
  envelope1.sustain(0.4);
  envelope1.release(70);
  
  // PWM
  pwm1.amplitude(.75);
  pwm1.frequency(50);
}

  void loop() { 
    button0.update();
    if (button0.fallingEdge()) {
      envelope1.noteOff();
      Serial.println("Button released, sending NoteOff");
    }
    
    if (button0.risingEdge()) {
      envelope1.noteOn();
      Serial.Println("Button Pressed, sending NoteOn");
      Serial.Println();
    }
  Serial.Println("Max Audio Blocks Used: ");
  Serial.Print(AudioMemoryUsageMax());
  Serial.Println();
  delay(100);
}

