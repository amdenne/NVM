#define FRAME_RATE 30
#define NO_SCENE 0
#define GAME_TITLE 1
#define GAME_PLAY 2
#define GAME_OVER 3
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8
#define TILE_SIZE 16
#define PLAYER_SPRITE_WIDTH 10
#define PLAYER_SPRITE_HEIGHT 16
#define WORLD_HEIGHT 4
#define WORLD_WIDTH 8
#define GRASS 0
#define WATER 2


#include <Arduboy2.h>

Arduboy2 arduboy;
Sprites sprites;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

unsigned long counter = 0;
byte lastScene = NO_SCENE;
byte selectedOption = 1;
byte currentScene;
boolean gameOverAnimPlayedOnce = false;
char option1[] = "Game Title";
char option2[] = "Play Game";
char option3[] = "Game Over";
byte maxPlayerHealth = 8;
byte currentPlayerHealth = 8;
int playerX = (WIDTH / 2) - (PLAYER_SPRITE_WIDTH / 2);
int playerY = (HEIGHT / 2) - (PLAYER_SPRITE_HEIGHT / 2);
int mapX = 0;
int mapY = 0;
int world[WORLD_HEIGHT][WORLD_WIDTH] = { 
	{ GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WATER, WATER },
	{ GRASS, WATER, WATER, GRASS, GRASS, WATER, WATER, WATER },
	{ GRASS, WATER, WATER, GRASS, GRASS, WATER, WATER, WATER },
	{ GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WATER, WATER }
};

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);
  playNevermindSplash();
  currentScene = GAME_TITLE;
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
    if(currentPlayerHealth <= 0){
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
      if(!gameOverAnimPlayedOnce) drawGameOverScene();
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
  setPlayerHealthToFull();
}

void playGame(){  
  drawWorld();
  drawSpider();
  drawPlayer(); 

  arduboy.display();  
}

void debug(){
  arduboy.fillRect(0, 0, 130, 8, BLACK);
	arduboy.setCursor(0, 0);
  arduboy.print((playerY + PLAYER_SPRITE_WIDTH/2 - mapY) / TILE_SIZE );
  arduboy.print(",");
  arduboy.print((playerX + PLAYER_SPRITE_WIDTH/2 - mapX) / TILE_SIZE );
  
  arduboy.setCursor(0, 8);
  arduboy.fillRect(0, 8, 60, 8, BLACK);
  arduboy.print(mapY);
  arduboy.print(",");
  arduboy.print(mapX);
  arduboy.print("MapY/X");

  arduboy.setCursor(0, 16);
  arduboy.fillRect(0, 16, 60, 8, BLACK);
  arduboy.print(playerY);
  arduboy.print(",");
  arduboy.print(playerX);
  arduboy.print("PlyrY/X");

  arduboy.setCursor(35, 0);
  arduboy.print("U:");
  arduboy.print((playerY - PLAYER_SPRITE_HEIGHT - mapY) / TILE_SIZE);
  arduboy.print(",");
  arduboy.print("L:");
  arduboy.print((playerX - PLAYER_SPRITE_WIDTH - mapX) / TILE_SIZE);

  arduboy.setCursor(80, 0);
  arduboy.print("D:");
  arduboy.print((playerY + PLAYER_SPRITE_HEIGHT - mapY) / TILE_SIZE);
  arduboy.print(",");
  arduboy.print("R:");
  arduboy.print((playerX + PLAYER_SPRITE_WIDTH - mapX) / TILE_SIZE);
}

void drawPlayer(){
  int tileY = (playerY + PLAYER_SPRITE_HEIGHT/2 - mapY) / TILE_SIZE;
  int tileX = (playerX + PLAYER_SPRITE_WIDTH/2 - mapX) / TILE_SIZE;

  if (arduboy.pressed(DOWN_BUTTON)) {
    sprites.drawPlusMask(playerX, playerY, CHAR_FORWARD_WALKING, counter);

    tileY = (playerY + PLAYER_SPRITE_HEIGHT - mapY) / TILE_SIZE;
    if (playerY + PLAYER_SPRITE_HEIGHT < mapY + TILE_SIZE * WORLD_HEIGHT && world[tileY][tileX] < WATER)
      mapY--;
  }

  else if (arduboy.pressed(UP_BUTTON)){
    sprites.drawPlusMask(playerX, playerY, CHAR_BACK_WALKING, counter);

    tileY = (playerY - PLAYER_SPRITE_HEIGHT - mapY) / TILE_SIZE;
    if (mapY < playerY + PLAYER_SPRITE_HEIGHT / 2 && world[tileY][tileX] < WATER)
      mapY++;
  }

  else if (arduboy.pressed(LEFT_BUTTON))  {
    sprites.drawPlusMask(playerX, playerY, CHAR_LEFT_WALKING, counter);

    tileX = (playerX - PLAYER_SPRITE_WIDTH - mapX) / TILE_SIZE;
    if (mapX < playerX && world[tileY][tileX] < WATER)
      mapX++;
  }

  else if (arduboy.pressed(RIGHT_BUTTON))  {
    sprites.drawPlusMask(playerX, playerY, CHAR_RIGHT_WALKING, counter);

    tileX = (playerX + PLAYER_SPRITE_WIDTH - mapX) / TILE_SIZE;
    if (playerX + PLAYER_SPRITE_WIDTH < mapX + TILE_SIZE * WORLD_WIDTH && world[tileY][tileX] < WATER)
      mapX--;
  }

  else {
    sprites.drawPlusMask(playerX, playerY, CHAR_FORWARD_IDLE, 0);
  }  
  
  drawPlayerHealth();
  debug();
}

void drawPlayerHealth(){
  arduboy.fillRect(3, 3, (maxPlayerHealth * 2) + 2, 7, BLACK);
  arduboy.fillRect(4, 4, (currentPlayerHealth * 2), 5, WHITE);
}

void drawSpider(){
  int spiderX = mapX ;
  int spiderY = 12;
  sprites.drawPlusMask(64 + mapX, 12 + mapY, SPIDER, counter);
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

void setPlayerHealthToFull() {
  currentPlayerHealth = maxPlayerHealth;
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