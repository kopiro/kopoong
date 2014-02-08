#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <QMessageBox>

class MainWindow : public QWidget { Q_OBJECT
private:
    QPushButton *pb_Add;
    QTextEdit *te_File;
    QLineEdit *le_Name;
    QPushButton *pb_setName;
    QComboBox *cb_Type;
    QLineEdit *le_X;
    QLineEdit *le_Pos;
    QLineEdit *le_WrongY;
    QLineEdit *le_SpeedMult;
    QPushButton *pb_Save;
public:
    MainWindow(QWidget *parent = 0);
public slots:
    void setName();
    void addElement();
    void save();
};

#endif // MAINWINDOW_H
