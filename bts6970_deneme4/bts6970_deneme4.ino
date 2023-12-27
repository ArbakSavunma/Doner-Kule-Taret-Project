// Bu kodda bütün işlevler düzenlenip fonksiyonlara ayrılmıştır. Ve Teknofest Fuarında test edilmiştir. Testler esnasında bazı işlevler pasifleştirilmiştir.
//Sabit değerler kullanılarak çalışılmıştır. Düzenlenecektir!!!

int pwmleft=11;        //pin tanımlamaları
int pwmright=10;
int enleft=5;
int enright=2;
int LIS=9;
int RIS=6;
int pot=A0;
float potdeg = 0;
float potval=190;
unsigned long lastmillis=0;
int rottec=0;
//************************************************************************
unsigned long delaycompare(float potdeg);       //Fonksiyon prototipleri
float pwmloop(unsigned long del,int potdirect);
void slowing(float potval,int en,int dis,int potdirect, int rottec);
//************************************************************************
void setup() {
  Serial.begin(115200);
  pinMode(pwmleft, OUTPUT);       //pin ve seri haberleşme döngüsü
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
//*************************************************************************
void loop() {
  potdeg = analogRead(pot);  //joystickten veri okunur
  if (potdeg < 301 || potdeg > 722) {
    if (potdeg < 301) {
      rottec=1;
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);         // sola dönüş
      potdeg = (300 - potdeg)*0.85; 
      
      pwmloop(delaycompare(potdeg),pwmleft);
    } 
    else {
      rottec=2;
      digitalWrite(enright, HIGH);
      digitalWrite(enleft, HIGH);       //sağa dönüş
      potdeg = (potdeg - 723)*0.85;
    
      pwmloop(delaycompare(potdeg),pwmright);
    }
  } 
  else {
    Serial.println("SON ELSE GİRDİ");
    if(rottec==1) {
      slowing(potval,enleft,enright,pwmleft,rottec);            //yavaşlama soldan
      potval=0;
    }
    else if(rottec==2) {
      slowing(potval,enright,enleft,pwmright,rottec);           // yavaşlama sağdan
      potval=0;
    }
    else{
      digitalWrite(enright, LOW);         //durma
      digitalWrite(enleft, LOW);
      analogWrite(pwmright, 0);
      analogWrite(pwmleft, 0);
      delay(50);
    }
    digitalWrite(enright, LOW);           //durma
    digitalWrite(enleft, LOW);
    analogWrite(pwmright, 0);
    analogWrite(pwmleft, 0);
    delay(50);
  }
  
}
//************************************************************************
unsigned long delaycompare(float potdeg) {
  unsigned long del;
  if(potdeg>=0 && potdeg<=50)
        del=1000;
      else if(potdeg>50 && potdeg<=100)
        del=900;
      else if(potdeg>100 && potdeg<=150)
        del=800;
      else if(potdeg>150 && potdeg<=175)
        del=700;
      else if(potdeg>175 && potdeg<=200)
        del=600;
      else if(potdeg>200 && potdeg<=215)
        del=500;
      else if(potdeg>215 && potdeg<=225)
        del=400;
      else if(potdeg>225 && potdeg<=235)
        del=350;
      else if(potdeg>235 && potdeg<=255)
        del=300;
      else
        del=300;

      return del;
}
//**************************************************************************
float pwmloop(unsigned long del,int potdirect) {
  long now=millis();
  
    if(now-lastmillis>delaycompare(potdeg)) {
        
      lastmillis=now;
      if(potval>220)
        potval=220;
      if(potval<190)
        potval=190;
      potval +=10;
      delay(100);
      Serial.println(potval);
      analogWrite(potdirect, potval);
     
    } else {
      Serial.println("bekliyorsol");
      if(potval>220)
        potval=220;
      Serial.println(potval);
      analogWrite(potdirect, potval);
      delay(100);
    }
    return potval;
}
//*******************************************************************************
void slowing(float potval,int en,int dis,int potdirect, int rottec) {
  for(int i=potval; i>0; i-=10) {
         digitalWrite(en, HIGH);
         digitalWrite(dis, HIGH);
         analogWrite(potdirect, i);
         Serial.println("azaliyor");
         Serial.println(i);
         delay(3);
         
  }
}
//********************************************************************************