#ifndef echoprint_h
#define echoprint_h

#include "Marlin.h"

class Echoprint
{
  public:
    Echoprint(int SCK, int SDA);
    void Tx(uint8_t dat);
  private:
    int _SCK;
    int _SDA; 
};

#endif