// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

//
// Welcome to the Talkie library examples.
//
// Talkie is a speech synthesiser that works from a fixed vocabulary.
//
// There are hundreds of words in the 'Vocabulary' examples.
//

/*
 * Voice PWM output pins for different ATmegas:
 *  ATmega328 (Uno and Nano): non inverted at pin 3, inverted at pin 11.
 *  ATmega2560: non inverted at pin 6, inverted at pin 7.
 *  ATmega32U4 (Leonardo): non inverted at pin 10, inverted at pin 9.
 *  ATmega32U4 (CircuitPlaygound): only non inverted at pin 5.
 *
 *  As default both inverted and not inverted outputs are enabled to increase volume if speaker is attached between them.
 *  Use Talkie Voice(true, false); if you only need not inverted pin or if you want to use SPI on ATmega328 which needs pin 11.
 *
 *  The outputs can drive headphones directly, or add a simple audio amplifier to drive a loudspeaker.
 */
#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"

Talkie voice;

void setup() {
  pinMode(15, OUTPUT); // test LED
  digitalWrite(15, LOW);
  pinMode(22, OUTPUT);  // SHUTDOWN PIN
  digitalWrite(22, HIGH);
}

void loop() {
  voice.say(sp2_DANGER);
  digitalWrite(15, HIGH);
  voice.say(sp2_DANGER);
  digitalWrite(15, LOW);
  voice.say(sp2_RED);
  digitalWrite(15, HIGH);
  voice.say(sp2_ALERT);
  digitalWrite(15, LOW);
  voice.say(sp2_MOTOR);
  digitalWrite(15, HIGH);
  voice.say(sp2_IS);
  digitalWrite(15, LOW);
  voice.say(sp2_ON);
  digitalWrite(15, HIGH);
  voice.say(sp2_FIRE);
  digitalWrite(15, LOW);
}
