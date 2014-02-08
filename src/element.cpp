#include "element.h"

element::element(pong *game, float x, float y, float w, float h, float dx, float dy, std::string id, bool touchable, float speed_mult, short position) : QObject() {
    this->game = game;
    if (x<0) x = game->getWidth()-abs(x)-w;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->sx = x;
    this->sy = y;
    this->sw = w;
    this->sh = h;
    this->dx = dx*speed_mult;
    this->dy = dy*speed_mult;
    this->id = id;
    this->image = id + ".png";
    this->speed_mult = speed_mult;
    this->s_speed_mult = speed_mult;
    this->position = directions(position);
    this->touchable = touchable;

    //Defaults
    this->command = element::NONE;
    this->alive = true;

    this->id_on_game = this->game->addElement(this);
}

std::string element::directionsCastString(directions d) {
    switch(d) {
    case UP: return "up";
    case DOWN: return "down";
    case LEFT: return "left";
    case RIGHT: return "right";
    case SPACE: return "space";
    }
}

float element::getX() {
    return x;
}

float element::getY() {
    return y;
}

float element::getSX() {
    return sx;
}

float element::getSY() {
    return sy;
}

float element::getW() {
    return w;
}

float element::getH() {
    return h;
}

float element::getSW() {
    return sw;
}

float element::getSH() {
    return sh;
}

float element::getdX() {
    return dx;
}

float element::getdY() {
    return dy;
}

float element::getSpeedMult() {
    return speed_mult;
}

void element::setSpeedMult(float speed_mult) {
    this->speed_mult *= speed_mult;
}

void element::setScaleX(float scale) {
    w *= scale;
}

void element::setScaleY(float scale) {
    h *= scale;
}

bool element::isAt(float x, float y) {
    return (this->x==x && this->y==y) ? true : false;
}

void element::setImagePath(std::string image) {
    this->image = image;
}

std::string element::getImagePath() {
    return image;
}

bool element::isTouchable() {
    return touchable;
}

std::string element::getId() {
    return id;
}

int element::getIdOnGame() {
    return id_on_game;
}

bool element::isAlive() {
    return alive;
}

void element::setAlive(bool status) {
    alive=status;
}

void element::setCommand(element::directions dir) {
    command = dir;
}

void element::setCoo(float x, float y) {
    this->x = x;
    this->y = y;
}

void element::setProp(int w, int h) {
    this->w = w;
    this->h = h;
}

element::directions element::getDirectionX() {
    if (dx==0) return NONE;
    return dx>0 ? RIGHT : LEFT;
}

element::directions element::getDirectionY() {
    if (dy==0) return NONE;
    return dy>0 ? DOWN : UP;
}

element::directions element::getPosition() {
    return position;
}

bool element::isBetween(float x, float a, float b) {
    return x>=a && x<=b;
}

bool element::dedectCollisionWith(element *e) {
   float e_x_at, e_y_at;
   return dedectCollisionWith(e, e_x_at, e_y_at);
}

bool element::dedectCollisionWith(element *e, float &e_x_at, float &e_y_at) {
    // Approssima tutto a rettangoli costruiti all'esterno dell'elemento
    float tmy = y+h/2;
    if (isBetween(x, e->getX(), e->getX()+e->getW())) { // t coming from right <--
        e_x_at = 1.00;
        e_y_at = (tmy-e->getY())/e->getH();
        if (e_y_at>=0 && e_y_at<=1)
            return true;
    }
    if (isBetween(x+w, e->getX(), e->getX()+e->getW())) { // t coming from left -->
        e_x_at = 0.00;
        e_y_at = (tmy-e->getY())/e->getH();
        if (e_y_at>=0 && e_y_at<=1)
            return true;
    }

    float tmx = x+w/2;
    if (isBetween(y, e->getX(), e->getX()+e->getW())) { // t coming from down
        e_y_at = 1.00;
        e_x_at = (tmx-e->getX())/e->getW();
        if (e_x_at>=0 && e_x_at<=1)
            return true;
    }
    if (isBetween(y+h, e->getX(), e->getX()+e->getW())) { // from down
        e_y_at = 0.00;
        e_x_at = (tmx-e->getX())/e->getW();
        if (e_x_at>=0 && e_x_at<=1)
            return true;
    }
    return false;
}
