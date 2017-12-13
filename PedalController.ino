#include "MIDIUSB.h"

const int NUM_PEDALS = 13; //C2-C3

const int LOAD = 2;
const int CLOCK = 3;
const int DATA = 4;

const int CHANNEL = 0;
const int VELOCITY = 127;

 // TODO: octave adjustment using buttons? 
int octave = 3; // C2 + 1 since numbering starts at -1 (https://www.midikits.net/midi_analyser/midi_note_numbers_for_octaves.htm)

bool pedals[NUM_PEDALS];

void setup() {
  for (int pedal = 0; pedal < NUM_PEDALS; pedal++)
      pedals[pedal] = false;
  
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, INPUT);

  // Provide power to daughterboard. Due to a lapse in my foresight, I neglected to include a Vcc out pin on the I/O.
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

// from https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino
// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void noteOn(byte pitch) {
  midiEventPacket_t noteOn = {0x09, 0x90 | CHANNEL, pitch, VELOCITY};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte pitch) {
  midiEventPacket_t noteOff = {0x08, 0x80 | CHANNEL, pitch, VELOCITY};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
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
        noteOn(pedal + (octave * 12));
      else
        noteOff(pedal + (octave * 12));
      pedals[pedal] = digitalRead(DATA); // Update new value to array
    }
    digitalWrite(CLOCK, 1);
    delayMicroseconds(10); // TODO: reduce?
  }
}
