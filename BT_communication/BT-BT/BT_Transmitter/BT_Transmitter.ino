
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
 
#include "bt_utils.hpp"

#define BT_RX     2
#define BT_TX     3

#define MPU_ADDR 0x68

SoftwareSerial BTtransmiter(BT_RX,BT_TX);    // RX,TX
MPU6050 mpu(MPU_ADDR);

int ax, ay, az;
int gx, gy, gz;

char data[4] = {125,10, -10, '\0'};

long txtime = 0;

void setup()
{  
  Serial.begin(9600);
  BTtransmiter.begin(38400);
  Wire.begin();
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));

  
}

void loop()
{
  mpu.getAcceleration(&ax, &ay, &az);
  
  //Calcular los angulos de inclinacion
  float accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
  float accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
  Serial.println(accel_ang_x);
 Serial.println(accel_ang_y);
 
   if(millis() - txtime >  50)
   {
     static uint8_t i = 0;
    
     BTtransmiter.write(data[i]);

     if(i == 2)
     {
      i = 0;
      data[1] = (int)accel_ang_x;
      data[2] = (int)accel_ang_y;
     }else
       ++i;
      
     txtime = millis();
   }

}
