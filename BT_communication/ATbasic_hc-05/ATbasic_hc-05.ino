// Basic Bluetooth sketch HC-05_02_38400
// Connect the HC-05 module and communicate using the serial monitor
//
// The HC-05 defaults to commincation mode when first powered on.
// Needs to be placed in to AT mode
// After a factory reset the default baud rate for communication mode is 38400
//
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  BT RX to Arduino pin 3 (through a voltage divider)
//  BT TX to Arduino pin 2 (no need voltage divider)
 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX.
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
 
char c = ' ';
 
void setup() 
{
    // start th serial communication with the host computer
    Serial.begin(9600);
    serialFlush();
    Serial.println(" Arduino ready");
    delay(200);
 
    // start communication with the HC-05 using 38400
    BTserial.begin(38400);  
    Serial.println(" hc-05 Ready");
}
 
void loop()
{
 
     // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
 
        // mirror the commands back to the serial monitor
        // makes it easy to follow the commands
        Serial.write(c);   
        BTserial.write(c);  
    }
 
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}  
