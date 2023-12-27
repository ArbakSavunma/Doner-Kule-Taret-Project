// Bu kodda joystickin ölü bölgesi (1023 analog değerde 300 ile 723 değerler arası orta bölge)  
//dışında gelen veriye göre birebir oranda hareket ettirilen yönde motorun döndürülmesi amaçlanmıştır.
#define pwmleft 11
#define pwmright 10
#define enleft 5
#define enright 2
#define LIS 9
#define RIS 6
#define pot A0
float potdeg = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pwmleft, OUTPUT);
  pinMode(pwmright, OUTPUT);
  pinMode(enleft, OUTPUT);
  pinMode(enright, OUTPUT);
  pinMode(RIS, OUTPUT);
  pinMode(LIS, OUTPUT);
  digitalWrite(enright, HIGH);
  digitalWrite(enleft, HIGH);
  digitalWrite(LIS, LOW);
  digitalWrite(RIS, LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  potdeg = analogRead(pot);
  if (potdeg < 301 || potdeg > 722) {
    if (potdeg < 300) {
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);
      potdeg = (300 - potdeg)*0.85;
      Serial.println(potdeg);
      analogWrite(pwmleft, potdeg);
      delay(100);
    } else if (potdeg > 722) {
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);
      potdeg = (potdeg - 723)*0.85;
      Serial.println(potdeg);
      analogWrite(pwmright, potdeg);
      delay(100);
    } else {
      digitalWrite(enright, LOW);
      digitalWrite(enleft, LOW);
      potdeg = 0;
      Serial.println(potdeg);
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(100);
    }
  } else {
    digitalWrite(enright, LOW);
    digitalWrite(enleft, LOW);
    potdeg = 0;
    Serial.println(potdeg);
    analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
    delay(50);
  }
}