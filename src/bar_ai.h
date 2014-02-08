#ifndef BAR_AI_H
#define BAR_AI_H
#include "bar.h"

class bar_AI : public bar {
private:
    int wrong_y;
    element* busyBall;
public:
    bar_AI(pong *game, float start_x, float start_y, float width, float height, float speed_mult, element::directions position, float touch_dx_comeback, float touch_straight, int wrong_y);
    void move();
    void touchedByElement(element *e, float e_x_at, float e_y_at);
    element* getBusyBall();
};

#endif // BAR_AI_H
