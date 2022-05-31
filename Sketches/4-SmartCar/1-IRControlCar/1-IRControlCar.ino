#include <IRremote.h>

int IRPin = 12;
int motor_left[] = {9, 8};
int motor_right[] = {10, 11};

IRrecv IR(IRPin);
decode_results cmd;

void setup() 
{
  Serial.begin(9600);
  IR.enableIRIn();
  for (int i = 0; i < 2; i++)
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop()
{
    while ( IR.decode( &cmd )==0){}
   
    Serial.println(cmd.value, HEX);

    switch (cmd.value)
    {
      case 0xFE08F7:
      Stop();
      break;
      case 0xFE30CF:
      GoForward();
      break;
      case 0xFEB04F:
      GoBack();
      break;
      case 0xFE708F:
      GoRight();
      break;
      case 0xFEF00F:
      GoLeft();
      break;
    }

    delay(300);
    IR.resume();
}

void GoBack()
{
    digitalWrite(motor_left[0], 0);
    digitalWrite(motor_left[1], 1);
    digitalWrite(motor_right[1], 1);
    digitalWrite(motor_right[0], 0);
}

void GoForward()
{
    digitalWrite(motor_left[0], 1);
    digitalWrite(motor_left[1], 0);
    digitalWrite(motor_right[1], 0);
    digitalWrite(motor_right[0], 1);
}

void GoRight()
{
    digitalWrite(motor_left[0], 0);
    digitalWrite(motor_left[1], 1);
    digitalWrite(motor_right[1], 0);
    digitalWrite(motor_right[0], 1);
}

void GoLeft()
{
    digitalWrite(motor_left[0], 1);
    digitalWrite(motor_left[1], 0);
    digitalWrite(motor_right[1], 1);
    digitalWrite(motor_right[0], 0);
}

void Stop()
{
    digitalWrite(motor_left[0], 0);
    digitalWrite(motor_left[1], 0);
    digitalWrite(motor_right[1], 0);
    digitalWrite(motor_right[0], 0);
}
