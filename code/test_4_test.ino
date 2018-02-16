#include <ESP8266WiFi.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <WiFiClient.h>
#include <ESP8266WebServer.h>       //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <ESP8266mDNS.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS
#include <FS.h>                     //http://esp8266.github.io/Arduino/versions/2.1.0/doc/filesystem.html  
#include <ArduinoJson.h>            //https://bblanchon.github.io/ArduinoJson/
#include <PubSubClient.h>           //https://github.com/Imroy/pubsubclient
#include <ESP8266httpUpdate.h>      //https://github.com/Links2004/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/ESP8266httpUpdate        
#include <ESP8266HTTPClient.h>      //https://github.com/Links2004/Arduino/tree/libraries/ESP8266HTTPClient 
#include <ESP8266HTTPUpdateServer.h>//https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer 
#include <Wire.h>                   //https://github.com/esp8266/Arduino/tree/master/libraries/Wire 
#include <Ticker.h>                 //https://github.com/esp8266/Arduino/tree/master/libraries/Ticker 
#include <SPI.h>                    //http://www.arduino.cc/en/Reference/SPI

String w1,w2,w3,w4,w5,w6; //настройки wifi
int w7,w8;//настройки wifi

int var=1;//wifi 
int wifire;
int reconnect;
 
 

int mqw1,mqw3,mqw8,mqw10;//htm19
String mqw2,mqw4,mqw5,mqw6,mqw7,mqw9;//htm19
String top1,top2,top3,top4; //адресное пространство MQTT 


float rev_code=0.04;//текущая версия кода
WiFiClient mqtttestclient; 
PubSubClient mqttclient(mqtttestclient);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80); 
WiFiClient client;
File fsUploadFile;


int re1,re2,re3,re4;
  
void callback(const MQTT::Publish& pub){
     String payload = pub.payload_string();
      if(String(pub.topic()) == top3 + "bn-sz01"){ //уровень устройства 
                 re1 = payload.toInt(); 
                 if (re2 == 1){ 
                     analogWrite(12, re1);
                     save20();
                     } else {
                     analogWrite(12, re1);
                    }   
                }
      if(String(pub.topic()) == top2 + "bn-sz01"){ //уровень комнаты
                   re1 = payload.toInt(); 
                   if (re2 == 1){ 
                     analogWrite(12, re1);
                     save20();
                     } else {
                     analogWrite(12, re1);
                    }      
                }
     if(String(pub.topic()) == top1 + "bn-sz01"){ //уровень дома
                   re1 = payload.toInt(); 
                   if (re2 == 1){ 
                     analogWrite(12, re1);
                     save20();
                     } else {
                     analogWrite(12, re1);
                    }      
                }           
            
}

void setup(void){
     Serial.begin(9600);
     SPIFFS.begin();  
     
     pinMode(13, OUTPUT);
     pinMode(12, OUTPUT);
     digitalWrite(13, LOW);
     openfile();//файл настроек 
     openfilehtm19();// файл настроек  htm19 MQTT
     openfilehtm20();// файл настроек  htm20 файл настроек

     if (re3 == 1){ 
        for(int i=0;i<=re1;i++){
            analogWrite(12,i);
            delay(3);   
           }
         } else {
           analogWrite(12, re1);//включение светодиодов
         }
       
      top3 += "/home/"+mqw7+ "/"+mqw6+"/";//уровень устройства
      top2 += "/home/"+mqw7+"/";//уровень комнаты     
      top1 += "/home/";//уровень дома
        
      //Serial.println(top3);//уровень устройства
      //Serial.println(top2);//уровень комнаты
      //Serial.println(top1);//уровень дома
     wifi();//подключение к wifi 
     Serial.println(WiFi.localIP());
     serveron();//запуск сервера порт 80  

}
void loop(void){   
     server.handleClient(); 
     wifitest(); 
     if (mqw1 == 1){//
         if (mqttclient.connected()){
             mqttclient.loop();
             }else {
              mqtt_connect();
             }
       }
}


