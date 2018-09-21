void mqtt_connect(){// подключение к MQTT серверу
     mqttclient.set_server(mqw2,mqw3);      
     if (mqttclient.connect(MQTT::Connect(mqw6).set_auth(mqw4.c_str(), mqw5.c_str()))) {
         mqttclient.set_callback(callback);
         //Serial.println("Connected to MQTT server ");
         // подписываемся под топики
         //mqttclient.subscribe("/home/#");
          mqttclient.subscribe(top3 + "BN-SZ01/leds");
          mqttclient.subscribe(top2 + "BN-SZ01/leds");
          mqttclient.subscribe(top1 + "BN-SZ01/leds");

          mqttclient.subscribe(top3 + "BN-SZ01/led");
          mqttclient.subscribe(top2 + "BN-SZ01/led");
          mqttclient.subscribe(top1 + "BN-SZ01/led");

          mqttclient.subscribe(top3 + "BN-SZ01/status");

          mqttclient.subscribe(top3 + "BN-SZ01/reset");
          mqttclient.subscribe(top2 + "BN-SZ01/reset");
          mqttclient.subscribe(top1 + "BN-SZ01/reset");
          
          mqttclient.subscribe(top3 + "BN-SZ01/update");
          
          mqttclient.subscribe(top3 + "BN-SZ01/save_state");
          
        } 
}
 
