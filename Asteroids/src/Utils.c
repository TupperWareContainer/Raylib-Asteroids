#include "Utils.h"

float ModifiedVector2Angle(Vector2 origin, Vector2 v1){
    Vector2 v1Transform = {v1.x - origin.x, v1.y - origin.y}; 

    float angle = RAD2DEG * atan2(v1Transform.y, v1Transform.x); 

    return angle; 
} 

Vector2 RotatePointByAngle(Vector2 origin, Vector2 point, float angleDegrees){
    Vector2 modTransform = {point.x - origin.x, point.y - origin.y}; 
    
    float newY = modTransform.x * cos(angleDegrees * DEG2RAD) - modTransform.y * sin(angleDegrees * DEG2RAD); 
    float newX = modTransform.x * sin(angleDegrees * DEG2RAD) + modTransform.y * cos(angleDegrees *DEG2RAD); 

    modTransform.x = newX + origin.x; 
    modTransform.y = newY + origin.y; 

    return modTransform;  
}