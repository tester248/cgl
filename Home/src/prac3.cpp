#include <iostream>
#include <graphics.h>

using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;   // 1000

int computeCode(double x, double y, int x_min, int y_min, int x_max, int y_max) {
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

void cohenSutherlandClip(double x1, double y1, double x2, double y2, int x_min, int y_min, int x_max, int y_max) {
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
    int code2 = computeCode(x2, y2, x_min, y_min, x_max, y_max);

    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        } else if (code1 & code2) {
            // If both endpoints are outside rectangle, in same region
            break;
        } else {
            // Some segment of line lies within the rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }
            // Replace point outside rectangle by intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, x_min, y_min, x_max, y_max);
            }
        }
    }
    if (accept) {
        setcolor(RED);
        line(x1, y1, x2, y2);
    } else {
        cout << "Line lies completely outside the clipping window." << endl;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define a fixed clipping window 
    int x_min = 100, y_min = 100, x_max = 400, y_max = 300; 

    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    int x1, y1, x2, y2;
    cout << "Enter coordinates of line (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw the original line in white
    setcolor(WHITE);
    line(x1, y1, x2, y2);

    // Clip the line and draw the clipped portion in red
    cohenSutherlandClip(x1, y1, x2, y2, x_min, y_min, x_max, y_max);

    getch();
    closegraph();
    return 0;
}