#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <Arduboy2.h>
#include "bitmaps.h"

class EnemyEntity {
    Sprites sprites;

private:
    unsigned char _spriteHeight;
    unsigned char _spriteWidth;
    unsigned char _healthMultiplier;
    Rect _enemyCollider;


public:
    EnemyEntity();
    EnemyEntity(byte _level);
    byte xPos;
    byte yPos;
    byte level;
    byte maxHealth;
    byte currentHealth;

    unsigned char spriteHeight();
    unsigned char spriteWidth();
    Rect enemyCollider();
    void reset();

    void attack();
    void shoot();


};







#endif