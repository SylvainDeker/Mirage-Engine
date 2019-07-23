#pragma once

#include <QApplication>
#include "ui_MainWindow.h"

class MainWindow :public QMainWindow, private Ui::MainWindow{
	Q_OBJECT
	
public:
	explicit MainWindow( QWidget* parent = nullptr );
//	virtual ~MainWindow();

};

