#include "mainwindow.h"

#include <QApplication>

// Тут буквально нічого не змінено

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
