#include <IBusBM.h>
// iBus 1.1.4 (FS-I6X)

//Motor 1 FL
#define f1 2
#define b1 3
#define s1 4

//Motor 2 FR
#define f2 7
#define b2 6
#define s2 5

//Motor 3 BC
#define f3 8
#define b3 9
#define s3 10

IBusBM ibus; //iBus Object

//Channel 1-5 reading (Joy)
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//Channel 6 reading (Switch) (Disabled)
/*
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
*/

void setup() {
  Serial.begin(115200);
  ibus.begin(Serial1); //iBus init on Serial1

  //Set motor driver pinmode
  for(int i=2;i<=10;i++){
    pinMode(i,OUTPUT);
  }

  //Constant Speed (Disabled)
  /*
  analogWrite(s1,255);
  analogWrite(s2,255);
  analogWrite(s3,255);
  */
}

void loop() {

  //CH1-4 (Joy)
  int rawROTATE = readChannel(0, -100, 100, 0);
  int rawFB = readChannel(2, -100, 100, 0);
  int rawLR = readChannel(3, -100, 100, 0);
  
  //Mapping
  if(rawROTATE<-20){
    int ROTATE_CCW = 0;
    ROTATE_CCW = map(rawROTATE, 0, -100, 0, 80);

    digitalWrite(f1,1);digitalWrite(b1,0);analogWrite(s1,ROTATE_CCW);
    digitalWrite(f2,1);digitalWrite(b2,0);analogWrite(s2,ROTATE_CCW);
    digitalWrite(f3,0);digitalWrite(b3,1);analogWrite(s3,ROTATE_CCW);

  }else if(rawROTATE>=20){
    int ROTATE_CW = 0;
    ROTATE_CW = map(rawROTATE, 0, 100, 0, 80);

    digitalWrite(f1,0);digitalWrite(b1,1);analogWrite(s1,ROTATE_CW);
    digitalWrite(f2,0);digitalWrite(b2,1);analogWrite(s2,ROTATE_CW);
    digitalWrite(f3,1);digitalWrite(b3,0);analogWrite(s3,ROTATE_CW);

  }else if(rawFB<-20){
    int FW = 0;
    FW = map(rawFB, 0, -100, 0, 200);
    
    digitalWrite(f1,1);digitalWrite(b1,0);analogWrite(s1,FW);
    digitalWrite(f2,0);digitalWrite(b2,1);analogWrite(s2,FW);
    digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);

  }else if(rawFB>=20){
    int RW = 0;
    RW = map(rawFB, 0, 100, 0, 200);

    digitalWrite(f1,0);digitalWrite(b1,1);analogWrite(s1,RW);
    digitalWrite(f2,1);digitalWrite(b2,0);analogWrite(s2,RW);
    digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);

  }else if(rawLR<-20){
    int L = 0;
    L = map(rawLR, 0, -100, 0, 200);

    digitalWrite(f1,1);digitalWrite(b1,0);analogWrite(s1,L);
    digitalWrite(f2,1);digitalWrite(b2,0);analogWrite(s2,L);
    digitalWrite(f3,1);digitalWrite(b3,0);analogWrite(s3,L);

  }else if(rawLR>=20){
    int R = 0;
    R = map(rawLR, 0, 100, 0, 200);

    digitalWrite(f1,0);digitalWrite(b1,1);analogWrite(s1,R);
    digitalWrite(f2,0);digitalWrite(b2,1);analogWrite(s2,R);
    digitalWrite(f3,0);digitalWrite(b3,1);analogWrite(s3,R);

  }else{
    digitalWrite(f1,0);digitalWrite(b1,0);analogWrite(s1,0);
    digitalWrite(f2,0);digitalWrite(b2,0);analogWrite(s2,0);
    digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);
  } 
}
