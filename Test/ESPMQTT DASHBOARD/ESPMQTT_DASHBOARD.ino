#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* wifi = "VALCAR";
const char* cont = "geagonzalez";
const char* broker = "192.168.1.69";
const int puerto = 1883;

WiFiClient nodemcu;
PubSubClient moduloT(nodemcu);

void setupWifi()
{
    delay(10);

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

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Mensaje recivido en: ");
    Serial.println(topic);

    Serial.print("Mensaje:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println("");
}

void reconectar()
{
    while (!moduloT.connected())
    {
        Serial.print("Intentando conexion MQTT...");

        String idCliente = "MODULO-T";

        if (moduloT.connect(idCliente.c_str()))
        {
            Serial.println("Conectado con exito :D");

            moduloT.subscribe("test");
        }
        else
        {
            Serial.print("Fallo en la conexion.    ERROR: ");
            Serial.print(moduloT.state());
            Serial.println("    Reintentando en 5s");

            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    setupWifi();

    moduloT.setServer(broker, puerto);
    moduloT.setCallback(callback);
}

void loop()
{
    if (!moduloT.connected())
    {
        reconectar();
    }

    moduloT.loop();

    delay(10);
}
