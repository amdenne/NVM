#include "EnemyEntity.h"
using namespace std;

EnemyEntity:: EnemyEntity(byte _level){
    _spriteHeight = 16;
    _spriteWidth = 16;
    _healthMultiplier = 10;
    _enemyCollider = Rect(xPos, yPos, _spriteWidth, _spriteHeight);  
    // _idleSprite = CHAR_FORWARD_IDLE;
    // _downWalkSprite = CHAR_FORWARD_WALKING;
    // _leftWalkSprite = CHAR_LEFT_WALKING;
    // _rightWalkSprite = CHAR_RIGHT_WALKING;
    // _upWalkSprite = CHAR_BACK_WALKING;

    level = _level;
    maxHealth = _level * _healthMultiplier;
    currentHealth = _level * _healthMultiplier;
    xPos = (WIDTH / 2) - (_spriteWidth / 2);
    yPos = (HEIGHT / 2) - (_spriteHeight / 2);
}

unsigned char EnemyEntity::spriteWidth(){ return _spriteWidth;}
unsigned char EnemyEntity::spriteHeight(){ return _spriteHeight;}
Rect EnemyEntity::enemyCollider(){ return _enemyCollider;}
