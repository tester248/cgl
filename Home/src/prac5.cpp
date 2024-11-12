#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;

// Function to move the cursor and draw a line segment
void move(int j, int h, int &x, int &y) {
    if (j == 1) y -= h;
    else if (j == 2) x += h;
    else if (j == 3) y += h;
    else if (j == 4) x -= h;
    lineto(x, y);
}

// Recursive function to generate Hilbert curve
void hilbert(int r, int d, int l, int u, int i, int h, int &x, int &y) {
    if (i > 0) {
        i--;
        hilbert(d, r, u, l, i, h, x, y); 
        move(r, h, x, y);
        hilbert(r, d, l, u, i, h, x, y);
        move(d, h, x, y);
        hilbert(r, d, l, u, i, h, x, y);
        move(l, h, x, y);
        hilbert(u, l, d, r, i, h, x, y);
    }
}

int main() {
    int n, x1, y1;
    int x0 = 50, y0 = 150, x, y, h = 10;
    int r = 2, d = 3, l = 4, u = 1; 

    cout << "Enter the order of the Hilbert curve (n): ";
    cin >> n;

    x = x0;
    y = y0;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    moveto(x, y); // Move to the starting position
    hilbert(r, d, l, u, n, h, x, y); // Generate the Hilbert curve

    getch();
    closegraph();
    return 0;
}