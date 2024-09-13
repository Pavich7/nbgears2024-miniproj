#include <IBusBM.h>

// iBus 1.1.4 (FS-I6X)

IBusBM ibus; //iBus Object

//Channel 1-5 reading (Joy)
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//Channel 6 reading (Switch)
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup() {
  Serial.begin(115200);
  ibus.begin(Serial1); //iBus init on Serial1
}

void loop() {

  //CH1-4 (Joy)
  int rawROTATE = readChannel(0, -100, 100, 0);
  int rawFB = readChannel(2, -100, 100, 0);
  int rawLR = readChannel(3, -100, 100, 0);
  
  //Mapping
  if(rawROTATE<0){
    int ROTATE_CCW = 0;
    ROTATE_CCW = map(rawROTATE, 0, -100, 0, 255);
  }else if(rawROTATE>=0){
    int ROTATE_CW = 0;
    ROTATE_CW = map(rawROTATE, 0, 100, 0, 255);
  }

  if(rawFB<0){
    int FW = 0;
    FW = map(rawFB, 0, -100, 0, 255);
  }else if(rawFB>=0){
    int RW = 0;
    RW = map(rawFB, 0, 100, 0, 255);
  }

  if(rawLR<0){
    int L = 0;
    L = map(rawLR, 0, -100, 0, 255);
  }else if(rawLR>=0){
    int R = 0;
    R = map(rawLR, 0, 100, 0, 255);
  }

}
