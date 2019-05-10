#define FRAME_RATE 30
#define NO_SCENE 0
#define GAME_TITLE 1
#define GAME_PLAY 2
#define GAME_OVER 3

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
    createMenu();
  }
  else if(currentScene == NO_SCENE)
  {
    for(byte x = 0; x < WIDTH; x++){
      for(byte y = 0; y < HEIGHT; y++){
        sprites.drawSelfMasked(x, y, GRASS_SPRITE, counter);
      }
    }
    arduboy.display();

    if (arduboy.pressed(B_BUTTON)) {
      lastScene = NO_SCENE;
      currentScene = GAME_TITLE;
    }
  }
  else if (currentScene == GAME_PLAY) {
    while (currentScene == GAME_PLAY) {
      playGame();
      
      if(arduboy.pressed(B_BUTTON)) {
        lastScene = GAME_PLAY;
        currentScene = GAME_TITLE;
      }
    }
  }
  else if (currentScene == GAME_OVER) {
    while (currentScene == GAME_OVER) {
      drawGameOverScene(true);
      if (arduboy.pressed(B_BUTTON)) {
        lastScene = GAME_OVER;
        currentScene = GAME_TITLE;
      }
    }
  }
}

void drawGameOverScene(bool animateGameOver){
  while (animateGameOver)  {
    arduboy.clear();
    arduboy.setCursor(4, HEIGHT / 2);
    char gameOverText[15] = "Wow, you suck.";
    for (byte i = 0; strlen(gameOverText) >= i; i++) {
      arduboy.print(gameOverText[i]);
      arduboy.display();
      arduboy.delayShort(250);
    }
    arduboy.delayShort(1000);
    arduboy.clear();
    arduboy.setCursor(4, HEIGHT / 2);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(1000);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(1000);
    arduboy.print(".");
    arduboy.display();
    arduboy.delayShort(1000);
    arduboy.clear();
    arduboy.setTextSize(2);
    arduboy.setCursor(4, 20);
    arduboy.println("gitgudlul");
    arduboy.display();
    arduboy.setTextSize(1);
    arduboy.delayShort(3000);
    animateGameOver = false;
  }
}
void playGame(){
  arduboy.clear();  
  arduboy.setCursor(4, HEIGHT/2);
  arduboy.println("this is the");
  arduboy.println("game scene");
  arduboy.display();  
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
  else if(arduboy.justPressed(A_BUTTON)) {
    lastScene = currentScene;
    currentScene = selectedOption;
  }
  else if(arduboy.justPressed(LEFT_BUTTON)){
    lastScene = currentScene;
    currentScene = NO_SCENE;
  }

  arduboy.delayShort(30);
}


void highlightItem(byte selectedOption) {
  if (selectedOption == GAME_TITLE)
    highlightFirstItem();
  else if (selectedOption == GAME_PLAY)
    highlightSecondItem();
  else if (selectedOption == GAME_OVER)
    highlightThirdItem();
}

void highlightThirdItem() {
  arduboy.drawRect(2, 43, 40, 11, WHITE);
  arduboy.display();
}

void highlightSecondItem() {
  arduboy.drawRect(2, 28, 40, 11, WHITE);
  arduboy.display();
}

void highlightFirstItem() {
  arduboy.drawRect(2, 13, 28, 11, WHITE);
  arduboy.display();
}

void playNevermindSplash() {
  animateNevermindDown(-16, 10, 2);
  animateGamesRight(-80, 45, 10);
  arduboy.delayShort(500);
  arduboy.clear();
}

void createMenu() {
  arduboy.clear();
  sprites.drawPlusMask(64, -2, gate_plus_mask, counter);
  drawMenu();
  arduboy.display();
}

void drawMenu(){
  arduboy.setCursor(4, 15);
  arduboy.println("Test");
  arduboy.setCursor(4, 30);
  arduboy.println("Test 2");
  arduboy.setCursor(4, 45);
  arduboy.println("Test 3");
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

boolean isButtonPushedWhileDelay(int delayTime) {
  for (byte i = 0; i < delayTime; i++)
  {
    arduboy.delayShort(10);
    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      return true;
    }
  }
  return false;
}
