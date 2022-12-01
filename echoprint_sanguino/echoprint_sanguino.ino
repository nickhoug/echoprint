
#define spoof_MOSI MOSI
#define spoof_SCK SCK

#define SDA_HIGH digitalWrite(spoof_MOSI, HIGH)
#define SDA_LOW digitalWrite(spoof_MOSI, LOW)
#define SCK_HIGH digitalWrite(spoof_SCK, HIGH)
#define SCK_LOW digitalWrite(spoof_SCK, LOW)

/*
 * Bit-Bang I2C made for EchoPrint
 * 
 * SCK: 
 * 
 * _____     ______     ______     ______     ______     ______     ______     ______     ______     _____________     
 *     |     |    |     |    |     |    |     |    |     |    |     |    |     |    |     |    |     |     
 *     |     |    |     |    |     |    |     |    |     |    |     |    |     |    |     |    |     |     
 *     |_____|    |_____|    |_____|    |_____|    |_____|    |_____|    |_____|    |_____|    |_____|          
 * 
 * 
 * SDA:
 * 
 *           ____________          ____________          ____________          ____________           ____________
 *           |          |          |          |          |          |          |          |           |
 *           |     1    |    0     |     1    |    0     |     1    |    0     |     1    |    0      |
 * __________|          |__________|          |__________|          |__________|          |___________|___________
 * 
 */

void setup() {
  Serial.begin(115200);
  pinMode(spoof_MOSI, OUTPUT); 
  pinMode(spoof_SCK, OUTPUT);
  SCK_HIGH; 
  SDA_LOW; 
}

void loop() {
  Tx(0x0F); 
  delay(1000); 
  Tx(0x08); 
  delay(1000);
  Tx(0x00); 
  delay(1000);
  Tx(0x87); 
  delay(1000);
  Tx(0xAB); 
  delay(1000);
  Tx(0xBE); 
  delay(1000);
  Tx(0xEF); 
  delay(1000);
  Tx(0x2C); 
  delay(1000);
  Tx(0x5D); 
  delay(1000);
}

/* Transmit 8 bit data to slave */
void Tx(uint8_t dat){
    SCK_LOW;
    for(int i = 0; i < 8; i++){ //gets sent LSB first
        ((dat >> i)  & 0x01) ? SDA_HIGH : SDA_LOW; //Mask for the eigth bit 
        SCK_HIGH;
        SCK_LOW; 
    }
    SCK_HIGH;
    SDA_LOW;
}
