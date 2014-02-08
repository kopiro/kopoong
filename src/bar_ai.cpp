#include "bar_ai.h"

bar_AI::bar_AI(pong *game, float start_x, float start_y, float width, float height, float speed_mult, element::directions position, float touch_dx_comeback, float touch_straight, int wrong_y) :
        bar(game, start_x, start_y, width, height, speed_mult, position, touch_dx_comeback, touch_straight),
        wrong_y(wrong_y),
        busyBall(NULL) {
        image = id + "_" + directionsCastString(position) + ".png";
}

void bar_AI::move() {
    setCommand(element::NONE);
    if (busyBall!=NULL) {
        if (busyBall->getDirectionX()==getPosition()) {
            int wrong_y_gen = -(rand()%wrong_y)+(rand()%wrong_y*2);
            if (busyBall->getY() + wrong_y_gen > y+(h/2)) setCommand(element::DOWN);
            else if (busyBall->getY() + wrong_y_gen < y+(h/2)) setCommand(element::UP);
        } else busyBall = NULL;
    } else {
        element *prior_ball = NULL;
        bool is_available;
        for (int i=0;i<game->sizeElements();i++) {
            is_available = true;
            element *tmp_ball = game->getElement(i);
            if (tmp_ball==NULL || tmp_ball==this) continue;
            if (tmp_ball->getId()=="ball" && tmp_ball->getDirectionX()==this->getPosition()) {
                for (int j=0;j<game->sizeElements();j++) {
                    element *e = game->getElement(j);
                    if (e==NULL || e==this || e->getId()!="bar") continue;
                    bar_AI *oth_bar = dynamic_cast<bar_AI*>(e);
                    if (oth_bar!=NULL)
                        if (oth_bar->getBusyBall()==tmp_ball)
                            is_available = false;
                }
                if (!is_available) continue;
                if (prior_ball==NULL) prior_ball = tmp_ball; //First initialization exception
                //The distance between two points (sqrt((xa-xb)^2+(ya+yb)^2))
                if ( sqrt( ((x-prior_ball->getX())*(x-prior_ball->getX())) + ((x-prior_ball->getX())*(x-prior_ball->getX())) ) <=
                     sqrt( ((x-tmp_ball->getX())*(x-tmp_ball->getX())) + ((y-tmp_ball->getY())*(y-tmp_ball->getY())) ) )
                    prior_ball = tmp_ball;
            }
        }
        busyBall = prior_ball;
    }
    if (magnetic_element!=NULL)
        if (rand()%500==0)
            releaseMagneticElement();
    bar::move();
}

void bar_AI::touchedByElement(element *e, float e_x_at, float e_y_at) {
    if (e==busyBall) busyBall=NULL;
    bar::touchedByElement(e, e_x_at, e_y_at);
}

element* bar_AI::getBusyBall() {
    return busyBall;
}

