#include <LiquidCrystal.h>
#include <Wire.h>
char ch;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int xpin=A0;
int ypin=A1;
int zpin=A2;
float threshhold=80.0;
float xval[15]={0};
float yval[15]={0};
float zval[15]={0};
float xavg;
float yavg;
float zavg;
int steps,flag=0,bpm=0;

void setup() 
{Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  analogWrite(6,100);
  analogWrite(9,28836);
  lcd.begin(16, 2);
  lcd.print("fitness_Band");
  calibrate();

}

void loop()
{ int acc=0;
  float totvect[15]={0};
  float totave[15]={0};
  float xaccl[15]={0};
  float yaccl[15]={0};
  float zaccl[15]={0};
  Serial.print(steps);
  
  for (int i=0;i<15;i++)
  {
    xaccl[i]=float(analogRead(xpin));
    delay(1);
    yaccl[i]=float(analogRead(ypin));
    delay(1);
    zaccl[i]=float(analogRead(zpin));
    delay(1);
    totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
    totave[i] = (totvect[i] + totvect[i-1]) / 2 ;
    delay(150);

    //cal steps 
    if (totave[i]>threshhold && flag==0)
    {
       steps=steps+1;
       flag=1;
    }
    else if (totave[i] > threshhold && flag==1)
    {
        //do nothing 
    }
    if (totave[i] <threshhold  && flag==1)
    {
      flag=0;
    }
   lcd.setCursor(0,1);
  //  Serial.print("steps=");
    //Serial.println(steps);
    lcd.print("steps=");
    lcd.print(steps);
  lcd.print(" ");
  lcd.print("BPM=");
    lcd.print(bpm);
  
  
  }
  delay(100);
}

void calibrate(){
  digitalWrite(13,HIGH);
  //Serial.println("Calibrating......");
  float sum=0;
  float sum1=0;
  float sum2=0;
  for (int i=0;i<15;i++)
  {
    xval[i]=float(analogRead(xpin));
    sum=xval[i]+sum;
  }
  delay(15);
  xavg=sum/15.0;
  Serial.println(xavg);
  for (int j=0;j<15;j++)
  {
    xval[j]=float(analogRead(xpin));
    sum1=xval[j]+sum1;
  }
  yavg=sum1/15.0;
  Serial.println(yavg);
  delay(15);
  for (int i=0;i<15;i++)
  {
    zval[i]=float(analogRead(zpin));
    sum2=zval[i]+sum2;
  }
  zavg=sum2/15.0;
  delay(15);
  Serial.println(zavg);
  digitalWrite(13,LOW);
  //Serial.println("Calibration Successful!");
  //delay(1500);

}
void receiveEvent(int howMany) {
   bpm = Wire.read();    // receive byte as an integer
  Serial.println(bpm);         // print the integer
}
