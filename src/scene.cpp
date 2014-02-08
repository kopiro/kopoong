#include "scene.h"

scene::scene(QString t) : QGraphicsScene(), paused(false), stopped(false) {
    settings = new QSettings("game/settings.ini", QSettings::IniFormat);
    gametype = t;
    qDebug()<<"receveid type "<<gametype;
    CFore = settings->value("game/color_fore").value<QColor>();
    CBack = settings->value("game/color_back").value<QColor>();
    //Set commands keys
    K0U = settings->value("commands/key_0_up").toInt();
    K0D = settings->value("commands/key_0_down").toInt();
    K1U = settings->value("commands/key_1_up").toInt();
    K1D = settings->value("commands/key_1_down").toInt();
    newGame();
}

scene::~scene() {
    delete game;
}

void scene::newGame() {
    gfxitems.clear();
    QDesktopWidget desktop;
    game = new pong(desktop.screenGeometry().width()-30, desktop.screenGeometry().height()-40);
    //game = new pong(desktop.width(), desktop.height());
    std::ifstream level(gametype.toStdString().c_str());
    qDebug()<<"reading file "<<gametype;
    std::string type;
    float x;
    float speed_mult;
    short pos;
    float wrong_ai;
    std::string bonus_name_string;
    while (level.good()) {
        level>>type;
        if (type=="new:bar") {
            level>>x;
            level>>speed_mult;
            level>>pos;
            new bar(game,
                    x,
                    (game->getHeight()-settings->value("bar/height").toFloat())/2,
                    settings->value("bar/width").toFloat(),
                    settings->value("bar/height").toFloat(),
                    speed_mult,
                    element::directions(pos),
                    settings->value("bar/touch_dx_comeback").toFloat(),
                    settings->value("bar/touch_straight").toFloat());
        } else if (type=="new:bar_ai") {
            level>>x;
            level>>speed_mult;
            level>>pos;
            level>>wrong_ai;
            new bar_AI(game,
                       x,
                       (game->getHeight()-settings->value("bar/height").toFloat())/2,
                       settings->value("bar/width").toFloat(),
                       settings->value("bar/height").toFloat(),
                       speed_mult,
                       element::directions(pos),
                       settings->value("bar/touch_dx_comeback").toFloat(),
                       settings->value("bar/touch_straight").toFloat(),
                       wrong_ai);
        } else if (type=="new:ball") {
            level>>speed_mult;
            new ball(game,
                     (game->getWidth()-settings->value("ball/diameter").toFloat())/2,
                     (game->getHeight()-settings->value("ball/diameter").toFloat())/2,
                     settings->value("ball/diameter").toFloat(),
                     speed_mult,
                     settings->value("ball/touch_speed_mult").toFloat(),
                     settings->value("ball/touch_angle_maxdev").toFloat());
        } else if (type=="new:bonus") {
            level>>bonus_name_string;
            QString bonus_name = QString::fromStdString("bonus_"+bonus_name_string);
            if (bonus_name=="bonus_bigbar") {
                new bonus_bigbar(game,
                                 settings->value(bonus_name+"/width").toFloat(),
                                 settings->value(bonus_name+"/height").toFloat(),
                                 settings->value(bonus_name+"/randappear").toInt(),
                                 settings->value(bonus_name+"/timeshow").toInt());
            } else if (bonus_name=="bonus_smallbar") {
                new bonus_smallbar(game,
                                   settings->value(bonus_name+"/width").toFloat(),
                                   settings->value(bonus_name+"/height").toFloat(),
                                   settings->value(bonus_name+"/randappear").toInt(),
                                   settings->value(bonus_name+"/timeshow").toInt());
            } else if (bonus_name=="bonus_magnet") {

                new bonus_magnet(game,
                                 settings->value(bonus_name+"/width").toFloat(),
                                 settings->value(bonus_name+"/height").toFloat(),
                                 settings->value(bonus_name+"/randappear").toInt(),
                                 settings->value(bonus_name+"/timeshow").toInt(),
                                 settings->value(bonus_name+"/timeeffect").toInt());
            }
        }
    }

    level.close();
    //Set Players
    game->leftPlayer->setName(settings->value("game/pleft_name").toString().toStdString());
    for (int i=0;i<game->sizeElements();i++) {
        element *e = game->getElement(i);
        if (e->getPosition()==element::LEFT) {
            game->leftPlayer->addID(e->getIdOnGame());
        }
    }
    game->rightPlayer->setName(settings->value("game/pright_name").toString().toStdString());
    for (int i=0;i<game->sizeElements();i++) {
        element *e = game->getElement(i);
        if (e->getPosition()==element::RIGHT) {
            game->leftPlayer->addID(e->getIdOnGame());
        }
    }
    connect(game->leftPlayer, SIGNAL(pointsChanged()), this, SLOT(updatePoints()));
    connect(game->rightPlayer, SIGNAL(pointsChanged()), this, SLOT(updatePoints()));
    //Build scene
    setSceneRect(0, 0, game->getWidth(), game->getHeight());
    addRect(0, 0, game->getWidth(), game->getHeight(), QPen(CBack), QBrush(CBack));
    addPixmap(QPixmap("images/back.jpg").scaled(QSize(game->getWidth(), game->getHeight()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //addLine(game->getWidth()/2, 0, game->getWidth()/2, game->getHeight(), QPen(CFore, 5, Qt::DashLine));
    addLine(0,0,0,game->getHeight(), QPen(CFore, 5, Qt::DashLine));
    addLine(game->getWidth(), 0, game->getWidth(), game->getHeight(), QPen(CFore, 5, Qt::DashLine));
    addLine(0,0,game->getWidth(),0,QPen(CFore, 5));
    addLine(0,game->getHeight(),game->getWidth(),game->getHeight(),QPen(CFore, 5));
    player_left_txt = addText("0", QFont("Helvetica",30,1));
    player_right_txt = addText("0", QFont("Helvetica",30,1));
    player_left_txt->setDefaultTextColor(CFore);
    player_right_txt->setDefaultTextColor(CFore);
    //For each element -> graphicsItem
    for (int i=0; i<game->sizeElements(); i++) {
        element *e = game->getElement(i);
        connect(e, SIGNAL(sign_touchedByElement(element*,element*)), this, SLOT(slot_touchedElement(element*,element*)));
        connect(e, SIGNAL(sign_touchedLimit(element*,element::directions)), this, SLOT(slot_touchedLimit(element*,element::directions)));
        QPixmap p = QPixmap(QString::fromStdString("images/"+e->getImagePath()));
        QGraphicsPixmapItem *g = this->addPixmap(p);
        gfxitems.push_back(g);
        g->setPos(e->getX(), e->getY());
        g->setPixmap(g->pixmap().scaled(e->getW(), e->getH(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    //Set OthText
    msg_text = addText("", QFont("Helvetica", 26, true));
    msg_text->setDefaultTextColor(CFore);
    bound_hover = addRect(0,0,game->getWidth(),game->getHeight(), QPen(CBack), QBrush(CBack));
    player_win_text = addText("",QFont("Helvetica", 60, true));
    player_win_text->setDefaultTextColor(CFore);
    player_win_text->hide();
    updatePoints();
    play();
}


void scene::timerEvent(QTimerEvent *event) {
    if (event->timerId()==move_timer_id) {
        game->moveAll();
        return;
    }
    if (event->timerId()==refresh_timer_id) {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e!=NULL) {
                QGraphicsPixmapItem *g = gfxitems[i];
                if (g->pos().x()!=e->getX() || g->pos().y()!=e->getY()) g->setPos(e->getX(), e->getY());
                if (g->pixmap().size().width()!=e->getW() || g->pixmap().size().height()!=e->getH())
                    g->setPixmap(g->pixmap().scaled(e->getW(), e->getH(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                //if (e->getId()=="ball")
                    //g->rotate(g->rotation()+20);

            }
        }
        return;
    }
    if (event->timerId()==msg_timer_id) {
        msg_text->hide();
    }
}

void scene::updatePoints() {
    player_left_txt->setPlainText(QString::fromStdString(game->leftPlayer->getName()) + ":  "+ QString::number(game->leftPlayer->getPoints()));
    player_right_txt->setPlainText(QString::fromStdString(game->rightPlayer->getName()) + ":  " + QString::number(game->rightPlayer->getPoints()));
    player_left_txt->setPos(game->getWidth()/4-player_left_txt->boundingRect().width()/2, game->getHeight()/8);
    player_right_txt->setPos(game->getWidth()-game->getWidth()/4-player_right_txt->boundingRect().width()/2, game->getHeight()/8);
    if (game->leftPlayer->getPoints()>game->rightPlayer->getPoints()) {
        player_left_txt->setDefaultTextColor(QColor("green"));
        player_right_txt->setDefaultTextColor(QColor("red"));
    } else if (game->leftPlayer->getPoints()<game->rightPlayer->getPoints()) {
        player_right_txt->setDefaultTextColor(QColor("green"));
        player_left_txt->setDefaultTextColor(QColor("red"));
    } else {
        player_right_txt->setDefaultTextColor(QColor(CFore));
        player_left_txt->setDefaultTextColor(QColor(CFore));
    }
    player* player_win = NULL;
    if (game->leftPlayer->getPoints()>=settings->value("game/points_towin").toInt()) player_win = game->leftPlayer;
    if (game->rightPlayer->getPoints()>=settings->value("game/points_towin").toInt()) player_win = game->rightPlayer;
    if (player_win!=NULL) {
        stop();
        bound_hover->show();
        player_win_text->setPlainText(QString::fromStdString(player_win->getName())+" WON!");
        player_win_text->setDefaultTextColor(CFore) ;
        player_win_text->setPos(game->getWidth()/2-player_win_text->boundingRect().width()/2, game->getHeight()/2-player_win_text->boundingRect().height()/2);
        player_win_text->show();
        QSound::play("sounds/win.wav");
    }
}

void scene::slot_touchedElement(element *sender, element *e) {
    if (settings->value("game/audio").toBool()) {
        std::string sound = "sounds/"+sender->getId()+"_touch_"+e->getId()+".wav";
        if (QFile::exists(QString::fromStdString(sound)))
            QSound::play(QString::fromStdString(sound));
    }
}

void scene::slot_touchedLimit(element *sender, element::directions dir) {
    if (settings->value("game/audio").toBool()) {
        std::string dir_string = (dir==element::LEFT || dir==element::RIGHT) ? "ofb" : "limit";
        std::string sound = "sounds/"+sender->getId()+"_"+dir_string+".wav";
        if (QFile::exists(QString::fromStdString(sound)))
            QSound::play(QString::fromStdString(sound));
    }
}

void scene::keyPressEvent(QKeyEvent *event) {
    if (event->key()==K0U) {
        game->getElement(0)->setCommand(element::UP);
        return;
    }
    if (event->key()==K0D) {
        game->getElement(0)->setCommand(element::DOWN);
        return;
    }
    if (event->key()==K1U) {
        game->getElement(1)->setCommand(element::UP);
        return;
    }
    if (event->key()==K1D) {
        game->getElement(1)->setCommand(element::DOWN);
        return;
    }
}

void scene::keyReleaseEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_L || event->key()==Qt::Key_R) {
        accept_tricks = true;
        keys.clear();
        keys.append(event->text());
        return;
    }
    if (accept_tricks) {
        keys.append(event->text());
        checkIfTrick();
    }

    if (event->key()==K0U) {
        game->getElement(0)->setCommand(element::NONE);
        return;
    }
    if (event->key()==K0D) {
        game->getElement(0)->setCommand(element::NONE);
        return;
    }
    if (event->key()==K1U) {
        game->getElement(1)->setCommand(element::NONE);
        return;
    }
    if (event->key()==K1D) {
        game->getElement(1)->setCommand(element::NONE);
        return;
    }
    if (event->key()==Qt::Key_P) {
        if (paused) play();
        else pause();
        return;
    }
    if (event->key()==Qt::Key_N) {
        newGame();
    }
    if (event->key()==Qt::Key_Escape) {
        delete this;
        //exit(0);
    }
    if (event->key()==Qt::Key_Space) {
        game->getElement(0)->setCommand(element::SPACE);
        game->getElement(1)->setCommand(element::SPACE);
    }
}

void scene::pause() {
    if (stopped) return;
    paused = true;
    msg_text->setPlainText("PAUSE");
    msg_text->show();
    killTimer(move_timer_id);
    killTimer(refresh_timer_id);
    killTimer(msg_timer_id);
}

void scene::stop() {
    stopped = true;
    killTimer(move_timer_id);
    killTimer(refresh_timer_id);
    killTimer(msg_timer_id);
}

void scene::play() {
    paused = false;
    stopped = false;
    bound_hover->hide();
    msg_text->hide();
    move_timer_id = startTimer(settings->value("timers/move").toInt());
    refresh_timer_id = startTimer(settings->value("timers/refresh").toInt());
}

void scene::checkIfTrick() {
    bool tricked = false;
    element::directions mpos = keys.left(1)=="l" ? element::LEFT : element::RIGHT;
    QString mkeys = keys.right(keys.length()-1);
    qDebug()<<mkeys;
    if (mkeys == "six") {
        if (mpos==element::LEFT) game->leftPlayer->addPoint(10);
        if (mpos==element::RIGHT) game->rightPlayer->addPoint(10);
        tricked = true;
    } else if (mkeys == "fast") {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e->getId()=="bar" && e->getPosition()==mpos)
                e->setSpeedMult(1.5);
        }
        tricked = true;
    } else if (mkeys == "big") {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e->getId()=="bar" && e->getPosition()==mpos)
                e->setScaleY(1.5);
        }
        tricked =true;
    } else if (mkeys == "sm") {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e->getId()=="bar" && e->getPosition()==mpos)
                e->setScaleY(0.75);
        }
        tricked =true;
    } else if (mkeys == "mag") {
        for (int i=0;i<game->sizeElements();i++) {
            element *e = game->getElement(i);
            if (e->getId()=="bar" && e->getPosition()==mpos) {
                bar* b = (bar*)e;
                b->setMagnetic(true);
            }
        }
        tricked = true;
    }
    if (tricked) {
        accept_tricks = false;
        keys.clear();
        msg_text->setPlainText("CHEAT ACTIVATED!");
        msg_text->show();
        msg_timer_id = startTimer(1000);
    }
}



