#include "Wire.h"
#include "Arduino.h"
#include "Talkie.h" 
#include "Vocab_US_Large.h"
#include "Vocab_US_TI99.h"

#define IDLE 0
#define DOWN 1
#define UP 2
#define PRESSED 3

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
uint8_t next_state; 

const int buttonTop = 27;
const int buttonSel = 14;
const int buttonBot = 13;

int top_state; 
int buttonStateTop;
int buttonStateTop_old;
int buttonTopFlag; 

int sel_state; 
int buttonStateSel;
int buttonStateSel_old;
int buttonSelFlag; 

int bot_state; 
int buttonStateBot;
int buttonStateBot_old;
int buttonBotFlag; 

byte encoderLine = 0; 

void state_machine_top(int button_input) {
  buttonStateTop_old = buttonStateTop; 
  buttonStateTop = button_input;
  switch(top_state){
    case IDLE: 
      if (buttonStateTop_old == 1 && buttonStateTop == 0) {
        top_state = DOWN; 
      }
      break; 
    case DOWN: 
      if (buttonStateTop_old == 0 && buttonStateTop == 1) {
        top_state = UP; 
      }
      break; 
    case UP:
      buttonTopFlag = 1; 
      top_state = PRESSED;
      break; 
    case PRESSED:
      buttonTopFlag = 0; 
      top_state = IDLE; 
      break; 
  }
}

void state_machine_sel(int button_input) {
  buttonStateSel_old = buttonStateSel; 
  buttonStateSel = button_input;
  switch(sel_state){
    case IDLE: 
      if (buttonStateSel_old == 1 && buttonStateSel == 0) {
        sel_state = DOWN; 
      }
      break; 
    case DOWN: 
      if (buttonStateSel_old == 0 && buttonStateSel == 1) {
        sel_state = UP; 
      }
      break; 
    case UP:
      buttonSelFlag = 1; 
      sel_state = PRESSED;
      break; 
    case PRESSED:
      buttonSelFlag = 0; 
      sel_state = IDLE; 
      break; 
  }
}

void state_machine_bot(int button_input) {
  buttonStateBot_old = buttonStateBot; 
  buttonStateBot = button_input;
  switch(bot_state){
    case IDLE: 
      if (buttonStateBot_old == 1 && buttonStateBot == 0) {
        bot_state = DOWN; 
      }
      break; 
    case DOWN: 
      if (buttonStateBot_old == 0 && buttonStateBot == 1) {
        bot_state = UP; 
      }
      break; 
    case UP:
      buttonBotFlag = 1; 
      bot_state = PRESSED;
      break; 
    case PRESSED:
      buttonBotFlag = 0; 
      bot_state = IDLE; 
      break; 
  }
}

