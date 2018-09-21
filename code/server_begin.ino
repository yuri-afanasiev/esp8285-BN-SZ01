void serveron() {
   server.on("/esp_update", [](){//Обнавление   
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       String fs_bin_test = server.arg("fs_bin");//fs 
       String code_bin_test = server.arg("code_bin");//code
       esp_update(fs_bin_test,code_bin_test);
     }); 
     
    server.on("/config", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    testjson();
    }); 
      
    server.on("/xml9", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm9xml();
    });   
   
    server.on("/json19", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm19json();
    }); 
     
    server.on("/json20", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm20json();
    });   
   
     
    server.on("/api", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    api();
    });  
     
     server.on("/api20", [](){    
     if(!server.authenticate(w5.c_str(),w6.c_str()))
     return server.requestAuthentication();  
     api20();
     });  
 
  
    server.on("/reset", [](){
     if(!server.authenticate(w5.c_str(),w6.c_str()))
        return server.requestAuthentication();  
        server.send(200, "text/json", "{\"status\":\"1\"}");
        ESP.restart();    
     }); 

    

     
       server.on("/leds", [](){
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();
       leds();
       }); 

      
      
       server.on("/api19", [](){    
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       api19();
       });   
     
       server.on("/led/off", [](){
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();
       digitalWrite(pin_led, HIGH); 
       led_status=0;
       if (mqw1 == 1){
           mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"0\",\"activated\":\"1\"}");//status 0-off activated 1-web
          }
       server.send(200, "text/json","{\"status\":\"0\",\"activated\":\"1\"}");//status 0-off activated 1-web
       }); 

     
       server.on("/led/on", [](){
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();
       digitalWrite(pin_led, LOW); 
       led_status=1;
       if (mqw1 == 1){
           mqttclient.publish(top3 + "BN-SZ01/led/status","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
           }
       server.send(200, "text/json", "{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
       }); 

       server.on("/status", [](){
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();
       String url;   
              url += "{\"leds\":\""; 
              url+=leds_status;
              url += "\",\"led\":\"";
              url+=led_status;
              url += "\",\"version\":\"";
              url+=rev_code;
              url +=  "\"}"; 
       server.send(200, "text/json",url); 
       }); 


       
    
    server.on("/config.json", [](){      
    server.send(403, "text/plain", "Forbidden");       
    });  
    
    server.on("/htm19.json", [](){      
    server.send(403, "text/plain", "Forbidden");       
    }); 
    
     
     server.onNotFound([](){
     if(!handleFileRead(server.uri()))
         server.send(404, "text/plain", "FileNotFound");
        }); 
        server.on("/list", HTTP_GET, handleFileList);  
        server.on("/edit", HTTP_GET, [](){
         if(!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
            });         
         server.on("/edit", HTTP_PUT, handleFileCreate); 
         server.on("/edit", HTTP_DELETE, handleFileDelete);
         server.on("/edit", HTTP_POST, [](){ server.send(200, "text/plain", ""); }, handleFileUpload);
         server.begin();
    
}
