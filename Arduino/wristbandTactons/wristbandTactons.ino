#include <TactonManager.h>
#include <TactonPlayerPreciseNew.h>
#include <Tacton.h>
byte pins[] = {
  6, 5, 11, 3};
byte pwmPin = 9;

TactonPlayerPreciseNew player(4, pins, 9);
TactonManager manager(&player);

byte command = 0;
byte posbuf = 0;
unsigned int nbf = 0;
byte buffer[60];
//unsigned long start = 0;
boolean active = false;

void setup()
{
  Serial.begin(57600);
//  player.init();
/*  player.debug1();
  player.debug2();
  player.debug3();
  player.debug4();*/
}

void loop()
{
  byte index;
  unsigned long timestamp;
  unsigned int param;

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
          /*Serial.print("Received: *");
          for (int i = 0 ; i < 6 ; i++)
            Serial.print(buffer[i], HEX);
          Serial.println("*");*/
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
    //sets an amplitude for each vibrator
    // Ana1a2...an
    // n = nb tactors (1 byte)
    // A1, A2, ..., an : amplitudes (1 byte per tactor)
    case 'A':
      if (nbf == 0 && Serial.available() >= 1)
        nbf = (unsigned int) Serial.read();
      if (nbf > 0)
      {
        //DO NOT OVERFLOW max(nbf): 60
        while (posbuf < nbf && Serial.available() > 0)
        {
          buffer[posbuf] = Serial.read();
          posbuf++;
        }
        if (posbuf >= nbf)
        {
          manager.setAmplitudes(nbf, buffer);
          posbuf = 0;
          command = 0;
          nbf = 0;
        }
      }
      break;
    //sets the frequency
    case 'F':
      if (Serial.available() >= 2)
      {
        param = (((unsigned long)Serial.read()) << 8) | \
            (((unsigned long)Serial.read()));
        manager.setFrequency(param);
        command = 0;
      }
      break;
    //sets an angle in degrees
    case 'a':
      if (Serial.available() >= 2)
      {
        param = (((unsigned long)Serial.read()) << 8) | \
            (((unsigned long)Serial.read()));
        manager.setAngle(param);
        command = 0;
      }
      break;
    //sets a series on angles
    // sNDnA1A2...AN
    // N = nb angles (1 byte)
    // D = duration in ms of each frame (2 bytes)
    // n = number of frames (2 bytes)
    // A1, A2, ..., AN : angles (2 bytes per tactor)
    case 's':
      if (nbf == 0 && Serial.available() >= 1)
        nbf = (unsigned int) Serial.read();
      if (nbf > 0)
      {
        //DO NOT OVERFLOW max(nbf): 60
        while (posbuf < 2 * nbf + 4 && Serial.available() > 0)
        {
          buffer[posbuf] = Serial.read();
          //Serial.print(buffer[posbuf], HEX);
          posbuf++;
        }
        if (posbuf >= 2 * nbf + 4)
        {
          manager.setAngleSequence(nbf, \
            (buffer[0] << 8) | buffer[1], \
            (buffer[2] << 8) | buffer[3], \
            buffer + 4);
          posbuf = 0;
          command = 0;
          nbf = 0;
        }
      }
      break;
    //stop any vibration
    case 'B':
      manager.stop();
      command = 0;
      break;
    //Ask for feedback
    case 'I':
      Serial.write("I'm still alive");
      command = 0;
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