void state_machine(byte transmission, uint8_t screen_flag) {
  Serial.print(screen_flag);
  Serial.print("\n");
  switch(screen_flag) {
    case MAIN_MENU: 

      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
        next_state = MAIN_MENU;
      }
      else if (transmission == 0x01) { //tune
        voice.say(sp2_ADJUST);
        next_state = TUNE;
      }
      else if (transmission == 0x02) { // prepare
        voice.say(spt_MAKE);
        voice.say(sp4_READY);
        next_state = PREPARE; 
      }
      else if (transmission == 0x03) { // control
        voice.say(sp4_CONTROL); 
        next_state = CONTROL; 
      }
      else if (transmission == 0x04) { // No TF card
        voice.say(sp4_NO);
        voice.say(sp2_S);
        voice.say(sp2_D);
        next_state = NO_TF_CARD; 
      }
      else if (transmission == 0x05) { // init TF card
        voice.say(sp4_START);
        voice.say(sp2_S);
        voice.say(sp2_D);
        next_state = MAIN_MENU;
      }
      else if (transmission == 0x06) { // About printer
        voice.say(sp2_ABOUT); 
        voice.say(spt_PRINTER); 
        next_state = MAIN_MENU;
      }

    break; 

    case TUNE: 

      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
        next_state = MAIN_MENU;
      }
      else if (transmission == 0x01) { //speed
        voice.say(sp4_SPEED);
        next_state = TUNE;
      }
      else if (transmission == 0x02) { // Nozzle
        next_state = TUNE;
      }
      else if (transmission == 0x03) { // Bed
        next_state = TUNE;
      }
      else if (transmission == 0x04) { // Fan Speed
        next_state = TUNE;
      }
      else if (transmission == 0x05) { // Flow
        voice.say(sp2_FLOW);
        next_state = TUNE;
      }
      else if (transmission == 0x06) { // Baby step Z
        voice.say(spt_STEP);
        voice.say(sp2_Z);
        next_state = BABY_STEP_Z;
      }
      else if (transmission == 0x07) { // Change Filament
        voice.say(sp2_CHANGE); 
        next_state = TUNE;
      }

    break; 

    case BABY_STEP_Z: 
      if (transmission == 0x00) { // Baby step Z
        voice.say(spt_STEP);
        voice.say(sp2_Z);
        next_state = TUNE;
      }
    break; 

    case PREPARE:

      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
        next_state = MAIN_MENU;
      }
      else if (transmission == 0x01) { //move axis
        voice.say(spt_MOVE); 
        voice.say(spt_PRINTER);
        next_state = MOVE_AXIS;
      }
      else if (transmission == 0x02) { // auto home
        voice.say(sp2_AUTOMATIC); 
        voice.say(spt_HOME);
        next_state = PREPARE;
      }
      else if (transmission == 0x03) { // Set home offsets
        voice.say(sp2_SET);
        voice.say(spt_HOME);
        voice.say(spt_OFF);
        voice.say(spt_SET);
        next_state = PREPARE;
      }
      else if (transmission == 0x04) { // Disable stepers
        voice.say(spt_END);
        voice.say(sp2_MOTOR);
        next_state = PREPARE;
      }
      else if (transmission == 0x05) { // Cooldown
        next_state = PREPARE;
      }
      else if (transmission == 0x06) { // Preheat PLA
        voice.say(sp3_HEAT);
        voice.say(sp2_P);
        voice.say(sp2_L);
        voice.say(sp2_A);
        next_state = PREHEAT_PLA;
      }
      else if (transmission == 0x07) { // Preheat ABS
        voice.say(sp3_HEAT);
        voice.say(sp2_A);
        voice.say(sp2_B);
        voice.say(sp2_S);
        next_state = PREHEAT_ABS;
      }

    break;

    case MOVE_AXIS:
      if (transmission == 0x00) {      //Prepare
        voice.say(spt_MAKE);
        voice.say(sp4_READY); 
        next_state = PREPARE;
      }
      else if (transmission == 0x01) { //Move X
        voice.say(spt_MOVE); 
        voice.say(sp2_X);
        next_state = MOVE_AXIS;
      }
      else if (transmission == 0x02) { // Move Y
        voice.say(spt_MOVE); 
        voice.say(sp2_Y);
        next_state = MOVE_AXIS;
      }
      else if (transmission == 0x03) { // Move Z
        voice.say(spt_MOVE); 
        voice.say(sp2_Z);
        next_state = MOVE_AXIS;
      }
      else if (transmission == 0x04) { // Move E (extruder)
        voice.say(spt_MOVE); 
        voice.say(sp2_E);
        next_state = MOVE_AXIS;
      }

    break;

    case CONTROL: 
      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
        next_state = MAIN_MENU;
      }
      else if (transmission == 0x01) { //Temperature
        voice.say(sp3_TEMPERATURE);
        next_state = TEMPERATURE;
      }
      else if (transmission == 0x02) { // Motion
        voice.say(spt_MOVE);
        next_state = MOTION; 
      }
      else if (transmission == 0x03) { // Filament
        next_state = CONTROL;
      }
      else if (transmission == 0x04) { // Store Settings
        voice.say(spt_SAVE);
        next_state = CONTROL;
      }
      else if (transmission == 0x05) { // Load Settings
        voice.say(spt_LOAD); 
        next_state = CONTROL;
      }
      else if (transmission == 0x06) { // Initialize EEPROM
        voice.say(sp2_E);
        voice.say(sp2_E);
        voice.say(sp2_P);
        voice.say(sp2_R);
        voice.say(sp2_O);
        voice.say(sp2_M);
        next_state = CONTROL;
      }
      
    break;

    case TEMPERATURE: 
      if (transmission == 0x00) {      //control
        voice.say(sp4_CONTROL); 
        next_state = CONTROL; 
      }
      else if (transmission == 0x01) { //nozzle
        next_state = TEMPERATURE; 
      }
      else if (transmission == 0x02) { // Bed
        next_state = TEMPERATURE;
      }
      else if (transmission == 0x03) { // Fan Speed
        next_state = TEMPERATURE;
      }
      else if (transmission == 0x04) { // Preheat PLA config
        voice.say(sp3_HEAT);
        voice.say(sp2_P);
        voice.say(sp2_L);
        voice.say(sp2_A);
        next_state = PREHEAT_PLA_CONFIG;
      }
      else if (transmission == 0x05) { // Preheat ABS config
        voice.say(sp3_HEAT);
        voice.say(sp2_A);
        voice.say(sp2_B);
        voice.say(sp2_S);
        next_state = PREHEAT_ABS_CONFIG;
      }
    break;  

    case PREHEAT_PLA_CONFIG: 
      if (transmission == 0x00) {      //temperature
        voice.say(sp3_TEMPERATURE);
        next_state = TEMPERATURE; 
      }
      else if (transmission == 0x01) { // Fan Speed
        next_state = PREHEAT_PLA_CONFIG; 
      }
      else if (transmission == 0x02) { // Nozzle
        next_state = PREHEAT_PLA_CONFIG;
      }
      else if (transmission == 0x03) { // Bed store settings
        voice.say(spt_SAVE);
        next_state = PREHEAT_PLA_CONFIG;
      }
    break;

    case PREHEAT_ABS_CONFIG: 
      if (transmission == 0x00) {      //temperature
        voice.say(sp3_TEMPERATURE);
        next_state = TEMPERATURE; 
      }
      else if (transmission == 0x01) { // Fan Speed 
        next_state = PREHEAT_ABS_CONFIG;
      }
      else if (transmission == 0x02) { // Nozzle
        next_state = PREHEAT_ABS_CONFIG;
      }
      else if (transmission == 0x03) { // Bed store settings
        voice.say(spt_SAVE);
        next_state = PREHEAT_ABS_CONFIG;
      }
    break;

    case MOTION: 
      if (transmission == 0x00) {      //control
        voice.say(sp4_CONTROL); 
        next_state = CONTROL; 
      }
      else if (transmission == 0x01) { //velocity
        voice.say(sp4_SPEED);
        next_state = VELOCITY;
      }
      else if (transmission == 0x02) { //acceleration
        voice.say(sp5_ACCELERATED);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x03) { // jerk
        voice.say(sp2_PULL);
        next_state = JERK;
      }
      else if (transmission == 0x04) { // Steps/mmm
        voice.say(sp3_PER);
        voice.say(sp2_M);
        voice.say(sp2_M);
        next_state = STEPS;
      }
    break;

    case VELOCITY:
      if (transmission == 0x00) {      //Motion
        voice.say(spt_MOVE);
        next_state = MOTION;
      }
      else if (transmission == 0x01) { //Vmax X
        voice.say(sp2_V);
        voice.say(spt_TOP); 
        voice.say(sp2_X);
        next_state = VELOCITY;
      }
      else if (transmission == 0x02) { //Vmax Y
        voice.say(sp2_V);
        voice.say(spt_TOP); 
        voice.say(sp2_Y);
        next_state = VELOCITY;
      }
      else if (transmission == 0x03) { //Vmax Z
        voice.say(sp2_V);
        voice.say(spt_TOP); 
        voice.say(sp2_Z);
        next_state = VELOCITY;
      }
      else if (transmission == 0x04) { //Vmax E
        voice.say(sp2_V);
        voice.say(spt_TOP); 
        voice.say(sp2_E);
        next_state = VELOCITY;
      }
      else if (transmission == 0x05) { //Vmin
        voice.say(sp2_V);
        voice.say(spt_BOTTOM);
        next_state = VELOCITY;
      }
      else if (transmission == 0x06) { //VTrav min
        voice.say(sp2_V);
        voice.say(sp5_FLIGHT);
        voice.say(spt_BOTTOM);
        next_state = VELOCITY;
      }
    break;

    case ACCELERATION: 
      if (transmission == 0x00) {      //Motion
        voice.say(spt_MOVE);
        next_state = MOTION;
      }
      else if (transmission == 0x01) { //Accel
        voice.say(sp5_ACCELERATED);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x02) { //A-retract
        voice.say(sp2_A);
        voice.say(spt_BACK);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x03) { //A-travel
        voice.say(sp2_A);
        voice.say(sp5_FLIGHT);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x04) { //Amax X
        voice.say(sp2_A);
        voice.say(spt_TOP); 
        voice.say(sp2_X);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x05) { //Amax Y
        voice.say(sp2_A);
        voice.say(spt_TOP); 
        voice.say(sp2_Y);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x06) { //Amax Z
        voice.say(sp2_A);
        voice.say(spt_TOP); 
        voice.say(sp2_Z);
        next_state = ACCELERATION;
      }
      else if (transmission == 0x07) { //Amax E
        voice.say(sp2_A);
        voice.say(spt_TOP); 
        voice.say(sp2_E);
        next_state = ACCELERATION;
      }
    break;   

    case JERK: 
      if (transmission == 0x00) {      //Motion
        voice.say(spt_MOVE);
        next_state = MOTION;
      }
      else if (transmission == 0x01) { //Vx-jerk
        voice.say(sp2_V);
        voice.say(sp2_X);
        voice.say(sp2_PULL);
        next_state = JERK;
      }
      else if (transmission == 0x02) { //Vy-jerk
        voice.say(sp2_V);
        voice.say(sp2_Y);
        voice.say(sp2_PULL);
        next_state = JERK;
      }
      else if (transmission == 0x03) { //Vz-jerk
        voice.say(sp2_V);
        voice.say(sp2_Z);
        voice.say(sp2_PULL);
        next_state = JERK;
      }
      else if (transmission == 0x04) { //Ve-jerk
        voice.say(sp2_V);
        voice.say(sp2_E);
        voice.say(sp2_PULL);
        next_state = JERK;
      }
    break; 

    case STEPS: 
      if (transmission == 0x00) {      //Motion
        voice.say(spt_MOVE);
        next_state = MOTION;
      }
      else if (transmission == 0x01) { //Xsteps/mm
        voice.say(sp2_X);
        voice.say(sp3_PER);
        voice.say(sp2_M);
        voice.say(sp2_M);
        next_state = STEPS;
      }
      else if (transmission == 0x02) { //Ysteps/mm
        voice.say(sp2_Y);
        voice.say(sp3_PER);
        voice.say(sp2_M);
        voice.say(sp2_M);
        next_state = STEPS;
      }
      else if (transmission == 0x03) { //Zsteps/mm
        voice.say(sp2_Z);
        voice.say(sp3_PER);
        voice.say(sp2_M);
        voice.say(sp2_M);
        next_state = STEPS;
      }
      else if (transmission == 0x04) { //Esteps/mm
        voice.say(sp2_E);
        voice.say(sp3_PER);
        voice.say(sp2_M);
        voice.say(sp2_M);
        next_state = STEPS;
      }
    break; 

    case NO_TF_CARD: 
      if (transmission == 0x00) {      //info screen
        voice.say(sp4_INFORMATION); 
        next_state = MAIN_MENU;
      }
    break; 

  }
}

