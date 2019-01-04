#ifndef MPU_H
#define MPU_H

#include "Vector.h"
#include <Wire.h>

const int MPU_addr = 0x68;
const int mpuPowerPin = 3;
const int mpuInitDelay = 10;
const int gateChangeAngle = 150;
const int angleTol = 30;

void turnOnMPU();
void turnOffMPU();
Vector readAcceleration(Vector* toUpdate);

#endif
