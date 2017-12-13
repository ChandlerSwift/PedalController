# Arduino Pedal Controller

An Arduino sketch for my [Arduino MIDI Interface board](https://blog.chandlerswift.com/wp-content/uploads/2017/12/MIDI_Board_Schematic.pdf), for a shift-register-based circuit allowing a single-pedalboard from an Baldwin 125B (?) organ to be interfaced with either a computer over USB-MIDI or a physical MIDI cable.

### Testing
To verify functionality on Linux, use `aseqdump`:

```
chandler@ChandlerUbuntu:~/Arduino/MIDIController$ aseqdump -l
 Port    Client name                      Port name
  0:0    System                           Timer
  0:1    System                           Announce
 14:0    Midi Through                     Midi Through Port-0
 20:0    Virtual Raw MIDI 1-0             VirMIDI 1-0
 21:0    Virtual Raw MIDI 1-1             VirMIDI 1-1
 22:0    Virtual Raw MIDI 1-2             VirMIDI 1-2
 23:0    Virtual Raw MIDI 1-3             VirMIDI 1-3
 36:0    Teensy MIDI                      Teensy MIDI MIDI 1
chandler@ChandlerUbuntu:~/Arduino/MIDIController$ aseqdump -p 36
Waiting for data. Press Ctrl+C to end.
Source  Event                  Ch  Data
 36:0   Note on                15, note 60, velocity 100
 36:0   Note off               15, note 60, velocity 100
 36:0   Note on                15, note 60, velocity 100
 36:0   Note off               15, note 60, velocity 100
```