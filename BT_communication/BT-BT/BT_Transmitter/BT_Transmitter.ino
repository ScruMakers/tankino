
#include <SoftwareSerial.h>

#define BT_RX     2
#define BT_TX     3

SoftwareSerial BTtransmiter(BT_RX,BT_TX);    // RX,TX

char *data = "Hello World\n";
char *c;

void setup()
{  
  Serial.begin(9600);
  BTtransmiter.begin(38400);
  c=data;
}

void loop()
{
  int s = BTtransmiter.write(*c);
  
/*  if(s<0){
    Serial.print("Error("); Serial.print(s); Serial.print(") ");
  }else{
    Serial.print("Alright("); Serial.print(s); Serial.print(") ");
    Serial.println("Enviado 'a'");
  }
*/

  if(*c == '\n')
  {
    c=data;
    delay(500);
  }else
  {
    c=c+1;
  }
  
  
  
  delay(5);
}
