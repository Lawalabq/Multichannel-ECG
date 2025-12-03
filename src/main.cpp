#include <Arduino.h>
#include <SPI.h>


//Pin definitions
int CS_PIN = 10;
int MOSI_PIN= 11;
int MISO_PIN=12;
int SCK_PIN = 13;

int A0 = 2;
int A1 = 3;
int EN = 4;


//Differential Pairs
int16_t pair1 =0;
int16_t pair2 =0;
int16_t pair3 =0;
int16_t pair4 =0;


void setup() {
  //Assign pin functions
  pinMode(CS_PIN,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(EN,OUTPUT);

// initialize SPI:
  SPI.begin(); 
  SPI.beginTransaction(SPISettings(2500000, MSBFIRST, SPI_MODE3));

}



unsigned long start_time = micros();
byte start_num =1;





void loop() {
  if (start_time-micros()% 500 == 0) { //2000 Hz
    start_time = micros();
    
    int A0_val = ((start_num)&1);
    int A1_val = ((start_num>>1)&1);
    int EN_val = ((start_num>>2)&1);

    digitalWrite(A0,A0_val);
    digitalWrite(A1,A1_val);
    digitalWrite(EN,EN_val);

    start_num=start_num+2;
    start_num = start_num%8;
  }

  digitalWrite(CS_PIN,LOW);
  delayNanoseconds(20);
  
  byte data_buffer[3];
  SPI.transfer(&data_buffer,3);

  u_int16_t final=0;

  u_int16_t first_byte = data_buffer[0];
  u_int16_t second_byte = data_buffer[1];
  u_int16_t third_byte = data_buffer[1];

  first_byte= first_byte & 0b11; // first two bits

  third_byte = third_byte>>2; // last 6 bits

  final = final | first_byte<<14;
  final = final | second_byte<<6;
  final = final | third_byte;

  int16_t signedCode = (int16_t) final;  
  float value = (signedCode / 32768.0) * 5.0;

  digitalWrite(CS_PIN,HIGH);
  delayNanoseconds(400);

  switch (start_num)
  {
  case 1:
    pair1=value;
    break;
  case 3:
    pair2=value;
    break;
  case 5:
    pair3=value;
    break;
    case 7:
    pair4=value;
    break;
  default:
    break;
  }

}

