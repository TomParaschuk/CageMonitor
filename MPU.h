#ifndef MPU_H
#define MPU_H

#include "Vector.h"
#include <Wire.h>
#include "Utilities.h"

const int MPU_addr = 0x68;
const int mpuPowerPin = 3;
const int mpuInitDelay = 100;
const int gateChangeAngle = 150;
const int angleTol = 30;

void turnOnMPU();
void turnOffMPU();
void readAcceleration(Vector* toUpdate);
void powerAndReadAcceleration(Vector* toUpdate);

#endif
