#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 4

#define A0 3
#define A1 5
#define A2 6
#define A3 9

#define D0 14 
#define D1 15
#define D2 16
#define D3 17

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


        String modoJson = datos["modo"];
        String pinJson = datos["pin"];
        String valJson = datos["val"];

        int pin;
        int val = valJson.toInt();

        if (pinJson == "A0")
        {
            pin = A0;
        }

        if (pinJson == "A1")
        {
            pin = A1;
        }

        if (pinJson == "A2")
        {
            pin = A2;
        }

        if (pinJson == "A3")
        {
            pin = A3;
        }

        if (pinJson == "D0")
        {
            pin = D0;
        }

        if (pinJson == "D1")
        {
            pin = D1;
        }

        if (pinJson == "D2")
        {
            pin = D2;
        }

        if (pinJson == "D3")
        {
            pin = D3;
        }

        delay(100)

        if (modoJson == "analogico")
        {
            analogWrite(pin, val);
        }

        if (modoJson == "digital")
        {
            digitalWrite(pin, val);
        }
        
        mensajeListo = false;
    }
}