
#include <SoftwareSerial.h>
#include "bt_utils.hpp"

#define BT_RX     2
#define BT_TX     3

SoftwareSerial BTtransmiter(BT_RX,BT_TX);    // RX,TX

char *data = "Hello World\r\n";


void setup()
{  
  Serial.begin(9600);
  BTtransmiter.begin(38400);
}

void loop()
{
  int s = write_stream(BTtransmiter, data);
  delay(100);
  
  if(s<0){
    Serial.print("Error("); Serial.print(s); Serial.print(") ");
  }else{
    Serial.print("Alright("); Serial.print(s); Serial.print(") ");
    Serial.println("Enviado 'a'");
  }
  
}
