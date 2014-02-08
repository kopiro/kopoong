#ifndef BONUS_BIGBAR_H
#define BONUS_BIGBAR_H
#include "bonus.h"

class bonus_bigbar : public bonus {
public:
    bonus_bigbar(pong* game, float w, float h, int rand_mod, int interval_showed);
    void touchedByElement(element *e, float e_x_at, float e_y_at);
};

#endif // BONUS_BIGBAR_H
