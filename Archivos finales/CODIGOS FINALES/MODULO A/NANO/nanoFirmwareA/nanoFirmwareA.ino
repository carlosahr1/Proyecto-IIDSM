//----LIBRERIAS----//
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
//----VARIABLES Y CONSTANTES----//
#define rxPin 2
#define txPin 4
SoftwareSerial nodemcu(rxPin, txPin);
String mensaje = "";
bool mensajeListo = true;
//----SETUP----//
void setup ()
{
    Serial.begin(9600);
    nodemcu.begin(9600);
}
//----LOOP----//
void loop()
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
            Serial.print("Error en la deserializacion   ERROR: ");
            Serial.println(error.c_str());
            mensajeListo = false;
            return;
        }
        if (documento["tipo"] == "peticion")
        {
            documento["tipo"] = "respuesta";

            documento["A0"] = analogRead(14);
            documento["A1"] = analogRead(15);
            documento["A2"] = analogRead(16);
            documento["A3"] = analogRead(17);
            documento["D0"] = digitalRead(3);
            documento["D1"] = digitalRead(5);
            documento["D2"] = digitalRead(6);
            documento["D3"] = digitalRead(9);

            serializeJson(documento, nodemcu);
        }
        mensajeListo = false;
    }
}