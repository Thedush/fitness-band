#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
DS3231  rtc(SDA, SCL);
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);
int t=0;
unsigned long int time1,last=0;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0,craze,CHANGE);
  analogWrite(6,130);
   analogWrite(9,2000);
lcd.begin(16, 2);
Wire.begin(); 
  Serial.begin(9600);
 Serial.begin(9600);
  rtc.begin();
last=millis();   
}
void craze (){

t=1;
  
}

void loop() {
  time1=millis(); 
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr());

  if((time1-last) >  10000){
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("please take ");
  lcd.setCursor(0, 1);
lcd.print(" your tablet");

   while(t==0){
 
 analogWrite(9,0);

  delay(1000);
 analogWrite(9,28836);
 delay(1000);
 

   }
   lcd.clear();
   last=millis();  
   }
   
   Wire.beginTransmission(8);
  int available = Wire.requestFrom(8, (uint8_t)2);
   if(available == 2)
  {
    int received = Wire.read() << 8 | Wire.read(); 
 lcd.setCursor(0 ,1);
 
    lcd.print(received);
    lcd.print("    ");
  }
 Wire.endTransmission();
  
Wire.beginTransmission(9);
 available = Wire.requestFrom(9, (uint8_t)2);
   if(available == 2)
  {
    int receivedValue = Wire.read() << 8 | Wire.read(); 
 // lcd.setCursor(1 ,5);
  // lcd.clear();
 
    lcd.print(receivedValue);
    lcd.print(" ");
 Serial.println(receivedValue);
  }
 Wire.endTransmission();

t=0;
}
