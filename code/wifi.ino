void wifi() {
      WiFi.disconnect();
      WiFi.hostname ("BN-SZ01");
      WiFi.mode(WIFI_STA);  
      WiFi.begin(w1.c_str(), w2.c_str());
      int i = 0;
      while (WiFi.status() != WL_CONNECTED && i < w7) {
             delay(1000);
             i++;
             //Serial.print(".");
           }
      if (WiFi.status() != WL_CONNECTED)  {     
          wifiap();    
         } 
        digitalWrite(pin_led, HIGH);  
}
void wifitest() {
     int iw = 0;  
     if (wifire == 0){
         if (WiFi.status() != WL_CONNECTED)  { 
             while (WiFi.status() != WL_CONNECTED && iw< w8) { 
                    digitalWrite(pin_led, LOW); 
                    delay(1000); 
                    digitalWrite(pin_led, HIGH); 
                    //Serial.print("reconnect ");
                    iw++;
                   }
             reconnect++; 
            }
         }
     if (wifire == 0){
         if (iw == w8){
             wifiap();
             mqw1=0;
             wifire=1;
            }
       }   
}
void wifiap() {      
     WiFi.disconnect();
     WiFi.mode(WIFI_AP);  
     WiFi.softAP(w3.c_str(),w4.c_str());
     digitalWrite(pin_led, LOW); 
     wifire=1;
     var=0;
}
