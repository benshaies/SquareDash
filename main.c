#include <raylib.h>
#include "player.h"
#include "level.h"

const int screenWidth = 1500;
const int screenHeight = 750;

//Create player variable
Player player;

//Define camera variable
Camera2D camera;


void draw(){
    BeginDrawing();

    ClearBackground(WHITE);

    BeginMode2D(camera);
    
    drawPlayer(&player, &camera);

    drawLevel();

    EndMode2D();
    

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "Square Dash");
    SetTargetFPS(60);

    //Player init
    playerInit(&player, &camera);
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