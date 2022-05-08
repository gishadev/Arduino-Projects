#include <IRremote.h>
int IRPin = 10;
int rPin = 9;
int gPin = 6;
int bPin = 5;
IRrecv IR(IRPin);
decode_results cmd;

const long PlayCmd = 0xFFC23D;
const long OneCmd = 0xFF30CF;
const long TwoCmd = 0xFF18E7;
const long ThreeCmd = 0xFF7A85;
const long EQCmd = 0xFF906F;
const long PlusCmd = 0xFFA857;
const long MinusCmd = 0xFFE01F;

float dimStep = 0.25;
float rVal, gVal, bVal;
float dFactor = 1;

int dTime = 500;

void setup() 
{
  Serial.begin(9600);
  IR.enableIRIn();

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() 
{
  while (IR.decode(&cmd) == 0) {}
  Serial.println(cmd.value, HEX);
  switch(cmd.value)
  {
    case PlayCmd:
    TurnOff();
    break;

    case PlusCmd:
    ChangeDim(+dimStep);
    break;
    case MinusCmd:
    ChangeDim(-dimStep);
    break;
    
    case OneCmd:
    SetColor(1.,0.,0.);
    break;
    case TwoCmd:
    SetColor(0.,1.,0.);
    break;
    case ThreeCmd:
    SetColor(0.,0.,1.);
    break;

    case EQCmd:
    ActivateDiscoMode();
    break;
  }
  
  delay(dTime);
  IR.resume();
}

void TurnOff()
{
  dFactor = 0.1;
  SetColor();
}

void SetColor(float r, float g, float b)
{
  rVal = 255.0 * r;
  gVal = 255.0 * g;
  bVal = 255.0 * b;

  SetColor();
}

void SetColor()
{
  analogWrite(rPin, rVal * dFactor);
  analogWrite(gPin, gVal * dFactor);
  analogWrite(bPin, bVal * dFactor);
  delay(50);
}

void ChangeDim(float value)
{
  dFactor += value;
  SetColor();
  delay(50);
}

void ActivateDiscoMode()
{
  int randomIterations = 100;
  while (randomIterations > 0)
  {
    SetColor(RandomFloat(),RandomFloat(),RandomFloat());    
    randomIterations--;
    delay(75);
  }

  delay(50);
  TurnOff();
}

float RandomFloat()
{
  return (float) rand()/RAND_MAX; 
}
