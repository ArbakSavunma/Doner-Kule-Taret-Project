#define enA   13
#define enB   12
#define in1   11
#define in2   10
#define in3   9
#define in4   8
#define pot   A0
int potdeg=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  digitalWrite(enA, LOW);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  potdeg = analogRead(pot);
  potdeg = map(potdeg,0,1023,0,255);
  analogWrite(enA, potdeg);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(40);  

}
