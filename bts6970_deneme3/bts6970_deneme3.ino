// Evet gelelim bu koda. Bu kodda ölü bölgeler dışında joystick değerlerine göre delay değerleri belirlenip interrupt ile bu zaman değerleri arasında motor
//sürücüsüne gönderilecek PWM sinyali arttırılır. Yön değiştirme durumda ise yavaşlatma uygulanır. 
#define pwmleft 11
#define pwmright 10
#define enleft 5
#define enright 2
#define LIS 9
#define RIS 6
#define pot A0
float potdeg = 0;
float sagpot =0;
float solpot =0;
unsigned long lastmillis=0;
unsigned long delaysag=0;
unsigned long delaysol=0;
int rottec=0;
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
    
    if (potdeg < 301) {
      rottec=1;
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);
      potdeg = (300 - potdeg)*0.85; 
      if(potdeg>=0 && potdeg<=50)
        delaysol=5000;
      else if(potdeg>50 && potdeg<=100)
        delaysol=4750;
      else if(potdeg>100 && potdeg<=150)
        delaysol=4500;
      else if(potdeg>150 && potdeg<=175)
        delaysol=4000;
      else if(potdeg>175 && potdeg<=200)
        delaysol=3000;
      else if(potdeg>200 && potdeg<=215)
        delaysol=2000;
      else if(potdeg>215 && potdeg<=225)
        delaysol=1000;
      else if(potdeg>225 && potdeg<=235)
        delaysol=750;
      else if(potdeg>235 && potdeg<=255)
        delaysol=500;
      else
        delaysol=500;
      long now=millis();
      if(now-lastmillis>delaysol) {
        lastmillis=now;
        if(solpot>255)
          solpot=255;
        solpot +=5;
        delay(100);
        Serial.println(solpot);
        analogWrite(pwmleft, solpot);
        delay(100);
      } else {
        Serial.println("bekliyorsol");
        if(solpot>255)
          solpot=255;
        Serial.println(solpot);
        analogWrite(pwmleft, solpot);
        delay(100);
      }
     /* if(potdeg<180) {
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
      }*/
    } 

    else {
      rottec=2;
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);
      potdeg = (potdeg - 723)*0.85;
      if(potdeg>=0 && potdeg<=50)
        delaysag=5000;
      else if(potdeg>50 && potdeg<=100)
        delaysag=4750;
      else if(potdeg>100 && potdeg<=150)
        delaysag=4500;
      else if(potdeg>150 && potdeg<=175)
        delaysag=4000;
      else if(potdeg>175 && potdeg<=200)
        delaysag=3000;
      else if(potdeg>200 && potdeg<=215)
        delaysag=2000;
      else if(potdeg>215 && potdeg<=225)
        delaysag=1000;
      else if(potdeg>225 && potdeg<=235)
        delaysag=750;
      else if(potdeg>235 && potdeg<=255)
        delaysag=500;
      else
        delaysag=500;
      long now=millis();
      if(now-lastmillis>delaysag) {
        lastmillis=now;
        if(sagpot>255)
          sagpot=255;
        sagpot +=5;
        delay(100);
        Serial.println(sagpot);
        analogWrite(pwmright, sagpot);
        delay(100);
      } else {
        Serial.println("bekliyorsag");
        if(sagpot>255)
          sagpot=255;
        Serial.println(sagpot);
        analogWrite(pwmright, sagpot);
        delay(100);
      }
      /*if(potdeg<180) {
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
      }*/
    }

   
  } 
  else {
    Serial.println("SON ELSE GİRDİ");
    if(rottec==1) {
      for(int i=solpot; i>0; i--) {
         digitalWrite(enleft, HIGH);
         digitalWrite(enright, HIGH);
         analogWrite(pwmleft, i);
         Serial.println("azaliyor");
         Serial.println(i);
         delay(10);
      }
    }
    else if(rottec==2) {
      for(int i=sagpot; i>0; i--) {
         digitalWrite(enright, HIGH);
         digitalWrite(enleft, HIGH);
         analogWrite(pwmright, i);
         Serial.println("azaliyor");
         Serial.println(i);
         delay(10);
      }
    }
    else{
      digitalWrite(enright, LOW);
      digitalWrite(enleft, LOW);
      sagpot=0;
      solpot=0;
      potdeg = 0;
      Serial.println("BURAYA GİRDİ1");
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(50);
    }
      digitalWrite(enright, LOW);
      digitalWrite(enleft, LOW);
      sagpot=0;
      solpot=0;
      potdeg = 0;
      Serial.println(potdeg);
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(50);
  }
  
}