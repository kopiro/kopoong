#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QSound>
#include <QDesktopWidget>
#include <QTimerEvent>
#include <QFile>
#include <QSettings>
#include <Qstring>
#include <QPixmap>
#include <vector>
#include <fstream>

#include "pong.h"
#include "bar.h"
#include "bar_ai.h"
#include "bonus_bigbar.h"
#include "bonus_smallbar.h"
#include "bonus_magnet.h"
#include "ball.h"

class scene : public QGraphicsScene { Q_OBJECT

private:

    std::vector<QGraphicsPixmapItem*> gfxitems;

    QString keys;
    bool accept_tricks;
    void checkIfTrick();
    QGraphicsTextItem *msg_text;

    bool paused;
    bool stopped;

    int msg_timer_id;
    int move_timer_id;
    int refresh_timer_id;

    QGraphicsTextItem *player_left_txt;
    QGraphicsTextItem *player_right_txt;
    QGraphicsTextItem *player_win_text;

    QGraphicsRectItem *bound_hover;

    pong *game;
    QSettings *settings;

    void newGame();

    unsigned int K0U, K0D, K1U, K1D;
    QColor CFore, CBack;

public:

    scene(QString t);
    ~scene();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QString gametype;

    void pause();
    void play();
    void stop();


signals:
public slots:

    void updatePoints();
    void slot_touchedElement(element *sender, element* e);
    void slot_touchedLimit(element *sender, element::directions dir);

protected:

    void timerEvent(QTimerEvent *event);
};

#endif // SCENE_H
