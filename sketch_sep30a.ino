#include <Adafruit_VL53L0X.h>
#define Fan_32 32
#define Fan_33 33
#define Fan_38 38
#define Fan_39 39
#define Fan_8 8
#define Fan_9 9
int line_1 = A0;
int line_2 = A3;
int line_3 = A11;
int time =0;

int fire_R = A4;
int fire_1 = A5;
int fire_2 = A6;
int fire_3 = A7;
int fire_4 = A8;
int fire_5 = A9;
int fire_L = A10;

int c=5;
int fire_Rh = A1;
int fire_2h = A12;
int fire_3h = A13;
int fire_4h = A14;
int fire_5h = A15;
int fire_Lh = A2;


int motor_b1 = 4;
int motor_b2 = 5;
int motor_c1 = 6;
int motor_c2 = 7;

#define LEFT_ENCODER_PIN1 18  
#define LEFT_ENCODER_PIN2 19
#define RIGHT_ENCODER_PIN1 2
#define RIGHT_ENCODER_PIN2 3
volatile int BML,BMR;

int line_val[5] = {0};
int fire_val[7] = {0};
int fire_valh[7] = {0};

int y=200;
int state = -3;
int dis_L = 0;
int dis_F = 0;
int count = 0;
int z=99999;
// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
//#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 12
//#define SHT_LOX2 13

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
//VL53L0X_RangingMeasurementData_t measure2;


