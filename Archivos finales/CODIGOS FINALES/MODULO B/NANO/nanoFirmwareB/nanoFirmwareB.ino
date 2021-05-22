#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 4

#define A0 14
#define A1 15
#define A2 16
#define A3 17

#define D0 3 
#define D1 5
#define D2 6
#define D3 9

String mensajeJson;
bool mensajeListo;


SoftwareSerial nodemcu(rxPin, txPin);

void setup()
{
    Serial.begin(9600);
    nodemcu.begin(9600);
}

void loop()
{
    delay(10);

    while(nodemcu.available())
    {
        mensajeJson = nodemcu.readString();
        mensajeListo = true;

    }

    if (mensajeListo)
    {
        StaticJsonDocument<1024> datos;

        DeserializationError error = deserializeJson(datos, mensajeJson);

        if (error)
        {
            Serial.print("Error en la deserializacion. ERROR: ");
            Serial.print(error.c_str());
            mensajeListo = false;
            return;
        }

        int val;
        String valorJson = datos["valor"];
        val = valorJson.toInt();
        
        int pin;
        String pinJson = datos["pin"]
        mensajeListo = false;
    }
}