#define FRAME_RATE 30
#define NO_SCENE 0
#define GAME_TITLE 1
#define GAME_PLAY 2
#define GAME_OVER 3
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8
#define TILE_SIZE 16
#define WORLD_HEIGHT 4
#define WORLD_WIDTH 8
#define GRASS 0
#define WATER 2
#define MAX_PLAYER_PROJECTILES 10

#include "Player.h"
  Player player(1);
#include "bitmaps.h"
#include <Arduboy2.h>
  Arduboy2 arduboy;
  Sprites sprites;

class Projectile{
  public :
  // Projectile(int x, int y, byte width, byte height, byte speed) : x{x}, y{y}, width{width}, height{height}, speed{speed} {}
  int  x;
  int y;
  byte width;
  byte height;
  byte speed;
};

Rect playerCollider;
Rect enemyCollider;
unsigned long counter = 0;
byte lastScene = NO_SCENE;
byte selectedOption = 1;
byte currentScene;
boolean gameOverAnimPlayedOnce = false;
char option1[] = "Game Title";
char option2[] = "Play Game";
char option3[] = "Game Over";
int mapX = 0;
int mapY = 0;
int world[WORLD_HEIGHT][WORLD_WIDTH] = { 
	{ GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WATER, WATER },
	{ GRASS, WATER, GRASS, GRASS, GRASS, WATER, WATER, WATER },
	{ GRASS, WATER, WATER, GRASS, GRASS, WATER, WATER, WATER },
	{ GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WATER, WATER }
};

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);
  playNevermindSplash();
  currentScene = GAME_TITLE;
  // Projectile playerProjectiles[MAX_PLAYER_PROJECTILES];
}

void debug(){
  arduboy.fillRect(0, 0, 60, 8, BLACK);
  arduboy.setCursor(0,0);
  arduboy.print(player.spriteHeight());  
  arduboy.print(",");
  arduboy.print(player.spriteWidth());
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  setScene();

  if (arduboy.everyXFrames(15)) counter++;
  if (counter > 1) counter = 0;
}

void setScene() {
  lastScene = currentScene;
  arduboy.clear();
  if (currentScene == GAME_TITLE) {
    menuSelectionStuff();
    drawMenu();
  }
  else if(currentScene == NO_SCENE)
  {
    arduboy.clear();
    arduboy.display();

    if (arduboy.pressed(A_BUTTON)) {
      lastScene = NO_SCENE;
      currentScene = GAME_TITLE;
    }
  }
  else if (currentScene == GAME_PLAY) {
    if(player.currentHealth <= 0){
      currentScene = GAME_OVER;
      setScene();
    }    
      playGame();      
    if(arduboy.pressed(A_BUTTON)) {
      lastScene = GAME_PLAY;
      currentScene = GAME_TITLE;
    }    
  }
  else if (currentScene == GAME_OVER) {
    while (currentScene == GAME_OVER) {
      if (!gameOverAnimPlayedOnce)
        drawGameOverScene();
      if (arduboy.pressed(A_BUTTON)) {
        gameOverAnimPlayedOnce = false;
        lastScene = GAME_OVER;
        currentScene = GAME_TITLE;

        resetPlayer();
      }
    }
  }
}

void resetPlayer() {
  mapX = 0;
  mapY = 0; 
  player = Player(1);
}

void playGame(){  
  drawWorld();
  drawSpider();
  drawPlayer(); 
  moveProjectiles();
  checkCollision();
  debug();

  arduboy.display();  
}

void checkCollision(){
  if(arduboy.collide(playerCollider, enemyCollider)){
    mapX+=10;
    player.currentHealth--;
  }
}

void drawPlayer(){
  byte feetSize = 2;
  int currentFeetY = (player.yPos + (player.spriteHeight() - feetSize) - mapY) / TILE_SIZE;
  int currentFeetX = (player.xPos + player.spriteWidth() / 2 - mapX) / TILE_SIZE;
  int nextFeetY;
  int nextFeetX;

  playerCollider = Rect(player.xPos, player.yPos, player.spriteWidth(), player.spriteHeight());  

  if (arduboy.pressed(DOWN_BUTTON)) {
    player.walkDown(counter);
    //sprites.drawPlusMask(playerX, playerY, CHAR_FORWARD_WALKING, counter);

    nextFeetY = (player.yPos + player.spriteHeight() + 2 - mapY) / TILE_SIZE;
    if ((player.yPos + player.spriteHeight()) < (mapY + TILE_SIZE * WORLD_HEIGHT) && world[nextFeetY][currentFeetX] < WATER)
      mapY--;
  }
  else if (arduboy.pressed(UP_BUTTON)){
    player.walkUp(counter);
    //sprites.drawPlusMask(playerX, playerY, CHAR_BACK_WALKING, counter);

    nextFeetY = (player.yPos + player.spriteHeight() / 2 - mapY) / TILE_SIZE;
    if (mapY < player.yPos + player.spriteHeight() / 2 && world[nextFeetY][currentFeetX] < WATER)
      mapY++;
  }
  else if (arduboy.pressed(LEFT_BUTTON))  {
    player.walkLeft(counter);
    //sprites.drawPlusMask(playerX, playerY, CHAR_LEFT_WALKING, counter);

    nextFeetX = (player.xPos - mapX) / TILE_SIZE;
    if (mapX < player.xPos && world[currentFeetY][nextFeetX] < WATER)
      mapX++;
  }
  else if (arduboy.pressed(RIGHT_BUTTON))  {
    player.walkRight(counter);
    //sprites.drawPlusMask(playerX, playerY, CHAR_RIGHT_WALKING, counter);

    nextFeetX = (player.xPos + player.spriteWidth() - mapX) / TILE_SIZE;
    if (player.xPos + player.spriteWidth() < mapX + TILE_SIZE * WORLD_WIDTH && world[currentFeetY][nextFeetX] < WATER)
      mapX--;
  }
  else {
    player.idle(0);
    //sprites.drawPlusMask(playerX, playerY, CHAR_FORWARD_IDLE, 0);
  }  

  if(arduboy.pressed(B_BUTTON)){
    shoot();
  }
  
  drawPlayerHealth();
}

