#include <iostream>
using namespace std;


class Rectangle
{
public:
    Rectangle(int width, int height, int x0, int y0);
    int getWidth();
    int getHeight();
    int getPerimeter();
    void setWidth(int width);
    void setHeight(int height);
    void setOrigin(int x0, int y0);
    void moveBy(int dx, int dy);
    string toString();

private:
    int w; int h;
    int x; int y;
};
