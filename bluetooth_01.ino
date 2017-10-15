#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int numerico, temp;
int volt = 3;
boolean apagado = true;
float pwm_p;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){    
    numerico = Serial.parseInt();                      
  }
    if(numerico == 100){
      apagado = true;  
    }else{
      apagado = false;
    }       
   if(apagado == false && numerico >= 15 && numerico <= 30){
      float pwm_p = ((30 * 50) / (float) numerico);
      pwm_p *= 0.01f;
      int send_pwm = pwm_p * 255;
      analogWrite(volt,send_pwm);
                  
      temp = dht.readTemperature();
      String cadena = String(temp);
      Serial.println(" "+cadena);
    }
    
    if(apagado){
        analogWrite(volt,0);
    }   
   delay(500);
}
