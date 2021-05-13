#include<SoftwareSerial.h>
#include<ArduinoJson.h>

SoftwareSerial nano(D2, D4);

void setup ()
{
    Serial.begin(9600);
    nano.begin(9600);
}

void loop ()
{
    DynamicJsonDocument doc(1024);
    doc["tipo"] = "peticion";
    serializeJson(doc, nano);

    String mensaje = nano.readString();

    Serial.println(mensaje);
    delay(1000);
}