void setup() {
  Wire.begin();
  pinMode(buttonTop, INPUT_PULLUP);
  pinMode(buttonSel, INPUT_PULLUP);
  pinMode(buttonBot, INPUT_PULLUP);
  Serial.begin(9600);           // start serial for output
  state_machine(encoderLine, screen_flag);
  Wire.beginTransmission(0x04);
  Wire.write(encoderLine);
  Wire.endTransmission();
  Serial.print(encoderLine);
  Serial.print("\n");
}

void loop() {
  state_machine_top(digitalRead(buttonTop));
  state_machine_sel(digitalRead(buttonSel));
  state_machine_bot(digitalRead(buttonBot));
  delay(20);
  if (buttonTopFlag == 1) {
    encoderLine++; 
    state_machine(encoderLine, screen_flag);
    Wire.beginTransmission(0x04);
    Wire.write(encoderLine);
    Wire.endTransmission();
    Serial.print(encoderLine);
    Serial.print("\n");
  }
  if (buttonSelFlag == 1) {
    encoderLine = 0;
    screen_flag = next_state;
    state_machine(encoderLine, screen_flag);
    Wire.beginTransmission(0x04);
    Wire.write(0xFF);
    Wire.endTransmission();
    Serial.print(0xFF);
    Serial.print("\n");
  }
  if (buttonBotFlag == 1) {
    if (encoderLine != 0) {
      encoderLine--;
    }
      state_machine(encoderLine, screen_flag);
      Wire.beginTransmission(0x04);
      Wire.write(encoderLine);
      Wire.endTransmission();
      Serial.print(encoderLine);
      Serial.print("\n");
  }
}
