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
int gameState = 0; // 0 = menu || 1 = playing || -1 = Paused
int menuState = 0; // 0 = Start menu || 1 = level selector
int currentLevel = 0; // 0 = None selected

Font gameFont;

//Colors
Color groundColor = (Color){198, 215, 255, 255};
Color spikeColor = (Color){147, 56, 56, 255};
Color backgroundColor = (Color){102, 191, 255, 255}; // light, neutral blue-gray


void drawMenu(){
    BeginDrawing();

    ClearBackground(backgroundColor );

    Vector2 mousePos = GetMousePosition();

    DrawRectangle(425, 95, 675, 75, WHITE);
    DrawRectangleLinesEx((Rectangle){425, 95, 675, 75}, 3.0f, BLACK);
    DrawTextEx(gameFont, "Sqaure Dash", (Vector2){450, 100}, 65, 2, BLACK);
    
    if(menuState == 0){
        //Play and or level selector
        DrawRectangle(650, 300, 200, 75, isHovering(mousePos,(Rectangle){650, 300, 200, 75}) ? YELLOW : WHITE);
        DrawTextEx(gameFont, "Play", (Vector2){675, 315}, 45, 2, BLACK);
        DrawRectangleLinesEx((Rectangle){650, 300, 200, 75}, 3.0f, BLACK);

        if(isHovering(mousePos,(Rectangle){650, 300, 200, 75}) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            menuState = 1;
        }
    }
    else if(menuState == 1){
        //Level 1
        DrawRectangle(400, 300, 100, 75, isHovering(mousePos,(Rectangle){400, 300, 100, 75}) ? YELLOW : WHITE);
        DrawText("1", 440, 305, 75, BLACK);
        DrawRectangleLinesEx((Rectangle){400, 300, 100, 75}, 3.0f, BLACK);

        //Level 2
        DrawRectangle(700, 300, 100, 75, isHovering(mousePos,(Rectangle){700, 300, 100, 75}) ? YELLOW : WHITE);
        DrawText("2", 730, 305, 75, BLACK);
        DrawRectangleLinesEx((Rectangle){700, 300, 100, 75}, 3.0f, BLACK);

        //Level 3
        DrawRectangle(1000, 300, 100, 75, isHovering(mousePos,(Rectangle){1000, 300, 100, 75}) ? YELLOW : WHITE);
        DrawText("3", 1030, 305, 75, BLACK);
        DrawRectangleLinesEx((Rectangle){1000, 300, 100, 75}, 3.0f, BLACK);

        //Level selection check
        //Level 1
        if(isHovering(mousePos,(Rectangle){400, 300, 100, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            currentLevel = 1;
            gameState = 1;
        }
        //Level 2
        else if(isHovering(mousePos,(Rectangle){700, 300, 100, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            currentLevel = 2;
            gameState = 1;
        }
        //Level 3
        else if(isHovering(mousePos,(Rectangle){1000, 300, 100, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            currentLevel = 3;
            gameState = 1;
        }

    }
    
    //Level drawings
    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){250, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){300, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){350, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);

    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){1100, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){1150, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(texture, (Rectangle){50, 0, 50, 50}, (Rectangle){1200, 500, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);

    for(int i = 0; i < 30; i++){
        DrawTexturePro(texture, (Rectangle){100, 0, 50, 50}, (Rectangle){i*50, 550, 50, 50}, (Vector2){0,0}, 0.0f, Fade(WHITE, 1.0f));
    }

    EndDrawing();
}


void draw(){
    BeginDrawing();

    ClearBackground(backgroundColor);


    BeginMode2D(camera);

    if(currentLevel == 1){
        drawLevel(texture, level1);
    }
    else if(currentLevel == 2){
        drawLevel(texture, level2);
    }
    else if(currentLevel == 3){
        drawLevel(texture, level3);
    }

        
    drawPlayer(&player, &camera);

    EndMode2D();
    

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "Square Dash");
    SetTargetFPS(60);

    //Player init
    playerInit(&player, &camera);

    //Load texture
    texture = LoadTexture("../assets/SquareDashSprites.png");

    //Load font
    gameFont = LoadFontEx("../assets/SuperPixel-m2L8j.ttf", 65, 0, 0);


}

int main(void){
    
    //Call init funciton
    init();

    while(!WindowShouldClose()){
        

        if(gameState == 0){
            drawMenu();
        }
        else if(gameState == 1){
            draw();

            switch (currentLevel){
                case 1:
                    playerCollisions(&player, level1);
                    break;
                case 2:
                    playerCollisions(&player, level2);
                    break;
                case 3:
                    playerCollisions(&player, level3);
                    break;
            }
            
            playerMovement(&player);
        }
        
    }
    UnloadFont(gameFont);
}