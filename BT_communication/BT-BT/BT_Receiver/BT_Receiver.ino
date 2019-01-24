
#include<SoftwareSerial.h>

#define RIGHT1                 5
#define RIGHT2                 6
#define LEFT1                  9
#define LEFT2                  10
#define WAITING_INIT           0
#define WAITING_X              1
#define WAITING_Y              2
#define MAX_MOTORS_VALUE       255
#define MIN_MOTORS_VALUE       30
#define MAX_TURN               100
#define SQUARE_SIZE_X          10    // This value is remapping to analogWrite byte function
#define SQUARE_SIZE_Y          10

SoftwareSerial mySerial(2,3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX.
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
char c = ' ';
char state;
char x,y;

void Stop();
void calculateAndMove(int &x, int &y);

uint8_t testValue = 150;

void setup(){      
   Serial.begin(9600);        // Usb serial communication
   mySerial.begin(38400);     // Bluetooth serial communication
   state = WAITING_INIT;      // Initialize state
   pinMode(RIGHT1, OUTPUT);   // Set motors pins as outputs
   pinMode(RIGHT2, OUTPUT);
   pinMode(LEFT1, OUTPUT);
   pinMode(LEFT2, OUTPUT);
   Stop();
   delay(1000);
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
                      calculateAndMove((int)x, (int)y);
                    }
                    break;
          }
          
          delay(20);
        }
}

void right(int value){
  if(value>255)value=255;
  if(value<-255)value=-255;
  if(value>0){
    analogWrite(RIGHT1, value);
    analogWrite(RIGHT2, 0);
  }else{
    analogWrite(RIGHT1, 0);
    analogWrite(RIGHT2, abs(value)); 
  }
}

void rightDown(uint8_t value){
  analogWrite(RIGHT1, 0);
  analogWrite(RIGHT2, abs(value));
}

void left(int value){
  if(value>255)value=255;
  if(value<-255)value=-255;
  if(value>0){
    analogWrite(LEFT1, value);
    analogWrite(LEFT2, 0);
  }else{
    analogWrite(LEFT1, 0);
    analogWrite(LEFT2, abs(value)); 
  }
}

void leftDown(uint8_t value){
  analogWrite(LEFT1, 0);
  analogWrite(LEFT2, abs(value));
}

void Stop()
{
  analogWrite(RIGHT1, 0);
  analogWrite(RIGHT2, 0);
  analogWrite(LEFT1, 0);
  analogWrite(LEFT2, 0);
}

void calculateAndMove(int x, int y){

  int new_x = (x * MAX_MOTORS_VALUE) / 80;   // Mapping x (angle) in motors value range
  int new_y = (y * MAX_TURN) / 80;         // Mapping y (angle) in motors value range
  
  if(y > -SQUARE_SIZE_Y && y < SQUARE_SIZE_Y){
    new_y = 0;
  }
  if(x > -SQUARE_SIZE_X && x < SQUARE_SIZE_X){
    new_x = 0;
    new_y = new_y*2;
  }

  int sumxy = abs(new_x) + abs(new_y);
  int resxy = -sumxy;

  Serial.println(new_x);
  Serial.println(new_y);

  if(new_x>0){            // Go Ahead
    if(new_y>0){          // Turn right
      right(new_x);
      left(sumxy);
    }else if(new_y<0){    // Turn left
      right(sumxy);
      left(new_x);
    }else{                // Straight
      right(new_x);
      left(new_x);
    }
  }else if(new_x<0){      // Go Back
    if(new_y>0){          // Turn right
      right(new_x);
      left(resxy);
    }else if(new_y<0){    // Turn left
      right(resxy);
      left(new_x);
    }else{                // Straight
      right(new_x);
      left(new_x);
    }
  }else{                  // Static
    right(-new_y);
    left(new_y);
  }
}
