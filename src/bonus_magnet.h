#ifndef BONUS_MAGNET_H
#define BONUS_MAGNET_H
#include "bonus.h"
#include "bar.h"

class bonus_magnet : public bonus {
private:
    int interval_effect;
    int left_timerid;
    int right_timerid;
public:
    bonus_magnet(pong* game, float w, float h, int rand_mod, int interval_showed, int interval_effect);
    void touchedByElement(element *e, float e_x_at, float e_y_at);
    void timerEvent(QTimerEvent *e);
};

#endif // BONUS_MAGNET_H
