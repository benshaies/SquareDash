#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

typedef struct{
    Vector2 pos;
    float speed;
    Rectangle rec;
    bool isOnGround;
    float velocityY;
    float rotaiton;

}Player;

void playerInit(Player *player, Camera2D *camera);

void playerMovement(Player *player);

void playerCollisions(Player *player);

void drawPlayer(Player *player, Camera2D *camera);


#endif