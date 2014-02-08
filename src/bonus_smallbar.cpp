#include "bonus_smallbar.h"

bonus_smallbar::bonus_smallbar(pong *game, float w, float h, int rand_mod, int interval_showed) :
        bonus(game, w,  h, rand_mod, interval_showed, "bonus_smallbar") {
}

void bonus_smallbar::touchedByElement(element *e, float e_x_at, float e_y_at) {
    hide();
    element::directions what_bar = whatBar(e);
    for (int i=0;i<game->sizeElements();i++) {
        element *e = game->getElement(i);
        if (e->getPosition()==what_bar)
            e->setScaleY(0.75);
    }
    emit sign_touchedByElement(this, e);
}
