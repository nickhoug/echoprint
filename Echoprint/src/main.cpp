#include "Wire.h"
#include "Arduino.h"
#include "Talkie.h" 
#include "Vocab_US_Large.h"
#include "Vocab_US_TI99.h"

#define I2C_DEV_ADDR 0x04

#define MAIN_MENU 0
#define TUNE 2
#define PREPARE 3
#define CONTROL 4
#define NO_TF_CARD 5
#define BABY_STEP_Z 6
#define PREHEAT_PLA 7
#define PREHEAT_ABS 8
#define MOVE_AXIS 9
#define TEMPERATURE 10
#define MOTION 11
#define PREHEAT_PLA_CONFIG 12
#define PREHEAT_ABS_CONFIG 13
#define VELOCITY 14
#define ACCELERATION 15
#define JERK 16
#define STEPS 17

Talkie voice;
uint32_t i = 0;
byte transmission; 
uint8_t screen_flag = 0; 
uint8_t sel_flag = 0; 


void state_machine(byte transmission, uint8_t screen_flag) {
  
  switch(screen_flag) {
    case MAIN_MENU: 

      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
      }
      else if (transmission == 0x01) { //tune
        voice.say(sp2_ADJUST);
      }
      else if (transmission == 0x02) { // prepare
        voice.say(spt_MAKE);
        voice.say(sp4_READY);
      }
      else if (transmission == 0x03) { // control
         voice.say(sp4_CONTROL); 
      }
      else if (transmission == 0x04) { // No TF card
        voice.say(sp4_NO);
        voice.say(sp2_S);
        voice.say(sp2_D);
        voice.say(spt_MEMORY);
      }
      else if (transmission == 0x05) { // init TF card
        voice.say(sp4_START);
        voice.say(sp2_S);
        voice.say(sp2_D);
        voice.say(spt_MEMORY);
      }
      else if (transmission == 0x06) { // About printer
        voice.say(sp2_ABOUT); 
        voice.say(spt_PRINTER); 
      }

    break; 

    case TUNE: 

      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
      }
      else if (transmission == 0x01) { //speed
        voice.say(sp4_SPEED);
      }
      else if (transmission == 0x02) { // Nozzle
        
      }
      else if (transmission == 0x03) { // Bed
         
      }
      else if (transmission == 0x04) { // Fan Speed
        
      }
      else if (transmission == 0x05) { // Flow
        voice.say(sp2_FLOW);
      }
      else if (transmission == 0x06) { // Baby step Z
        voice.say(spt_STEP);
        voice.say(sp2_Z);
      }
      else if (transmission == 0x07) { // Change Filament
        voice.say(sp2_CHANGE); 
      }

    break; 
  }

}

void onReceive(int len){
  Serial.printf("onReceive[%d]: ", len);
  while(Wire.available()){
    transmission = Wire.read(); 
    Serial.print(transmission);
    state_machine(transmission, screen_flag);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Wire.onReceive(onReceive);
  Wire.begin((uint8_t)I2C_DEV_ADDR);
 //pinMode(15, OUTPUT); 
  //digitalWrite(27, HIGH);

#if CONFIG_IDF_TARGET_ESP32
  char message[64];
  snprintf(message, 64, "%u Packets.", i++);
  Wire.slaveWrite((uint8_t *)message, strlen(message));
#endif
}

void loop() {

}
