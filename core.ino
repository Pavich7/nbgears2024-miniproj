#include <IBusBM.h>

// iBus 1.1.4 (FS-I6X)

IBusBM ibus; //iBus Object

//Channel 1-4 reading (Joy)
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
  for (byte i = 0; i < 5; i++) {
    int value = readChannel(i, -100, 100, 0);
    Serial.print("Ch");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(value);
    Serial.print(" | ");
  }
  //CH6 (Switch)
  Serial.print("Ch6: ");
  Serial.print(readSwitch(5, false));
  Serial.println();

  //Small delay
  delay(10);

  //End INPUT Zone...

}