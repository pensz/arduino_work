void setup() {
    Serial.begin(9600);
}

char bufs[256];
int i = 0;

void loop() {
    unsigned char temp;

    //if (Serial.available() > 0) {
    temp = Serial.read();

    if (temp != 255) {

        if (temp == '_') {
            bufs[i] = '\0';

            Serial.print("reply: ");
            Serial.println(i);

            Serial.println(bufs);        
            i=0;
        } else {
            bufs[i++] = temp;
        }
    }

    delay(500);
    //}

}
