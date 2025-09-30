#include <Servo.h>
#include <Adafruit_VL53L0X.h>

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

#define SHT_LOX1 50
#define SHT_LOX2 51

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

Servo myservo;  



int pos = 155 , v = 180, speed = 255 ,state=0;
int FI[9] = {0,0,0,0,0,0,0,0,0};

void setID(){
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
    if(!lox1.begin(LOX1_ADDRESS))
  {
    Serial.println("Failed1");
    while(1);
  }
   delay(10);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  if(!lox2.begin(LOX2_ADDRESS))
  {
    Serial.print("Failed2");
    while(1);
  }
  Serial.print("finish 2");
}

void setup() {

  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);

  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(52,OUTPUT);

  Serial.begin(9600);
  myservo.attach(53);  
  myservo.write(v);
  
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  Serial.print("finish 1");
  setID();
  Serial.print("finish init");
}


void loop() {
//Serial.println(apple);
//  FI[0] = analogRead(A2);
//  FI[1] = analogRead(A3);
//  FI[2] = analogRead(A4);
//  FI[3] = analogRead(A5);
//  FI[4] = analogRead(A6);
////for(int i =0;i<5;i++){
////  Serial.print(FI[i]);
////}
 lox1.rangingTest(&measure1,false);
 lox2.rangingTest(&measure2,false);
 Serial.print(measure1.RangeMilliMeter);
 Serial.print("\t");
 Serial.println(measure2.RangeMilliMeter);
//// Fan();
if(state ==0 ){
 if(FI[0] >= 300 || FI[1] >=300 || FI[2]>=320 || FI[3] >= 300 || FI[4] >=300 ) state = 1;
 
 if( measure1.RangeMilliMeter <= 150) {R2(); }
 else if ( measure2.RangeMilliMeter <= 135 ) {R(); }
 else if ( measure2.RangeMilliMeter >= 160) L();
 else S();
}
else if(state ==1 ){
 if(!(FI[0] >= 300 || FI[1] >=300 || FI[2]>=320 || FI[3] >= 300 || FI[4] >=300))state=0;
 if(FI[2]>=300) 
 {
   Stop();
   Fan();
   delay(5000);
   state=0;
 }
   Serial.println(state);
 }
}
else if (FI[0] >= 230 || FI[1] >=230)  R2();
else if (FI[3] >= 230 || FI[4] >=230)  L2();
else  S();}
}
//  }
//  for(int i = 0; i< 5 ; i++) {
//  Serial.print(FI[i]);
//  Serial.println("\t");

void Fan(){
  myservo.write(pos);
 digitalWrite(6,LOW);
 digitalWrite(7,HIGH);
 delay(1500);
 digitalWrite(6,LOW);
 digitalWrite(7,LOW);
 delay(1000);

  }

void L()
{
  analogWrite(2,speed);
  analogWrite(3,0);
  analogWrite(4,speed);
  analogWrite(5,0);
  }
  void R()
{
  analogWrite(2,speed);
  analogWrite(3,0);
  analogWrite(4,speed);
  analogWrite(5,0);
  }
  void S()
{
  analogWrite(2,speed);
  analogWrite(3,0);
  analogWrite(4,speed);
  analogWrite(5,0);
  }
  void Stop()
  {
  analogWrite(2,0);
  analogWrite(3,0);
  analogWrite(4,0);
  analogWrite(5,0);
  }
  void R2(){
  analogWrite(2,speed);
  analogWrite(3,0);
  analogWrite(4,0);
  analogWrite(5,speed);
    
    }
    void L2(){
  analogWrite(2,0);
  analogWrite(3,speed);
  analogWrite(4,speed);
  analogWrite(5,0);
    
    }
//    void VV()
//    {
//      digitalWrite(53,HIGH);
//  delay(10);
//  digitalWrite(53,LOW);}
