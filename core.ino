#include <IBusBM.h>
// iBus 1.1.4 (FS-I6X)

//Motor 1 FL
#define f2 13
#define b2 12
#define s2 11

//Motor 2 FR
#define f3 6
#define b3 7
#define s3 5

//Motor 3 BC
#define f1 9
#define b1 8
#define s1 10

IBusBM ibus; //iBus Object

//Channel 1-5 reading (Joy)
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() {
  Serial.begin(115200);
  ibus.begin(Serial); //iBus init on Serial1

  //Set motor driver pinmode
  for(int i=2;i<=13;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {
  if (Serial.available()){
    //CH1-4 (Joy)
    int rawROTATE = readChannel(0, -100, 100, 0);
    int rawFB = readChannel(2, -100, 100, 0);
    int rawLR = 0; //readChannel(3, -100, 100, 0);
  
    //Mapping
    if(rawROTATE<-20){
      int ROTATE_CCW = 0;
      ROTATE_CCW = map(rawROTATE, 0, -100, 0, 255);

      digitalWrite(f1,0);digitalWrite(b1,1);analogWrite(s1,ROTATE_CCW*0.5);
      digitalWrite(f2,0);digitalWrite(b2,1);analogWrite(s2,ROTATE_CCW*0.5);
      digitalWrite(f3,0);digitalWrite(b3,1);analogWrite(s3,ROTATE_CCW*0.5);

    }else if(rawROTATE>=20){
      int ROTATE_CW = 0;
      ROTATE_CW = map(rawROTATE, 0, 100, 0, 255);

      digitalWrite(f1,1);digitalWrite(b1,0);analogWrite(s1,ROTATE_CW*0.5);
      digitalWrite(f2,1);digitalWrite(b2,0);analogWrite(s2,ROTATE_CW*0.5);
      digitalWrite(f3,1);digitalWrite(b3,0);analogWrite(s3,ROTATE_CW*0.5);

    }else if(rawFB<-20){
      int FW = 0;
      FW = map(rawFB, 0, -100, 0, 255);
    
      digitalWrite(f1,1);digitalWrite(b1,0);analogWrite(s1,FW);
      digitalWrite(f2,0);digitalWrite(b2,1);analogWrite(s2,FW);
      digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);

    }else if(rawFB>=20){
      int RW = 0;
      RW = map(rawFB, 0, 100, 0, 255);

      digitalWrite(f1,0);digitalWrite(b1,1);analogWrite(s1,RW);
      digitalWrite(f2,1);digitalWrite(b2,0);analogWrite(s2,RW);
      digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);

    }else{
      digitalWrite(f1,0);digitalWrite(b1,0);analogWrite(s1,0);
      digitalWrite(f2,0);digitalWrite(b2,0);analogWrite(s2,0);
      digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);
    } 
  }else{
    digitalWrite(f1,0);digitalWrite(b1,0);analogWrite(s1,0);
    digitalWrite(f2,0);digitalWrite(b2,0);analogWrite(s2,0);
    digitalWrite(f3,0);digitalWrite(b3,0);analogWrite(s3,0);
  }
}
