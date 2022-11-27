#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}

//#include "tests/all_tests.h"
//
//int main(int argc, char *argv[])
//{
//    test_params();
//}

