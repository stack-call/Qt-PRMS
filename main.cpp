#include "login.h"
#include "PRMS.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    PRMS system;
    system.run();

    return a.exec();
}
