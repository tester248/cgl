#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// DDA Line Drawing Algorithm
void lineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, WHITE);
        x += xInc;
        y += yInc;
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
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    circle_algo(300, 300, 80);     // Outer circle
    circle_algo(300, 300, 76 / 2);  // Inner circle

    // Calculate triangle vertices
    int radius = 80;
    float angle = 3.14159 / 180; 
    int c = radius * cos(30 * angle);
    int s = radius * sin(30 * angle);

    // Draw the triangle using DDA
    lineDDA(300, 300 - radius, 300 - c, 300 + s); 
    lineDDA(300 - c, 300 + s, 300 + c, 300 + s);
    lineDDA(300 + c, 300 + s, 300, 300 - radius);

    getch();
    closegraph();
    return 0;
}