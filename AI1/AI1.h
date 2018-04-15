#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AI1.h"
#include<QMouseEvent>
class AI1 : public QMainWindow
{
	Q_OBJECT

public:
	AI1(QWidget *parent = Q_NULLPTR);
protected:
	void mousePressEvent(QMouseEvent*event);
	void mouseReleaseEvent(QMouseEvent*event);
	void mouseMoveEvent(QMouseEvent*event);
protected:
	void keyPressEvent(QKeyEvent*event);
	void keyReleaseEvent(QKeyEvent*event);
private:
	Ui::AI1Class ui;
	private slots:
	void setlong();
	private slots:
	void setwide();
	private slots :
	void createmaze();
	private slots:
	void setbarrier();
	private slots:
	void setbegin();
	private slots:
	void setend();
	private slots:
	void hunt();
	private slots:
	void escape();
	private slots:
	void hunter();
private:
	void initial();
	
};
