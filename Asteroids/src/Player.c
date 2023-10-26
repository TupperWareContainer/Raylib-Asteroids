#include "Player.h"
#include "raymath.h"
#include "Utils.h"
#include "Projectile.h"

void RenderPlayer(Player player){
    DrawTriangleLines(player.p1,player.p2,player.p3,player.color);
}


void ApplyAcceleration(Player* player, int aX, int aY){
    player->vX += aX * GetFrameTime(); 
    player->vY += aY * GetFrameTime(); 
}

void UpdatePlayer(Player* player, bool doMouseRot, float rotBank){
    player->pos.x = player->pos.x + player->vX; 
    player->pos.y = player->pos.y + player->vY; 

    if(doMouseRot) player->angle = -ModifiedVector2Angle(player->pos, GetMousePosition()); 
    else player -> angle = rotBank;

    UpdatePoints(player); 

}

void UpdatePoints(Player* player){
    Vector2 p1 = {player->pos.x, player->pos.y + player->radius};
    Vector2 p2 = {player->pos.x - player->radius, player->pos.y - player->radius};
    Vector2 p3 = {player->pos.x + player->radius, player->pos.y - player->radius}; 

    player->p1 = RotatePointByAngle(player->pos,p1,player->angle); 
    player->p2 = RotatePointByAngle(player->pos,p2,player->angle); 
    player->p3 = RotatePointByAngle(player->pos,p3,player->angle); 
}

void FireProjectile(Player player, Projectile projectilePool[], int numProjectiles){
    for(int i = 0; i < numProjectiles; i++){
        if(!projectilePool[i].active){
            projectilePool[i].pos = player.p1; 
            projectilePool[i].radius = PLAYER_PROJECTILE_RADIUS; 
            projectilePool[i].velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(player.p1,player.pos)),PLAYER_PROJECTILE_SPEED); 
            projectilePool[i].color = PLAYER_PROJECTILE_COLOR; 
            projectilePool[i].active = true; 
            break; 
        }
    }
}


Player PlayerInit(Vector2 pos, float vX, float vY, float radius, Color color){
    Vector2 p1 = {pos.x, pos.y - radius};
    Vector2 p2 = {pos.x - radius, pos.y + radius};
    Vector2 p3 = {pos.x + radius, pos.y + radius}; 

    Player player = {pos,vX,vY,radius,0,color,p1,p2,p3}; 
}