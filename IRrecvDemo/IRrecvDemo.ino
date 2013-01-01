/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 4;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(3, 1);
}

void loop() {

    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        if (results.value == 0xFF02FD) {
            digitalWrite(3, 1);
        }

        switch(results.decode_type) {
            case NEC:
                Serial.println("NEC");
                break;

            case SONY:
                Serial.println("SONY");
                break;

            case RC5:
                Serial.println("RC5");
                break;

            case RC6:
                Serial.println("RC6");
                break;

            default:
                Serial.println("Unknown encoding");

        }

        if (results.value == 0xFF42BD) {
            digitalWrite(3, 0);
        }

        irrecv.resume(); // Receive the next value
    }
}
