#ifndef BAR_H
#define BAR_H
#include "element.h"

class bar : public element
{
protected:
    float touch_dx_comeback;
    float touch_straight;
    bool magnetic;
    element* magnetic_element;
    int y_at_of_magnetic_element;
    float dy_moving;
public:
    bar(pong* game, float start_x, float start_y, float width, float height, float speed_mult, element::directions position, float touch_dx_comeback, float touch_straight);
    virtual void move();
    virtual void touchedByElement(element *e, float e_x_at, float e_y_at);
    void touchedLimit(element::directions dir);
    void setMagnetic(bool status);
    void releaseMagneticElement();
};

#endif // BAR_H
