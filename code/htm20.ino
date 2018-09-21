void api20() {
     re1 = server.arg("save_state").toInt();//Запоминать % состояние
     re2 = server.arg("on_off").toInt();//ON / OFF при включении 
     re3 = server.arg("soft_start").toInt();//Плавное включение 
     save20();//  запись в память модуля
     server.send(200, "text/json","{\"status\":\"1\"}");
}

void openfilehtm20() {
  File configFile = SPIFFS.open("/htm20.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
        re1 = json["d1"];// 
        re2 = json["d2"];//
        re3 = json["d3"];//
} 

bool save20() {
  DynamicJsonBuffer  jsonBuffer;
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

void  htm20json(){
       String url;   
              url += "{\"save_state\":\""; 
              url+=re1;
              url += "\",\"on_off\":\"";
              url+=re2;
              url += "\",\"soft_start\":\"";
              url+=re3;
              url +=  "\"}"; 
server.send(200, "text/json",url); 
}   
////////////////////////////////


void openfilehtm27() {
  File configFile = SPIFFS.open("/htm27.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  leds_status = json["d1"];
} 

bool save27() {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = leds_status;
  File configFile = SPIFFS.open("/htm27.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}
 
