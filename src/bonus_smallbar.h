#ifndef BONUS_SMALLBAR_H
#define BONUS_SMALLBAR_H
#include "bonus.h"

class bonus_smallbar : public bonus
{
public:
    bonus_smallbar(pong *game, float w, float h, int rand_mod, int interval_showed);
    void touchedByElement(element *e, float e_x_at, float e_y_at);
};

#endif // BONUS_SMALLBAR_H
