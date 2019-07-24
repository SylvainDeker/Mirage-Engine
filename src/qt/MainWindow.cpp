#include <QWidget>
#include <QResizeEvent>
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow( parent )
{
    setupUi( this );



}

void MainWindow::resizeEvent(QResizeEvent *event){
	mainglwidget->resize(event->size().width(),event->size().height());




}
