#include <TactonManager.h>
#include <TactonPlayer.h>
#include <Tacton.h>
byte pins[] = {
  3, 11, 5, 9};
TactonPlayer player(4, pins);
TactonManager manager(&player);

void* operator new(size_t n, void * p) { 
  return p; 
}
void* operator new(size_t n) { 
  return malloc(n); 
}
void operator delete (void * p) { 
  free(p); 
};

byte command = 0;
byte posbuf = 0;
unsigned int nbf = 0;
byte buffer[60];
//unsigned long start = 0;
boolean active = false;

void setup()
{
  Serial.begin(57600);
  player.debug1();
  player.debug2();
  player.debug3();
  player.debug4();
}

void loop()
{
  byte index;
  unsigned long timestamp;

  if (Serial.available() > 0)
  {
    if (command == 0)
      command = Serial.read();
    switch(command)
    {
    //set the timestamp to 0, and watch for scheduled tactons
    case 'S':
//      start = millis();
      manager.setOffset(millis());
      command = 0;
      active = true;
      break;
    //stop watching scheduled tactons, and erase registered tactons
    case 'Q':
      command = 0;
      manager.clear();
      active = false;
      break;
    //register a tacton
    case 'N':
      if (nbf == 0 && Serial.available() >= 2)
        nbf = (((unsigned int) Serial.read()) << 8) | ((unsigned int) Serial.read());
      if (nbf > 0)
      {
        //DO NOT OVERFLOW max(nbf): 10
        while (posbuf < nbf * 6 && Serial.available() > 0)
        {
          buffer[posbuf] = Serial.read();
          posbuf++;
        }
        if (posbuf >= nbf*6)
        {
          manager.add(nbf, buffer);
          posbuf = 0;
          command = 0;
          nbf = 0;
        }
      }
      break;
    //play a specified tacton
    case 'V':
      if (nbf == 0 && Serial.available() >= 2)
        nbf = (((unsigned int) Serial.read()) << 8) | ((unsigned int) Serial.read());
      if (nbf > 0)
      {
        //DO NOT OVERFLOW max(nbf): 10
        while (posbuf < nbf * 6 && Serial.available() > 0)
        {
          buffer[posbuf] = Serial.read();
          posbuf++;
        }
        if (posbuf >= nbf*6)
        {
          manager.play(nbf, buffer);
          posbuf = 0;
          command = 0;
          nbf = 0;
        }
      }
      break;
    //play a registered tacton
    case 'T':
      if (Serial.available() >= 1)
      {
        index = Serial.read();
        manager.play(index);
        command = 0;
  /*      Serial.print("Play");
        Serial.println(index, DEC);*/
      }
      break;
    //schedule the play of a registered tacton
    case 'P':
      if (Serial.available() >= 5)
      {
        index = Serial.read();
        timestamp = (((unsigned long)Serial.read()) << 24) | \
            (((unsigned long)Serial.read()) << 16) | \
            (((unsigned long)Serial.read()) << 8) | \
            (((unsigned long)Serial.read()));
/*        Serial.print("Plan ");
        Serial.println(timestamp, DEC);
        Serial.print(" played at ");
        Serial.print(timestamp + start, DEC);
        Serial.print(" shift=");
        Serial.println(start, DEC);*/
        manager.addPlay(index, timestamp);
        command = 0;
      }
      break;
    //unknown command: do nothing
    default:
      command = 0;
      break;
    }
  }

  if (active)
    manager.checkPlay();
}

