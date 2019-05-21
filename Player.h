#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>
#include "bitmaps.h"

class Player {
    Arduboy2 arduboy;
    Sprites sprites;
    enum Directions { Up, Down, Left, Right };
    enum PlayerState { Idle, Walking, Attacking };

private: 
    unsigned char _numberOfAnimationsPerFacing = 4;
    unsigned char _walkOffset = 1;
    unsigned char _attackOffset = 3;
    unsigned char _spriteHeight = 16;
    unsigned char _spriteWidth = 24;
    unsigned char _healthMultiplier = 10;
    unsigned long _lastAttack = 0;
    unsigned long _attackSpeed = 1000;
    unsigned long _attackDuration = 250;
    unsigned char _playerState = Idle;

    Rect _playerCollider;
    Rect _weaponCollider;

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
        _spriteWidth = 12;
        _healthMultiplier = 10;

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
        
        _playerState = Attacking;
        
        if((currentMillis - _lastAttack) >= _attackSpeed ){
            byte width;
            byte height;
            byte x = xPos;
            byte y = yPos;
            if(currentlyFacing == Up) { y = yPos - (8); width = 3; height = 8; };
            if(currentlyFacing == Down) { y = yPos + (10); width = 3; height = 8; };
            
            if(currentlyFacing == Left) { y = yPos + (_spriteHeight / 2); x = xPos - (8); width = 8; height = 4; };
            if(currentlyFacing == Right) { y = yPos + (_spriteHeight / 2); x = xPos + 10; width = 8; height = 4; };
            
            _weaponCollider = Rect(x, y, width, height);
            // arduboy.fillRect(x, y, width, height, BLACK);
            // if(currentlyFacing == Up || currentlyFacing == Down)
            //     arduboy.fillRect(x, y, width - 2, height, WHITE);
            // if(currentlyFacing == Left || currentlyFacing == Right)
            //     arduboy.fillRect(x, y, width, height - 2, WHITE);
            drawAttack();
            _lastAttack = millis();
           
        }  
    };

    void shoot(){

    };

    void walkLeft(unsigned long counter) {
        currentlyFacing = Left;
        _playerState = Walking;
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, counter + (_numberOfAnimationsPerFacing * Left) + _walkOffset);
    };
    void walkRight(unsigned long counter) {
        currentlyFacing = Right;
        _playerState = Walking;
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, counter + (_numberOfAnimationsPerFacing * Right) + _walkOffset);
    };
    void walkUp(unsigned long counter) {
        currentlyFacing = Up;
        _playerState = Walking;    
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, counter + (_numberOfAnimationsPerFacing * Up) + _walkOffset);
    };
    void walkDown(unsigned long counter) {
        currentlyFacing = Down;
        _playerState = Walking;
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, counter + (_numberOfAnimationsPerFacing * Down) + _walkOffset);
    };

    void idle(unsigned long counter){
        _playerState = Idle;
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, counter + (_numberOfAnimationsPerFacing * currentlyFacing));
    };

    void drawAttack(){
        sprites.drawPlusMask(xPos, yPos, PLAYER_SPRITE, (_numberOfAnimationsPerFacing * currentlyFacing) + _attackOffset);
    };

    void removeWeaponCollider(){
        _weaponCollider = Rect();
    }
};
#endif
