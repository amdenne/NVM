#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Arduboy2.h>

class Projectile {

private:
    Rect _projectileCollider;

public:
    Projectile(byte x, byte y, byte widthSize, byte heightSize, byte facingDirection, byte moveSpeed = 2){
        xPos = x;
        yPos = y;
        width = widthSize;
        height = heightSize;
        direction = facingDirection;
        speed = moveSpeed;

    };
    byte xPos;
    byte yPos;
    byte width;
    byte height;
    byte speed;
    byte direction;

};

#endif