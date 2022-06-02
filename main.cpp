#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include "version.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("mugi-serial");
    a.setApplicationVersion(VERSION);
    MainWindow w;
    w.show();
    return a.exec();
}