void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(18), ReadEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), ReadEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), ReadEncoderC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ReadEncoderD, CHANGE);
  pinMode(RIGHT_ENCODER_PIN1, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER_PIN2, INPUT_PULLUP);
  pinMode(LEFT_ENCODER_PIN1, INPUT_PULLUP);
  pinMode(LEFT_ENCODER_PIN2, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(line_1, INPUT);
  pinMode(line_2, INPUT);
  pinMode(line_3, INPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);
  pinMode(motor_c1, OUTPUT);
  pinMode(motor_c2, OUTPUT);

  pinMode(Fan_38, OUTPUT);
  pinMode(Fan_39, OUTPUT);
  pinMode(Fan_33, OUTPUT);
  pinMode(Fan_32, OUTPUT);
  pinMode(Fan_8, OUTPUT);
  pinMode(Fan_9, OUTPUT);

  pinMode(SHT_LOX1, OUTPUT);
  //pinMode(SHT_LOX2, OUTPUT);
  Serial.println("Shutdown pins 設定為輸出");
  digitalWrite(SHT_LOX1, LOW);
  //digitalWrite(SHT_LOX2, LOW);
  Serial.println("初始化完成"); 
  setID();

 
}
//left(200,200)
//Line_following(260);
//速差抓7
void loop() {
  // put your main code here, to run repeatedly:
   detect();
  if(state==-3){
    if(analogRead(A0)<350){
    state = -2;
    }
    if(analogRead(A11)<400){
    forward(90,140);
    }
    if(analogRead(A3)<400){
    forward(140,90);
    }
  }
  if(state == -2){
    stop();
    delay(100);
    back(105,100);
    Line_following(700);
    stop();
    delay(100);
    left(167,162);
    Line_following(380);
    stop();
    delay(500);
    //do{
    // left(100,100);
    // }while(analogRead(A0)<350);
    // stop();
    // delay(500);
    // left(165,162);
    // Line_following(400);
    // stop();
    // delay(1000);
    // do{
    // left(150,150);
    // }while(analogRead(A11)<350);
    //  stop();
    // delay(1000);
    // right(155,150);
    // Line_following(260);
    forward(250,250);
    Line_following(250);
    stop();
    delay(100);
    state = 0;
  }
  // if(state == -1){

  // if(analogRead(A4) > 150)
  //     state = 1;
  // if(analogRead(A10) > 150)
  //     state = 2;
  // if( analogRead(A1) > 150)
  //     state = 7;
  // if(analogRead(A2) > 150)
  //     state = 8;
  // if(analogRead(A3)<350){
  // forward(35,140);
  // }
  // else{
  // forward(140,35);
  // }
  // if(analogRead(A0)<270){
  // stop();
  // delay(1000);
  // }
  //}
  if(state == 0){ //尋找火焰
    if(analogRead(A0) < 300 ){
      back(155,155);
      delay(300);
      left(155,155);
      delay(250);
    }
    else if(analogRead(A3) < 300){
      back(155,155);
      delay(300);
      left(150,150);
      delay(250);
      
    }
    int x=120;
    if(analogRead(A5) > x || analogRead(A6) > x || analogRead(A7) > x || analogRead(A8) > x || analogRead(A9) > x ){
    sound();
      state = 3;
    }
    if(  analogRead(A12) > x || analogRead(A13) > x || analogRead(A14) > x || analogRead(A15) > x||analogRead(A2) > x){
    sound2();
    state = 6 ;
    }
    if(analogRead(A4) > y)
      state = 1;
    if(analogRead(A10) > y)
      state = 2;
    if( analogRead(A1) > 150)
      state = 8;
    // if(analogRead(A2) > y)
    //   state = 8;
    if(dis_F < z){
      back(155,155);
      delay(300);
      left(155,155);
      delay(300); 
    }
    else{
      forward(155,150);
    }
  }

  if(state == 1){   //右轉面相火焰
    stop();
    delay(100);
    back(100,100);
    Line_following(80);
    sound();
    right(207,200);
    Line_following(260);
    stop();
    state = 3;
  }
  if(state == 7){   //第二層右轉面相火焰
    stop();
    delay(100);
    back(100,100);
    Line_following(80); 
    sound2();
    right(207,200);
    Line_following(260);
    stop();
    state = 6;
  }

  if(state == 2){    //左轉面相火焰
    stop();
    delay(100);
    back(100,100);
    Line_following(80);
    sound();
    left(207,200);
    Line_following(260);
    stop();
    state = 3;
  }
  if(state == 8){    //第二層左轉面相火焰
    stop();
    delay(100);
    back(100,100);
    Line_following(80);
    sound2();
    left(207,200);
    Line_following(260);
    stop();
    state = 6;
  }
  if(state == 3){   //往前找火焰
    if(analogRead(A0) < 350 || analogRead(A3) < 350 || analogRead(A11) < 350)
      state = 4;
    if(analogRead(A5) > 150)
      forward(100,100);
    else if(analogRead(A5) > 150 || analogRead(A6) > 150)
      right(140,70);
    else if(analogRead(A8) > 150 || analogRead(A9) > 150)
      left(70,140);
    else
      forward(130,130);
  }
    if(state == 6){   //第二層往前找火焰
  
    if(analogRead(A0) < 350 || analogRead(A3) < 350 || analogRead(A11) < 350)
      state = 4;

    if(analogRead(A13) > 150)
      forward(100,100);
    else if( analogRead(A12) > 160||analogRead(A2) > 160)
      right(125,80);
    else if(analogRead(A14) > 160 || analogRead(A15) > 160)
      left(80,125);
    else
      forward(130,130);
    }
  if(state == 4){  //吹襲火焰
    stop(); 
    delay(100);
    forward(100,100);
    delay(100);
    stop();
    delay(100);
    Fan();
    left(100,100);
    delay(200);
    for(int i=0;i<2;i++){
    right(100,100);
    delay(400);
    left(100,100);
    delay(400);  
    }
    right(100,100);
    delay(200);
    stop();
    delay(100);
    FanS();
    state = c;
  }

  if(state == 5){//第一次滅完火
    stop();
    delay(100);
    back(107,100);
    Line_following(300);
    stop();
    delay(100);
    left(107,100);
    Line_following(170);
    stop();
    delay(100);
    forward(157,150);
    Line_following(980);
    stop();
    delay(100);
    right(107,100);
    Line_following(165);
    stop();
    delay(100);
    forward(183,180);
    Line_following(2050);
    stop();
    delay(100);
    left(100,100);
    Line_following(325);
    stop();
    delay(100);
    forward(157,150);
    Line_following(100);
    stop();
    delay(100);
    c = 9;
    state = 0;
  }
  if(state == 9){//第二次滅完火
    stop();
    delay(100);
    back(100,100);
    Line_following(150);
    right(100,100);
    Line_following(330);
    forward(153,150);
    Line_following(1800);
    stop();
    delay(500);
    left(100,100);
    Line_following(150);
    c = 10;
    state = 0;
  }
  if(state == 10){//第三次滅完火
  back(100,100);
  Line_following(190);
  right(107,100);
  Line_following(300);
  forward(155,150);
  Line_following(1000);
  right(100,100);
  Line_following(280);
  forward(155,150);
  Line_following(550);
  right(100,100);
  Line_following(265);
  forward(155,150);
  Line_following(100);
  c=11;
  state = 0;
  }
  if(state == 11){
  z=300;
  back(155,155);
  delay(200);
  right(100,100);
  Line_following(10);
  c=11;
  state = 0;
  }
}
void Line_following(int dis  ){
  BML = 0;
  BMR = 0;

  while(1){ 
//    if(abs(BML) > dis || abs(BMR) > dis || now_timer >= time) break; 
    if((abs(BML)+abs(BMR))/2 > dis ) break;

    delay(5);
 //   Serial.println(BMR);  
  } 
//    Serial.println(BMR); 
}
void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  //digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  //digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  //digitalWrite(SHT_LOX2, LOW);
  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println("Failed to boot first VL53L0X");
    while(1);
  }
  // delay(10);
  // activating LOX2
  // digitalWrite(SHT_LOX2, HIGH);
  // delay(10);

  //initing LOX2
  // if(!lox2.begin(LOX2_ADDRESS)) {
  //   Serial.println("Failed to boot second VL53L0X");
  //   //while(1);
  // }
}

