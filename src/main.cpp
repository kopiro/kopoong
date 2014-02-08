/*
PONG GAME in QT/C++
Kopoong
Version 1.2
Developed by Flavio De Stefano
destefano.flavio@gmail.com
Università di Parma 2010
Ingegneria Informatica
Matr 222060
*/

#include <ctime>
#include <cstdlib>
#include <QApplication>
#include <QCoreApplication>
#include "loader.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //Set Application Info
    a.setApplicationName("Kopoong");
    a.setApplicationVersion("1.2");
    a.setOrganizationName("KSD (Kopiro Software Depelovement)");
    a.setOrganizationDomain("kopiro.it");


    srand(time(NULL));

    //Init the app
    loader *l = new loader();
    l->show();

    return a.exec();
}
