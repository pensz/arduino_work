
int inputPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  
  Serial.print("read ");
  int x = digitalRead(inputPin);
  Serial.println(x);
  delay(2000);
  
}
