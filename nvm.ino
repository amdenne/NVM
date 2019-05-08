#include <Arduboy2.h>
#include "bitmaps.h"

#define FRAME_RATE 28
#define FRAMES_IN_TITLE 28

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

Arduboy2 arduboy;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

uint16_t frames = ARRAY_LEN(OUT);
unsigned long counter = 0;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  drawTitle();
  counter++;

  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))
    counter = 0;
}

void drawTitle() {
  if (counter < FRAMES_IN_TITLE) {
    arduboy.clear();
    ardbitmap.drawCompressed(WIDTH / 2, HEIGHT / 2, OUT[counter % frames], WHITE, ALIGN_CENTER, MIRROR_NONE);
    arduboy.display();
  }

  if (counter >= FRAMES_IN_TITLE and counter % 2 == 0) {
    arduboy.setCursor(45, 52);
    arduboy.print("            ");
    arduboy.display();
    if (isButtonPushedWhileDelay(50))
      counter = 0; //TODO: change menu or something
  }

  if (counter >= FRAMES_IN_TITLE and counter % 2 != 0) {
    arduboy.setCursor(45, 52);
    arduboy.print("Press A or B");
    arduboy.display();
    if (isButtonPushedWhileDelay(50))
      counter = 0; //TODO: change menu or something
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
