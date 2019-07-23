#include <QApplication>
#include "qt/MainWindow.hpp"


int main(int argc, char * argv[])
{

    QApplication qt( argc, argv );

    MainWindow hello(nullptr);
    hello.resize( 600, 300 );

    hello.show();
    return qt.exec();

}
