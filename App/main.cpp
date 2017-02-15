#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "login/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    //Login w;
    //w.setFixedSize(850,600); //设置窗体固定大小
    w.show();

    return a.exec();
}
