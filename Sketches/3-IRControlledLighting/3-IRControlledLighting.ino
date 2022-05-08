#include <IRremote.h>
int IRPin = 10;
int rPin = 9;
int gPin = 6;
int bPin = 5;
IRrecv IR(IRPin);
decode_results cmd;

const long PlayCmd = 0xFF00FF;
const long RedCmd = 0xFFA05F;
const long GreenCmd = 0xFFE01F;
const long BlueCmd = 0xFF609F;
const long DiscoCmd = 0xFF10EF;
const long PlusCmd = 0xFF20DF;
const long MinusCmd = 0xFF40BF;

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
    
    case RedCmd:
    SetColor(1.,0.,0.);
    break;
    case GreenCmd:
    SetColor(0.,1.,0.);
    break;
    case BlueCmd:
    SetColor(0.,0.,1.);
    break;

    case DiscoCmd:
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
