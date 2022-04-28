int lightPin = 9;

int dimLevel;
int blinksCount = 0;
int blinkDelay;

String introMsg = "Greetings! I'm your personal blinker.";

void setup() 
{
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
   Serial.println(introMsg);
   Serial.println("Write dim level (0 - 100)%.");
   while (Serial.available()) Serial.read();
   while (Serial.available() == 0){}
   dimLevel = Serial.parseInt();

   Serial.println("Write blinks count.");
   while (Serial.available()) Serial.read();
   while (Serial.available() == 0){}
   blinksCount = Serial.parseInt();

   Serial.println("Write blink delay in ms.");
   while (Serial.available()) Serial.read();
   while (Serial.available() == 0){}
   blinkDelay = Serial.parseInt();

   StartBlinking();
}

void StartBlinking()
{
  int dim = dimLevel / 100. * 255.;
  for (int i = 0; i < blinksCount; i++)
  {
    analogWrite(lightPin, dim);  
    delay(blinkDelay);
    analogWrite(lightPin, 0);  
    delay(blinkDelay);
  }
  
  delay(1000);
}
