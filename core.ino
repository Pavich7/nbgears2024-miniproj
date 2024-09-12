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

  //INPUT Zone...

  //CH1-4 (Joy)
  int ROTATE = readChannel(0, -100, 100, 0);
  int LIFT = readChannel(1, -100, 100, 0);
  int FB = readChannel(2, -100, 100, 0);
  int LR = readChannel(3, -100, 100, 0);
  //Small delay
  delay(10);

  //End INPUT Zone...

}
