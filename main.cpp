#include "widget.h"
#include "form.h"
#include "form01.h"
#include "form02.h"
#include "form03.h"
#include "form04.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Form s;
    s.show();

    Form01 s1;
    s1.show();

    Form02 s2;
    s2.show();

    Form03 s3;
    s3.show();

    Form04 s4;
    s4.show();

    return a.exec();
}
