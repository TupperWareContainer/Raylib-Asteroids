#ifndef PLAYER_H
#define PLAYER_H 

#include <raylib.h>
#include "Projectile.h"
#include "Utils.h"

#define PLAYER_PROJECTILE_RADIUS 10
#define PLAYER_PROJECTILE_SPEED 500
#define PLAYER_PROJECTILE_COLOR BLUE

typedef struct Player{

Vector2 pos; 

float   vX; 

float   vY; 

float   radius; 

float   angle; 

Color   color; 

Vector2 p1; 

Vector2 p2; 

Vector2 p3; 


} Player; 

void RenderPlayer(Player player); 


void ApplyAcceleration(Player* player, int aX, int aY); 

void UpdatePlayer(Player* player, bool doMouseRot, float rotBank); 

Player PlayerInit(Vector2 pos, float vX, float vY, float radius, Color color); 

void UpdatePoints(Player* player); 

void FireProjectile(Player player, Projectile projectilePool[], int numProjectiles); 

#endif // PLAYER_H