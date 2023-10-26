#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"


typedef struct Projectile
{
    Vector2     pos; 

    float       radius; 

    Vector2     velocity; 

    Color       color; 

    bool        active; 

} Projectile;


#define INACTIVE_PROJECTILE CLITERAL(Projectile){{0,0},0.0f,{0,0},BACKGROUND_COLOR,false} 

void UpdateProjectile(Projectile* projectile); 

void RenderProjectile(Projectile projectile); 


#endif //PROJECTILE_H