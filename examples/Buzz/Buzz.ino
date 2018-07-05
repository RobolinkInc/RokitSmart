#include <SmartInventor.h>

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_D4,NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
// note durations: 4 = 1/duration sec = 0.25 sec
int noteDurations[] = {
  4, 4, 4, 4,  4, 4, 4, 4 };

void setup()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    SmartInventor.Buzz(melody[thisNote],noteDurations[thisNote]); 
  }
}

void loop()
{
}

