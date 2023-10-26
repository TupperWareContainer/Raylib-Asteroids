#ifndef ASTEROID_H
#define ASTEROID_H
#include <raylib.h>
#include "raymath.h"
#include "Projectile.h"
#include "math.h"
typedef struct Asteroid
{
    Vector2     pos;
    Vector2     velocity;  
    int         sides; 
    int         radiusMult; 
    float       rot;
    Color       color; 
    bool        active; 

} Asteroid;

bool CheckAsteroidHit(Projectile projectile, Asteroid asteroid); 

void RenderAsteroid(Asteroid asteroid);

void ShrinkAsteroid(Asteroid* asteroid, Vector2 playerPos); 

void UpdateAsteroid(Asteroid* asteroid, Vector2 playerPos); 

void ResetAsteroid(Asteroid* asteroid, Vector2 playerPos);

#define INACTIVE_ASTEROID CLITERAL(Asteroid){{0,0},{0,0},5,1,0,RED,false}

#define DEFAULT_ASTEROID_RADIUS 15

#define ASTEROID_MAX_SPEED 50

#define ASTEROID_MAX_RAD_MULT 3
#endif // ASTEROID_H