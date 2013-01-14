

#include <IRremote.h>

IRsend irsend;

void setup() {
    Serial.begin(9600);
}


char bufs[256];
int i = 0;

void _controlTV(char *tosend) {
    Serial.print("control tv ");

    int i = 2; // skip "T "
    unsigned long code = 0;

    while (tosend[i] != '\0') {
        char tmp = tosend[i];
        code = code << 4;
        
        if (tmp >= '0' && tmp <= '9') {
            tmp = tmp - '0';
        } else if (tmp >= 'A' && tmp <= 'F') {
            tmp = tmp - 'A' + 10;
        } else if (tmp >= 'a' && tmp <= 'f') {
            tmp = tmp - 'a' + 10;
        }
        
        //Serial.print((int)tmp);
        //Serial.print(" ");

        code = code | tmp;
        i++;
    }
    
    irsend.sendNEC(code, 32);
    
    Serial.print(code, HEX);
    Serial.println(" sent!");
    return;
}

void loop() {
    unsigned char temp;

    if (Serial.available() > 0) {
        temp = Serial.read();

        if (temp != 255) {

            if (temp == '\0') {  // use '\0' to indicate command end.
                bufs[i] = '\0';

                //Serial.print("received: ");

                if (bufs[0] == 'T') {
                    _controlTV(bufs);
                }

                //Serial.println(bufs);
                i=0;
            } else {
                bufs[i++] = temp;
            }
        }

        delay(100);
    }

}
