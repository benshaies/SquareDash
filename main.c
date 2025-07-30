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
int menuState = 0; // 0 = Start menu || 1 = level selector || 2 = Level finished screen
int currentLevel = 0; // 0 = None selected

Font gameFont;

//Colors
Color groundColor = (Color){198, 215, 255, 255};
Color spikeColor = (Color){147, 56, 56, 255};
Color levelOneColor = (Color){102, 191, 255, 255}; // light, neutral blue-gray
Color levelTwoColor = (Color){255, 223, 153, 255};
Color levelThreeColor = (Color){255, 102, 102, 255};

Sound click, done;
Music mainMenu, oneMusic, twoMusic, threeMusic;

void drawMenu(){
    BeginDrawing();

    ClearBackground(levelOneColor );

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
            PlaySound(click);
            menuState = 1;
        }

        DrawTextEx(gameFont, "RMB to\n  Jump", (Vector2){200, 325}, 35, 2, BLACK);
        DrawTextEx(gameFont, "SPACE to\n  Pause", (Vector2){1100, 325}, 35, 2, BLACK);

        DrawRectangle(650, 450, 200, 75, isHovering(mousePos,(Rectangle){650, 450, 200, 75}) ? YELLOW : WHITE);
        DrawTextEx(gameFont, "Quit", (Vector2){670, 465}, 45, 2, BLACK);
        DrawRectangleLinesEx((Rectangle){650, 450, 200, 75}, 3.0f, BLACK);
        if(isHovering(mousePos,(Rectangle){650, 450, 200, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            CloseWindow();
        }
    }
    else if(menuState == 1){
        musicRestart = true;
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
            PlaySound(click);
            currentLevel = 1;
            gameState = 1;
        }
        //Level 2
        else if(isHovering(mousePos,(Rectangle){700, 300, 100, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            currentLevel = 2;
            gameState = 1;
        }
        //Level 3
        else if(isHovering(mousePos,(Rectangle){1000, 300, 100, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            currentLevel = 3;
            gameState = 1;
        }

        DrawRectangle(650, 450, 200, 75, isHovering(mousePos,(Rectangle){650, 450, 200, 75}) ? YELLOW : WHITE);
        DrawTextEx(gameFont, "Back", (Vector2){665, 465}, 45, 2, BLACK);
        DrawRectangleLinesEx((Rectangle){650, 450, 200, 75}, 3.0f, BLACK);
        if(isHovering(mousePos,(Rectangle){650, 450, 200, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            gameState = 0;
            menuState = 0;
            player.pos = (Vector2){300, 400};
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

    if(menuState == 2 || menuState == 3){

        
         DrawRectangle(0,0, 1500, 750, Fade(BLACK, 0.60));

        //Replay Button
        DrawRectangle(650, 450, 200, 75, isHovering(mousePos,(Rectangle){650, 450, 200, 75}) ? YELLOW : WHITE);
        DrawTextEx(gameFont, "Replay", (Vector2){660, 470}, 35, 2, BLACK);
        DrawRectangleLinesEx((Rectangle){650, 450, 200, 75}, 3.0f, BLACK);
        if(isHovering(mousePos,(Rectangle){650, 450, 200, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            musicRestart = true;
            gameState = 1;
            menuState = 1;
            player.pos = (Vector2){300, 400};
        }

        DrawRectangle(650, 600, 200, 75, isHovering(mousePos,(Rectangle){650, 600, 200, 75}) ? YELLOW : WHITE);
        DrawTextEx(gameFont, "Exit", (Vector2){680, 615}, 45, 2, BLACK);
        DrawRectangleLinesEx((Rectangle){650, 600, 200, 75}, 3.0f, BLACK);
        if(isHovering(mousePos,(Rectangle){650, 600, 200, 75}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            PlaySound(click);
            gameState = 0;
            menuState = 1;
            player.pos = (Vector2){300, 400};
        }

        if(menuState == 2){
            DrawTextEx(gameFont, "Level Complete", (Vector2){400, 275}, 65, 2, GOLD);
        }

    }

    EndDrawing();
}


void draw(){
    BeginDrawing();

    BeginMode2D(camera);

    if(currentLevel == 1){
        UpdateMusicStream(oneMusic);
        SetMusicVolume(oneMusic, 0.15f);

        if (musicRestart) {
            SeekMusicStream(oneMusic, 0.0f);
            PlayMusicStream(oneMusic);
            musicRestart = false;
        }

        ClearBackground(levelOneColor);
        drawLevel(texture, level1);
    }
    else if(currentLevel == 2){
        UpdateMusicStream(twoMusic);
        SetMusicVolume(twoMusic, 0.3f);

        if (musicRestart) {
            SeekMusicStream(twoMusic, 0.0f);
            PlayMusicStream(twoMusic);
            musicRestart = false;
        }
        ClearBackground(levelTwoColor);
        drawLevel(texture, level2);
    }
    else if(currentLevel == 3){
        UpdateMusicStream(threeMusic);
        SetMusicVolume(threeMusic, 0.3f);

        if (musicRestart) {
            SeekMusicStream(threeMusic, 0.0f);
            PlayMusicStream(threeMusic);
            musicRestart = false;
        }
        ClearBackground(levelThreeColor);
        drawLevel(texture, level3);
    }

    if(player.pos.x/12500 >= 1.0){
        PlaySound(done);
        gameState = 0;
        menuState = 2;
    }

        
    drawPlayer(&player, &camera);

    if(IsKeyPressed(KEY_SPACE)){
        gameState = 0;
        menuState = 3;
    }

    EndMode2D();
    

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "Square Dash");
    SetTargetFPS(60);
    InitAudioDevice();

    //Player init
    playerInit(&player, &camera);

    //Load texture
    texture = LoadTexture("../assets/SquareDashSprites.png");

    //Load font
    gameFont = LoadFontEx("../assets/SuperPixel-m2L8j.ttf", 65, 0, 0);

    //Load soung
    click = LoadSound("../assets/tabClick.wav");
    done = LoadSound("../assets/timerDone.mp3");

    //Load music
    mainMenu = LoadMusicStream("../assets/mainmenu.mp3");
    PlayMusicStream(mainMenu);

    oneMusic = LoadMusicStream("../assets/level1.mp3");
    PlayMusicStream(oneMusic);

    twoMusic = LoadMusicStream("../assets/level2.mp3");
    PlayMusicStream(twoMusic);
    
    threeMusic = LoadMusicStream("../assets/level3.mp3");
    PlayMusicStream(threeMusic);


}

int main(void){
    
    //Call init funciton
    init();

    while(!WindowShouldClose()){
        

        if(gameState == 0){
            
            UpdateMusicStream(mainMenu);
            SetMusicVolume(mainMenu, 0.4f);
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
    UnloadSound(click);
    UnloadSound(done);
    UnloadTexture(texture);
    UnloadMusicStream(mainMenu);
    UnloadMusicStream(oneMusic);
    UnloadMusicStream(twoMusic);
    UnloadMusicStream(threeMusic);
    CloseAudioDevice();
    CloseWindow();
}