#ifndef _ALPHABET_H_
#define _ALPHABET_H_

#include "display.h"

/*
functions to write out alphabet characters across screen
takes in 3 arguments which indicate the X and Y position of the letter's bottom left pixel and its color
3 arguments:X and Y indicate the top left starting position of each letter
*/

void A(int X, int Y, int color) {
    makeEntity(X+2,X+5,Y,Y+1,color);
    makeEntity(X,X+1,Y+2,Y+9,color);
    makeEntity(X+6,X+7,Y+2,Y+9,color);
    makeEntity(X+2,X+5,Y+4,Y+5,color);
}

void B(int X, int Y, int color) {
    makeEntity(X,X+5,Y,Y+1,color);
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+5,Y+4,Y+5,color);
    makeEntity(X,X+5,Y+8,Y+9,color);
    makeEntity(X+6,X+7,Y+2,Y+3,color);
    makeEntity(X+6,X+7,Y+6,Y+7,color);
}

void C(int X, int Y, int color) {
    makeEntity(X,X+1,Y+2,Y+7, color);
    makeEntity(X+2,X+8,Y,Y+1,color); 
    makeEntity(X+2,X+8,Y+8,Y+9,color); 
}

void D(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+5,Y,Y+1,color);
    makeEntity(X,X+5,Y+8,Y+9,color);
    makeEntity(X+6,X+7,Y+2,Y+7,color);
}

void E(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+7,Y,Y+1,color);
    makeEntity(X,X+5,Y+4,Y+5,color);
    makeEntity(X,X+7,Y+8,Y+9,color);
}

void F(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+7,Y,Y+1,color);
    makeEntity(X,X+5,Y+4,Y+5,color);
}

void G(int X, int Y, int color) {
    makeEntity(X+2,X+9,Y+8,Y+9, color);
    makeEntity(X,X+1,Y+2,Y+7,color);
    makeEntity(X+2,X+7,Y,Y+1,color);
    makeEntity(X+8,X+9,Y+4,Y+8,color);
    makeEntity(X+3,X+7,Y+4,Y+5,color);
}

void H(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+5,Y+4,Y+5,color);
    makeEntity(X+6,X+7,Y,Y+9,color);
}

void I(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
}

void J(int X, int Y, int color) { 
    makeEntity(X,X+1,Y+6,Y+7, color);
    makeEntity(X+2,X+5,Y+8,Y+9, color);
    makeEntity(X+6,X+7,Y,Y+7,color); 
}

void K(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X+2,X+3,Y+4,Y+5, color);
    makeEntity(X+4,X+5,Y+2,Y+3,color);
    makeEntity(X+4,X+5,Y+6,Y+7,color);
    makeEntity(X+6,X+7,Y+8,Y+9,color);
    makeEntity(X+6,X+7,Y,Y+1,color);
}

void L(int X, int Y, int color) {
    makeEntity(X,X+5,Y+8,Y+9,color);
    makeEntity(X,X+1,Y,Y+9,color);
}

void M(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X+8,X+9,Y,Y+9,color);
    makeEntity(X+2,X+3,Y+2,Y+3,color);
    makeEntity(X+6,X+7,Y+2,Y+3,color);
    makeEntity(X+4,X+5,Y+4,Y+5,color);
}

void N(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X+2,X+3,Y+2,Y+3,color);
    makeEntity(X+4,X+5,Y+4,Y+5,color);
    makeEntity(X+6,X+7,Y,Y+9,color);
}

void O(int X, int Y, int color) {
    makeEntity(X,X+1,Y+2,Y+7,color);
    makeEntity(X+2,X+5,Y,Y+1,color);
    makeEntity(X+6,X+7,Y+2,Y+7,color);
    makeEntity(X+2,X+5,Y+8,Y+9,color);
}

void P(int X, int Y, int color) {
    makeEntity(X,X+5,Y,Y+1,color);
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X,X+5,Y+4,Y+5,color);
    makeEntity(X+6,X+7,Y+2,Y+3,color);
}

