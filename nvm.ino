#include <Arduboy2.h>
#define FRAME_RATE 30
#define NO_SCENE 0
#define GAME_TITLE 1
#define GAME_PLAY 2
#define GAME_OVER 3

Arduboy2 arduboy;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

unsigned long counter = 0;
int lastScene = NO_SCENE;
int selectedOption = 1;
int currentScene;


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

  counter++;
}

void setScene() {
  lastScene = currentScene;
  if (currentScene == GAME_TITLE) {
    menuSelectionStuff();
    createMenu();
  }
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

  highlightItem(selectedOption);
  arduboy.delayShort(50);
}


void highlightItem(int selectedOption) {
  if (selectedOption == 1)
    highlightFirstItem();
  else if (selectedOption == 2)
    highlightSecondItem();
  else if (selectedOption == 3)
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
  animateNevermindDown();
  animateGamesRight();
  arduboy.delayShort(500);
  arduboy.clear();
}

void createMenu() {
  arduboy.clear();
  arduboy.setCursor(4, 15);
  arduboy.println("Test");
  arduboy.setCursor(4, 30);
  arduboy.println("Test 2");
  arduboy.setCursor(4, 45);
  arduboy.println("Test 3");
  arduboy.display();
}

void animateNevermindDown() {
  int y = -16;
  while (y < 10) {
    if (arduboy.nextFrame()) {
      arduboy.clear();
      arduboy.drawBitmap(0, y, NEVERMIND, 128, 16, WHITE);
      arduboy.display();
      y += 2;
    }
  }
}

void animateGamesRight() {
  int x = -80;
  while (x < 45) {
    if (arduboy.nextFrame()) {
      arduboy.clear();
      arduboy.drawBitmap(0, 10, NEVERMIND, 128, 16, WHITE);
      arduboy.drawBitmap(x, 29, GAMES, 80, 17, WHITE);
      arduboy.display();
      x += 10;
    }
  }
}

boolean isButtonPushedWhileDelay(int delayTime) {
  for (int i = 0; i < delayTime; i++)
  {
    arduboy.delayShort(10);
    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      return true;
    }
  }
  return false;
}
