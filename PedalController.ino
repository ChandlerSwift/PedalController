//#include "MIDIUSB.h"

const int NUM_PEDALS = 8; //13; //C2-C3

const int LOAD = 2;
const int CLOCK = 3;
const int DATA = 4;

int octave = 2; // TODO: octave adjustment using buttons?

bool pedals[NUM_PEDALS];

void setup() {
  Serial.begin(115200);
  Serial.println("initializing...");
  for (int pedal = 0; pedal < NUM_PEDALS; pedal++)
      pedals[pedal] = false;

//  usbMIDI.begin();
  
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, INPUT);
}

void loop() {
  
  digitalWrite(LOAD,0);
  delayMicroseconds(1000); // TODO: reduce?
  digitalWrite(LOAD,1);
  delayMicroseconds(1000);

  for (int pedal = 0; pedal < NUM_PEDALS; pedal++)
  {
    digitalWrite(CLOCK, 0);
    delayMicroseconds(1000); // TODO: reduce?
    if (digitalRead(DATA) != pedals[pedal]) // key has been pressed or released
    { 
      if (digitalRead(DATA)) {
        Serial.print("KEY "); Serial.print(pedal + 36); Serial.print(" pressed");
        //usbMIDI.sendNoteOn(key, 100, manual);
      } else {
        Serial.print("KEY "); Serial.print(pedal + 36); Serial.print(" released");
        //usbMIDI.sendNoteOff(key, 100, manual);
      }
      pedals[pedal] = digitalRead(DATA); // Update new value to array
    }
    digitalWrite(CLOCK, 1);
    delayMicroseconds(1000); // TODO: reduce?
  }
  //delay(100);
}
