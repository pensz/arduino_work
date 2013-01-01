#define ADD 0x00
int IR_S =  6;     //接arduino 7号引脚
void setup() 
{ 
    pinMode(IR_S, OUTPUT);
    Serial.begin(9600); // 9600 波特率
}

void loop() 
{   
    uint8_t dat, temp;

    IR_Send38KHZ(350,1);//发送9ms的起始码    
    IR_Send38KHZ(175,0);//发送4.5ms的结果码
    
    //IR_Send38KHZ(280,1);//发送9ms的起始码
    //IR_Send38KHZ(140,0);//发送4.5ms的结果码

    IR_Sendcode(0x00);//用户识别码
    IR_Sendcode(0xBF);//用户识别码反吗

    temp = 0x01;
    //temp = 0x0D;
    IR_Sendcode(temp);//操作码
    IR_Sendcode(~temp);//操作码反码

    IR_Send38KHZ(22,1);//发送结束码 21
    Serial.println("__ok___");

    delay(3000);
}



void IR_Send38KHZ(int x,int y) //产生38KHZ红外脉冲
{ 
    for(int i=0;i<x;i++)//15=386US
    { 
        if(y==1)
        {
            digitalWrite(IR_S,1);
            delayMicroseconds(9);
            digitalWrite(IR_S,0);
            delayMicroseconds(9);
        }
        else
        {
            digitalWrite(IR_S,0);
            delayMicroseconds(20);
        }            
    }
}

void IR_Sendcode(uint8_t x) //
{
    //Serial.println(x, HEX);
    for(int i=0;i<8;i++)
    {
        if((x&0x01)==0x01)
        {
            IR_Send38KHZ(23,1);
            IR_Send38KHZ(64,0);             
        }
        else
        {
            IR_Send38KHZ(23,1);
            IR_Send38KHZ(21,0);  
        }
        //Serial.print(x & 0x01 );
        //Serial.print(" ");
        x=x>>1;
    }  
    //Serial.println("__end__");
}
