
#include<SoftwareSerial.h>

#define WAITING_INIT 0
#define WAITING_X 1
#define WAITING_Y 2
// se define al Pin2 como RX, Pin3 como TX
SoftwareSerial mySerial(2,3);
char c = ' ';
char state;
char x,y;

void setup(){      
   Serial.begin(9600);
   mySerial.begin(38400);
   state = WAITING_INIT;
}

void loop() {
        if(mySerial.available()>0){
          c = mySerial.read();
          switch(state){
                case WAITING_INIT:
                    if (c==125)state=WAITING_X;
                    break;
                case WAITING_X:
                    if(c==125){
                      state = WAITING_X;
                    }else{
                      x=c;
                      state = WAITING_Y;
                    }
                    break;
                case WAITING_Y:
                    if(c==125){
                      state = WAITING_X;
                    }else{
                      y=c;
                      state = WAITING_INIT;
                      Serial.print("X: ");
                      Serial.print((int)x);
                      Serial.print("   Y: ");
                      Serial.println((int)y);
                    }
                    break;
          }
          
          delay(5);
        }
}
