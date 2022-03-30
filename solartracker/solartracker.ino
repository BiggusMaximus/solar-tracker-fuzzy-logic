#include <VarSpeedServo.h>
#define ldr1 A0
#define ldr2 A1
#define ldr3 A2
#define ldr4 A3

VarSpeedServo servo1;
VarSpeedServo servo2;

uint8_t i, j;
uint16_t value1, value2, value3, value4;
uint8_t avgtop, avgdown, avgright, avgleft;

void setup()
{ 
    Serial.begin(9600);
    pinMode(ldr1, INPUT);
    pinMode(ldr2, INPUT);
    pinMode(ldr3, INPUT);
    pinMode(ldr4, INPUT);
    servo1.attach(7);
    servo2.attach(9);
}

void loop()
{
    value1 = analogRead(ldr1);
    value2 = analogRead(ldr2);
    value3 = analogRead(ldr3);
    value4 = analogRead(ldr4);
    delay(200);
    Serial.print("Value1: " + String(value1) + "  | Value2: " + String(value2) + "  | Value3: " + String(value3) + "  | Value4: " + String(value4)+ "\n");
    
    value1 = map(value1, 0, 1023, 0, 100);
    value2 = map(value2, 0, 1023, 0, 100);
    value3 = map(value3, 0, 1023, 0, 100);
    value4 = map(value4, 0, 1023, 0, 100);
    
    avgtop = 0,5*(value1 + value2);
    avgdown = 0,5*(value3 + value4);
    avgleft = 0,5*(value2 + value3);
    avgright = 0,5*(value1 + value4);

    if (avgtop < avgdown)
    {
        servo1.slowmove(i + 1, 125);
    }
    if (avgtop > avgdown)
    {
        servo1.slowmove(i - 1, 125);
    }
    if (avgleft < avgright)
    {
        servo2.slowmove(j + 1, 125);
    }
    if (avgleft < avgright)
    {
        servo2.slowmove(j - 1, 125);
    }
}
