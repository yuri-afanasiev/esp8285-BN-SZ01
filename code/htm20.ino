void api20() {
     re1 = server.arg("re1").toInt();//ON / OFF при включении  
     re2 = server.arg("re2").toInt();//Запоминать % состояние 
     re3 = server.arg("re3").toInt();//Плавное включение 
     save20();//  запись в память модуля
     server.send(200, "text/plain", "OK");
}

void openfilehtm20() {
  File configFile = SPIFFS.open("/htm20.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
        re1 = json["d1"];// 
        re2 = json["d2"]; //
        re3 = json["d3"]; //
} 

bool save20() {
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = re1;// 
  json["d2"] = re2;// 
  json["d3"] = re3;//
  File configFile = SPIFFS.open("/htm20.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}

void  htm20xml(){
String  url1="<?xml version='1.0'?>";
        url1+="<Donnees>"; 
        url1+="<q1>";
        url1+=re1;// 
        url1+="</q1>";
        url1+="<q2>";
        url1+=re2;// 
        url1+="</q2>";
        url1+="<q3>";
        url1+=re3;// 
        url1+="</q3>";
        url1+="</Donnees>"; 
server.send(200,"text/xml",url1);
}         
void led() {
     re1 = server.arg("re1").toInt();//   
     if (re2 == 1){ 
         analogWrite(12, re1);
         save20();
         } else {
         analogWrite(12, re1);
        }
     server.send(200, "text/plain", "OK");
}
