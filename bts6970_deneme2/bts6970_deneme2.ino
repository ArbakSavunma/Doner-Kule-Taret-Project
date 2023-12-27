// Bu kodda joystickin oynatılma derecesine belli bir raddeye kadar oranlı kontrol edilir (1800<=300 || 722=>990).
// Bu noktalardan sonra 5 saniyede bir 5 PWM artacak şekilde kontrol edilir.
#define pwmleft 11
#define pwmright 10
#define enleft 5
#define enright 2
#define LIS 9
#define RIS 6
#define pot A0
float potdeg = 0;
float sagpot =181;
float solpot =181;
unsigned long lastmillis=0;
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
      if(potdeg<180) {
        Serial.println("potdeg 180den kucuk");
        Serial.println(potdeg);
        analogWrite(pwmleft, potdeg);
        delay(100);
      }else {
        long now=millis();
        if(now-lastmillis>5000) {
          lastmillis=now;
          if(solpot>255)
            solpot=255;
          solpot +=5;
          delay(100);
          Serial.println(solpot);
          analogWrite(pwmleft, solpot);
          delay(100);
        } else {
          Serial.println("bekliyor");
          if(solpot>255)
            solpot=255;
          Serial.println(solpot);
          analogWrite(pwmleft, solpot);
          delay(100);
        }
      }
    } 

    else if (potdeg > 722) {
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);
      potdeg = (potdeg - 723)*0.85;
      if(potdeg<180) {
        Serial.println("potdeg 180den kucuk");
        Serial.println(potdeg);
        analogWrite(pwmright, potdeg);
        delay(100);
      }else {
        long now=millis();
        if(now-lastmillis>5000) {
          lastmillis=now;
          if(sagpot>255)
            sagpot=255;
          sagpot +=5;
          delay(100);
          Serial.println(sagpot);
          analogWrite(pwmright, sagpot);
          delay(100);
        } else {
          Serial.println("bekliyor");
          if(sagpot>255)
            sagpot=255;
          Serial.println(sagpot);
          analogWrite(pwmright, sagpot);
          delay(100);
        }
      }
    }

    else {
      digitalWrite(enright, LOW);
      digitalWrite(enleft, LOW);
      sagpot=181;
      solpot=181;
      potdeg = 0;
      Serial.println(potdeg);
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(50);
    }
  } 
  else {
      digitalWrite(enright, LOW);
      digitalWrite(enleft, LOW);
      sagpot=181;
      solpot=181;
      potdeg = 0;
      Serial.println(potdeg);
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(50);
  }
  
}