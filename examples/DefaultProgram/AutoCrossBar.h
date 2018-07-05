
void AutoCrossBar()
{
  int melody[] = {
    NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
  };

  SmartInventor.DCMotorUse();
  DDRC = 0b10000001;
  byte speed = 20;
  
  while (1)
  {
     SmartInventor.DCMove(forward, speed);
    
    if(!SmartInventor.TimeCheckMillis(5000))
    {
     if ((PINC) & 0b01111110)
      {
        SmartInventor.DCMove(forward, stop);
        speed += 10;
        for (int i = 0; i < speed / 10 - 2; i++)
        {
          SmartInventor.Buzz(melody[i], 8);
        }
      
        unsigned char led_sign = 0;
        DDRC =  0b11111111;
        while (led_sign < 8)
        {
          PORTC = ((1 << (led_sign + 1)) - 1);
          led_sign++;
          delay(50);
        }
        while (led_sign > 0)
        {
          PORTC = ((1 << (led_sign + 1)) - 1);
          led_sign--;
          delay(50);
        }
        DDRC = 0b10000001;

        if (speed > 100)  speed = 20;

        while ((PINC) & 0b01111110)
        delay(10);
                
        delay(1500);

        SmartInventor.PreviousMillis =  millis();
      }
    }
    else
    {
      SmartInventor.Buzz(2315, 8);
      SmartInventor.Buzz(1981, 12);
      speed = 20;
      SmartInventor.PreviousMillis =  millis();
    }
  }
}


