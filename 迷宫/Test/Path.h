#pragma once
class Path
{
public:
	Path();
	Path( CPoint postion, int Roadwith);
	~Path();
public:
	int IsPass;//是路还是墙？
	int RoadWith;//路宽
	CPoint postion;//格子位置
	void DrawPath(CDC*pDC);
	void DrawPath1(CDC*pDC);
	Path *next;
	bool flag;
	bool left;
	bool right;
	bool up;
	bool down;
};

