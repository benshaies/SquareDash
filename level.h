#ifndef LEVEL_H
#define LEVEL_H
#include "raylib.h"

extern int level1[15][250];
extern int level2[15][250];
extern int level3[15][250];

void drawLevel(Texture2D texture, int currentLevel[15][250]);

bool isHovering(Vector2 mousePos, Rectangle rec);




#endif
