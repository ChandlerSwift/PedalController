#include <MIDI.h>
#include <SoftwareSerial.h>

const int NUM_PEDALS = 13; //C2-C3

const int LOAD = 2;
const int CLOCK = 3;
const int DATA = 4;

const int CHANNEL = 1;
const int VELOCITY = 127;

SoftwareSerial mySerial(10, 16);
MIDI_CREATE_INSTANCE(SoftwareSerial, mySerial, midi2);

 // TODO: octave adjustment using buttons? 
int octave = 3; // C2 + 1 since numbering starts at -1 (https://www.midikits.net/midi_analyser/midi_note_numbers_for_octaves.htm)

bool pedals[NUM_PEDALS];

void setup() {
  midi2.begin();

  for (int pedal = 0; pedal < NUM_PEDALS; pedal++)
      pedals[pedal] = false;
  
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, INPUT);

  // Provide power to daughterboard. Due to a lapse in my foresight, I neglected to include a Vcc out pin on the I/O.
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop() {
  
  digitalWrite(LOAD,0);
  delayMicroseconds(10); // TODO: reduce?
  digitalWrite(LOAD,1);
  delayMicroseconds(10);

  for (int pedal = 0; pedal < NUM_PEDALS; pedal++)
  {
    digitalWrite(CLOCK, 0);
    delayMicroseconds(10); // TODO: reduce?
    if (digitalRead(DATA) != pedals[pedal]) // key has been pressed or released
    {
      if (digitalRead(DATA))
        midi2.sendNoteOn(pedal + (octave * 12), VELOCITY, CHANNEL);
      else
        midi2.sendNoteOff(pedal + (octave * 12), VELOCITY, CHANNEL);
      pedals[pedal] = digitalRead(DATA); // Update new value to array
    }
    digitalWrite(CLOCK, 1);
    delayMicroseconds(10); // TODO: reduce?
  }
}
