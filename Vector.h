#ifndef VECTOR_H
#define VECTOR_H

//vector used for acceleration information
struct Vector
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
  
  Vector()
  {
    x=0;
    y=0;
    z=0;
  }

  Vector(int xInit, int yInit, int zInit)
  {
    x = xInit;
    y = yInit;
    z = zInit;
    calculateMagnitude();
  }  

  //debug print
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

  //mutators to update members
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

double angleBetweenVectors(Vector initial, Vector current);

#endif
