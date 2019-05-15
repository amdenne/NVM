#include "Player.h"
using namespace std;

Player::Player(byte _level) {
    unsigned char _spriteHeight = 16;
    unsigned char _spriteWidth = 10;
    unsigned char _healthMultiplier = 10;
    // static const unsigned char _idleSprite = CHAR_FORWARD_IDLE;
    // static const unsigned char _downWalkSprite = CHAR_FORWARD_WALKING;
    // static const unsigned char _leftWalkSprite = CHAR_LEFT_WALKING;
    // static const unsigned char _rightWalkSprite = CHAR_RIGHT_WALKING;
    // static const unsigned char _upWalkSprite = CHAR_BACK_WALKING;

    level = _level;
    maxHealth = _level * _healthMultiplier;
    currentHealth = _level * _healthMultiplier;
    xPos = (WIDTH / 2) - (_spriteWidth / 2);
    yPos = (HEIGHT / 2) - (_spriteHeight / 2);
}

unsigned char Player::spriteWidth(){ return _spriteWidth;}
unsigned char Player::spriteHeight(){ return _spriteHeight;}

void Player::walkLeft(unsigned long counter){
    sprite.drawPlusMask(xPos, yPos, CHAR_LEFT_WALKING, counter);
};
void Player::walkRight(unsigned long counter)    {
    sprite.drawPlusMask(xPos, yPos, CHAR_RIGHT_WALKING, counter);
};
void Player::walkUp(unsigned long counter)    {
    sprite.drawPlusMask(xPos, yPos, CHAR_BACK_WALKING, counter);
};
void Player::walkDown(unsigned long counter)    {
    sprite.drawPlusMask(xPos, yPos, CHAR_FORWARD_WALKING, counter);
};
void Player::idle(unsigned long counter)    {
    sprite.drawPlusMask(xPos, yPos, CHAR_FORWARD_IDLE, counter);
}

