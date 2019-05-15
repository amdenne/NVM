#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>
    Sprites sprite;
#include "bitmaps.h"

class Player {
private: 
    unsigned char _spriteHeight;
    unsigned char _spriteWidth;
    unsigned char _healthMultiplier;

    // const unsigned char _idleSprite = CHAR_FORWARD_IDLE;
    // const unsigned char _downWalkSprite = CHAR_FORWARD_WALKING;
    // const unsigned char _leftWalkSprite = CHAR_LEFT_WALKING;
    // const unsigned char _rightWalkSprite = CHAR_RIGHT_WALKING;
    // const unsigned char _upWalkSprite = CHAR_BACK_WALKING;

public:
    Player();
    Player(byte _level);
    byte xPos;
    byte yPos;
    byte level;
    byte maxHealth;
    byte currentHealth;

    // Projectile projectile[];

    unsigned char spriteHeight();
    unsigned char spriteWidth();
    void walkLeft(unsigned long counter);
    void walkRight(unsigned long counter);
    void walkUp(unsigned long counter);
    void walkDown(unsigned long counter);
    void idle(unsigned long counter);
};
#endif
