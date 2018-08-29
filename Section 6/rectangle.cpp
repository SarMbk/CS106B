#include "rectangle.h"

Rectangle::Rectangle(int width, int height, int x0, int y0){
    this->w = width;
    this->h = height;
    this->x = x0;
    this->y = y0;
}

int Rectangle:: getHeight(){
    return this->h;
}

int Rectangle::getWidth(){
    return this->w;
}

int Rectangle::getPerimeter(){
    return 2*(this->w + this->h);
}

void Rectangle::setHeight(int height){
    this->h = height;
}

void Rectangle::setWidth(int width){
    this->w = width;
}

void Rectangle::setOrigin(int x0, int y0){
    this->x = x0;
    this->y = y0;
}

void Rectangle::moveBy(int dx, int dy){
    this->x+=dx;
    this->y+=dy;
}


string Rectangle::toString(){
    return "width:" + std::to_string(w) + "  height:" + std::to_string(h)+
           "  x0:" + std::to_string(x) + "  y0:" + std::to_string(y);
}
