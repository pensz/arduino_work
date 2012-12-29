int a=2;  
int b=3;  
int c=4;  
int d=5;

int e=8;  
int f=9;  
int g=10;  
int dp=11;  

int output[] = {a, b, c, d, e, f, g, dp};
int digs[20][20] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3 
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 0, 0, 0}, // 7 
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8 
    {1, 1, 1, 1, 0, 1, 1, 0}, // 9
    {0, 0, 0, 0, 0, 0, 0, 1}  // . 
};

void digital(int dig) {
    int i=0;

    for (i=0; i<8; i++) {
        digitalWrite(output[i], digs[dig][i]);
    }

}
  
void setup() { 
    Serial.begin(9600);
    int i;
    for (i=0; i<8; i++) {
        pinMode(output[i], OUTPUT); // set output
    }
}


void loop() {
    int i = 0;
    for (i=0; i<11; i++) {
        digital(i);
        delay(1000);
    }
}  
