/*

  Projeto CG Unicap

    Authors:
        Diego Marcolan
        Miguel Amaral
        Ethan Rafael
        Davyson Costa
*/


#include <QtGui/QApplication>
#include "janelaprincipal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JanelaPrincipal w;
    w.show();

    return a.exec();
}
