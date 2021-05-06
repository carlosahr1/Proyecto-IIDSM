#include <SoftwareSerial.h>

#define rx D2
#define tx D3

SoftwareSerial NodeMCU(rx, tx);

void setup()
{
	Serial.begin(9600);
	NodeMCU.begin(9600);
}

void loop()
{
  NodeMCU.println("Este es un mensaje de NODEMCU");
  Serial.println("Enviando mensaje a Arduino Nano...");
  delay(2000);
}
