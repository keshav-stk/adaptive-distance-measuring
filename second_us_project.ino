#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2); // lcd connected pin
#define trig 9// defining diferent pins
#define eco 8
#define red 10
#define yellow 11
#define green 12

int cm, inch;
long dur;
byte count = 0;
int ch[10];

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trig, OUTPUT);// defining pin modes
pinMode(eco, INPUT);
pinMode(red, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
lcd.begin(16,2);
lcd.print("Ultrasonic sensor");
lcd.setCursor(0,1);
lcd.print("working...");
delay(200);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(trig, LOW);// sending pulse to sensor
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);

dur = pulseIn(eco, HIGH);//reading incoming sensor value
cm = dur * 0.034/2;
// inch = cm /2.54;
// lcd.setCursor(0,0);
// lcd.print(dur);
ch[count]=cm;// to only execute the calculation if there is difference in distance from previous loop
if(count ==0 ||(ch[count]-ch[0])!=0){
if((ch[count]-ch[0])!=0){
  ch[0]=ch[count];
  count=0;
}
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Dist:");
lcd.print(cm);
lcd.print("cm");

if(cm>950){
  digitalWrite(green,HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  lcd.setCursor(0,1);
  lcd.print("FAR FAR AWAY");
}
else if(cm<949 && cm>=600){
  digitalWrite(yellow,HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
 lcd.setCursor(0,1);
 lcd.print("A BIT FAR");
}
else if(cm<600 && cm>=300){
  digitalWrite(yellow,HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
 lcd.setCursor(0,1);
 lcd.print("! BIT CLOSE !");  
}
else if(cm<300 && cm>=200){
  digitalWrite(red,HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
 lcd.setCursor(0,1);
 lcd.print("! CLOSE !");
}
else{
  digitalWrite(red,HIGH);
  tone(1,500);// cant make the buzzer work
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
 lcd.setCursor(0,1);
 lcd.print("! TOO CLOSE !");

}
}
count=1;
}
