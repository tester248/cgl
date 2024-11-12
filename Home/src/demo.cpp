#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <cmath>
using namespace std;
class Line
{
protected:
	int step;
public:
	void drawLine(int x1, int y1, int x2, int y2)
	{
		int dx = x2 - x1;
		int dy = y2 - y1;
		if (abs(dx) > abs(dy))
			step = abs(dx);
		else
			step = abs(dy);
		float x_i = (float) dx / step;
		float y_i = (float) dy / step;
		float x = x1;
		float y = y1;
		for (int i = 0; i <= step; i++)
		{
			putpixel(round(x), round(y), WHITE);
			x += x_i;
			y += y_i;
		}
	}
};
int main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm,"");
	Line l;
	cleardevice();
	int n;
	cout << "Enter number of lines: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		cout << "Enter the first coordinate (x1, y1): ";
		cin >> x1 >> y1;
		cout << "Enter the last coordinate (x2, y2): ";
		cin >> x2 >> y2;
		l.drawLine(x1, y1, x2, y2);
	}
	getch();
	closegraph();
	return 0;
}
