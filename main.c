#include <raylib.h>
#include "player.h"
#include "level.h"

const int screenWidth = 1500;
const int screenHeight = 750;

//Create player variable
Player player;

//Define camera variable
Camera2D camera;

//Sprite Texture variable
Texture2D texture;

//GameStae
int gameState = 0;
int menuState = 0;

//Game font
Font font;

void drawMenu(){
    DrawTextEx(font, "Square Dash", (Vector2){250, 150}, 60, 2, BLACK);
}


void draw(){
    BeginDrawing();

    ClearBackground(BLUE);


    BeginMode2D(camera);

    drawLevel(texture);
        
    drawPlayer(&player, &camera);

    

    //EndMode2D();
    

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "Square Dash");
    SetTargetFPS(60);

    //Player init
    playerInit(&player, &camera);

    //Load texture
    texture = LoadTexture("../assets/SquareDashSprites.png");

    //Font
    font = LoadFontEx("../assets/font.ttf", 150, 0, 0);


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