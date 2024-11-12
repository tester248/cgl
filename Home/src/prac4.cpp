#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;
class Point
{
public:
  int x, y;
  Point()
  {
    x = 0;
    y = 0;
  }
  Point(int x1, int y1)
  {
    x = x1;
    y = y1;
  }
  Point operator+(Point p)
  {
    Point result;
    result.x = x + p.x;
    result.y = y + p.y;
    return result;
  }
  Point operator*(float scale)
  {
    Point result;
    result.x = x * scale;
    result.y = y * scale;
    return result;
  }

  Point rotate(float angle)
  {
    Point result;
    float rad = angle * M_PI / 180.0;
    result.x = x * cos(rad) - y * sin(rad);
    result.y = x * sin(rad) + y * cos(rad);
    return result;
  }
};
class Shape
{
public:
  Point vertices[4];
  Shape(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
  {
    vertices[0] = Point(x1, y1);
    vertices[1] = Point(x2, y2);
    vertices[2] = Point(x3, y3);
    vertices[3] = Point(x4, y4);
  }
  void draw(int color = WHITE)
  {
    setcolor(color);
    for (int i = 0; i < 4; i++) {
      line(vertices[i].x,
           vertices[i].y,
           vertices[(i + 1) % 4].x,
           vertices[(i + 1) % 4].y);
    }
  }
  void translate(Point translation_vector)
  {
    for (int i = 0; i < 4; i++) {
      vertices[i] = vertices[i] + translation_vector;
    }
  }
  void scale(float scale_factor)
  {
    for (int i = 0; i < 4; i++) {
      vertices[i] = vertices[i] * scale_factor;
    }
  }
  void rotate(float angle)
  {
    for (int i = 0; i < 4; i++) {
      vertices[i] = vertices[i].rotate(angle);
    }
  }
};

int
main()
{
  int gd = DETECT, gm;
  initgraph(&gd, &gm, NULL);
  Shape square(100, 100, 200, 100, 200, 200, 100, 200);
  square.draw();
  delay(2000);
  cleardevice();
  square.translate(Point(15, 5));
  square.draw();
  delay(2000);
  cleardevice();
  square.scale(1.2);
  square.draw();
  delay(2000);
  cleardevice();
  square.rotate(20);
  square.draw();
  delay(2000);
  getch();
  closegraph();
  return 0;
}