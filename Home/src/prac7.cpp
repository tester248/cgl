#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
using namespace std;
void drawMan(int x, int y) {
  line(x, y, x, y - 50);
  circle(x, y - 60, 10);
  line(x, y, x - 10, y + 30);
  line(x, y, x + 10, y + 30);
  line(x, y - 30, x - 15, y - 10);
  line(x, y - 30, x + 15, y - 10);
  line(x - 30, y - 20, x - 30, y - 80);
  line(x - 80, y - 80, x + 20, y - 80);
  arc(x - 30, y - 80, 0, 180, 50);
}
int main() {
  int gd = DETECT, gm;
  initgraph(&gd, &gm, NULL);
  int x = 100;
  int y = 380;
  while (true) {
    cleardevice();
    line(20, 380, 580, 380);
    drawMan(x, y);

    x += 5;
    if (x > getmaxx()) {
      x = 0;
    }
    setcolor(WHITE);
    for (int j = 0; j < 100; j++) {
      outtextxy(rand() % getmaxx(), rand() % (getmaxy() - 50), "|");
    }
    delay(100);
  }
  closegraph();
  return 0;
}