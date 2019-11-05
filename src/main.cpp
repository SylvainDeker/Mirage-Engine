#include "qt/Mainwindow.hpp"
#include <ctime>
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
