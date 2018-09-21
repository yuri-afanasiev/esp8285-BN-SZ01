void leds() {
     leds_status_web=leds_status;
     leds_status = server.arg("brightness").toInt();//яркость 
     bool smooth_change = server.arg("smooth_change").toInt();//плавное изменение  
    
     if (smooth_change == 1){ //плавное изменение  
            leds_web();
            if (re1 == 1){ //Запоминать % состояние
                save27();
                }
               } else {
                      if (re1 == 1){ //Запоминать % состояние
                          analogWrite(pin_leds, leds_status);
                          save27();
                         } else {
                           analogWrite(pin_leds, leds_status);
                         } 
               }
            String url;   
            url += "{\"status\":\""; 
            url+=leds_status;
            url += "\",\"activated\":\"1";
            url +=  "\"}"; 
     if (mqw1 == 1){
         mqttclient.publish(top3 + "BN-SZ01/leds/status", url);//status   activated 1-web
         }
     server.send(200, "text/json", url);//status   activated 1-web
}

void leds_mqtt(int leds_status_mqtt,int smooth_change_mqtt) {
     leds_status = leds_status_mqtt;
     String url;   
            url += "{\"status\":\""; 
            url+=leds_status;
            url += "\",\"activated\":\"2";
            url +=  "\"}"; 
     if (smooth_change_mqtt == 1){ //плавное изменение  
         leds_web();
         } else {
           if (re1 == 1){ //Запоминать % состояние
               analogWrite(pin_leds, leds_status);
               save27();
              } else {
                analogWrite(pin_leds, leds_status);
                     } 
         }
     mqttclient.publish(top3 + "BN-SZ01/leds/status", url);//status   activated 1-web
       
     
}
void leds_web(){
  if (leds_status_web <= leds_status){ //плавное изменение  
            for(int i=leds_status_web;i<=leds_status;i++){
                    analogWrite(pin_leds,i);
                    delay(1);
                   }      
            leds_status_web=leds_status;
               } else {
                       for(int i=leds_status_web;i>=leds_status;i--){
                           analogWrite(pin_leds,i);
                           delay(1);
                          } 
            leds_status_web=leds_status;
              }
               
}
