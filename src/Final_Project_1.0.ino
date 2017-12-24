//Reference https://learn.adafruit.com/adafriend/overview

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Tone.h"


Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Eye animation frames
static const uint8_t  PROGMEM
sadBlinkImg[][8] = {    
  { 
    B00100100,         // Fully open sad eye
    B01000010,
    B10000001,
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111       }
  ,
  { 
    B00100100,         
    B01000010,
    B10000001,
    B00000000,
    B01111110,
    B11111111,
    B11111111,
    B11111111        }
  ,
  { 
    B00100100,         
    B01000010,
    B10000001,
    B00000000,
    B00000000,
    B01111110,
    B11111111,
    B11111111       }
  ,
  {
    B00100100,         
    B01000010,
    B10000001,
    B00000000,
    B00000000,
    B00000000,
    B01111110,
    B11111111        }
  ,
  { 
    B00100100,         // Fully closed sad eye
    B01000010,
    B10000001,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111       } 

};

static const uint8_t  PROGMEM
blinkImg[][8] = {    
  { 
    B00111100,         // Fully open eye
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100       }
  ,
  { 
    B00000000,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100       }
  ,
  { 
    B00000000,
    B00000000,
    B00111100,
    B11111111,
    B11111111,
    B11111111,
    B00111100,
    B00000000       }
  ,
  { 
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B11111111,
    B01111110,
    B00011000,
    B00000000       }
  ,
  { 
    B00000000,         // Fully closed eye
    B00000000,
    B00000000,
    B00000000,
    B10000001,
    B01111110,
    B00000000,
    B00000000       } 
};

static const uint8_t  PROGMEM
happyBlinkImg[][8] = {   
  { 
    B00111100,         // Fully open happy eye
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B00000000,
    B10000001,
    B01111110       }
  ,
  { 
    B00000000,         
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B00000000,
    B10000001,
    B01111110       }
  ,
  { 
    B00000000,         
    B00000000,
    B01111110,
    B11111111,
    B11111111,
    B00000000,
    B10000001,
    B01111110       }
  ,
  { 
    B00000000,         
    B00000000,
    B00000000,
    B01111110,
    B11111111,
    B00000000,
    B10000001,
    B01111110       }
  ,
  { 
    B00000000,         // Fully closed happy eye      
    B00000000,
    B00000000,
    B01111110,
    B10000001,
    B00000000,
    B10000001,
    B01111110       } 
};

static const uint8_t PROGMEM 
annoyedBlinkImg[][8] = {   
  { 
    B10000001,         // Fully open annoyed eye
    B01100110,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100       }
  ,
  { 
    B10000001,       
    B01100110,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00000000        }
  ,
  { 
    B10000001,       
    B01100110,
    B00000000,
    B11111111,
    B11111111,
    B01111110,
    B00000000,
    B00000000       }
  ,
  {
    B10000001,       
    B01100110,
    B00000000,
    B11111111,
    B01111110,
    B00000000,
    B00000000,
    B00000000        }
  ,
  { 
    B10000001,         // Fully closed annoyed eye
    B01100110,
    B00000000,
    B10000001,
    B01111110,
    B00000000,
    B00000000,
    B00000000       } 

};

uint8_t
blinkIndex[] = { 
  1, 2, 3, 4, 3, 2, 1 }, // Blink bitmap sequence
blinkCountdown = 100, 
gazeCountdown  =  75, 
gazeFrames     =  50; 
int8_t
eyeX = 3, eyeY = 3,   // Current eye position
newX = 3, newY = 3,   // Next eye position
dX   = 0, dY   = 0;   // Distance from prior to new position

Tone tone1;

#define OCTAVE_OFFSET 0

