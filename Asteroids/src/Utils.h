#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"
#include <math.h>

float ModifiedVector2Angle(Vector2 origin, Vector2 v1);  

Vector2 RotatePointByAngle(Vector2 origin, Vector2 point, float angleDegrees); 
#endif // UTILS_H