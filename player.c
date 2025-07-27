#include "player.h"
#include <raylib.h>
#include "stdlib.h"
#include "stdio.h"

//Stock gravity
float gravity =  0.85f;
float jumpPower = -22.5f;

void playerInit(Player *player, Camera2D *camera){
    player->pos = (Vector2){300, 800};
    player->speed = 2.5f;
    player->rec = (Rectangle){300, 800, 50, 50};
    player->isOnGround = false;
    player->velocityY = 0.0f;
    player->rotaiton = 0.0f;

    //Camera init
    camera->target = player->pos;
    camera->offset = (Vector2){300, 800};
    camera->zoom = 1.0f;
} 

void playerMovement(Player *player){

    //Jump code
    if(IsKeyPressed(KEY_SPACE) && player->isOnGround){
        player->isOnGround = false;
        player->velocityY = jumpPower;
    }

    //Move player forward
    player->pos.x += 5.0f;

    //Update player stuff
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;
     

}

void playerCollisions(Player *player){

    //Checking collsions with ground and adding gravity
    player->pos.y += player->velocityY;

    //Ground check and resetting
    if(player->pos.y < 725){
        player->velocityY += gravity;
        player->isOnGround = false;
        player->rotaiton += 3.5f;
    }
    else{
        player->rotaiton = 0.0f;
        player->isOnGround = true;
        player->velocityY = 0;
        player->pos.y = 725;
    }

    

}

void drawPlayer(Player *player, Camera2D *camera){

    //Update camera location
    camera->target.x = player->pos.x;

    DrawRectanglePro(player->rec, (Vector2){25, 25}, player->rotaiton, BLUE);

}

