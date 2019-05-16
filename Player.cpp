#include "Player.h"
using namespace std;

Player::Player(byte _level) {
    _spriteHeight = 16;
    _spriteWidth = 10;
    _healthMultiplier = 10;
    _playerCollider = Rect(xPos, yPos, _spriteWidth, _spriteHeight);
      
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
    currentlyFacing = DirectionDown;
};
void Player::reset() { Player(1); }

void Player::shoot(){ 
    _p.
};
unsigned char Player::spriteWidth(){ return _spriteWidth;}
unsigned char Player::spriteHeight(){ return _spriteHeight;}
Rect Player::playerCollider(){ return _playerCollider;}

void Player::walkLeft(unsigned long counter){
    currentlyFacing = DirectionLeft;
    sprites.drawPlusMask(xPos, yPos, CHAR_LEFT_WALKING, counter);
};
void Player::walkRight(unsigned long counter) {
    currentlyFacing = DirectionRight;
    sprites.drawPlusMask(xPos, yPos, CHAR_RIGHT_WALKING, counter);
};
void Player::walkUp(unsigned long counter) {
    currentlyFacing = DirectionUp;
    sprites.drawPlusMask(xPos, yPos, CHAR_BACK_WALKING, counter);
};
void Player::walkDown(unsigned long counter) {
    currentlyFacing = DirectionDown;
    sprites.drawPlusMask(xPos, yPos, CHAR_FORWARD_WALKING, counter);
};
void Player::idle(unsigned long counter) {
    sprites.drawPlusMask(xPos, yPos, CHAR_FORWARD_IDLE, counter);
};

