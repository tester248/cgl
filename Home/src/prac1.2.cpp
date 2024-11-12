#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// DDA Line Drawing Algorithm
void lineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = static_cast<float>(dx) / steps;
    float yinc = static_cast<float>(dy) / steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(static_cast<int>(x), static_cast<int>(y), WHITE);
        x += xinc;
        y += yinc;
    }
}

// Function to plot 8 symmetrical points for circle drawing
void display(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

// Bresenham's Circle Drawing Algorithm
void circle_algo(int x1, int y1, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    display(x1, y1, x, y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        display(x1, y1, x, y);
    }
}

int main() {
    int gd = DETECT, gm = DETECT;
    initgraph(&gd, &gm, NULL);

    // Draw the outer rectangle
    lineDDA(100, 100, 600, 100);
    lineDDA(600, 100, 600, 400);
    lineDDA(600, 400, 100, 400);
    lineDDA(100, 400, 100, 100);

    // Draw the inner lines (forming a diamond shape)
    lineDDA(100, 250, 350, 100);
    lineDDA(350, 100, 600, 250);
    lineDDA(600, 250, 350, 400);
    lineDDA(350, 400, 100, 250);

    // Draw the circle
    circle_algo(350, 250, 250 / 2); 

    getch();
    closegraph();
    return 0;
}