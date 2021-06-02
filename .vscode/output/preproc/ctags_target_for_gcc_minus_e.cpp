# 1 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\NANO\\nanoFirmwareB\\nanoFirmwareB.ino"
# 2 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\NANO\\nanoFirmwareB\\nanoFirmwareB.ino" 2
# 3 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\NANO\\nanoFirmwareB\\nanoFirmwareB.ino" 2
# 17 "c:\\Users\\xXC4R\\Desktop\\Proyecto-main\\Archivos finales\\CODIGOS FINALES\\MODULO B\\NANO\\nanoFirmwareB\\nanoFirmwareB.ino"
String mensajeJson;
bool mensajeListo;


SoftwareSerial nodemcu(2, 4);

void setup()
{
    Serial.begin(9600);
    nodemcu.begin(9600);
}

void loop()
{
    delay(10);

    while(nodemcu.available())
    {
        mensajeJson = nodemcu.readString();
        mensajeListo = true;

    }

    if (mensajeListo)
    {
        StaticJsonDocument<1024> datos;

        DeserializationError error = deserializeJson(datos, mensajeJson);

        if (error)
        {
            Serial.print("Error en la deserializacion. ERROR: ");
            Serial.print(error.c_str());
            mensajeListo = false;
            return;
        }

        String modoJson = datos["modo"];
        String pinJson = datos["pin"];
        String valJson = datos["val"];

        int pin;
        int val = valJson.toInt();

        if (pinJson == "A0")
        {
            pin = 3;
        }

        if (pinJson == "A1")
        {
            pin = 5;
        }

        if (pinJson == "A2")
        {
            pin = 6;
        }

        if (pinJson == "A3")
        {
            pin = 9;
        }

        if (pinJson == "D0")
        {
            pin = 14;
        }

        if (pinJson == "D1")
        {
            pin = 15;
        }

        if (pinJson == "D2")
        {
            pin = 16;
        }

        if (pinJson == "D3")
        {
            pin = 17;
        }

        delay(100);

        if (modoJson == "analogico")
        {
            analogWrite(pin, val);
        }

        if (modoJson == "digital")
        {
            digitalWrite(pin, val);
        }

        mensajeListo = false;
    }
}
