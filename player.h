#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

typedef struct{
    Vector2 pos;
    float speed;
    Rectangle rec;
    bool isOnGround;
    float velocityY;

}Player;

void playerInit(Player *player);

void playerMovement(Player *player);

void playerCollisions(Player *player);

void drawPlayer(Player *player);

#endif