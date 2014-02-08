#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QGridLayout *newlayout = new QGridLayout();
    pb_Add = new QPushButton("&Add");
    connect(pb_Add, SIGNAL(clicked()), this, SLOT(addElement()));
    le_Name = new QLineEdit("New Game");
    pb_setName = new QPushButton("&Set name");
    connect(pb_setName, SIGNAL(clicked()), this, SLOT(setName()));
    le_X = new QLineEdit("0");
    le_Pos = new QLineEdit("1");
    le_SpeedMult = new QLineEdit("1.0");
    le_WrongY = new QLineEdit("10");
    cb_Type = new QComboBox();
    cb_Type->addItem("bar");
    cb_Type->addItem("bar_ai");
    cb_Type->addItem("ball");
    cb_Type->addItem("bonus bigbar");
    cb_Type->addItem("bonus smallbar");
    cb_Type->addItem("bonus magnet");
    te_File = new QTextEdit();
    newlayout->addWidget(le_Name, 0, 0, 1, 5);
    newlayout->addWidget(pb_setName, 0, 5);
    QLabel *lb_Type = new QLabel("Type");
    newlayout->addWidget(lb_Type, 1, 0);
    newlayout->addWidget(cb_Type, 2, 0);
    QLabel *lb_X = new QLabel("X-Coord");
    newlayout->addWidget(lb_X, 1, 1);
    newlayout->addWidget(le_X, 2, 1);
    QLabel *lb_Pos = new QLabel("Position");
    newlayout->addWidget(lb_Pos, 1, 2);
    newlayout->addWidget(le_Pos, 2, 2);
    QLabel *lb_SpeedMult = new QLabel("SpeedMult");
    newlayout->addWidget(lb_SpeedMult, 1, 3);
    newlayout->addWidget(le_SpeedMult, 2, 3);
    QLabel *lb_WrongY = new QLabel("Wrong Interval Y");
    newlayout->addWidget(lb_WrongY, 1, 4);
    newlayout->addWidget(le_WrongY, 2, 4);
    newlayout->addWidget(pb_Add, 2, 5);
    newlayout->addWidget(te_File, 3, 0, 1, 6);
    pb_Save = new QPushButton("&Save");
    connect(pb_Save, SIGNAL(clicked()), this, SLOT(save()));
    newlayout->addWidget(pb_Save, 4, 0, 1, 6);
    this->setLayout(newlayout);

}

void MainWindow::setName() {
    te_File->setPlainText(le_Name->text());
}

void MainWindow::addElement() {
    QString ct = te_File->toPlainText();
    ct += "\n";
    ct += "new:";
    ct += cb_Type->currentText() + " ";
    if (cb_Type->currentText()=="bar") {
        ct += le_X->text() + " ";
        ct += le_SpeedMult->text() + " ";
        ct += le_Pos->text() + " ";
    } else if (cb_Type->currentText()=="bar_ai") {
        ct += le_X->text() + " ";
        ct += le_SpeedMult->text() + " ";
        ct += le_Pos->text() + " ";
        ct += le_WrongY->text();
    } else if (cb_Type->currentText()=="ball") {
        ct += le_SpeedMult->text();
    }
    te_File->setText(ct);
}

void MainWindow::save() {
    try {
        std::ofstream w(QString("game/type/"+le_Name->text()+".dat").toStdString().c_str());
        w<<te_File->toPlainText().toStdString().c_str();
        w.close();
        QMessageBox::information(this, "Level saved", "Level saved correctly");
    } catch (int ex) {
        QMessageBox::critical(this, "Error", "Error while saving:"+QString::number(ex));
    }
}
