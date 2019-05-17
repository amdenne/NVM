#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H

#include <Arduboy2.h>
#include "bitmaps.h"

class EnemyEntity {
    Arduboy2 arduboy;
    Sprites sprites;
    enum Directions { Up, Down, Left, Right };

private: 
    unsigned char _spriteHeight = 16;
    unsigned char _spriteWidth = 10;
    unsigned char _healthMultiplier = 10;
    Rect _enemyCollider;
    //Rect _weaponCollider;

public:
    byte xPos;
    byte yPos;
    byte level;
    byte maxHealth;
    byte currentHealth;
    byte currentlyFacing;
    EnemyEntity(){};
    EnemyEntity(byte _level) {
        _spriteHeight = 16;
        _spriteWidth = 10;
        _healthMultiplier = 10;

        level = _level;
        maxHealth = _level * _healthMultiplier;
        currentHealth = _level * _healthMultiplier;
        xPos = (WIDTH / 2) - (_spriteWidth / 2);
        yPos = (HEIGHT / 2) - (_spriteHeight / 2);
        currentlyFacing = Down;

    };

unsigned char spriteHeight() { return _spriteHeight; };
unsigned char spriteWidth() { return _spriteWidth; };
Rect enemyCollider() { return _enemyCollider; };
//Rect weaponCollider() { return _weaponCollider; };

void reset() { EnemyEntity(1); };

void draw(byte x, byte y, unsigned long counter) {
    xPos = x;
    yPos = y;
    sprites.drawPlusMask(xPos, yPos, SPIDER, counter);
    arduboy.fillRect(xPos, yPos - (_spriteHeight / 2), (maxHealth * 2) + 2, 3, BLACK);
    arduboy.fillRect(xPos, yPos - (_spriteHeight / 2), (currentHealth * 2), 5, WHITE);
    _enemyCollider = Rect(xPos, yPos, _spriteWidth, _spriteHeight);
}
void attack(){};
void shoot(){};

};
#endif