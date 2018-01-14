void mqtt_connect(){// подключение к MQTT серверу
     mqttclient.set_server(mqw2,mqw3);      
     if (mqttclient.connect(MQTT::Connect(mqw6).set_auth(mqw4.c_str(), mqw5.c_str()))) {
         Serial.println("Connected to MQTT server ");
         mqttclient.set_callback(callback);
         // подписываемся под топики
         //mqttclient.subscribe(mqw7,mqw10);          
         mqttclient.subscribe("/home/#");
        } 
}
 
