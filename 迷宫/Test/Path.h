#pragma once
class Path
{
public:
	Path();
	Path( CPoint postion, int Roadwith);
	~Path();
public:
	int IsPass;//��·����ǽ��
	int RoadWith;//·��
	CPoint postion;//����λ��
	void DrawPath(CDC*pDC);
	void DrawPath1(CDC*pDC);
	Path *next;
	bool flag;
	bool left;
	bool right;
	bool up;
	bool down;
};

