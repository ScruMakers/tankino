
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);// RX,TX

char c = ' ';

void setup(){  
  Serial.begin(9600);
  mySerial.begin(38400);
}
void loop(){
  c = 'a';
  int s = mySerial.write(c);
  if(s<0){
    Serial.print("Error("); Serial.print(s); Serial.print(") ");
  }else{
    Serial.print("Alright("); Serial.print(s); Serial.print(") ");
  }
  
  Serial.println("Enviado 'a'");
  delay(500);
}
