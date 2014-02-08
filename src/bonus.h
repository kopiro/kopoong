#ifndef BONUS_H
#define BONUS_H
#include <cstdlib>
#include "element.h"

class bonus : public element
{
private:
    int bonus_num;
    int rand_mod;
    int interval_showed;
    int timer_id;
public:
    bonus(pong* game, float w, float h, int rand_mod, int interval_showed, std::string id);
    void move();
    void touchedLimit(element::directions dir);
    virtual void touchedByElement(element *e, float e_x_at, float e_y_at) = 0;
    void timerEvent(QTimerEvent *e);
    element::directions whatBar(element *ball);
    void hide();
    void show();
};

#endif // BONUS_H
