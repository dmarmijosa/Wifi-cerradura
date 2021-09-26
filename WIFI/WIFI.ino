#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#include <Wire.h>
#include <Keypad_I2C.h>
#include <Keypad.h>

#include "configuracion.h"
#include "conexionwifi.hpp"
#include "api.hpp"
#include "hora.hpp"
#include "variables.hpp"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const byte FILAS = 4;
const byte COLUMNAS = 3; 
 
char teclas[FILAS][COLUMNAS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
 
byte PinsFilas[FILAS] = {0,1,2,3}; 
byte PinsColumnas[COLUMNAS] = {4,5,6};

String mypassword="";

int i2caddress = 0x20;

int counter=0;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(teclas), PinsFilas, PinsColumnas, FILAS, COLUMNAS, i2caddress );


void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();
  wifista();
  
  delay(2000);
  timeClient.begin();
  
  pinMode(D3,OUTPUT);
  pinMode(D5,OUTPUT);
  
  Wire.begin(D2,D1);
  kpd.begin();
  lcd.clear();
  lcd.print("Ingrese password");
  digitalWrite(D3, LOW); 
  digitalWrite(D5, HIGH);
  delay(2000);
  digitalWrite(D3, LOW); 
  digitalWrite(D5, LOW);
  
}

void loop(){
  timeClient.update();
  horaActual();
  char key = kpd.getKey();;
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print("*");
  }
  if (key == '1')
  {
 
    mypassword = mypassword + 1;   
  }
  
    if (key == '2')
  {
 
    mypassword = mypassword + 2;  
  }
  
  if (key == '3')
  {
 
    mypassword = mypassword + 3; 
  }
  
   if (key == '4')
  {
  
    mypassword = mypassword + 4;  
  }
  
  if (key == '5')
  {
  
    mypassword = mypassword + 5;
  }
  
   if (key == '6')
  {
   
    mypassword = mypassword + 6; 
  }
  
   if (key == '7')
  {
 
    mypassword = mypassword + 7; 
  }
 
   if (key == '8')
  {
 
    mypassword = mypassword + 8; 
  }
  
  if (key == '9')
  {
 
    mypassword = mypassword + 9;
  }
             
  if (key == '0')
  {
 
    mypassword = mypassword + 0; 
  }
  if(key == '#'){
    mypassword = "";
    counter=0;
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Ingrese password");
    
  }
  if(key =='*'){

    if(maestra() ==mypassword){
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bienvenido");
        lcd.setCursor(0,1);
        lcd.print("Administrador");
        abierto();
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Ingrese password");
        mypassword = "";
        counter=0;
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Ingrese password");
    }else{
      if(horaActual()>=ingreso() && horaActual()<=salida()){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Validando....");
        if(pass() ==mypassword){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Bienvenido");
          lcd.setCursor(0,1);
          String numHab = "HABITACION:"+(String)numeroHabitacion;
          lcd.print(numHab);
          abierto();
          lcd.clear();
          mypassword = "";
          counter=0;
          lcd.setCursor(0,0); 
          lcd.println("Ingrese password");
      }else{
          lcd.clear();
          lcd.setCursor(0,0);
          cerrado();
          lcd.print("Pass incorrecto");
          delay(2000);
          mypassword = "";
          counter=0;
          lcd.setCursor(0,0); 
          lcd.print("Ingrese password");
      }
      
    }else{
        lcd.clear();
        lcd.setCursor(0,0);
        cerrado();
        lcd.print("Fuera de horario");
        delay(3000);
        mypassword = "";
        lcd.setCursor(0,0); 
       
    }
      lcd.clear();
      lcd.println("Ingrese password");
    }
  }
}

void abierto()
{
  digitalWrite(D3,HIGH);
  digitalWrite(D5,LOW);
  delay(2000);
  digitalWrite(D3, LOW); 
  digitalWrite(D5, HIGH);
  delay(1000);
  digitalWrite(D3, LOW); 
  digitalWrite(D5, LOW);
  
}

void cerrado()
{
  digitalWrite(D3,LOW);
  digitalWrite(D5,HIGH);
  
  /*digitalWrite(D3, HIGH); 
  digitalWrite(D5, LOW);*/
  
  digitalWrite(D3, LOW); 
  digitalWrite(D5, LOW);
  
}
