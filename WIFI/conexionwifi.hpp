
#include <LiquidCrystal_I2C.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h >
#include <WiFiManager.h>
WiFiManager wifiManager;
void wifista(){
  LiquidCrystal_I2C lcd(0x27,16,2);
  delay(1000);
  lcd.backlight();
  Serial.begin(9600);
  wifiManager.autoConnect("sofpymesTEMP");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Estas en linea");
}
