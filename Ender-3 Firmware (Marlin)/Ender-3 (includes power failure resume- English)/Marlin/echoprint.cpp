#include "Marlin.h"
#include "echoprint.h"

Echoprint::Echoprint(int SCK, int SDA)
{
  pinMode(SCK, OUTPUT); 
  pinMode(SDA, OUTPUT);
  digitalWrite(SCK, HIGH); 
  digitalWrite(SDA, LOW);
  _SCK = SCK;
  _SDA = SDA;
}

void Echoprint::Tx(uint8_t dat){
    digitalWrite(_SCK, LOW);
    for(int i = 0; i < 8; i++){ //gets sent LSB first
        ((dat >> i)  & 0x01) ? digitalWrite(_SDA, HIGH) : digitalWrite(_SDA, LOW); //Mask for the eigth bit 
        digitalWrite(_SCK, HIGH);
        digitalWrite(_SCK, LOW); 
    }
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SDA, LOW);
}
