#include "MPU.h"
#include "Vector.h"
#include "UserInterface.h"

//debug
const int debugWaitTime = 1000;

//vectors to record MPU acceleration
Vector initAccel;
Vector currentAccel;

void setup()
{
  //configure the reset button pin
  pinMode(buttonPin, INPUT);
  //configure the MPU power pin
  pinMode(mpuPowerPin, OUTPUT);
  
  turnOnMPU();

  //for debug
  Serial.begin(9600);
 
  while(digitalRead(buttonPin) == 0);

  //wait for the first button press
  
  readAcceleration(&initAccel);
  //initAccel.output();

  turnOffMPU();
} 


void loop()
{ 
  delay(debugWaitTime);

  turnOnMPU();
  
  readAcceleration(&currentAccel);
  //currentAccel.output();
  double angle = angleBetweenVectors(initAccel, currentAccel);
  Serial.print("angle between Vectors: ");
  Serial.println(angle);
  if(fabs(angle - (double)gateChangeAngle) < angleTol)
  {
    Serial.println("closed");
  }
  else
  {
    Serial.println("still open");
  }

  turnOffMPU();
  
}
