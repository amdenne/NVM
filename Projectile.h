#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Arduboy2.h>

class Projectile {

private:
    Rect _projectileCollider;

public:
    Projectile(byte speed = 2);
    byte xPos;
    byte yPos;
    byte width;
    byte height;
    byte speed;
    byte direction;

};

#endif