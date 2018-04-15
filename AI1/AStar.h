#pragma once
//用于寻找路径的A*算法
#include<vector>
#include<list>
#include<math.h>
using namespace std;
class Point
{
public:
	int x, y;//坐标
	int f, g, h;
	Point *parent;
	//初始化
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
//给定终点和起点，初始迷宫，生成最佳路径
int getg(Point*point)
{
	if (point->parent == NULL)
		return 1;
	else
		return point->parent->g + 1;
}
//曼哈顿距离
int geth(Point*point, Point*end)
{
	return abs(end->x - point->x) + abs(end->y - point->y);
}

int getf(Point*point)
{
	return point->g + point->h;
}
//获取下一个最优节点
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
//判断是否在list中
Point* inlist(list<Point*>closelist, Point*point)
{
	for (Point*p : closelist)
	{
		if (p->x == point->x&&p->y == point->y)
			return p;
	}
	return NULL;
}
//判断是否可扩展
bool expandable(Point*point, Point*p, vector<vector<int>>maze, list<Point*>closelist)

{
	if ((p->x<0) || (p->x>maze.size() - 1)
		|| (p->y<0) || (p->y>maze[0].size() - 1)//边界
		|| (maze[p->x][p->y] == 1)//障碍
		|| (p->x == point->x&&p->y == point->y)//重合
		|| (inlist(closelist, p)))//在close表
		return false;
	else
		return true;
}
vector<Point*>surround(Point*point, vector<vector<int>>maze, list<Point*>closelist)
{
	vector<Point*>s;
	//左下右上
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
//进行寻路
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
			if (!inlist(openlist, target))//不在表中
			{
				target->parent = cur;
				target->g = getg(target);
				target->h = geth(cur, &end);
				target->f = getf(target);
				openlist.push_back(target);
			}
			else//在表中
			{
				int g = cur->g + 1;
				if (g < target->g)
				{
					target->parent = cur;
					target->g = g;
					target->f = getf(target);
				}
			}
			//判断
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
