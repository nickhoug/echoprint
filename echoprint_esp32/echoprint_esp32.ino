
// Wire Peripheral Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI Peripheral device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#define I2C_SDA 21
#define I2C_SCL 22

uint8_t falling_edge = 0; 
byte transmission = 0x00;
uint8_t read_flag = 0; 
int timer = 0; 

void IRAM_ATTR i2c() {
  falling_edge++; 
  timer = millis();  

  switch (falling_edge) {
    case 1: 
      break;
    case 2: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 3: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 4: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 5: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 6: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 7: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 8: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      break;
    case 9: 
      (transmission <<= 1) |= digitalRead(I2C_SDA);
      falling_edge = 0; 
      read_flag = 1; 
      break;
  }

}

byte flipByte(byte c)
     {
       c = ((c>>1)&0x55)|((c<<1)&0xAA);
       c = ((c>>2)&0x33)|((c<<2)&0xCC);
       c = (c>>4) | (c<<4) ;

       return c;
     }

void setup() {
  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);
  Serial.begin(115200);           // start serial for output
  attachInterrupt(digitalPinToInterrupt(I2C_SCL), i2c, FALLING);
}

void loop() {
  
  if (millis() > timer + 50) {
    falling_edge = 0; 
    read_flag = 0;  
  }
  
  if (read_flag == 1) {
    transmission = flipByte(transmission); 
    Serial.printf("Command = 0x%02x\r\n", transmission);
    Serial.printf("\n");
    transmission = 0x00; 
    read_flag = 0; 
  }
  
}
