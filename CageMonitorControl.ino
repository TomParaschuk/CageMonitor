#include<Wire.h>

//MPU
const int MPU_addr=0x68;
const int mpuPowerPin = 3;
const int pinOnDelay = 10;

//reset button
const int buttonPin = 2;
const int buttonState = 0;

//constants
const int waitTime = 1000;
const int gateChangeAngle = 150;
const int angleTol = 30;

//acceleration vector from MPU
//used to find the angle of the closing door
struct vector
{
  int x;
  int y;
  int z;
  double magnitude;
  
  void calculateMagnitude()
  {
    magnitude = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    return;
  }
  
  vector()
  {
    x=0;
    y=0;
    z=0;
  }
    
  vector(int xInit, int yInit, int zInit)
  {
    x = xInit;
    y = yInit;
    z = zInit;
    calculateMagnitude();
  }  

  
  output()
  {
    if(!Serial)
    {
      Serial.begin(9600);
    }
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(", y: ");
    Serial.print(y);
    Serial.print(", z: ");
    Serial.print(z);
    Serial.print(", magnitude: ");
    Serial.println(magnitude);
  }

  setX(int newX)
  {
    x = newX;
    calculateMagnitude();
  }

  setY(int newY)
  {
    y = newY;
    calculateMagnitude();
  }

  setZ(int newZ)
  {
    z = newZ;
    calculateMagnitude();
  }

  setAll(int newX, int newY, int newZ)
  {
    x = newX;
    y = newY;
    z = newZ;
    calculateMagnitude();
  }
  
};

//acceleration vectors of the cage
vector initAccel;
vector currentAccel;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(mpuPowerPin, OUTPUT);
  //pinMode(
  
  pinMode(SDA, INPUT);  // remove internal pullup
    pinMode(SCL, INPUT);  // remove internal pullup
  
  turnOnMPU(); 

  

  
  Serial.begin(9600);
 
  while(digitalRead(buttonPin) == 0)
  {
  }

  //wait for the first button press

  
  readAcceleration(&initAccel);
  //initAccel.output();

  turnOffMPU();
} 


void loop()
{ 
  delay(waitTime);

  turnOnMPU();
  
  readAcceleration(&currentAccel);
  //currentAccel.output();
  double angle = angleBetweenVectors(initAccel, currentAccel);
  Serial.print("angle between vectors: ");
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

double angleBetweenVectors(vector initial, vector current)
{
  double dotProduct = (double)initial.x*(double)current.x+(double)initial.y*(double)current.y+(double)initial.z*(double)current.z;  
  double thetaRad = fabs(acos(dotProduct/(initial.magnitude*current.magnitude)));
  return thetaRad*180/PI;
}

vector readAcceleration(vector* toUpdate)
{
  int acX;
  int acY;
  int acZ;
  
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  acX=Wire.read()<<8|Wire.read();   
  acY=Wire.read()<<8|Wire.read(); 
  acZ=Wire.read()<<8|Wire.read();
  
  toUpdate->setAll(acX,acY,acZ);
}

void turnOnMPU()
{
  if(digitalRead(mpuPowerPin) == LOW)
  {     
    digitalWrite(mpuPowerPin,HIGH);
    delay(pinOnDelay);


    Wire.begin();
    Wire.beginTransmission(MPU_addr); 
    Wire.write(0x6B); 
    Wire.write(0); 
    Wire.endTransmission(true);
    
    delay(1000);
  }
}

void turnOffMPU()
{
  if(digitalRead(mpuPowerPin) == HIGH)
  {
    digitalWrite(mpuPowerPin,LOW);
    Wire.end();
    pinMode(SDA, INPUT);  // remove internal pullup
    pinMode(SCL, INPUT);  // remove internal pullup
  }
}
