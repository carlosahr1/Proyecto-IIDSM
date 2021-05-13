#include <SoftwareSerial.h> //Libreria para comunicacion serial
#include <ArduinoJson.h> //Libreria para Json

#define rxPin 2 //Pin de recepcion
#define txPin 4 //Pin de transmision

//Pines analogicos

#define A0 14 
#define A1 15
#define A2 16
#define A3 16

//Pines digitales

#define D0 3
#define D1 5
#define D2 6
#define D3 9

//Variables

String mensaje = "";
bool mensajeListo = false;

SoftwareSerial nodemcu (rxPin, txPin); //Creacion de la comunicacion serial "nodemcu"

void setup ()
{
    Serial.begin(9600);
    nodemcu.begin(9600);
}

void loop ()
{
    while (nodemcu.available())
    {
        mensaje = nodemcu.readString();
        mensajeListo = true;
    }
    if (mensajeListo)
    {
        DynamicJsonDocument documento(1024);
        DeserializationError error = deserializeJson(documento, mensaje);
        if (error)
        {
            Serial.print("Error en la deserializacion.    ERROR: ");
            Serial.println(error.c_str());
            mensajeListo = false;
            return;
        }
        if (documento["tipo"] == "peticion")
        {
            documento["tipo"] = "respuesta";

            documento["A0"] = analogRead(A0);
            documento["A1"] = analogRead(A1);
            documento["A2"] = analogRead(A2);
            documento["A3"] = analogRead(A3);

            documento["D0"] = digitalRead(D0);
            documento["D1"] = digitalRead(D1);
            documento["D2"] = digitalRead(D2);
            documento["D3"] = digitalRead(D3);

            serializeJson(documento, nodemcu);
        }
        mensajeListo = false;
    }
    
}