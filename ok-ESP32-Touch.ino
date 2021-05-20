#include "DFRobot_Gesture_Touch.h"
#include "HardwareSerial.h"

#ifdef __AVR__
#elif defined ESP_PLATFORM
#include "HardwareSerial.h"
HardwareSerial mySerial(1);
HardwareSerial touchSerial(2);
#endif

DFRobot_Gesture_Touch   DFGT(&touchSerial); 

unsigned char order[4] = {0xAA,0x06,0x00,0xB0};
void setup() {
mySerial.begin(9600, SERIAL_8N1, 16, 17);  // speed, type, RX, TX
touchSerial.begin(9600, SERIAL_8N1, 1, 3);  // speed, type, RX, TX
Serial1.begin(9600);
volume(0x1E);//音量设置0x00-0x1E
delay(1000);
while(mySerial.available()) // flush serial buffer
mySerial.read();
Serial.println("gesture&touch sensor test");
DFGT.setGestureDistance(20); // suggest default value
DFGT.enableFunction(DFGT_FUN_ALL); // enable all functions
DFGT.disableFunction(DFGT_FUN_RIGHT | DFGT_FUN_LEFT); // disable function test
}

void loop() {
  int8_t rslt = DFGT.getAnEvent(); // get an event that data saved in serial buffer
if(rslt != DF_ERR) {
// DFGT.setSleep(DFGT_SLEEP_DISABLE); // disable auto sleep
switch(rslt) {

case DFGT_EVT_TOUCH1: {
Serial.println("get event touch1");
play(0x01);//指定播放:0x01-文件0001
delay(1000);
} break;
case DFGT_EVT_TOUCH2: {
Serial.println("get event touch2");
play(0x02);//指定播放:0x02-文件0002
delay(1000);
} break;
case DFGT_EVT_TOUCH3: {
Serial.println("get event touch3");
play(0x03);//指定播放:0x03-文件0004
delay(1000);
} break;
case DFGT_EVT_TOUCH4: {
Serial.println("get event touch4");
play(0x04);//指定播放:0x04-文件0004
delay(1000);
} break;
case DFGT_EVT_TOUCH5: {
Serial.println("get event touch5");
play(0x05);//指定播放:0x05-文件0005
delay(1000);
} break;
}
}
}


void play(unsigned char Track)
{
unsigned char play[6] = {0xAA,0x07,0x02,0x00,Track,Track+0xB3};//0xB3=0xAA+0x07+0x02+0x00,即最后一位为校验和
Serial1.write(play,6);
}
void volume( unsigned char vol)
{
unsigned char volume[5] = {0xAA,0x13,0x01,vol,vol+0xBE};//0xBE=0xAA+0x13+0x01,即最后一位为校验和
Serial1.write(volume,5);
}