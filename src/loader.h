#ifndef LOADER_H
#define LOADER_H

#include "scene.h"
#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QGridLayout>
#include <QPicture>
#include <QLabel>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QButtonGroup>
#include <QTextStream>


class loader : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup *buttons;
    QGraphicsView *gv_Viewer;
    QPushButton *pb_Exit;
public:
    loader(QWidget *parent = 0);
signals:
public slots:
    void newGame(QAbstractButton* b);
    void exitGame();
};

#endif // LOADER_H
