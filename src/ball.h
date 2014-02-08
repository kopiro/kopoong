#ifndef BALL_H
#define BALL_H
#include "element.h"

class ball : public element
{
private:
    float angle;
    float touch_speed_mult;
    float touch_angle_maxdev;
public:
    ball(pong *game, float start_x, float start_y, float diameter, float speed_mult, float touch_speed_mult, float touch_angle_maxdev);
    void move();
    void calculateNewDeltasByAngle();
    void reset();
    void touchedByElement(element *e, float e_x_at, float e_y_at);
    void touchedLimit(element::directions dir);
    float sin_deg(float angle);
    float cos_deg(float angle);
    void timerEvent(QTimerEvent *e);
};

#endif // BALL_H
