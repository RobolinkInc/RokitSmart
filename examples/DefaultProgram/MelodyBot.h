
void MelodyBot()
{
  int note;
  int melody[] = {
    NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
  };

  int minSen = 1023;
  int maxSen = 0;

  pinMode(23, INPUT_PULLUP);

  DDRC = 0xff;
  PORTC = 0;

  while (1)
  {
    int sen = analogRead(22);
    minSen = min(sen, minSen);
    maxSen = max(sen, maxSen);
    note = map(sen, minSen, maxSen, 0, 8);
    note = 7 - note;
    
    PORTC = (0b11111111 >> note);

    if (((PINA & 0b00010000) >> 4) == 0)  //pushed
    {
      SmartInventor.Buzz(melody[note], 4);
      do {
        delay(10);
      }
      while (!digitalRead(23));
    }
  }
}




