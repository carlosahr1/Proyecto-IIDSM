# 1 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\ESP\\espFirmwareB\\espFirmwareB.ino"
# 2 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\ESP\\espFirmwareB\\espFirmwareB.ino" 2
# 3 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\ESP\\espFirmwareB\\espFirmwareB.ino" 2
# 4 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\ESP\\espFirmwareB\\espFirmwareB.ino" 2
# 5 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\ESP\\espFirmwareB\\espFirmwareB.ino" 2




const char* wifi = "VALCAR";
const char* pass = "geagonzalez";
const char* idCliente = "Modulo-B";
const char* broker = "192.168.1.69";
const int puerto = 1883;

WiFiClient nodemcu;
PubSubClient moduloB(nodemcu);
SoftwareSerial nano(4, 2);

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

    String topico;
    for (int i = 0; i < 10; i++)
    {
        topico += (char)topic[i];
    }


    String pinJson;
    String modoJson;

    if (topico == "moduloB/A0")
    {
        pinJson = "A0";
        modoJson = "analogico";
    }
    if (topico == "moduloB/A1")
    {
        pinJson = "A1";
        modoJson = "analogico";
    }
    if (topico == "moduloB/A2")
    {
        pinJson = "A2";
        modoJson = "analogico";
    }
    if (topico == "moduloB/A3")
    {
        pinJson = "A3";
        modoJson = "analogico";
    }

    if (topico == "moduloB/D0")
    {
        pinJson = "D0";
        modoJson = "digital";
    }
    if (topico == "moduloB/D1")
    {
        pinJson = "D1";
        modoJson = "digital";
    }
    if (topico == "moduloB/D2")
    {
        pinJson = "D2";
        modoJson = "digital";
    }
    if (topico == "moduloB/D3")
    {
        pinJson = "D3";
        modoJson = "digital";
    }

    StaticJsonDocument<1024> datos;

    datos["modo"] = modoJson;
    datos["pin"] = pinJson;
    datos["val"] = mensaje;

    serializeJson(datos, Serial);
    Serial.println("");
    serializeJson(datos, nano);

}

void reconectar()
{
    while (!moduloB.connected())
    {
        Serial.print("Intentando conexion MQTT...");

        if (moduloB.connect(idCliente))
        {
            Serial.println("");
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
