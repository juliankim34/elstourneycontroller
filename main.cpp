#include <QApplication>
#include "elscontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //controller w;
    elscontroller w;
    w.show();

    return a.exec();
}
