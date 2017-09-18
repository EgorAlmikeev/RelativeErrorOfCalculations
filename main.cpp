#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedWidth(500);
    w.show();
    w.setStyleSheet(
                    ".QPushButton { background-color : #FAFBFC; border-radius : 5px; }"
                    ".QLineEdit { border-radius : 5px; }"
                    ".QLabel { border-radius : 5px; }"
                    );

    return a.exec();
}
