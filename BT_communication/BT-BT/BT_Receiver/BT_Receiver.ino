
#include<SoftwareSerial.h>

// se define al Pin2 como RX, Pin3 como TX
SoftwareSerial mySerial(2,3);

char c = ' ';

void setup(){      
 
   Serial.begin(9600);
   mySerial.begin(9600);
   
}

void loop() {

        if(mySerial.available()>0){
          c=mySerial.read();
          if(c<0){
            Serial.print("Error (<0) ");
          }else{
            Serial.print("Alright (>0) ");
          }
          
          Serial.print("Recibido: ");
          Serial.println(c);
          delay(500);
        }

}
