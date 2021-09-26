StaticJsonDocument<192> doc;
String pass(){
  DeserializationError error = deserializeJson(doc, getApi());
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    
  }

  JsonObject data = doc["data"];
  const char* data_p = data["p"]; // "8260"

  String p = String(data_p)+"";

  return(p);
}

double ingreso(){
  DeserializationError error = deserializeJson(doc, getApi());
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str()); 
  }
  JsonObject data = doc["data"];
  const char* data_i = data["i"];
  double i = String(data_i).toDouble();
  return(i);
}

double salida(){
  DeserializationError error = deserializeJson(doc, getApi());
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
  }
  JsonObject data = doc["data"];
  const char* data_o = data["o"]; // "202106191955"
  double o = String(data_o).toDouble();
  return(o);
}

String maestra(){ 
  DeserializationError error = deserializeJson(doc, getApi());
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
  }
  JsonObject data = doc["data"];
  const char* data_m = data["m"]; 
  String m = String(data_m);
  return(m);
}
