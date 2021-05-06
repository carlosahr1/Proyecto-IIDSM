//    L I B R E R I A S    //
#include<ArduinoJson.h>
#include<SoftwareSerial.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
//    V A R    &    C O N S T   //
#define rxPin 4    //D2
#define txPin 2    //D4

unsigned long tiempo = millis();

const char* wifi = "VALCAR";
const char* cont = "geagonzalez";
const char* broker = "192.168.1.690";
const char* idCliente = "Modulo-A";
const int puerto = 1883;

SoftwareSerial nano(rxPin, txPin);
WiFiClient nodemcu;
PubSubClient moduloA(nodemcu);
//    W I F I    C O N F I G    /
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
//    R E C O N E C T A R    //
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
//    S E T U P    //
void setup()
{
    Serial.begin(9600);
    nano.begin(9600);

    wifiConfig();

    moduloA.setServer(broker, puerto);
}
//    L O O P    //
void loop()
{
    
}