#include "Projectile.h"

void UpdateProjectile(Projectile* projectile){
    projectile->pos.x += projectile->velocity.x * GetFrameTime(); 
    projectile->pos.y += projectile->velocity.y * GetFrameTime(); 

    if((projectile->pos.x - projectile->radius > GetRenderWidth()|| projectile->pos.x + projectile->radius < 0) && projectile->active)
    {
        projectile->active = false; 
    }
    else if((projectile->pos.y - projectile->radius > GetRenderHeight() || projectile->pos.y + projectile->radius < 0) && projectile->active){
        projectile->active = false; 
    }
}

void RenderProjectile(Projectile projectile){
    DrawCircleLines(projectile.pos.x,projectile.pos.y,projectile.radius,projectile.color); 
}