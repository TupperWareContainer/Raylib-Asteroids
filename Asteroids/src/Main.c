#include <stdio.h> 
#include <raylib.h>
#include "Player.h"
#include "Asteroid.h"

//-- RENDER SETTINGS --//
#define WINDOW_WIDTH 700 
#define WINDOW_HEIGHT 700 
#define BACKGROUND_COLOR BLACK
#define TICKRATE 50 

//-- CONTROLS --//
#define UP      KEY_W 
#define DOWN    KEY_S
#define LEFT    KEY_A
#define RIGHT   KEY_D
#define STOP    KEY_X
#define SHOOT   KEY_SPACE
#define RLEFT   KEY_Q
#define RRIGHT  KEY_E


//-- PLAYER SETTINGS --//
#define IMPULSE             30 
#define MOUSE_ROT           true
#define ROTATION_IMPULSE    10

//-- GAME SETTINGS --//
#define MAX_PROJECTILES     40 
#define MAX_ASTEROIDS       15


//@TODO: dispose of projectiles after they hit vertical limit

int main(int argc, char const *argv[])
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids"); 

    SetTargetFPS(60); 

    Player p = {{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, 0.0f, 0.0f, 20.0f, 0.0f, RAYWHITE}; 

    Asteroid asteroids[MAX_ASTEROIDS]; 

    Projectile projectiles[MAX_PROJECTILES]; 

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        asteroids[i] = INACTIVE_ASTEROID;   
        ResetAsteroid(&asteroids[i],p.pos); 
    }

    for(int i = 0; i < MAX_PROJECTILES; i++){
        projectiles[i] = INACTIVE_PROJECTILE; 
    } 

    float gameTimer = 0.0f; 

    float rotBank = 0.0f; 

    while(!WindowShouldClose()){
        
        if(IsKeyPressed(SHOOT)){
            FireProjectile(p, projectiles,MAX_PROJECTILES); 
        }

        if(gameTimer >= 1.0/TICKRATE){
            gameTimer = 0.0f; 
            if(IsKeyDown(UP)){
                ApplyAcceleration(&p,0,-1.0 * IMPULSE); 
            }
            else if(IsKeyDown(DOWN)){
                ApplyAcceleration(&p,0,1.0 * IMPULSE); 
            }

            if(IsKeyDown(LEFT)){
                ApplyAcceleration(&p,-1.0 * IMPULSE,0); 
            }
            else if (IsKeyDown(RIGHT)){
                ApplyAcceleration(&p,1.0 * IMPULSE,0.0);
            }

            if(!MOUSE_ROT){
                if(IsKeyDown(RLEFT)){
                    rotBank += ROTATION_IMPULSE; 
                }
                else if(IsKeyDown(RRIGHT)){
                    rotBank -= ROTATION_IMPULSE; 
                }
            }

            if(IsKeyDown(STOP)){
                ApplyAcceleration(&p,p.vX * -IMPULSE * 0.25, p.vY * -IMPULSE * 0.25);
            }

           

            UpdatePlayer(&p, MOUSE_ROT, rotBank); 

            if(p.pos.x > WINDOW_WIDTH + p.radius){
                p.pos.x = -p.radius;
            }
            else if(p.pos.x < -p.radius){
                p.pos.x = WINDOW_WIDTH + p.radius; 
            }

            if(p.pos.y > WINDOW_HEIGHT + p.radius){
                p.pos.y = -p.radius; 
            }
            else if(p.pos.y < -p.radius){
                p.pos.y = WINDOW_HEIGHT + p.radius; 
            }

            for(int i = 0; i < MAX_PROJECTILES; i++){
                if(projectiles[i].active == true){
                    UpdateProjectile(&projectiles[i]); 
                }
            }

            for(int i = 0; i < MAX_ASTEROIDS; i++){
                if(asteroids[i].active){
                    UpdateAsteroid(&asteroids[i],p.pos); 
                }
            }

            for(int i = 0; i < MAX_ASTEROIDS; i++){
                if(asteroids[i].active){
                    for(int proj = 0; proj < MAX_PROJECTILES; proj++){
                        if(projectiles[proj].active){
                            if(CheckAsteroidHit(projectiles[proj],asteroids[i])){
                                ShrinkAsteroid(&asteroids[i],p.pos); 
                                projectiles[proj] = INACTIVE_PROJECTILE; 
                            }
                        }
                    }
                }
            }
        }


        BeginDrawing(); 

            ClearBackground(BACKGROUND_COLOR); 

            RenderPlayer(p); 

            for(int i = 0; i < MAX_PROJECTILES; i++){
                if(projectiles[i].active == true){
                    RenderProjectile(projectiles[i]); 
                }
            }
            for(int i = 0; i < MAX_ASTEROIDS; i++){
                if(asteroids[i].active) RenderAsteroid(asteroids[i]); 
            }

            ListProjectiles(projectiles); 
            ListAsteroids(asteroids); 
        EndDrawing(); 

        gameTimer += GetFrameTime(); 
    }
    CloseWindow(); 

    return 0;
}

void ListProjectiles(Projectile projectiles[]){
    int numActive = 0; 
    int numInactive = 0; 

    for(int i = 0; i < MAX_PROJECTILES; i++){
        if(projectiles[i].active) numActive++; 
        else numInactive++; 
    }
    char activeStr[12];
    char inactiveStr[12];  
    sprintf(activeStr, "Active: %d",numActive);
    sprintf(inactiveStr,"Inactive: %d",numInactive); 

    DrawText("Projectiles:",10,10,12,GREEN); 
    DrawText(activeStr,10,20,12,GREEN); 
    DrawText(inactiveStr,10,30,12,GREEN); 
}

void ListAsteroids(Asteroid asteroids[]){
    int numActive = 0; 
    int numInactive = 0;

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(asteroids[i].active) numActive++; 
        else numInactive++; 
    }
    char activeStr[12];
    char inactiveStr[12];  
    sprintf(activeStr, "Active: %d",numActive);
    sprintf(inactiveStr,"Inactive: %d",numInactive); 

    DrawText("Asteroids:",10,50,12,YELLOW); 
    DrawText(activeStr,10,60,12,YELLOW); 
    DrawText(inactiveStr,10,70,12,YELLOW); 
}
