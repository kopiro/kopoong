#include "ball.h"

ball::ball(pong *game, float start_x, float start_y, float diameter, float speed_mult, float touch_speed_mult, float touch_angle_maxdev) :
        element(game, start_x, start_y, diameter, diameter, 0, 0, "ball", false, speed_mult),
        touch_speed_mult(touch_speed_mult),
        touch_angle_maxdev(touch_angle_maxdev) {
            reset();
}

void ball::move() {
    if (!alive) return;
    setCoo(x+dx,y+dy); //Move
    //Control if touched limit
    if (y<=0) touchedLimit(element::UP);
    if (y+h>=game->getHeight()) touchedLimit(element::DOWN);
    if (x<=0) {
        touchedLimit(element::LEFT);
        game->rightPlayer->addPoint();
    }
    if (x+w>=game->getWidth()) {
        touchedLimit(element::RIGHT);
        game->leftPlayer->addPoint();
    }
    //Control Touched By Element
    float e_x_at; float e_y_at;
    for (int i=0 ; i<game->sizeElements() ; i++) {
        element *e = game->getElement(i);
        if (e==NULL || e==this || !e->isTouchable()) continue;
        if (dedectCollisionWith(e, e_x_at, e_y_at)) touchedByElement(e, e_x_at, e_y_at);
    }
}

void ball::touchedByElement(element *e, float e_x_at, float e_y_at) {
    float touch_at; float angle_deviation = 0;
    if (e_x_at==0) {
        touch_at = e_y_at;
        angle_deviation = -touch_angle_maxdev*(2*touch_at-1);
    } else if (e_x_at==1) {
        touch_at = e_y_at;
        angle_deviation = +touch_angle_maxdev*(2*touch_at-1);
    } else if (e_y_at==0 || e_y_at==1) touch_at = e_x_at;
    angle = 180 - angle + angle_deviation; //Invert the angle and calculate the angle
    calculateNewDeltasByAngle();
    for (int i=0;i<3;i++) setCoo(x+dx, y+dx); //To speed-up the ball after touch
    speed_mult *= touch_speed_mult;
    e->touchedByElement(this, e_x_at, e_y_at);
    emit sign_touchedByElement(this, e);
}

void ball::touchedLimit(element::directions dir) {
    if (dir==UP || dir==DOWN) {
        angle *= -1; //Invert the angle
        calculateNewDeltasByAngle();
    } else if (dir==LEFT) reset();
    else if(dir==RIGHT) reset();
    emit sign_touchedLimit(this, dir);
}

void ball::calculateNewDeltasByAngle() {
    //angle = atan(tan(angle));
    dx = speed_mult * cos_deg(angle);
    dy = speed_mult * sin_deg(angle);
}

void ball::reset() {
    setCoo(sx,sy);
    alive = false; //Don't move!
    angle = rand()%2==0 ? 0 : 180; //Rand, left or right
    calculateNewDeltasByAngle();
    speed_mult = s_speed_mult; //Reset the initial speed
    startTimer(1000);
}

void ball::timerEvent(QTimerEvent *e) {
    alive = true; //Move
    killTimer(e->timerId());
}

float ball::cos_deg(float angle) {
    return cos(angle*M_PI/180);
}

float ball::sin_deg(float angle) {
    return sin(angle*M_PI/180);
}