void moveProjectiles(){
  
}

void shoot(){
  // Projectile shot{1, 2, 3, 4, 5};

  // playerProjectiles.push(shot);
  arduboy.fillRect(mapX - (player.xPos / 2), mapY - (player.yPos / 2), 2, 2, BLACK);
}

void drawPlayerHealth(){
  arduboy.fillRect(3, 3, (player.maxHealth * 2) + 2, 7, BLACK);
  arduboy.fillRect(4, 4, (player.currentHealth * 2), 5, WHITE);
}

void drawSpider(){
  int spiderX = 5 * TILE_SIZE + mapX;
  int spiderY = 0 + mapY;
  sprites.drawPlusMask(spiderX, spiderY, SPIDER, counter);
  enemyCollider = Rect(spiderX, spiderY, 17, 16);
}

void drawWorld() {
  const int tilesWide = WIDTH / TILE_SIZE + 1;
  const int tilesHigh = HEIGHT / TILE_SIZE + 1;

  for (int y = 0; y < tilesHigh; y++) {
    for (int x = 0; x < tilesWide; x++) {
        const int tileX = x - mapX / TILE_SIZE;
        const int tileY = y - mapY / TILE_SIZE;
        if(tileX >= 0 && tileY >= 0 && tileX < WORLD_WIDTH && tileY <  WORLD_HEIGHT)
          arduboy.drawBitmap((x * TILE_SIZE + mapX % TILE_SIZE), (y * TILE_SIZE + mapY % TILE_SIZE), TILESET[world[tileY][tileX] + counter], TILE_SIZE, TILE_SIZE, WHITE);
    }
  }
}

void drawGameOverScene(){
  gameOverAnimPlayedOnce = true;
    arduboy.clear();
    arduboy.setCursor(4, HEIGHT / 2);
    char gameOverText[15] = "Wow, you suck.";
    for (byte i = 0; strlen(gameOverText) >= i; i++) {
      arduboy.print(gameOverText[i]);
      arduboy.display();
      arduboy.delayShort(100);
    }
    arduboy.delayShort(250);
    arduboy.clear();
    arduboy.setCursor(4, HEIGHT / 2);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(250);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(250);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(250);
    arduboy.clear();
    arduboy.setTextSize(2);
    arduboy.setCursor(4, 20);
    arduboy.println("gitgudlul");
    arduboy.display();
    arduboy.setTextSize(1);
}

void menuSelectionStuff() {
  arduboy.pollButtons();

  if (arduboy.justPressed(DOWN_BUTTON)) {
    selectedOption++;
    if (selectedOption > 3)
      selectedOption = 1;
  }
  else if (arduboy.justPressed(UP_BUTTON)) {
    selectedOption--;
    if (selectedOption < 1)
      selectedOption = 3;
  }
  else if(arduboy.justPressed(B_BUTTON)) {
    lastScene = currentScene;
    currentScene = selectedOption;
  }
  // else if(arduboy.justPressed(LEFT_BUTTON)){
  //   lastScene = currentScene;
  //   currentScene = NO_SCENE;
  // }

  arduboy.delayShort(30);
}

void highlightItem(byte selectedOption) {
  if (selectedOption == GAME_TITLE)
    highlight(2, 13, option1);
  else if (selectedOption == GAME_PLAY)
    highlight(2, 28, option2);
  else if (selectedOption == GAME_OVER)
    highlight(2, 43, option3);
}

void highlight(byte x, byte y, char item[]) {
  byte itemWidth = strlen(item) * CHAR_WIDTH + 3;
  arduboy.drawRect(x, y, itemWidth, 11, WHITE);
  arduboy.display();
}

void playNevermindSplash() {
  animateNevermindDown(-16, 10, 2);
  animateGamesRight(-80, 45, 10);
  arduboy.delayShort(500);
  arduboy.clear();
}

void drawMenu() {
  arduboy.clear();
  sprites.drawPlusMask(66, -2, gate_plus_mask, counter);
  drawMenuText();
  arduboy.display();
}

void drawMenuText(){
  arduboy.setCursor(4, 15);
  arduboy.println(option1);
  arduboy.setCursor(4, 30);
  arduboy.println(option2);
  arduboy.setCursor(4, 45);
  arduboy.println(option3);
  arduboy.setCursor(60, 56);
  arduboy.print("selected: ");
  arduboy.print(selectedOption);
  highlightItem(selectedOption);
}

void animateNevermindDown(int16_t startingPosY, int16_t endingPosY, int16_t speed) {
  while (startingPosY < endingPosY) {
    if (arduboy.nextFrame()) {
      arduboy.clear();
      arduboy.drawBitmap(0, startingPosY, NEVERMIND, 128, 16, WHITE);
      arduboy.display();
      startingPosY += speed;
    }
  }
}

void animateGamesRight(int16_t startingPosX, int16_t endingPosX, int16_t speed) {
  while (startingPosX < endingPosX) {
    if (arduboy.nextFrame()) {
      arduboy.clear();
      arduboy.drawBitmap(0, 10, NEVERMIND, 128, 16, WHITE);
      arduboy.drawBitmap(startingPosX, 29, GAMES, 80, 17, WHITE);
      arduboy.display();
      startingPosX += 10;
    }
  }
}