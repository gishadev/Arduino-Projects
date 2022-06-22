#include <GyverMAX7219.h>
#include <GyverGFX.h>

#define AM_W 32
#define AM_H 8

// Matrix (4x1), CS on D5
MAX7219 < 4, 1, 5 > matrix;

void setup() 
{
  matrix.begin();       
  matrix.setBright(1);
  
  matrix.dot(0, 0);    
  matrix.update();     
  delay(1000);
  matrix.clear();
}

void loop() 
{
  for (int i = 0; i < AM_W; i++)
  {
    matrix.dot(i,0);
    matrix.update();  
    delay(100);
    matrix.clear();
  }
}
