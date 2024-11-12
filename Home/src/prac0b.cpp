#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <cmath>
using namespace std;
class Circle
{
public:
	void drawCircle(int x, int y, int rad) 
		{
			float dp;
			int x1, y1;
			x1 = 0;
			y1 = rad;
			dp = 3 - 2 * rad;
			while (x1 <= y1)
			{
				display(x1, y1, x, y);
				if (dp <= 0)
				{
					dp += (4 * x1) + 6;
				} else {
					dp += 4 * (x1 - y1) + 10;
					y1--;
				}
				x1++;
			}
		}
	void display(int x1, int y1, int x, int y)
	{
		putpixel(x + x1, y + y1, WHITE);
		putpixel(x + x1, y - y1, WHITE);
		putpixel(x - x1, y + y1, WHITE);
		putpixel(x - x1, y - y1, WHITE);
		putpixel(x + y1, y + x1, WHITE);
		putpixel(x + y1, y - x1, WHITE);
		putpixel(x - y1, y + x1, WHITE);
		putpixel(x - y1, y - x1, WHITE);
	}
};
int main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm,"");
	Circle c;
	cleardevice();
	
	int x, y, r;
	cout << "\nEnter the center coordinates for the circle: ";
	cin >> x >> y;
	cout << "\nEnter the radius of the circle: ";
	cin >> r;
	c.drawCircle(x, y, r);
	getch();
	closegraph();
	return 0;
}
