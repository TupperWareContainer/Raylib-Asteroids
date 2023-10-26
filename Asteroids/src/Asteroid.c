#include "Asteroid.h"

bool CheckAsteroidHit(Projectile projectile, Asteroid asteroid){
    return CheckCollisionCircles(asteroid.pos,asteroid.radiusMult * DEFAULT_ASTEROID_RADIUS,projectile.pos,projectile.radius); 
}

void RenderAsteroid(Asteroid asteroid){
    DrawPolyLines(asteroid.pos,asteroid.sides,asteroid.radiusMult * DEFAULT_ASTEROID_RADIUS,asteroid.rot,asteroid.color); 
}

void ShrinkAsteroid(Asteroid* asteroid, Vector2 playerPos){
    asteroid->radiusMult--; 
    if(asteroid-> radiusMult <= 0){
        ResetAsteroid(asteroid,playerPos); 
    }
}

void UpdateAsteroid(Asteroid* asteroid, Vector2 playerPos){
    asteroid->pos.x += asteroid->velocity.x * GetFrameTime(); 
    asteroid->pos.y += asteroid->velocity.y * GetFrameTime(); 
    float rad = asteroid->radiusMult * DEFAULT_ASTEROID_RADIUS; 
    if(asteroid->pos.x - rad > GetRenderWidth() || asteroid->pos.x + rad < 0){
        ResetAsteroid(asteroid,playerPos);
    }
    else if(asteroid->pos.y - rad > GetRenderHeight() || asteroid->pos.y + rad < 0){
        ResetAsteroid(asteroid,playerPos); 
    }
}

void ResetAsteroid(Asteroid* asteroid,Vector2 playerPos){
    asteroid->pos.x = sinf(GetRandomValue(0,2 * PI)) * GetRenderHeight(); 
    asteroid->pos.y = sinf(GetRandomValue(0,2 * PI)) * GetRenderHeight();
    asteroid->velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(asteroid->pos,playerPos)),-ASTEROID_MAX_SPEED); 
    asteroid->radiusMult = GetRandomValue(1,ASTEROID_MAX_RAD_MULT); 
    asteroid->active = true; 
}