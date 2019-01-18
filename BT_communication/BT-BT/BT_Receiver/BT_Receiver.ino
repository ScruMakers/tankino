
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
#define MAX_TURN               50
#define SQUARE_SIZE_X          28    // This value is remapping to analogWrite byte function
#define SQUARE_SIZE_Y          5

// se define al PRIGHT2 como RX, PLEFT1 como TX
SoftwareSerial mySerial(2,3);
char c = ' ';
char state;
char x,y;


void Stop();
void calculateAndMove(int &x, int &y);

uint8_t testValue = 150;

void setup(){      
   Serial.begin(9600);
   mySerial.begin(38400);
   state = WAITING_INIT;

  Serial.println(sizeof(int));
  delay(10000);
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

    

/*  rightUp(testValue);
  leftUp(testValue);

  delay(1000);
  
  rightDown(testValue);
  leftDown(testValue);

  delay(1000);
  
  rightUp(testValue);
  leftDown(testValue);

  
  delay(1000);
  
  rightDown(testValue);
  leftUp(testValue);

  delay(1000);

  Stop();

  delay(1000);*/
        
}

void rightUp(uint8_t value){
  analogWrite(RIGHT1, abs(value));
  analogWrite(RIGHT2, 0);
}

void rightDown(uint8_t value){
  analogWrite(RIGHT1, 0);
  analogWrite(RIGHT2, abs(value));
}

void leftUp(uint8_t value){
  analogWrite(LEFT1, abs(value));
  analogWrite(LEFT2, 0);
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

  int new_x = x * MAX_MOTORS_VALUE / 90;   // Mapping x (angle) in motors value range
  int new_y = y * MAX_TURN / 90;         // Mapping x (angle) in motors value range
  

  if(x > -SQUARE_SIZE_X && x < SQUARE_SIZE_X){
    new_x = 0;
  }
  if(y > -SQUARE_SIZE_Y && y < SQUARE_SIZE_Y){
    new_y = 0;
  }

  Serial.println(new_x);
  Serial.println(new_y);

  if(new_x > 0){    // Go forward
    if(new_y > 0){  // Turn right
      Serial.println("++!");
      rightUp(new_x - new_y); 
      leftUp(new_x + new_y);
    }else{          // Turn left
      Serial.println("+-!");
      rightUp(new_x + new_y);
      leftUp(new_x - new_y);
    }
  }else{            // Go back
    if(new_y > 0){  // Turn right
      Serial.println("-+!");
      rightDown(new_x - new_y); 
      leftDown(new_x + new_y);
    }else{          // Turn left
      Serial.println("00!");
      rightDown(new_x + new_y);
      leftDown(new_x - new_y);
    }
  }

}
