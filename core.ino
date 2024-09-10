#include <IBusBM.h>

// (INCOMPLETED) Define motor driver pin (ex. m1f, m1 = Motor 1, f= Forward, or b = Backward, sp = Speed).
//m1-m3 are wheels and m4 is lift.

/* UNCOMMENT when FINISED.
#define m1f 
#define m1b 
#define m1sp 5

#define m2f 
#define m2b 
#define m2sp 4

#define m3f
#define m3b
#define m3sp 33

#define m4f
#define m4b
#define m4sp 25
*/

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

  //CH1-5 (Joy)
  int CH1value = readChannel(0, -100, 100, 0);
  int CH2value = readChannel(1, -100, 100, 0);
  int CH3value = readChannel(2, -100, 100, 0);
  int CH4value = readChannel(3, -100, 100, 0);
  int CH5value = readChannel(4, -100, 100, 0);
  Serial.print(CH1value);

  //CH6 (Switch)
  int CH6value = readSwitch(5, false);
  Serial.print(CH6value);

  Serial.println();
  delay(10);

  //End INPUT Zone...

}
