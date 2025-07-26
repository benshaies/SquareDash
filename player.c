#include "player.h"
#include <raylib.h>

//Stock gravity
float gravity =  0.85f;

void playerInit(Player *player){
    player->pos = (Vector2){300, 800};
    player->speed = 2.5f;
    player->rec = (Rectangle){300, 800, 75, 75};
    player->isOnGround = false;
    player->velocityY = 0.0f;
} 

void playerMovement(Player *player){
    //Update player stuff
    player->pos = (Vector2){player->rec.x, player->rec.y};

    //Jump code
    if(IsKeyPressed(KEY_SPACE) && player->isOnGround){
        player->isOnGround = false;
        player->velocityY = -22.5f;
    }
}

void playerCollisions(Player *player){

    //Checking collsions with ground and adding gravity
    player->rec.y += player->velocityY;
    if(player->rec.y < 925){
        player->velocityY += gravity;
        player->isOnGround = false;
    }
    else{
        player->isOnGround = true;
        player->velocityY = 0;
        player->rec.y = 925;
    }


}

void drawPlayer(Player *player){

    DrawRectangleLinesEx(player->rec, 5.0f, BLUE);

}

