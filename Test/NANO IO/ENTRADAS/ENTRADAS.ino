#include <ArduinoJson.h>

String mensaje = "";
bool mensajeListo = false;

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    while(Serial.available())
{
    mensaje = Serial.readString();
    mensajeListo = true;
}

if(mensajeListo)
{
    DynamicJsonDocument documento(1024);
    DeserializationError error = deserializeJson(documento, mensaje);
if(error)
{
    Serial.print("Error en la deserializacion ERROR:  ");
    Serial.printIn(error.c_str());
    mensajeListo = false;
    return;
}
if(documento["tipo"] == "peticion")
{
    documento["tipo"] = "respuesta";
    documento["A0"] = analogRead(A0);
    documento["D2"] = digitalRead(2);

    serializeJson(documento, Serial );
}

  mensajeListo = false
  }

}
