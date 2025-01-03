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

void turnOn() {
  if (isOn)
    return ;

  for (int i = 0 ; i < 10 ; ++i) {
    if (!digitalRead(2))
      return ;

    delay(300);
  }
  palyAnimation();
  isOn = true ;
  delay(1000);
  showLogo();
}

void showLogo() {
  display.clearDisplay();
  delay(50);
  display.drawBitmap(0, 0, logo, 128, 64, WHITE);
  for (int i = 0 ; i < 10 ; i++) {
    if (i % 2 == 0)
      display.drawRect(i, i, 128 - 2 * i, 64 - 2 * i, WHITE);
    else
      display.drawRect(i, i, 128 - 2 * i, 64 - 2 * i, BLACK);

    display.display();
    delay(100);
  }
  delay(500);
  for (int i = 0 ; i < 5 ; i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, logo, 128, 64, WHITE);
    for (int j = 0 ; j < 8 - 2 * i ; j++) {
      if (j % 2 == 0)
        display.drawRect(j, j, 128 - 2 * j, 64 - 2 * j, WHITE);
      else
        display.drawRect(j, j, 128 - 2 * j, 64 - 2 * j, BLACK);
    }
    display.display();
    delay(100);
  }
}

void palyAnimation() {
  for (int i = 1 ; i <= 40 ; i++) {
    if (i % 8 == 1) {
      display.clearDisplay();
    }
    int noteDuration = 1200 / noteDurations[i - 1];
    tone(13, melody[i - 1], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.5;
    delay(pauseBetweenNotes);
    noTone(13);
    if (i % 8 == 0) {
      display.drawBitmap(0, 0, animation[i / 8], 128, 64, WHITE);
      display.display();
    }
  }
  display.display();
}

void login() {
  if (!isOn || isLog)
    return ;
  display.clearDisplay();
  display.drawBitmap(0, 0, logo, 128, 64, WHITE);
  display.display();
  delay(500);

  char key ;
  while (1) {
    key = keypad.getKey();
    if (key)
      break;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(20, 5);
  display.println("ENTER PASSWORD :");
  display.drawRoundRect(14, 20, 100, 18, 8, WHITE);
  display.display();
  checkPass();
}

void checkPass() {
  boolean samePass = true ;
  display.setCursor(18, 25);
  char key ;
  for (int i = 0 ; i < 8 ; i++) {
    while (1) {
      key = keypad.getKey();
      if (key)
        break;
    }
    if (key == '#') {
      samePass = false ;
      break;
    }
    if (key != password[i])
      samePass = false ;

    display.print("* ");
    display.display();
  }
  delay(500);

  display.clearDisplay();
  display.setCursor(20, 20);
  if (samePass) {
    isLog = true ;
    display.println("Welcome Back !!");
  } else {
    display.println("Wrong Password!");
    display.display();
    delay(750);
    display.println("\n   Try again later");
  }
  display.display();
  delay(1500);
}

void goMenu() {
  if (!isOn || !isLog || isLock)
    return ;
  char key ;
  int i = 0;
  showMenu(i);
  while (!isLock) {
    while (1) {
      key = keypad.getKey();
      if (key)
        break;
    }
    if (key == '0') {
      i = (++i) % 2 ;
    } else if (key == '#') {
      i = (++i) % 2 ;
    } else
      chooseApp(key, i);

    showMenu(i);
    tm.set(-1);
  }
}

void showMenu(int i) {
  display.clearDisplay();
  display.drawBitmap(0, 0, menu[i], 128, 64, WHITE);
  display.display();
}

void chooseApp(char key, int i) {
  if (key == 'A') {
    if (i == 0) {
      distanceApp() ;
    } else {
      calculator() ;
    }
  } else if (key == 'B') {
    if (i == 0) {
      temAndHum();
      // } else {
      //   // playGame();
    }
  } else if (key == 'C') {
    if (i == 0) {
      showClock();
    } else {
      gallery();
    }
  } else if (key == 'D') {
    if (i == 0) {
      cronometer();
      //   } else {
      //     lock();
    }
  }
}

void distanceApp() {
  char key ;
  while (1) {
    long duration, distance;
    display.clearDisplay();
    display.drawBitmap(0, 0, distanceTe, 128, 64, WHITE);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    delay(200);
    distance = duration * 0.0343 / 2;
    display.setTextSize(2);
    display.setCursor(20, 20);
    display.setTextColor(WHITE);
    display.print(distance);
    display.setCursor(15, 45);
    display.print(distance / 100.0);
    display.display();
    for (int i = 0 ; i < 100 ; i++) {
      key = keypad.getKey();
      if (key == '#')
        return;

      delay(10);
    }
  }
}

void showClock() {
  char key ;
  DateTime now = rtc.now();
  display.clearDisplay();
  display.drawBitmap(0, 0, clockTe, 128, 64, WHITE);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(80, 0);
  display.print(now.year());
  display.setCursor(90, 18);
  display.print("/");
  display.print(now.month());
  display.setCursor(90, 35);
  display.print("/");
  display.print(now.day());
  display.display();
  tm.set(2);
  tm.point(1);
  while (1) {
    DateTime now = rtc.now();
    tm.display(0, (now.hour() / 10) % 10);
    tm.display(1, now.hour() % 10);
    tm.display(2, (now.minute() / 10) % 10);
    tm.display(3, now.minute() % 10);
    for (int i = 0 ; i < 600 ; i++) {
      key = keypad.getKey();
      if (key == '#') {
        return;
      }
      delay(10);
    }
  }
}

void temAndHum() {
  char key ;
  while (1) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    display.clearDisplay();
    display.drawBitmap(0, 0, tempHumTe, 128, 64, WHITE);
    display.setCursor(57, 6);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print(t);
    display.setCursor(74, 32);
    display.print(h);
    display.display();
    for (int i = 0 ; i < 200 ; i++) {
      key = keypad.getKey();
      if (key == '#')
        return;

      delay(10);
    }
  }
}

void cronometer() {
  char key ;
  display.clearDisplay();
  display.drawBitmap(0, 0, cronoTe, 128, 64, WHITE);
  display.display();
  tm.point(1);
  tm.set(2);
  while (1) {
    if (second >= 100) {
      tm.display(0, (second / 600) % 10);
      tm.display(1, (second / 60) % 10);
      tm.display(2, (second / 10) % 6);
      tm.display(3, second % 10);
    } else {
      tm.display(0, second / 10);
      tm.display(1, second % 10);
      tm.display(2, (centisecond / 10) % 10);
      tm.display(3, centisecond % 10);
    }
    key = keypad.getKey();
    if (key == '#') {
      canCount = false ;
      centisecond = 0 ;
      second = 0 ;
      tm.set(-1);
      return;
    } else if (key == 'A') {
      canCount = true ;
    } else if (key == 'B') {
      canCount = false ;
      centisecond = 0 ;
      second = 0 ;
    } else if (key == 'C') {
      canCount = false ;
    } else if (key == 'D') {
      canCount = true ;
    }
  }
}

void TimingISR() {
  if (!canCount)
    return ;
  centisecond ++;
  if (centisecond == 100) {
    second ++;
    if (second == 5999) {
      second = 0;
    }
    centisecond = 0;
  }
}

void calculator() {
  char key ;
  int first = 0 ;
  int second = 0 ;
  int result = 0 ;
  char op ;
  display.clearDisplay();
  display.drawBitmap(0, 0, calculatorTe, 128, 64, WHITE);
  display.display();
  display.setCursor(10, 10);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  while (1) {
    while (1) {
      key = keypad.getKey();
      if (key) {
        if ((int) key - 48 < 10 && (int) key > 47) {
          if (first == result) {
            result = 0 ;
            first = 0 ;
          }
          display.clearDisplay();
          display.drawBitmap(0, 0, calculatorTe, 128, 64, WHITE);
          display.setCursor(15, 0);
          first = first * 10 + ((int) key - 48) ;
          display.print(first);
          display.display();
        } else if (key == '#') {
          return ;
        } else if (key == 'D') {
          continue ;
        } else {
          display.clearDisplay();
          display.drawBitmap(0, 0, calculatorTe, 128, 64, WHITE);
          display.setCursor(15, 0);
          display.print(first);
          display.setCursor(0, 25);
          display.print(chooseOperator(key));
          display.display();
          op = key ;
          break ;
        }
      }
    }
    while (1) {
      key = keypad.getKey();
      if (key) {
        if ((int) key - 48 < 10 && (int) key > 47) {
          display.clearDisplay();
          display.drawBitmap(0, 0, calculatorTe, 128, 64, WHITE);
          display.setCursor(15, 0);
          display.print(first);
          display.setCursor(0, 25);
          display.print(chooseOperator(op));
          second = second * 10 +  ((int) key - 48) ;
          display.setCursor(15, 25);
          display.print(second);
          display.display();
        } else if (key == 'D') {
          result = calculate(first, second, op);
          display.clearDisplay();
          display.drawBitmap(0, 0, calculatorTe, 128, 64, WHITE);
          display.setCursor(15, 0);
          display.print(first);
          display.setCursor(0, 25);
          display.print(chooseOperator(op));
          display.setCursor(15, 25);
          display.print(second);
          display.setCursor(0, 45);
          display.print("=");
          display.setCursor(15, 45);
          display.print(result);
          display.display();
          break ;
        } else if (key == '#') {
          return ;
        }
      }
    }
    first = result ;
    second = 0 ;
  }
}

int calculate(int a, int b, char op) {
  if (op == '*') {
    return a * b ;
  } else if (op == 'A') {
    return a / b ;
  } else if (op == 'B') {
    return a + b ;
  } else if (op == 'C') {
    return a - b ;
  }
  return -1;
}

char chooseOperator(char op) {
  if (op == '*') {
    return '*';
  } else if (op == 'A') {
    return '÷';
  } else if (op == 'B') {
    return '+';
  } else {
    return '-';
  }
}

void gallery() {
  char key ;
  int i = 0 ;
  display.setTextSize(2);
  display.setTextColor(WHITE);
  while (1) {
    i %= 6 ;
    display.clearDisplay();
    display.drawBitmap(0, 0, galleryTe, 128, 64, WHITE) ;
    display.drawBitmap(14, 0, photos[i], 100, 64, WHITE) ;
    display.setCursor(0, 43);
    display.print("A");
    display.setCursor(116, 43);
    display.print("B");
    display.display();
    while (1) {
      key = keypad.getKey();
      if (key) {
        if (key == 'A') {
          i += 5 ;
          break;
        } else if (key == 'B') {
          i++ ;
          break;
        } else if (key == '#') {
          return ;
        }
      }
    }
  }
}
