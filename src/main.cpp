#include "qt/Mainwindow.hpp"
#include <ctime>
#include <QApplication>
#include <cstdlib>
#include <assimp/version.h>

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::cout << aiGetLegalString() << '\n';
    return a.exec();
}
