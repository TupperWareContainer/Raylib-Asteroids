#pragma once
#include "raylib.h"
#include <vector>


#define B_BLOCK_WIDTH 10
#define B_BLOCK_HEIGHT 10

#define SNAKE_COLOR RAYWHITE

/// @brief Body blocks are what make up the body of the snake,
/// the snake consists of a list of body blocks that update 
/// their position to be that of a previous position of the snake 
struct BodyBlock{
    double posX;
    double posY;      

    void Render(){
        DrawRectangle(posX,posY,B_BLOCK_WIDTH,B_BLOCK_HEIGHT,SNAKE_COLOR); 
    }

};
struct Snake{

    double posX;
    double posY; 
    bool isGameOver = false; 

    std::vector<BodyBlock> blocks = std::vector<BodyBlock>(); 

    Snake(double posX, double posY){
        this->posX = posX; 
        this->posY = posY; 

        blocks.push_back(
            BodyBlock{posX,posY}                    /// head
        );

        blocks.push_back(
            BodyBlock{posX,posY - B_BLOCK_HEIGHT}   /// body
        );

    }

    void AddBlock(){
        int maxIndex = blocks.size() - 1; 

        blocks.push_back(
            BodyBlock{blocks[maxIndex].posX,blocks[maxIndex].posY}
        );
    }

    void UpdateBody(){
        for(int i = blocks.size() - 1; i >= 1; i--){
            if(blocks[i].posX == posX && blocks[i].posY == posY){
                isGameOver = true; 
                break;
            }

            blocks[i].posX = blocks[i - 1].posX; 
            blocks[i].posY = blocks[i - 1].posY; 
        }; 

        blocks[0].posX = posX;
        blocks[0].posY = posY; 
    }

    void MoveSnake( int dX, int dY){
        posX += dX * B_BLOCK_WIDTH;
        posY += dY * B_BLOCK_HEIGHT;

    }

    void Render(){
        

        for(int i = 0; i< blocks.size(); i++){
            blocks[i].Render(); 
        }
    }
}; 

struct Apple
{
    double posX;
    double posY; 

    Apple(int screenWidth, int screenHeight){
        RandomizePosition(screenWidth,screenHeight); 
    }


    void RandomizePosition(int wWidth, int wHeight){
        int randX = rand() % wWidth; 
        int randY = rand() % wHeight; 

        randX -= randX % 10; 
        randY -= randY % 10; 

        posX = randX; 
        posY = randY; 
    }

    void Render(){
        DrawRectangle(posX,posY,B_BLOCK_WIDTH,B_BLOCK_HEIGHT,RED); 
    }

    bool CheckIntersect(double x, double y){
        return CheckCollisionPointRec(
                Vector2{(float)x,(float)y},
                Rectangle{(float)posX,(float)posY,B_BLOCK_WIDTH,B_BLOCK_HEIGHT}
                ); 
    }
};

enum Direction{
    Up,
    Down,
    Left,
    Right,
    None
};
