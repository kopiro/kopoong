#include "loader.h"

loader::loader(QWidget *parent) : QWidget(parent) {

    QFile::copy("../../../resources/*", ".");

    setFixedSize(0,0);
    setWindowIcon(QIcon("images/myapp.ico"));
    QGridLayout *layout = new QGridLayout();
    QLabel *lb_Logo = new QLabel();
    lb_Logo->setPixmap(QPixmap("images/logo.png"));
    layout->addWidget(lb_Logo);
    buttons = new QButtonGroup();
    QDirIterator directory_walker("game/type", QDir::Files);
    while(directory_walker.hasNext()) {
        directory_walker.next();
        if(directory_walker.fileInfo().completeSuffix() == "dat") {
            try {
                QFile myFile(directory_walker.filePath());
                myFile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream stream(&myFile);
                QString line = stream.readLine();
                QPushButton *pb = new QPushButton(line);
                pb->setToolTip(directory_walker.fileInfo().filePath());;
                layout->addWidget(pb);
                buttons->addButton(pb);
            } catch (int ex) { }
        }
    }
    connect(buttons, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(newGame(QAbstractButton*)));
    pb_Exit = new QPushButton(tr("Exit"));
    connect(pb_Exit, SIGNAL(clicked()), this, SLOT(exitGame()));
    layout->addWidget(pb_Exit);
    setLayout(layout);
    setWindowTitle("Kopoong");
}


void loader::exitGame() {
    exit(1);
}

void loader::newGame(QAbstractButton* b) {
    scene *s = new scene(b->toolTip());
    gv_Viewer = new QGraphicsView(s);
    gv_Viewer->showFullScreen();
    connect(s, SIGNAL(destroyed()), gv_Viewer, SLOT(close()));
}
