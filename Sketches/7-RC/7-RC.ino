#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(10, 9);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
String inputString = "Hello world!";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  Serial.begin(9600);
}
void loop()
{
  //Send message to receiver
  byte buffer[inputString.length() + 1];
  inputString.toCharArray(buffer, inputString.length() + 1);
  radio.write(&buffer, sizeof(buffer));
  
  delay(250);
}
