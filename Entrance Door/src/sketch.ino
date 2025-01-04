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

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(A0, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  lcd.begin(20, 4);
  lcd.clear();
  lcd.createChar(1, empty);
  lcd.createChar(2, fill);
  lcd.createChar(3, x0);
  lcd.createChar(4, x1);
  lcd.createChar(5, x2);
  lcd.createChar(6, x3);
  lcd.createChar(7, x4);
  lcd.createChar(8, x5);
  Serial.begin(115200);
}

void loop() {
  if (isMovement()) {
    openDoor(analogRead(A0));
    play();
  }
  delay(250);
}

boolean isMovement() {
  return digitalRead(pirPin) && !doorIsOpen;
}

void openDoor(int limit) {
  doorIsOpen = true ;
  int time = 3500 ;
  int max = map(limit, 0, 1023, 0, 90);
  lcd.clear();
  lcd.print("WELLCOME");
  lcd.setCursor(4, 1);
  lcd.print("to my project!!!");
  for (int pos = 0 ; pos <= max ; pos++) {
    servo1.write(90 - pos);
    servo2.write(90 - pos);
    delay(35);
    time -= 35 ;
  }
  delay(time);
  lcd.clear();
}

void play() {
  int size = sizeof(durations) / sizeof(int);
  for (int note = 0, i = 0 ; note < size ; note++) {
    // to calculate the note duration, take one second divided by the note type.
    int duration = 1500 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);
    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = duration * 1; //1.25
    if (note >= 5 && note < 45) {
      fillLCD(note - 5, 2);
    } else if (note >= size - 40) {
      showLogo(i++);
    }
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

void fillLCD(int i, int charID) {
  // fill lcd Step by step
  lcd.setCursor((int)i / 4, i % 4);
  lcd.write(charID);
  lcd.setCursor((int)(79 - i) / 4, (79 - i) % 4);
  lcd.write(charID);
}

void showLogo(int i) {
  // show logo Step by step
  lcd.setCursor((int)i / 4, i % 4);
  if (i == 33) {
    lcd.write(1);
    i = 46 ;
    lcd.setCursor((int)i / 4, i % 4);
    lcd.write(8);
  } else if (i == 34) {
    lcd.write(1);
    i = 45 ;
    lcd.setCursor((int)i / 4, i % 4);
    lcd.write(7);
  } else if (i == 37) {
    lcd.write(3);
    i = 42 ;
    lcd.setCursor((int)i / 4, i % 4);
    lcd.write(6);
  } else if (i == 38) {
    lcd.write(4);
    i = 41 ;
    lcd.setCursor((int)i / 4, i % 4);
    lcd.write(5);
  } else {
    fillLCD(i, 1);
  }
}
