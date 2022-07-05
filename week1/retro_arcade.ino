/*
 * Arduino Retro Arcade (Weekend Projects Ep. 1)
 *
 * Created by Collin Wentzien, 2022
 *
 * If you plan to use this code in a video, please credit!
 * Otherwise the code is free to use :)
 *
 */

#include <TVout.h>
#include <fontALL.h>

const int leftkeyup = 6;
const int leftkeydown = 5;
const int rightkeyup = 4;
const int rightkeydown = 3;

int x = 59;
int y = 40;

int leftpos = 20;
int rightpos = 20;

int leftscore = 0;
int rightscore = 0;

int ballspeedx = 1;
int ballspeedy = 1;

int paddlespeed = 1;

TVout TV;

void setup() {
  Serial.begin(9600);
  
  TV.begin(NTSC,120,96);
  TV.select_font(font8x8);

  pinMode(leftkeyup, INPUT);
  pinMode(leftkeydown, INPUT);
  pinMode(rightkeyup, INPUT);
  pinMode(rightkeydown, INPUT);
  
  TV.clear_screen();

  TV.set_cursor(19, 32);
  TV.print("PRESS ANY");
  TV.set_cursor(19, 42);
  TV.print("BUTTON TO");
  TV.set_cursor(19, 52);
  TV.print("START GAME");

  while(digitalRead(leftkeyup) == LOW && digitalRead(leftkeydown) == LOW && digitalRead(rightkeyup) == LOW && digitalRead(rightkeydown) == LOW) {}
}

void loop() {
  TV.clear_screen();
  TV.set_cursor(0, 0);
  TV.print("P1:");
  TV.set_cursor(24, 0);
  TV.print(leftscore);
  TV.set_cursor(59, 0);
  TV.print("P2:");
  TV.set_cursor(83, 0);
  TV.print(rightscore);
  TV.draw_rect(0, 10, 119, 85, WHITE);
  TV.draw_line(59, 10, 59, 95, WHITE);

  drawPaddles();
  isCollided();
  TV.draw_rect(x, y, 3, 3, WHITE, WHITE);

  delay(20);
}

void isCollided() {
  if(x == 5) {
    if(y >= leftpos - 2 && y <= leftpos + 17) {
      ballspeedx = -ballspeedx;
    }
  }

  if(x == 111) {
    if(y >= rightpos - 2 && y <= rightpos + 17) {
      ballspeedx = -ballspeedx;
    }
  }

  if(x < 1) {
    ballspeedx = -ballspeedx;
    rightscore++;
    x = 59;
    y = 40;
  } if(x > 115) {
    ballspeedx = -ballspeedx;
    leftscore++;
    x = 59;
    y = 40;
  } if(y < 11) {
    ballspeedy = -ballspeedy;
  } if(y > 91) {
    ballspeedy = -ballspeedy;
  }

  x += ballspeedx;
  y += ballspeedy;
}

void drawPaddles() {
  if(digitalRead(leftkeyup) == HIGH && leftpos > 11) {
    leftpos -= paddlespeed;
  } else if(digitalRead(leftkeydown) == HIGH && leftpos < 76) {
    leftpos += paddlespeed;
  }

  if(digitalRead(rightkeyup) == HIGH && rightpos > 11) {
    rightpos -= paddlespeed;
  } else if(digitalRead(rightkeydown) == HIGH && rightpos < 76) {
    rightpos += paddlespeed;
  }
  
  TV.draw_rect(3, leftpos, 2, 18, WHITE, WHITE);
  TV.draw_rect(114, rightpos, 2, 18, WHITE, WHITE);
}
