#pragma once
//����Ѱ��·����A*�㷨
#include<vector>
#include<list>
#include<math.h>
using namespace std;
class Point
{
public:
	int x, y;//����
	int f, g, h;
	Point *parent;
	//��ʼ��
	Point(int X, int Y)
	{
		x = X;
		y = Y;
		f = 0;
		g = 0;
		h = 0;
		parent = NULL;
	}
};
//�����յ����㣬��ʼ�Թ����������·��
int getg(Point*point)
{
	if (point->parent == NULL)
		return 1;
	else
		return point->parent->g + 1;
}
//�����پ���
int geth(Point*point, Point*end)
{
	return abs(end->x - point->x) + abs(end->y - point->y);
}

int getf(Point*point)
{
	return point->g + point->h;
}
//��ȡ��һ�����Žڵ�
Point*next(list<Point*>openlist)
{
	if (!openlist.empty())
	{
		Point*point = openlist.front();
		for (Point*p : openlist)
		{
			if (p->f < point->f)
				point = p;

		}
		return point;
	}
	return NULL;
}
//�ж��Ƿ���list��
Point* inlist(list<Point*>closelist, Point*point)
{
	for (Point*p : closelist)
	{
		if (p->x == point->x&&p->y == point->y)
			return p;
	}
	return NULL;
}
//�ж��Ƿ����չ
bool expandable(Point*point, Point*p, vector<vector<int>>maze, list<Point*>closelist)

{
	if ((p->x<0) || (p->x>maze.size() - 1)
		|| (p->y<0) || (p->y>maze[0].size() - 1)//�߽�
		|| (maze[p->x][p->y] == 1)//�ϰ�
		|| (p->x == point->x&&p->y == point->y)//�غ�
		|| (inlist(closelist, p)))//��close��
		return false;
	else
		return true;
}
vector<Point*>surround(Point*point, vector<vector<int>>maze, list<Point*>closelist)
{
	vector<Point*>s;
	//��������
	if (expandable(point, new Point(point->x, point->y - 1), maze, closelist))
		s.push_back(new Point(point->x, point->y - 1));
	if (expandable(point, new Point(point->x + 1, point->y), maze, closelist))
		s.push_back(new Point(point->x + 1, point->y));
	if (expandable(point, new Point(point->x, point->y + 1), maze, closelist))
		s.push_back(new Point(point->x, point->y + 1));
	if (expandable(point, new Point(point->x - 1, point->y), maze, closelist))
		s.push_back(new Point(point->x - 1, point->y));
	return s;

}
//����Ѱ·
Point*move(Point&start, Point&end, vector<vector<int>>maze)
{
	list<Point*>openlist;
	list<Point*>closelist;
	openlist.push_back(new Point(start.x, start.y));
	Point*cur;
	vector<Point*>sur;
	while (!openlist.empty())
	{
		cur = next(openlist);
		openlist.remove(cur);
		closelist.push_back(cur);
		sur = surround(cur, maze, closelist);
		for (Point*target : sur)
		{
			if (!inlist(openlist, target))//���ڱ���
			{
				target->parent = cur;
				target->g = getg(target);
				target->h = geth(cur, &end);
				target->f = getf(target);
				openlist.push_back(target);
			}
			else//�ڱ���
			{
				int g = cur->g + 1;
				if (g < target->g)
				{
					target->parent = cur;
					target->g = g;
					target->f = getf(target);
				}
			}
			//�ж�
			Point*res = inlist(openlist, &end);
			if (res)
				return res;
		}

	}
	return NULL;

}




list<Point*>Astar(Point&start, Point&end, vector<vector<int>>maze)
{
	Point*res = move(start, end, maze);
	list<Point*>path;
	while (res)
	{
		path.push_front(res);
		res = res->parent;
	}
	return path;
}
