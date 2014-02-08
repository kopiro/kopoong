#ifndef ELEMENT_H
#define ELEMENT_H
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QTimerEvent>
#include <string>
#include "pong.h"

class pong;

class element : public QObject {
    Q_OBJECT
public:
    element (pong* game, float x, float y, float w, float h, float ix, float iy, std::string id, bool touchable = true, float speed_mult = 1, short position = NONE);

    float getX();
    float getY();
    float getSX();
    float getSY();
    float getW();
    float getH();
    float getSW();
    float getSH();
    float getdX();
    float getdY();

    enum directions { NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, SPACE = 5 };
    std::string directionsCastString(directions d);

    bool isAt(float x, float y);
    bool isBetween(float x, float a, float b);
    bool isAlive();
    bool isTouchable();
    float getSpeedMult();
    element::directions getDirectionX();
    element::directions getDirectionY();
    element::directions getPosition();
    std::string getId();
    std::string getImagePath();
    int getIdOnGame();

    void setCoo(float x, float y);
    void setProp(int w, int h);
    void setAlive(bool status);
    void setSpeedMult(float speed_mult);
    void setCommand(element::directions dir);
    void setScaleX(float scale);
    void setScaleY(float scale);
    void setImagePath(std::string image);

    bool dedectCollisionWith(element *e);
    bool dedectCollisionWith(element *e, float &e_x_at, float &e_y_at);

    // Questi metodi sotto vanno necessariamente implementati nella sottoclasse!
    virtual void move() = 0;
    virtual void touchedLimit(element::directions dir) = 0;
    virtual void touchedByElement(element *e, float e_x_at, float e_y_at) = 0;

protected:
    pong *game;
    float x, y; //Coordinate
    float sx, sy; //Coordinate iniziali
    float dx, dy; //Incrementi delle coordinate
    float w, h; //Lunghezza e altezza
    float sw, sh;
    float speed_mult;
    float s_speed_mult;
    int id_on_game;
    directions command;
    std::string id;
    std::string image;
    bool alive;
    bool touchable;
    directions position; //A destra o sinistra dello schermo
signals:
    void sign_touchedLimit(element *sender, element::directions dir);
    void sign_touchedByElement(element *sender, element *e);
};

#endif // ELEMENT_H
