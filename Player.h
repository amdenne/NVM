#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>
#include "bitmaps.h"
class Player {
    Arduboy2 arduboy;
    Sprites sprites;
    enum Directions { Up, Down, Left, Right };

private: 
    unsigned char _spriteHeight = 16;
    unsigned char _spriteWidth = 10;
    unsigned char _healthMultiplier = 10;
    unsigned long _lastAttack = 0;
    unsigned long _attackSpeed = 1000;

    Rect _playerCollider;
    Rect _weaponCollider;
    // const unsigned char _idleSprite = CHAR_FORWARD_IDLE;
    // const unsigned char _downWalkSprite = CHAR_FORWARD_WALKING;
    // const unsigned char _leftWalkSprite = CHAR_LEFT_WALKING;
    // const unsigned char _rightWalkSprite = CHAR_RIGHT_WALKING;
    // const unsigned char _upWalkSprite = CHAR_BACK_WALKING;

public:
    byte xPos;
    byte yPos;
    byte level;
    byte maxHealth;
    byte currentHealth;
    byte currentlyFacing;
    Player() = default;
    Player(byte _level) {
        _spriteHeight = 16;
        _spriteWidth = 10;
        _healthMultiplier = 10;

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
        currentlyFacing = Down;

        _playerCollider = Rect(xPos, yPos, _spriteWidth, _spriteHeight);

    };

    unsigned char spriteHeight(){ return _spriteHeight; };
    unsigned char spriteWidth() { return _spriteWidth; };
    Rect playerCollider() { return _playerCollider; };
    Rect weaponCollider() { return _weaponCollider; };

    void reset() { Player(1); };
    
    void attack(){
        unsigned long currentMillis = millis();
        if((currentMillis - _lastAttack) >= _attackSpeed ){
            byte width;
            byte height;
            byte x = xPos;
            byte y = yPos;
            if(currentlyFacing == Up) { y = yPos - (24 - 8); width = 4; height = 24; };
            if(currentlyFacing == Down) { y = yPos; width = 4; height = 24; };
            if(currentlyFacing == Left) { x = xPos - (24 - 5); width = 24; height = 4; };
            if(currentlyFacing == Right) { x = xPos; width = 24; height = 4; };
            
            _weaponCollider = Rect(x, y, width, height);
            arduboy.fillRect(x, y, width, height, BLACK);    
            _lastAttack = millis();  
        }  
    };
    void shoot(){

    };

    void walkLeft(unsigned long counter) {
        currentlyFacing = Left;
        sprites.drawPlusMask(xPos, yPos, CHAR_LEFT_WALKING, counter);
    };
    void walkRight(unsigned long counter) {
        currentlyFacing = Right;
        sprites.drawPlusMask(xPos, yPos, CHAR_RIGHT_WALKING, counter);
    };
    void walkUp(unsigned long counter) {
        currentlyFacing = Up;
        sprites.drawPlusMask(xPos, yPos, CHAR_BACK_WALKING, counter);
    };
    void walkDown(unsigned long counter) {
        currentlyFacing = Down;
        sprites.drawPlusMask(xPos, yPos, CHAR_FORWARD_WALKING, counter);
    };
    void idle(unsigned long counter) {
        sprites.drawPlusMask(xPos, yPos, CHAR_FORWARD_IDLE, counter);
    };
    void removeWeaponCollider(){
        _weaponCollider = Rect();
    }
};
#endif
