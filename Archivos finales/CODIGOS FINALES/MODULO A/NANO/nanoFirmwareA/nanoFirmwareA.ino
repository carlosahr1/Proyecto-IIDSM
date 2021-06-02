#include <ArduinoJson.h>                    
#include <SoftwareSerial.h>                 

#define rxPin 2                             
#define txPin 4                             

#define A0 14                               
#define A1 15                               
#define A2 16                               
#define A3 17                               

#define D0 3                                
#define D1 5                                
#define D2 6                                
#define D3 9                                

SoftwareSerial nodemcu(rxPin, txPin);       

void setup()                                
{
    Serial.begin(9600);                     
    nodemcu.begin(9600);                    
}

void loop()                                 
{
    delay(10);                              

    DynamicJsonDocument datos(1024);        

    int valA0 = analogRead(A0);             
    int valA1 = analogRead(A1);             
    int valA2 = analogRead(A2);             
    int valA3 = analogRead(A3);             

    int valD0 = digitalRead(D0);            
    int valD1 = digitalRead(D1);            
    int valD2 = digitalRead(D2);            
    int valD3 = digitalRead(D3);            

    datos["A0"] = valA0;                    
    datos["A1"] = valA1;                    
    datos["A2"] = valA2;                    
    datos["A3"] = valA3;                    

    datos["D0"] = valD0;                    
    datos["D1"] = valD1;                    
    datos["D2"] = valD2;                    
    datos["D3"] = valD3;                    

    serializeJson(datos, nodemcu);          
    serializeJson(datos, Serial);           
    Serial.println("");                     
    delay(1000);                            
}