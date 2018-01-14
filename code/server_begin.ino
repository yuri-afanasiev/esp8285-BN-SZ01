void serveron() {
   server.on("/esp_update", [](){//Обнавление   
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       String fs_bin_test = server.arg("fs_bin");//fs 
       String code_bin_test = server.arg("code_bin");//code
       esp_update(fs_bin_test,code_bin_test);
     }); 
      server.on("/led", [](){    
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       led();
     });  
    server.on("/xml1", [](){    
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       testxml();
     });  
         server.on("/xml9", [](){    
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       htm9xml();
     });   
   
   server.on("/xml19", [](){    
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       htm19xml();
     }); 
    server.on("/xml20", [](){    
   if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       htm20xml();
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
        server.send(200, "text/plain", "ok");
        ESP.restart();    
     }); 
     
      
      server.on("/api19", [](){    
     if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       api19();
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
