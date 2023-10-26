#include <iostream>
#include <raylib.h>
#include "snake.h"
#include <string>

#define W_WIDTH 400
#define W_HEIGHT 400

#define TICKRATE 15

int main(int argc, char const *argv[])
{   
    std::cout << "Hello, World!" << std::endl;

    std::cout << sizeof(BodyBlock) << std::endl; 
    std::cout << sizeof(Snake) << std::endl; 

    

    InitWindow(W_WIDTH,W_HEIGHT,"Snake"); 
    SetTargetFPS(60); 
Start:  

    Snake snake = Snake(W_WIDTH / 2, W_HEIGHT / 2);
    Apple apple = Apple(W_WIDTH,W_HEIGHT); 


    int dX = 0;
    int dY = 1; 

    Direction dir; 

    double step = 0; 
    int length = 1; 

    std::string stats = ""; 
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            
            if(snake.isGameOver) goto GameOver; 

            if(IsKeyPressed(KEY_W) && dir != Down){
                dir = Up; 
                dY = -1; 
                dX = 0; 
            }
            else if(IsKeyPressed(KEY_S) && dir != Up){
                dir = Down;  
                dY = 1; 
                dX = 0; 
            }
            // else{
            //     dY = 0;
            // }

            if(IsKeyPressed(KEY_D) && dir != Right){
                dir = Left; 
                dX = 1; 
                dY = 0; 
            }
            else if(IsKeyPressed(KEY_A) && dir != Left){
                dir = Right; 
                dX = -1; 
                dY = 0; 
            }
            // else{
            //     dX = 0; 
            // }

            step += GetFrameTime(); 

            if((dX != 0 || dY != 0) && step >= 1.0 / TICKRATE){
                snake.MoveSnake(dX,dY); 
                
                if(apple.CheckIntersect(snake.posX,snake.posY)){
                    apple.RandomizePosition(W_WIDTH,W_HEIGHT); 
                    snake.AddBlock(); 
                    length++; 
                }
                if(snake.posX > W_WIDTH || snake.posY  > W_HEIGHT || snake.posX < 0 || snake.posY < 0){
                    snake.isGameOver = true; 
                }


                snake.UpdateBody(); 
                step = 0; 
            }            

            snake.Render();
            apple.Render(); 
            stats = "FPS: " + std::to_string(GetFPS()) + "\n" +
                    "Snake Pos: {" + std::to_string(snake.posX) + ", " + std::to_string(snake.posY) + "}\n" +
                    "Score: " + std::to_string(length) + "\n"; 
            DrawText(stats.c_str(),20,20,12,GREEN);  
            
            goto DrawEnd; 
GameOver:
            DrawText("GAME OVER\nPress \"r\" to restart",W_WIDTH / 2 - 24 * 5, W_HEIGHT / 2,24, RED); 
            if(IsKeyPressed (KEY_R)){
                goto Start; 
            }

DrawEnd:    EndDrawing(); 
    }
    CloseWindow();
    return 0; 
}
