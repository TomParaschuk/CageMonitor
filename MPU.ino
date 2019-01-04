#include "MPU.h"

//safely turn on MPU and I2C
void turnOnMPU()
{
  //check if MPU on already
  if(digitalRead(mpuPowerPin) == LOW)
  {
    //supply power to the digital pin
    digitalWrite(mpuPowerPin,HIGH);

    //wait for startup
    delay(mpuInitDelay);

    //configure the I2C
    Wire.begin();
    //transmit initialization information
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); 
    Wire.write(0); 
    Wire.endTransmission(true);

    //wait for initialization information
    delay(mpuInitDelay);
  }
}

//safely terminate MPU and I2C
void turnOffMPU()
{
  //check if MPU off already
  if(digitalRead(mpuPowerPin) == HIGH)
  {
    //turn off power through digital pin
    digitalWrite(mpuPowerPin,LOW);
    //terminate I2C
    Wire.end();
    pinMode(SDA, INPUT);  // remove internal pullup
    pinMode(SCL, INPUT);  // remove internal pullup
  }
}

//read acceleration into a vector
Vector readAcceleration(Vector* toUpdate)
{
  //variables to read in acceleration
  int acX;
  int acY;
  int acZ;

  //receive information in acceleration registers
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  acX=Wire.read()<<8|Wire.read();   
  acY=Wire.read()<<8|Wire.read(); 
  acZ=Wire.read()<<8|Wire.read();

  //update the vector given
  toUpdate->setAll(acX,acY,acZ);
}
