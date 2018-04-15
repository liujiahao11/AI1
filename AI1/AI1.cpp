#include "AI1.h"
#include<QLabel>
#include"AStar.h"
#include<QList>
#include<qdebug.h>
#include<QTimer>
#include<QKeyEvent>
using namespace std;
//地图数组，全局变量
vector<vector<int>> maze;
int length;

int wideth;

int flag=0;//用于鼠标相应的标志位
QLabel *label[15][20];
int beginx;
int beginy;
int endx;
int endy;
int curx;
int cury;
int Count = 0;
int FLAG = 0;
vector<Point*>PATH;
int enable=0;
AI1::AI1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initial();
	QTimer *timer = new QTimer(this);
	timer->start(500);
	connect(timer, SIGNAL(timeout()), this, SLOT(hunter()));
}
void AI1::setlong()
{}
void AI1::setwide()
{}
void AI1::initial()
{
	int i;
	int j;


	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 20; j++)
		{
			label[i][j] = new QLabel;
			ui.layout->addWidget(label[i][j], i, j);
		}
	}
}
void AI1::createmaze()
{
	enable = 0;
	PATH.clear();
	flag = 0;
	Count = 0;
	beginx = -1;
	beginy = -1;
	endx = -1;
	endy = -1;
	curx = -1;
	cury = -1;
	FLAG = 0;
	


	int i;
	int j;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 20; j++)
		{
			
			label[i][j]->setStyleSheet(" ");
		}
	}

	 length = int(ui.edit_long->text().toDouble());
	 wideth = int(ui.edit_wide->text().toDouble());
	maze.resize(wideth);
	for (i = 0; i < wideth; i++)
	{
		maze[i].resize(length);
	}
	for (i = 0; i < wideth; i++)
	{
		
	for (j = 0; j < length; j++)
	{
		if (i == 0 || j == 0 || i == wideth - 1 || j == length - 1)
			maze[i][j] = 1;
		else
			maze[i][j] = 0;
	}
}
	
	
	
	
	for (i = 0; i < wideth; i++)

		for (j = 0; j < length; j++)
		{
		
			if (maze[i][j] == 1)
			label[i][j]->setStyleSheet("border-image: url(:/AI1/Resources/1204905.png)");
			
			
		}



}

void AI1::setbarrier()
{
	flag = 1;

}
void AI1::setbegin()
{
	flag = 2;
}
void AI1::setend()
{
	flag = 3;
}


void AI1::hunt()
{
	//Count++;
	flag = 0;
	Point begin(beginy, beginx);
	Point end(endy, endx);
	list<Point *>path = Astar(begin, end, maze);
	qDebug("%d", path.size());
	if (path.size() != 0)
	{
		for (Point*p : path) {
			PATH.push_back(p);

		}
		enable = 1;
	}
	
}
void AI1::hunter()
{

	if (enable==1&&Count<PATH.size()-1)
	{
		Count++;
		
		label[PATH[Count]->x][PATH[Count]->y]->setStyleSheet("border-image: url(:/AI1/Resources/1141878.png);");
		curx = PATH[Count]->y;
		cury = PATH[Count]->x;
	}
	if (Count == PATH.size() - 1)
		FLAG = 0;
}
void AI1::escape()
{
	FLAG = 1;
	label[endy][endx]->setStyleSheet("border-image: url(:/AI1/Resources/run.png);");
}
//鼠标相应
void AI1::mousePressEvent(QMouseEvent*event)
{
	QPoint mypos = event->globalPos() - pos();
	int X = round((mypos.x()-43.15) / (886 / 20));
	int Y = round((mypos.y()-83.23) / (607 / 15));
	switch (flag)
	{
	case 1:
		if (event->button()==Qt::LeftButton)
		{
			maze[Y][X] = 1;
			label[Y][X]->setStyleSheet("border-image: url(:/AI1/Resources/1204905.png)");
		}
		if (event->button() == Qt::RightButton)
		{
			maze[Y][X] = 0;
			label[Y][X]->setStyleSheet(" ");
		}

		break;
	case 2:
		if (event->button() == Qt::LeftButton)
		{
			if (maze[Y][X] != 1)
			{
				if (beginx != -1)
					label[beginy][beginx]->setStyleSheet(" ");
				beginx = X;
				beginy = Y;
				label[Y][X]->setStyleSheet("border-image: url(:/AI1/Resources/1141878.png);");
			}
		}
		break;
	case 3:
		if (event->button() == Qt::LeftButton)
		{
			if (maze[Y][X] != 1)
			{
				if (endx != -1)
					label[endy][endx]->setStyleSheet(" ");
				endx = X;
				endy = Y;
				label[Y][X]->setStyleSheet("border-image: url(:/AI1/Resources/1202514.png);");
			}
		}
		break;
	default:
		break;
	}
}
//移动鼠标
void AI1::mouseMoveEvent(QMouseEvent*event)
{
	QPoint mypos = event->globalPos() - pos();
	
	switch (flag)
	{
	case 1:
		
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}
//释放鼠标
void AI1::mouseReleaseEvent(QMouseEvent*event)
{
	
}
void AI1::keyPressEvent(QKeyEvent*event)
{
	if (FLAG == 1)
	{
		
		if (event->key() == Qt::Key_W)
		{
			if (endx >= 0 && endx < length&&endy >= 1 && endy < wideth&&maze[endy - 1][endx] != 1)
			{
				enable = 0;
				label[endy][endx]->setStyleSheet(" ");
				endx = endx;
				endy = endy - 1;
				label[endy][endx]->setStyleSheet("border-image: url(:/AI1/Resources/run.png);");
				beginx = curx;
				beginy = cury;
				PATH.clear();
				Count = 0;
				hunt();
			}
		}
		if (event->key() == Qt::Key_S)
		{
			if (endx >= 0 && endx < length&&endy >= 0 && endy < wideth-1&&maze[endy +1][endx] != 1)
			{
				enable = 0;
				label[endy][endx]->setStyleSheet(" ");
				endx = endx;
				endy = endy + 1;
				label[endy][endx]->setStyleSheet("border-image: url(:/AI1/Resources/run.png);");
				beginx = curx;
				beginy = cury;
				PATH.clear();
				Count = 0;
				hunt();
			}
		}
		if (event->key() == Qt::Key_A)
		{
			if (endx >= 1 && endx < length&&endy >= 0 && endy < wideth&&maze[endy ][endx-1] != 1)
			{
				enable = 0;
				label[endy][endx]->setStyleSheet(" ");
				endx = endx-1;
				endy = endy ;
				label[endy][endx]->setStyleSheet("border-image: url(:/AI1/Resources/run.png);");
				beginx = curx;
				beginy = cury;
				PATH.clear();
				Count = 0;
				hunt();
			}
		}
		if (event->key() == Qt::Key_D)
		{
			if (endx >= 0 && endx < length-1&&endy >= 0 && endy < wideth&&maze[endy][endx + 1] != 1)
			{
				enable = 0;
				label[endy][endx]->setStyleSheet(" ");
				endx = endx + 1;
				endy = endy;
				label[endy][endx]->setStyleSheet("border-image: url(:/AI1/Resources/run.png);");
				beginx = curx;
				beginy = cury;
				PATH.clear();
				Count = 0;
				hunt();
			}
		}


		

	}
}
void AI1::keyReleaseEvent(QKeyEvent*event)
{
}


