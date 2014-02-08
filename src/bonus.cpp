#include "bonus.h"

bonus::bonus(pong *game, float w, float h, int rand_mod, int interval_showed, std::string id) :
        element(game, 0, 0, w, h, 0, 0, id, false) ,
        rand_mod(rand_mod),
        interval_showed(interval_showed) {
    bonus_num = rand() % rand_mod;
    hide();
}

void bonus::move() {
    if (!alive) {
        int rand_n = rand()%rand_mod;
        if (rand_n == bonus_num) {
            show();
            timer_id = startTimer(interval_showed);
        }
    } else {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e->getId()=="ball") {
                if (e->dedectCollisionWith(this)) {
                    //Why not this->dedectCollisionWith(e)??
                    //Because this foo works fine when you pass the arg with major size of caller.
                    this->touchedByElement(e, 0, 0);
                }
            }
        }
    }
}

void bonus::timerEvent(QTimerEvent *e) {
    hide();
}

void bonus::hide() {
    killTimer(timer_id);
    alive = false;
    setCoo(RAND_MAX,RAND_MAX);
}

void bonus::show() {
    alive = true;
    int x_boundary = w+game->getWidth()/5;
    int y_boundary = h+game->getHeight()/5;
    setCoo( x_boundary + rand() % int(game->getWidth()-x_boundary*2), y_boundary + rand() % int(game->getHeight()-y_boundary*2));
}

void bonus::touchedLimit(element::directions dir) {
}

element::directions bonus::whatBar(element *ball) {
    element::directions what_bar = element::NONE;
    if (ball->getDirectionX()==element::LEFT) what_bar = element::RIGHT;
    else if (ball->getDirectionX()==element::RIGHT) what_bar = element::LEFT;
    return what_bar;
}


