
#include<SoftwareSerial.h>

#define IN1                 5
#define IN2                 6
#define IN3                 9
#define IN4                 10
#define WAITING_INIT        0
#define WAITING_X           1
#define WAITING_Y           2
#define MAX_MOTORS_VALUE    255
#define MIN_MOTORS_VALUE    30
#define MAX_TURN            50
#define SQUARE_SIZE         28    // This value is remapping to analogWrite byte function

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
                      //Serial.print("X: ");
                      //Serial.print((int)x);
                      //Serial.print("   Y: ");
                      //Serial.println((int)y);
                      calculateAndMove((int)x, (int)y);
                    }
                    break;
          }
          
          delay(5);
        }
}

void rightUp(uint8_t value){
  analogWrite(IN1, value);
  analogWrite(IN2, 0);
}

void rightDown(uint8_t value){
  analogWrite(IN1, 0);
  analogWrite(IN2, value);
}

void leftUp(uint8_t value){
  analogWrite(IN3, value);
  analogWrite(IN4, 0);
}

void leftDown(uint8_t value){
  analogWrite(IN3, 0);
  analogWrite(IN4, value);
}

void calculateAndMove(int x, int y){

  int new_x = x * MAX_MOTORS_VALUE / 90;   // Mapping x (angle) in motors value range
  int new_y = y * MAX_TURN / 90;         // Mapping x (angle) in motors value range
  

  if(x > -SQUARE_SIZE && x < SQUARE_SIZE){
    int new_x = 0;
  }
  if(y > -SQUARE_SIZE && y < SQUARE_SIZE){
    int new_y = 0;
  }

  if(new_x > 0){    // Go forward
    if(new_y > 0){  // Turn right
      rightUp(new_x - new_y); 
      leftUp(new_x + new_y);
    }else{          // Turn left
      rightUp(new_x + new_y);
      leftUp(new_x - new_y);
    }
  }else{            // Go back
    if(new_y > 0){  // Turn right
      rightDown(new_x - new_y); 
      leftDown(new_x + new_y);
    }else{          // Turn left
      rightDown(new_x + new_y);
      leftDown(new_x - new_y);
    }
  }

}
