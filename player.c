#include "player.h"
#include <raylib.h>
#include "stdlib.h"
#include "stdio.h"
#include "level.h"

//Stock gravity
float gravity =  0.85f;
float jumpPower = -15.0f;

Vector2 spawnPoint = {300, 400};

bool musicRestart = false;


void playerInit(Player *player, Camera2D *camera){
    player->pos = (Vector2){300, 600};
    player->speed = 2.5f;
    player->rec = (Rectangle){300, 800, 50, 50};
    player->velocityY = 0.0f;
    player->rotaiton = 0.0f;
    player->isJumping = true;

    //Camera init
    camera->target = player->pos;
    camera->offset = (Vector2){300, 600};
    camera->zoom = 1.0f;

    // camera->offset = (Vector2){600, 100};
    // camera->zoom = -1.0f;
} 

void playerMovement(Player *player){
        //Jump code
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !player->isJumping && player->velocityY == 0){
            //player->isOnGround = false;
            player->velocityY = jumpPower;
            player->isJumping = true;
        }

        //Move player forward
        player->pos.x += 7.0f;

        //Update player stuff
        player->rec.x = player->pos.x;
        player->rec.y = player->pos.y;
}

void playerCollisions(Player *player, int currentLevel[15][250]){

    //Checking collsions with ground and adding gravity
    player->pos.y += player->velocityY;

    //Constantly adding gravity no matter what
    player->velocityY += gravity;

    //Adding rotation effect
    if(player->isJumping){
        player->rotaiton += 5.0f;
    }
    else{
        player->rotaiton = 0;
    }

    //Check if player falls off
    if(player->pos.y > 1000){
        player->pos = spawnPoint;
        musicRestart = true;
    }

    // Level Collision Check
    for(int y = 0; y < 15; y++){
        for(int x = 0; x < 250; x++){

            Vector2 bottomPoint = {player->pos.x, player->pos.y+25};
            Vector2 bottomRightPoint = {player->pos.x-12.5, player->pos.y+25};
            Vector2 bottomLeftPoint = {player->pos.x+12.5, player->pos.y+25};

            Vector2 sidePoint = {player->pos.x + 25, player->pos.y};


            Rectangle currentRec = {x*50, y*50, 50, 50};

            //Ground Check
            if(currentLevel[y][x] == 0 && (CheckCollisionPointRec(bottomPoint, currentRec) || CheckCollisionPointRec(bottomRightPoint, currentRec)
            || CheckCollisionPointRec(bottomLeftPoint, currentRec))){
                player->velocityY = 0;
                player->pos.y = (y*50) - 25;
                player->isJumping = false;
            }

            if(currentLevel[y][x] == 0 && CheckCollisionPointRec(sidePoint, currentRec)){
                WaitTime(0.5);
                musicRestart = true;
                player->pos = spawnPoint;
            }

            if(currentLevel[y][x] == 1 && (CheckCollisionPointRec(sidePoint, currentRec)||CheckCollisionPointRec(bottomPoint, currentRec))){
                WaitTime(0.5);
                musicRestart = true;
                player->pos = spawnPoint;
            }

        }
    }

}

void drawPlayer(Player *player, Camera2D *camera){

    //Update camera location
    camera->target.x = player->pos.x;


    DrawRectanglePro(player->rec, (Vector2){25, 25}, player->rotaiton, WHITE);

    //Progress Bar
    DrawRectangleLinesEx((Rectangle){player->pos.x-200, 75, 350, 50}, 4.0f, BLACK);
    DrawRectangle(player->pos.x+5-200,80,350*(player->pos.x/12500),40, WHITE);
}

