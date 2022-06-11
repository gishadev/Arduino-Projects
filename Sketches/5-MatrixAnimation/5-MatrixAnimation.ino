int ROWS[] = {10, 12, 13, 11, A2, A0, A3, A1};
int COLUMNS[] = {7, 2, 3, 9, 4, 8, 6, 5};

float dTime = 1/8;
float animationTimeInMs = 1000;

  byte smallHeart[] = 
  {
  0,
  0b01100110,
  0xFF,
  0xFF,
  0xFF,
  0b01111110,
  0b00111100,
  0b00011000
  };

  byte bigHeart[] = 
  {
  0,
  0,
  0b00100100,
  0b01111110,
  0b01111110,
  0b00111100,
  0b00011000,
  0
  };

void setup() 
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(ROWS[i], OUTPUT);
    pinMode(COLUMNS[i], OUTPUT);
  }
}

void loop() 
{
  unsigned long stop = millis();
  while(millis()-stop<animationTimeInMs)
   Draw(smallHeart);

  stop = millis();
  while(millis()-stop<animationTimeInMs)
    Draw(bigHeart);
}

void Draw(byte picture[])
{
  for(int i = 0; i < 8; i++)
  {
    DrawRow(i, picture[i]);
    delay(dTime);
  }
}

void DrawRow(int row, byte columnLEDs)
{  
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(ROWS[i], HIGH);
    digitalWrite(COLUMNS[i], LOW);
  }

  if (columnLEDs != 0)
    digitalWrite(ROWS[row], LOW);
  else
    return;
  
  for(int i = 0; i < 8; i++)
  {
    int value = (columnLEDs & (1 << i)) ? 1 : 0;
    Serial.print(value);
    digitalWrite(COLUMNS[i], value);
  }
}
