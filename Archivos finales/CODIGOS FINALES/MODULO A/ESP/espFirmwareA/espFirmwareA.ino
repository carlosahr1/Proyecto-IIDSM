//----LIBRERIAS----//
#include<ArduinoJson.h>
#include<SoftwareSerial.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
//----VARIABLES & CONSTANTES----//
#define rxPin 4    //D2
#define txPin 2    //D4

unsigned long tiempo = millis();

const char* wifi = "VALCAR";
const char* cont = "geagonzalez";
const char* broker = "192.168.1.690";
const char* idCliente = "Modulo-A";
const int puerto = 1883;
String mensaje = "";
bool mensajeListo = false;

SoftwareSerial nano(rxPin, txPin);
WiFiClient nodemcu;
PubSubClient moduloA(nodemcu);
//----WIFI CONFIG----/
void wifiConfig()
{
    delay(100);
    Serial.println("");
    Serial.print("Conectando a ");
    Serial.println(wifi);

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi, cont);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("WiFi conectado");
    Serial.println("Direccion IP: ");
    Serial.println(WiFi.localIP());
}
//----RECONECTAR----//
void reconectar()
{
    while (!moduloA.connected())
    {
        Serial.print("Intentando conexion MQTT");

        if (moduloA.connect(idCliente))
        {
            Serial.println("Conexion exitosa");
        }
        else
        {
            Serial.print("Fallo en la conexion.    ERROR: ");
            Serial.print(moduloA.state());
            Serial.println("    Reintentando en 5s");
            delay(5000);
        }
    }
}
//----SETUP----//
void setup()
{
    Serial.begin(9600);
    nano.begin(9600);

    wifiConfig();

    moduloA.setServer(broker, puerto);
}
//----LOOP----//
void loop()
{
    if (!moduloA.connected())
    {
        reconectar();
    }
    
    while (nano.available())
    {
        mensaje = nano.readString();
        mensajeListo = true;
    }
    if (mensajeListo)
    {
        DynamicJsonDocument documento(1024);
        DeserializationError error = deserializeJson(documento, mensaje);
        
        if (error)
        {
            Serial.print("Error en la deserializacion    ERROR: ");
            Serial.println(error.c_str());
            mensajeListo = false;
            return;
        }
        if (documento["tipo"] == "respuesta")
        {
            char* valA0 = documento["A0"];
            char* valA1 = documento["A1"];
            char* valA2 = documento["A3"];
            char* valA3 = documento["A3"];
            char* valD0 = documento["D0"];
            char* valD1 = documento["D1"];
            char* valD2 = documento["D3"];
            char* valD3 = documento["D3"];

            moduloA.publish("A0", valA0);
            moduloA.publish("A1", valA1);
            moduloA.publish("A2", valA2);
            moduloA.publish("A3", valA3);
            moduloA.publish("D0", valD0);
            moduloA.publish("D1", valD1);
            moduloA.publish("D2", valD2);
            moduloA.publish("D3", valD3);
        }
        if (millis() - tiempo > 1000)
        {
            documento["tipo"] = "peticion";
            serializeJson(documento, nano);
            tiempo = millis();
        }
    }
    moduloA.loop();
    delay(10);
}
