

int voicePin = 7;


void setup() {
  Serial.begin(9600);

  pinMode(voicePin, INPUT);
}


void loop() {

  //delay(10);
  int voice = digitalRead(voicePin);
  if (voice == 0) {
    delay(1);
    voice = digitalRead(voicePin);
    if (voice == 0) {
      Serial.print("voice: ");
      Serial.println(!voice);
    }
  }
  //delay(10);
}
