 

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
 
bool re1,re2,re3;// 1 Запоминать % состояние 2 ON / OFF при включении  3 Плавное включение

 
#define pin_led 13      
#define pin_leds 12 


bool led_status;//светодиод 
int leds_status;//


 
 

int mqw1,mqw3;//htm19
String mqw2,mqw4,mqw5,mqw6,mqw7;//htm19
String top1,top2,top3,top4; //адресное пространство MQTT 
int mqtt_data_status;
String mqtt_code_bin,mqtt_fs_bin;
   int leds_status_web;
float rev_code=0.05;//текущая версия кода
WiFiClient mqtttestclient; 
PubSubClient mqttclient(mqtttestclient);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80); 
WiFiClient client;
File fsUploadFile;



  
void callback(const MQTT::Publish& pub){
     String payload = pub.payload_string();

//leds
if(String(pub.topic()) == top3 + "BN-SZ01/leds"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 int mqtt_smooth_change = json["smooth_change"];// 
                 leds_mqtt(mqtt_data_status,mqtt_smooth_change);
                }
if(String(pub.topic()) == top2 + "BN-SZ01/leds"){ //уровень комнаты
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 int mqtt_smooth_change = json["smooth_change"];// 
                 leds_mqtt(mqtt_data_status,mqtt_smooth_change);
                }
if(String(pub.topic()) == top1 + "BN-SZ01/leds"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 int mqtt_smooth_change = json["smooth_change"];// 
                 leds_mqtt(mqtt_data_status,mqtt_smooth_change);
                }
//led
              if(String(pub.topic()) == top3 + "BN-SZ01/led"){ //уровень устройаств
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_led, HIGH); 
                    }    
                }
              if(String(pub.topic()) == top2 + "BN-SZ01/led"){ //уровень комнаты 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_led, HIGH); 
                    }    
                }

             if(String(pub.topic()) == top1 + "BN-SZ01/led"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_led, HIGH); 
                    }    
                }

 
       
//status
                if(String(pub.topic()) == top3 + "BN-SZ01/status"){  
                   String url;   
                          url += "{\"leds\":\""; 
                          url+=leds_status;
                          url += "\",\"led\":\"";
                          url+=led_status;
                          url +=  "\"}"; 
                   mqttclient.publish(top3 + "BN-SZ01/status/status",url); 
                 }    

//reset
                  if(String(pub.topic()) == top3 + "BN-SZ01/reset"){ // 
                     mqttclient.publish(top3 + "BN-SZ01/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }    
                  if(String(pub.topic()) == top2 + "BN-SZ01/reset"){ // 
                     mqttclient.publish(top3 + "BN-SZ01/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    } 
                  if(String(pub.topic()) == top1 + "BN-SZ01/reset"){ // 
                     mqttclient.publish(top3 + "BN-SZ01/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }       

//update
                if(String(pub.topic()) == top3 + "BN-SZ01/update"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   String code_bin = json["code"];//code
                   String fs_bin = json["fs"];// fs 
                   mqtt_code_bin = code_bin;
                   mqtt_fs_bin = fs_bin;
                   mqttclient.publish(top3 + "BN-SZ01/update/status","{\"status\":\"1\"}"); 
                   esp_update(mqtt_fs_bin,mqtt_code_bin);
                }
//save_state
                if(String(pub.topic()) == top3 + "BN-SZ01/save_state"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   re1 = json["save_state"];//Запоминать % состояние 
                   re2 = json["on_off"];//ON / OFF при включении 
                   re3 = json["soft_start"];//Плавное включение
                   save20();//  запись в память модуля
                   mqttclient.publish(top3 + "BN-SZ01/save_state/status","{\"status\":\"1\"}"); 
                   
                }

}

void setup(void){
     //Serial.begin(9600);
     SPIFFS.begin();
     
     pinMode(pin_led, OUTPUT);
     digitalWrite(pin_led, LOW);
     pinMode(pin_leds, OUTPUT);
     
     openfile();//файл настроек 
     openfilehtm19();// файл настроек  htm19 MQTT
     openfilehtm20();// файл настроек  htm20 файл настроек
     openfilehtm27();// leds status
 
     if (re3 == 1){ 
         for(int i=0;i<=leds_status;i++){
             analogWrite(pin_leds,i);
             delay(3);
            }
        } else {
           if (re2 == 1){
               analogWrite(pin_leds, 1000);//включение светодиодов
               leds_status=1000;
             }
         }  
       
      top3 += "/home/"+mqw7+ "/"+mqw6+"/";//уровень устройства
      top2 += "/home/"+mqw7+"/";//уровень комнаты     
      top1 += "/home/";//уровень дома
 
     wifi();//подключение к wifi 
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