void Q(int X, int Y, int color) {
    O(X,Y,color);
    makeEntity(X+4,X+7,Y+6,Y+9,color);
}

void R(int X, int Y, int color) {
    P(X,Y,color);
    makeEntity(X+4,X+5,Y+6,Y+7,color);
    makeEntity(X+6,X+7,Y+8,Y+9,color);
}

void S(int X, int Y, int color) {
    makeEntity(X+2,X+7,Y,Y+1,color);
    makeEntity(X,X+1,Y+2,Y+3,color);
    makeEntity(X+2,X+5,Y+4,Y+5,color);
    makeEntity(X+6,X+7,Y+6,Y+7,color);
    makeEntity(X,X+5,Y+8,Y+9,color);
}

void T(int X, int Y, int color) {
    makeEntity(X,X+5,Y,Y+1,color);
    makeEntity(X+2,X+3,Y,Y+9,color);
}

void U(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+9,color);
    makeEntity(X+6,X+7,Y,Y+9,color);
    makeEntity(X,X+7,Y+8,Y+9,color);
}

void V(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+7, color);
    makeEntity(X+4,X+5,Y,Y+7,color);
    makeEntity(X+2,X+3,Y+8,Y+9,color);
}

void W(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+7,color);
    makeEntity(X+8,X+9,Y,Y+7,color);
    makeEntity(X+2,X+3,Y+8,Y+9,color);
    makeEntity(X+6,X+7,Y+8,Y+9,color);
    makeEntity(X+4,X+5,Y+6,Y+7,color);
}

void X(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+3,color);
    makeEntity(X+2,X+3,Y+4,Y+5,color);
    makeEntity(X+4,X+5,Y,Y+3,color);
    makeEntity(X,X+1,Y+6,Y+9,color);
    makeEntity(X+4,X+5,Y+6,Y+9,color);
}

void Y(int X, int Y, int color) {
    makeEntity(X,X+1,Y,Y+5,color);
    makeEntity(X+4,X+5,Y,Y+5,color);
    makeEntity(X+2,X+3,Y+4,Y+9,color);
}

void Z(int X, int Y, int color) {
    makeEntity(X,X+9,Y,Y+1,color);
    makeEntity(X+8,X+9,Y+2,Y+3,color);
    makeEntity(X+6,X+7,Y+4,Y+5,color);
    makeEntity(X+4,X+5,Y+6,Y+7,color);
    makeEntity(X+2,X+3,Y+8,Y+9,color);
    makeEntity(X,X+9,Y+8,Y+9,color);
}

struct letterToWhitespace{
    void (*letter)(int, int, int);
    int Xincrement; 
};

letterToWhitespace build(void (*letter)(int, int, int), int space) {
    letterToWhitespace character;
    character.letter = letter;
    character.Xincrement = space;
    return character;
}

letterToWhitespace convert[26] = {
    build(&A, 9),
    build(&B, 9),
    build(&C, 11),
    build(&D, 9),
    build(&E, 9),
    build(&F, 9),
    build(&G, 11),
    build(&H, 9),
    build(&I, 3),
    build(&J, 9),
    build(&K, 9),
    build(&L, 7),
    build(&M, 11),
    build(&N, 9),
    build(&O, 9),
    build(&P, 9),
    build(&Q, 9),
    build(&R, 9),
    build(&S, 9),
    build(&T, 7),
    build(&U, 9),
    build(&V, 7),
    build(&W, 11),
    build(&X, 7),
    build(&Y, 7),
    build(&Z, 11),
};

void printStr(char *str, int X, int Y, int color) { //start at X and Y positions based on where string is inputted
    for (int i = 0; str[i] != '\0'; i++){
        if(str[i] == ' ') {
            X = X + 6;
        }
        else {
            if(X > 120) {
                X = 2;
                Y+=15;
            }
            int indexVal = static_cast<int>(str[i] - 65);
                convert[indexVal].letter(X,Y,color);
                X = X + convert[indexVal].Xincrement;
        }
    }
}


#endif