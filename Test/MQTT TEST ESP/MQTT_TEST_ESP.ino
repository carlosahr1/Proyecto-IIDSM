
#include "EspMQTTClient.h"

EspMQTTClient client(
  "VALCAR",
  "geagonzalez",
  "192.168.1.69",  
  "MQTTUsername",   
  "MQTTPassword",  
  "NODEMCU",    
  1883              
);

void setup()
{
  Serial.begin(115200);


  client.enableDebuggingMessages(); 

}

void onConnectionEstablished()
{

  client.subscribe("mytopic/test", [](const String & payload) {
    Serial.println(payload);
  });

  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });

  client.publish("mytopic/test", "This is a message"); 

  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  client.loop();
}
