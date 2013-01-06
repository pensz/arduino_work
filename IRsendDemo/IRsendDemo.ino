/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
}


unsigned int data[] =
{
9000, 4500,  // begin of IR 9ms high & 4.5ms low
560,560, 560,560, 560,560, 560,560, 560,560, 560,560, 560,560, 560,560,   // 00
560,1600,560,1600,560,1600,560,1600,560,1600,560,1600,560,560, 560,1600,  // FD
560,1600,560,560, 560,560, 560,560, 560,560, 560,560, 560,560, 560,560,   // 80
560,560, 560,1600,560,1600,560,1600,560,1600,560,1600,560,1600,560,1600,  // ~80
560
};

void loop() {
    irsend.sendNEC(0xFD10EF, 32);
    //irsend.sendRaw(data, 67, 38);
    Serial.println("sendok");
    delay(3000);
}
