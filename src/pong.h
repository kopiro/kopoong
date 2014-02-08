#ifndef PONG_H
#define PONG_H
#include <vector>
#include "element.h"
#include "player.h"

class element;

class pong {
private:
    std::vector<element*> elements;
    float width, height;
public:
    pong(float width, float height);
    ~pong();

    float getWidth();
    float getHeight();

    int addElement(element *e);
    bool delElement(int index);
    element* getElement(int index);
    element* getElementByCoo(float x, float y);
    int sizeElements();

    void moveAll();

    player* leftPlayer;
    player* rightPlayer;
};

#endif // PONG_H
