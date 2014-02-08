#include "bonus_magnet.h"

bonus_magnet::bonus_magnet(pong *game, float w, float h, int rand_mod, int interval_showed, int interval_effect) :
        bonus(game, w, h, rand_mod, interval_showed, "bonus_magnet"),
        interval_effect(interval_effect) {
}

void bonus_magnet::touchedByElement(element *e, float e_x_at, float e_y_at) {
    hide();
    element::directions what_bar = whatBar(e);
    for (int i=0;i<game->sizeElements();i++) {
        element *e = game->getElement(i);
        if (e->getPosition()==what_bar) {
            if (e==NULL || e==this || e->getId()!="bar") continue;
            bar *this_bar = dynamic_cast<bar*>(e); //Cast from ELEMENT -> BAR_AI
            if (this_bar!=NULL) {
                this_bar->setMagnetic(true);
                if (what_bar==element::LEFT) left_timerid = startTimer(interval_effect);
                if (what_bar==element::RIGHT) right_timerid = startTimer(interval_effect);
            }
        }
    }
    emit sign_touchedByElement(this, e);
}

void bonus_magnet::timerEvent(QTimerEvent *t) {
    element::directions what_bar = (t->timerId()==left_timerid) ? element::LEFT : element::RIGHT;
    for (int i=0;i<game->sizeElements();i++) {
        element *e = game->getElement(i);
        if (e->getPosition()==what_bar) {
            if (e==NULL || e==this || e->getId()!="bar") continue;
            bar *this_bar = dynamic_cast<bar*>(e); //Cast from ELEMENT -> BAR_AI
            if (this_bar!=NULL)
                this_bar->setMagnetic(false);
        }
    }
    killTimer(t->timerId());
}
