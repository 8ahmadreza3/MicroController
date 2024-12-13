int speed = 10 ;
int cycle = 2 ;
int wait =  ((cycle*13)-3) * speed ;
int time =  ((cycle*13)-3) * speed ;

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  for (int i = 0; i < 13 ; i++)
    pinMode(i, OUTPUT);
  pinMode(13, INPUT);
  // Serial.begin(9600);
}

void loop() {
  if(digitalRead(13) == 0){
      return;
  }
  for(int i=0 ; i< 13; i++){
    if(digitalRead(13) == 0){
      f2();
      return;
    }
    if(wait <= 0){
      wait = time;
      f2() ;
      break;
    }
    f1(10, wait, i);
    wait -= speed ;
    // Serial.print(".A.");
  }
  // Serial.println();
}

void f1(int d, int wait, int start){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  for(int i=0 ; i<13 ; i++){
    if(i==start || i==(start+3)%13)
      digitalWrite(i, LOW);
    digitalWrite(i, HIGH);
  }
  
  delay(d);
  highAll();

  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  digitalWrite(A4, HIGH);
  for(int i=0 ; i<13 ; i++){
    if(i==(start+1)%13 || i==(start+2)%13) 
        digitalWrite(i, LOW);
    digitalWrite(i, HIGH);
  }
  delay(wait);
  highAll();

  delay(wait+50);
}

void f2(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  for(int i=0 ; i<=13 ; i++){
    digitalWrite(i-1, HIGH);
    digitalWrite(i, LOW);
    delay(100);
  }
  // Serial.println("RESETEd!!!!");
}

void highAll(){
  for (int i = 0; i < 13 ; i++)
    digitalWrite(i, HIGH);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  delay(10);
}
