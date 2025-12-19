#include <Arduino.h>
#include <SPI.h>







//Pin definitions
int CS_PIN = 10;
int MOSI_PIN= 11;
int MISO_PIN=12;
int SCK_PIN = 13;

int a0 = 8;
int a1 = 9;
int EN = 7; 


void setup() {

  Serial.begin(115200);
  //Assign pin functions
  pinMode(CS_PIN,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(EN,OUTPUT);  

  digitalWrite(EN,HIGH);
  digitalWrite(a0,LOW);
  digitalWrite(a1,HIGH);


}









// unsigned long start_time = micros()

void loop() {
  
}