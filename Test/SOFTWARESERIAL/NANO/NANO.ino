#include <SoftwareSerial.h>

#define rx 2
#define tx 3

SoftwareSerial ArduinoNano(rx, tx);

void setup()
{
	
	Serial.begin(9600);
	ArduinoNano.begin(9600);

}

void loop()
{
    String datos = String(ArduinoNano.readString());
    char mensaje[200];
    datos.toCharArray(mensaje, 200);
	  Serial.println(mensaje);
}
