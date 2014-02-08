#include "bar.h"

bar::bar(pong *game, float start_x, float start_y, float width, float height, float speed_mult, element::directions position, float touch_dx_comeback, float touch_straight) :
        element(game, start_x, start_y, width, height, 0, 1, "bar", true, speed_mult, position),
        touch_dx_comeback(touch_dx_comeback),
        touch_straight(touch_straight),
        magnetic(false),
        magnetic_element(NULL) {
    image = id + "_" + directionsCastString(position) + ".png";
}

void bar::move() {
    if (position==element::LEFT && x<sx) x+=touch_dx_comeback; //Come back to your position
    if (position==element::RIGHT && x>sx) x-=touch_dx_comeback; //Come back to your position
    if (!alive) return; //Don't move
    dy_moving = 0;
    if (command==UP) dy_moving = -dy;
    else if (command==DOWN) dy_moving = dy;
    if (y+dy_moving<=0) touchedLimit(element::UP);
    if (y+h+dy_moving>=game->getHeight()) touchedLimit(element::DOWN);
    y += dy_moving; //MOVE
    if (magnetic && magnetic_element!=NULL) {
        magnetic_element->setAlive(false);
        if (position==element::LEFT)
            magnetic_element->setCoo(x+w+1, magnetic_element->getY()+dy_moving);
        if (position==element::RIGHT)
            magnetic_element->setCoo(x-1-magnetic_element->getW(), magnetic_element->getY()+dy_moving);
        if (command == element::SPACE)
            releaseMagneticElement();
    }
}

void bar::touchedByElement(element *e, float e_x_at, float e_y_at) {
    if (position==element::LEFT) x-=touch_straight; //Come back
    if (position==element::RIGHT) x+=touch_straight; //Come back
    if (magnetic && magnetic_element==NULL) {
        magnetic_element = e;
        magnetic_element->setAlive(false);
        if (position==element::LEFT)
            magnetic_element->setCoo(magnetic_element->getX()-touch_straight, magnetic_element->getY());
        if (position==element::RIGHT)
            magnetic_element->setCoo(magnetic_element->getX()+touch_straight, magnetic_element->getY());
    }
    emit sign_touchedByElement(this, e);
}

void bar::touchedLimit(element::directions dir) {
    dy_moving = 0;
    if (dir==UP) y=dy;
    else if(dir==DOWN) y=game->getHeight()-h-dy;
    emit sign_touchedLimit(this, dir);
}
void bar::setMagnetic(bool status) {
    magnetic = status;
    if (!status) {
        if (magnetic_element!=NULL)
            releaseMagneticElement();
        magnetic_element = NULL;
    }
}

void bar::releaseMagneticElement() {
    magnetic_element->setAlive(true);
    magnetic_element = NULL;
}