const int notes[] = { 
  0,
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, //scale of notes and their frequencies
  NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
  NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
  NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

const char *songs[] = { // A selection of songs that the Adafriend will sing when happy. Watch for memory limits! These 7 are tested and working.
"Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b",
"Indiana Jones:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6",
"Take On Me:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5",
"Tetris:d=4,o=5,b=150:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a",
"Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5",
"Mahna Mahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.",
"The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6"
};


int tapNum = 15; 
byte mood = 1; 
const byte vibration PROGMEM = A0; 
const int tapLevel PROGMEM = 512;
long previousMillis = 0;        // will store last time LED was updated


const int decay PROGMEM = 30000;           // interval at which to decay emotions

unsigned long 
checkMillis,
 tapMillis,
 songMillis,
 currentMillis,
gameMillis;

void setup() {

  randomSeed(analogRead(A7));
  pinMode(vibration, INPUT_PULLUP);

  matrix.begin(0x70);
  matrix.setRotation(3);
  matrix.setBrightness(4);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  
  matrix.setTextColor(LED_ON);
  matrix.clear();
  matrix.writeDisplay();
  tone1.begin(10);
}

void loop() {
  while (true) {
  displayMood(mood);
  }
}


void displayMood(int moodNum) {
  switch (moodNum) {
    case 0:
      displaySadMood();
      prepareForNextMood();
      break;
    case 1:
      displayNeutralMood();
      prepareForNextMood();
      break;
    case 2:
      displayHappyMood();
      prepareForNextMood();
      break;
    case 3:
      displayAngryMood();
      prepareForNextMood();
      break;
  }
}

void displaySadMood() {
  matrix.clear();
  matrix.drawBitmap(0, 0,
  sadBlinkImg[
    (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
  blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
  0                                       // No, show bitmap 0
  ], 8, 8, LED_ON);
}

void displayNeutralMood() {
  matrix.clear();
  matrix.drawBitmap(0, 0,
  blinkImg[
    (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
  blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
  0                                       // No, show bitmap 0
  ], 8, 8, LED_ON);
}

void displayHappyMood() {
  matrix.clear();
  matrix.drawBitmap(0, 0,
  happyBlinkImg[
    (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
  blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
  0                                       // No, show bitmap 0
  ], 8, 8, LED_ON);
}

void displayAngryMood() {
  matrix.clear();
  matrix.drawBitmap(0, 0,
  annoyedBlinkImg[
    (blinkCountdown < sizeof(blinkIndex)) ? // Currently blinking?
  blinkIndex[blinkCountdown] :            // Yes, look up bitmap #
  0                                       // No, show bitmap 0
  ], 8, 8, LED_ON);
}

void prepareForNextMood() {
  // Decrement blink counter.  At end, set random time for next blink.
  if(--blinkCountdown == 0) blinkCountdown = random(5, 180);

  // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
  // Periodically, the pupil moves to a new position...
  if(--gazeCountdown <= gazeFrames) {
    // Eyes are in motion - draw pupil at interim position
    matrix.fillRect(
    newX - (dX * gazeCountdown / gazeFrames),
    newY - (dY * gazeCountdown / gazeFrames),
    2, 2, LED_OFF);
    if(gazeCountdown == 0) {    // Last frame?
      eyeX = newX;
      eyeY = newY;
      do { // Pick random positions until one is within the eye circle
        newX = random(0,7);
        newY = random(5,7);
        dX   = newX-3;
        dY   = newY-3;
      }
      while((dX * dX + dY * dY) >= 10);        // Thank you Pythagoras
      dX            = newX - eyeX;             // Horizontal distance to move
      dY            = newY - eyeY;             // Vertical distance to move
      gazeFrames    = random(3, 15);           // Duration of eye movement
      gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
    }
  }
  else {
    // Not in motion yet -- draw pupil at current static position
    matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
  }


  // Refresh all of the matrices in one quick pass
  matrix.writeDisplay();

  if(millis()-checkMillis > random(10000,30000))
  {
    sadNoise();
    checkMillis = millis();
  }

  tapMillis = millis();

  while(millis()-tapMillis < 40)
  {
    checkTaps();
  }
  songMillis = millis();
}


#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(const char *p) // the method to play a song
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; 
    p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }



  // get default octave
  if(*p == 'o')
  {
    p++; 
    p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }



  // get BPM
  if(*p == 'b')
  {
    p++; 
    p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }



  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)




  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }

    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

      // now get the note
    note = 0;

    switch(*p)
    {
    case 'c':
      note = 1;
      break;
    case 'd':
      note = 3;
      break;
    case 'e':
      note = 5;
      break;
    case 'f':
      note = 6;
      break;
    case 'g':
      note = 8;
      break;
    case 'a':
      note = 10;
      break;
    case 'b':
      note = 12;
      break;
    case 'p':
    default:
      note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }

    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {

      delay(duration);
    }
  }
}

void checkTaps()
{
  if(analogRead(vibration)<tapLevel)
  {
    tapNum++;
    tone1.play(NOTE_C5);
    delay(200);
    tone1.stop();
  }

  if(tapNum <= 10) mood = 0;
  else if(tapNum <= 20) mood = 1;
  else if(tapNum <= 30) mood = 2;
  else if(tapNum > 30) mood = 3;

  currentMillis = millis();

  if(currentMillis - previousMillis > decay) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    tapNum--;
    if(tapNum < 0) tapNum = 0;
    if(tapNum == 30) tapNum = 15;
    if(tapNum > 40) tapNum = 40;
  }

  currentMillis = millis();

  if(currentMillis - songMillis > random(30000,60000) && mood == 2)
  {
    matrix.clear();

    matrix.drawBitmap(0, 0, happyBlinkImg[0], 8, 8, LED_ON);
    eyeX = 3;
    eyeY = 3;
    matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
    matrix.writeDisplay();

    play_rtttl(songs[random(7)]);
    previousMillis = millis();
    checkMillis = millis();
    songMillis = millis();
  }
}

void happyNoise()
{
  int note = (int)random(13,39);
  tone1.play(notes[note]);
  delay(200);
  tone1.stop();
  tone1.play(notes[note+1]);
  delay(100);
  tone1.stop();
  tone1.play(notes[note+2]);
  delay(100);
  tone1.stop();
}

void sadNoise()
{
  int note = (int)random(2,26);
  tone1.play(notes[note]);
  delay(200);
  tone1.stop();
  tone1.play(notes[note-1]);
  delay(100);
  tone1.stop();
  tone1.play(notes[note-2]);
  delay(100);
  tone1.stop();
}

void angryNoise()
{
  int note = (int)random(2,7);
  tone1.play(notes[note]);
  delay(100);
  tone1.stop();
  tone1.play(notes[note-1]);
  delay(200);
  tone1.stop();
}

void neutralNoise()
{
  int note = (int)random(2,26);
  tone1.play(notes[note]);
  delay(200);
  tone1.stop();
}
