#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "display.h"

struct pixel {
    int X;
    int Y;
    int prevX;
    int prevY;
};

struct position {
  int X;
  int Y;
};

void playerControlledObj(int X, int Y) { //just a 9x9 rectange
    makeEntity(X, X+3, Y, Y+3, 0xFF0);
}

void commonEnemy(int X, int Y) { //just a rectangle until proper sprites are implemented
    makeEntity(X, X+5, Y, Y+5, 0x00F);
}

void commonAtk(int X, int Y) {
    makeEntity(X, X+3, Y, Y, 0xF00);
}

int commonAtkUpdate(int X, int Y) {
    makeEntity(X, X+3, Y, Y, 0x000);
    makeEntity(X+1,X+4, Y,Y, 0xF00);
    // makeEntity(X);
    // makeEntity();
    return X+1;
}

int commonAtkUpdateAlt(int X, int Y) {
    makeEntity(X, X+3, Y, Y, 0x000);
    makeEntity(X-4, X-1,Y,Y, 0xF00);

    return X-1;
}

#endif