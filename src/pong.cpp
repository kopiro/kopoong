#include "pong.h"

pong::pong(float width, float height) {
    this->width = width;
    this->height = height;
    this->leftPlayer = new player();
    this->rightPlayer = new player();
}

pong::~pong() {
    while (elements.size() > 0) {
        delete elements.back();
        elements.pop_back();
    }
}

float pong::getWidth() {
    return width;
}

float pong::getHeight() {
    return height;
}


int pong::addElement(element *e) {
    elements.push_back(e);
    return elements.size()-1;
}

bool pong::delElement(int index) {
    elements.erase(elements.begin()+index,elements.begin()+index+1);
    return true;
}

element* pong::getElement(int index) {
    if (index<0 || index>elements.size()) return NULL;
    return elements[index];
}

element* pong::getElementByCoo(float x, float y) {
    for (int i=0;i<elements.size();i++) {
        element *e = elements[i];
        if (e->isAt(x,y)) return e;
    }
}

int pong::sizeElements() {
    return elements.size();
}

void pong::moveAll() {
    for (int i=0;i<elements.size();i++) {
        element *e = elements[i];
        //if (e->isAlive())
            e->move();
    }
}
