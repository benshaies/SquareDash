#include <raylib.h>
#include "player.h"

const int screenWidth = 1750;
const int screenHeight = 1000;

//Create player variable
Player player;

void draw(){
    BeginDrawing();

    ClearBackground(WHITE);
    drawPlayer(&player);

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "Square Dash");
    SetTargetFPS(60);

    //Player init
    playerInit(&player);
}

int main(void){
    
    //Call init funciton
    init();

    while(!WindowShouldClose()){
        draw();
        playerCollisions(&player);
        playerMovement(&player);
    }
}