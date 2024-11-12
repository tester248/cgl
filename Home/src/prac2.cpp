#include <graphics.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a point
struct Point {
    int x, y;
};

// Function to draw a line using DDA algorithm
void lineDDA(int x1, int y1, int x2, int y2, int color = WHITE) 
{ 
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = static_cast<float>(dx) / steps;
    float yinc = static_cast<float>(dy) / steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(static_cast<int>(x), static_cast<int>(y), color); 
        x += xinc;
        y += yinc;
    }
}

// Function to fill a polygon using scan fill algorithm
void scanFill(vector<Point> polygon, int color)
{
    int ymin = polygon[0].y, ymax = polygon[0].y;
    for (Point p : polygon) {
        ymin = min(ymin, p.y);
        ymax = max(ymax, p.y);
    }

    for (int y = ymin; y <= ymax; y++) {
        vector<int> intersections;
        for (int i = 0; i < polygon.size(); i++) {
            int j = (i + 1) % polygon.size();
            if ((polygon[i].y <= y && polygon[j].y > y) || 
                (polygon[j].y <= y && polygon[i].y > y)) {
                float x = polygon[i].x + static_cast<float>(y - polygon[i].y) / (polygon[j].y - polygon[i].y) * (polygon[j].x - polygon[i].x);
                intersections.push_back(static_cast<int>(x));
            }
        }

        sort(intersections.begin(), intersections.end());

        for (int i = 0; i < intersections.size(); i += 2) {
            lineDDA(intersections[i], y, intersections[i + 1], y, color);
        }
    }
}

int main() 
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Define the concave polygon vertices
    vector<Point> polygon = {
        {100, 100},
        {200, 50},
        {300, 100},
        {350, 200},
        {300, 300},
        {200, 250},
        {100, 300}
    };

    // Draw the polygon outline
    for (int i = 0; i < polygon.size(); i++) {
        int j = (i + 1) % polygon.size();
        lineDDA(polygon[i].x, polygon[i].y, polygon[j].x, polygon[j].y);
    }

    // Fill the polygon with a color
    scanFill(polygon, RED);

    getch();
    closegraph();
    return 0;
}