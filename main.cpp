#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include "version.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("mugi-serial");
    a.setApplicationVersion(VERSION);
    a.setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;
    w.show();
    return a.exec();
}
