#include "sounds.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <DHT.h>
#include <TM1637.h>
#include <TimerOne.h>
#include <RTClib.h>
#include "templates.h"

boolean isOn = false ;
boolean isLog = false ;
boolean isLock = false ;

unsigned int centisecond = 0;
unsigned int second = 0;
boolean canCount = false ;

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {10, 9, 8, 7};
byte colPins[4] = {6, 5, 4, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int trigPin = 12, echoPin = 11;

DHT dht(23, DHT22);

RTC_DS3231 rtc;

TM1637 tm(27, 25);

char password[] = "10203040";

void setup() {
  tm.init();
  tm.set(2);
  pinMode(12, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
  }
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC. Dead now.");
    while (1);
  }
  Timer1.initialize(10000);
  Timer1.attachInterrupt(TimingISR);
}

void loop() {
  turnOn();
  login();
  goMenu();
}