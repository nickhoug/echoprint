#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"

Talkie voice;

void setup() {
}
void loop() {
    voice.say(spPAUSE2);
    voice.say(sp2_THE);
    voice.say(sp2_TIME);
    voice.say(sp3_IS);
    voice.say(sp3_FIVE);
    voice.say(sp3_OCLOCK);  
}