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
        mensajeListo =true; 
}

if(mensajeListo)
{
  DynamicJsonDocument documento(1024);
  DeserializationError error = deserializeJson(documento, mensaje);

if(error)
{
    Serial.print(F("Error en la deserializacion   ERROR:  "));
    Serial.println(error.c_str());
    mensajeListo = false;
    return;
}

if(documento["tipo"] == "respuesta")
{
    String stringPin = documento ["pin"];
    int pin = stringPin.toInt();
    String stringValor = documento["valor"];
    int valor = stringValor.toInt();

if(documento["accion"] == "analogico")
{
    Serial.println(F("CONTROL ANALOGICO"));
    Serial.print("PIN: ");
    Serial.println(pin);
    Serial.print("VALOR: ");
    Serial.println(valor);
    analogWrite(pin, valor);
}

if(documento["accion"] == "digital")
{
    Serial.println(F("CONTROL DIGITAL"));
    Serial.print("PIN: ");
    Serial.println(pin);
    Serial.print("VALOR: ");
    Serial.println(valor);
    digitalWrite(pin,valor);
   }
 }

 mensajeListo = false;
 }
}
