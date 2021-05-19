#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define rxPin 4
#define txPin 2

const char* wifi = "VALCAR";
const char* pass = "geagonzalez";
const char* idCliente = "Modulo-A";
const char* broker = "192.168.1.69";
const int puerto = 1883;

String mensajeJson;
char* mensaje;
bool mensajeListo = false;

SoftwareSerial nano(rxPin, txPin);

WiFiClient nodemcu;
PubSubClient moduloA(nodemcu);

void wifiConfig()
{
    Serial.println("");
    Serial.print("Conectando a: ");
    Serial.println(wifi);

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("-");
    }

    randomSeed(micros());

    Serial.println("Wifi conectado con exito");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
}

void reconectar()
{
    while (!moduloA.connected())
    {
        Serial.print("Intentano conexion MQTT...");
        
        if (moduloA.connect(idCliente))
        {
            Serial.println("Conectado con exito");
        }
        else
        {
            Serial.print("Fallo en la conexion. ERROR: ");
            Serial.println(moduloA.state());
            Serial.println("Reintentando en 5s");
            
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(9600);
    nano.begin(9600);

    wifiConfig();

    moduloA.setServer(broker, puerto);
}

void loop()
{
    if (!moduloA.connected())
    {
        reconectar();
    }

    while (nano.available())
    {
        mensajeJson = nano.readString();
        mensajeListo = true;
    }
    

    if (mensajeListo)
    {
        DynamicJsonDocument datos(1024);
        DeserializationError error = deserializeJson(datos, mensajeJson);
    
        if (error)
        {
            Serial.print("Error en la deserealizacion ERROR: ");
            Serial.println(error.c_str());
            mensajeListo = false;
            return;
        }
        
        String valA0 = datos["A0"];
        String valA1 = datos["A1"];
        String valA2 = datos["A2"];
        String valA3 = datos["A3"];
        
        String valD0 = datos["D0"];
        String valD1 = datos["D1"];
        String valD2 = datos["D2"];
        String valD3 = datos["D3"];

        moduloA.publish("moduloA/A0", valA0.c_str());
        moduloA.publish("moduloA/A1", valA1.c_str());
        moduloA.publish("moduloA/A2", valA2.c_str());
        moduloA.publish("moduloA/A3", valA3.c_str());

        moduloA.publish("moduloA/D0", valD0.c_str());
        moduloA.publish("moduloA/D1", valD1.c_str());
        moduloA.publish("moduloA/D2", valD2.c_str());
        moduloA.publish("moduloA/D3", valD3.c_str());
    }
}