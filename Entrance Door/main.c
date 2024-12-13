#include <Servo.h>
#include <LiquidCrystal.h>
#include "pitches.h"

const int pirPin = 3 ;
const int servo1Pin = 5 ;
const int servo2Pin = 6 ;
boolean doorIsOpen = false ;
const int BUZZER_PIN = 11;

Servo servo1;
Servo servo2;
LiquidCrystal lcd(13, 12, 10, 9, 8, 7);

int melody[] = {
  NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,
  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,
  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4,
  NOTE_E4, REST, NOTE_E4, NOTE_A4, NOTE_C5,
  //repeat
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,
  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,
  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4
};

int durations[] = {
  8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8,
  2, 8, 8, 8, 8,
  //repeats
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8
};

byte fill[8] = {
  0b00000,
  0b01111,
  0b01111,
  0b01001,
  0b01001,
  0b11001,
  0b11011,
  0b00011
};
byte empty[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte x0[8] = {
  0b00000,
  0b00001,
  0b00011,
  0b00111,
  0b01000,
  0b11011,
  0b11011,
  0b11011
};
byte x1[8] = {
  0b11011,
  0b11000,
  0b11011,
  0b01011,
  0b00011,
  0b00011,
  0b00001,
  0b00000
};
byte x2[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00101,
  0b10101,
  0b10101,
  0b10101
};
byte x3[8] = {
  0b10101,
  0b00100,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101
};
byte x4[8] = {
  0b00000,
  0b10000,
  0b11000,
  0b11100,
  0b11010,
  0b11011,
  0b11011,
  0b11011
};
byte x5[8] = {
  0b11011,
  0b00011,
  0b11011,
  0b11010,
  0b11000,
  0b11000,
  0b10000,
  0b00000
};