void detect(){
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  //lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  if(measure1.RangeStatus != 4){
  dis_F = measure1.RangeMilliMeter; //最遠120cm
  }

Serial.print(analogRead(A0));
Serial.print(" ");
Serial.print(analogRead(A3));
Serial.println(" ");
  
}
void stop(){
  analogWrite(motor_b1, 0);
  analogWrite(motor_b2, 0);
  analogWrite(motor_c1, 0);
  analogWrite(motor_c2, 0);
}
void forward(int a,int b){
  analogWrite(motor_b1, a);
  analogWrite(motor_b2, 0);
  analogWrite(motor_c1, b);
  analogWrite(motor_c2, 0);
}
void back(int a,int b){
  analogWrite(motor_b1, 0);
  analogWrite(motor_b2, a);
  analogWrite(motor_c1, 0);
  analogWrite(motor_c2, b);
}
void right(int a,int b){
  analogWrite(motor_b1, a);
  analogWrite(motor_b2, 0);
  analogWrite(motor_c1, 0);
  analogWrite(motor_c2, b);
}
void left(int a,int b){
  analogWrite(motor_b1, 0);
  analogWrite(motor_b2, a);
  analogWrite(motor_c1, b);
  analogWrite(motor_c2, 0);
}
void Fan(){
 
  digitalWrite(33, 0);
  digitalWrite(32, 1);
  digitalWrite(38, 0);
  digitalWrite(39, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
}
void FanS(){
  digitalWrite(32, 0);
  digitalWrite(33, 0);
  digitalWrite(38, 0);
  digitalWrite(39, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
}
void sound(){
  digitalWrite(52, HIGH);
  delay(10);
  digitalWrite(52, LOW);
  delay(5);
}
void sound2(){
  digitalWrite(52, HIGH);
  delay(10);
  digitalWrite(52, LOW);
  delay(5);
  digitalWrite(52, HIGH);
  delay(10);
  digitalWrite(52, LOW);
}
void ReadEncoderA()
{
    digitalRead(LEFT_ENCODER_PIN1) ^ digitalRead(LEFT_ENCODER_PIN2) ? ++BML : --BML;
    // Serial.println(BML);
}

void ReadEncoderB()
{
    digitalRead(LEFT_ENCODER_PIN1) ^ digitalRead(LEFT_ENCODER_PIN2) ? --BML : ++BML;
}

void ReadEncoderC()
{
    digitalRead(RIGHT_ENCODER_PIN1) ^ digitalRead(RIGHT_ENCODER_PIN2) ? --BMR : ++BMR;
    // Serial.println(BMR);
}

void ReadEncoderD()
{
    digitalRead(RIGHT_ENCODER_PIN1) ^ digitalRead(RIGHT_ENCODER_PIN2) ? ++BMR : --BMR;
}
