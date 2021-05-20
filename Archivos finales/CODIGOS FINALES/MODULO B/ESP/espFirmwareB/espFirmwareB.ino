#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define rxPin 4
#define txPin 2

const char* wifi = "VALCAR";
const char* pass = "geagonzalez";
const char* idCliente = "Modulo-B";
const char* broker = "192.168.1.69";
const int puerto = 1883;

WiFiClient nodemcu;
PubSubClient moduloB(nodemcu);
SoftwareSerial nano(rxPin, txPin);

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

    Serial.println("");
    Serial.println("Wifi conectado");
    Serial.println("Direccion IP:");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
    String mensaje;
    for (int i = 0; i < length; i++)
    {
        mensaje += (char)payload[i];
    }

    char val[200];
    mensaje.toCharArray(val, 200);

    DynamicJsonDocument datos(200);

    Serial.println(topic);
    Serial.println(val);
    serializeJson(datos, Serial);
}

void reconectar()
{
    while (!moduloB.connected())
    {
        Serial.print("Intentando conexion MQTT...");

        if (moduloB.connect(idCliente))
        {
            Serial.println("Conexion exitosa");

            moduloB.subscribe("moduloB/A0");
            moduloB.subscribe("moduloB/A1");
            moduloB.subscribe("moduloB/A2");
            moduloB.subscribe("moduloB/A3");

            moduloB.subscribe("moduloB/D0");
            moduloB.subscribe("moduloB/D1");
            moduloB.subscribe("moduloB/D2");
            moduloB.subscribe("moduloB/D3");
        }
        else
        {
            Serial.print("Fallo en la conexion. ERROR: ");
            Serial.println(moduloB.state());
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

    moduloB.setServer(broker, puerto);
    moduloB.setCallback(callback);
}

void loop()
{
    if (!moduloB.connected())
    {
        reconectar();
    }
    moduloB.loop();
    delay(100);
}