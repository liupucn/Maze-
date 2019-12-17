#include "stdafx.h"
#include "Path.h"


Path::Path()
{
}


Path::~Path()
{
}
Path::Path(CPoint postion, int Roadwith)
{
	this->postion.x = postion.x;
	this->postion.y = postion.y;
	this->RoadWith = Roadwith;
	this->IsPass = 1;
	this->flag = 1;
	this->down = 1;
	this->up = 1;
	this->right = 1;
	this->left = 1;
}
void Path::DrawPath(CDC*pDC)
{
	if (this->IsPass==0)
	{
		for (int i = postion.y; i < postion.y+RoadWith; i++)
		{
			for (int j = postion.x; j < postion.x+RoadWith; j++)
			{
				pDC->SetPixel(i,j,RGB(0,0,0));
			}
		}
	}
	else
	{
		if (this->IsPass == 1)
		for (int i = postion.y; i < postion.y + RoadWith; i++)
		{
			for (int j = postion.x; j < postion.x+RoadWith; j++)
			{
				pDC->SetPixel(i, j, RGB(255, 255, 255));
			}
		}
		else
		for (int i = postion.y; i < postion.y + RoadWith; i++)
		{
			for (int j = postion.x; j < postion.x + RoadWith; j++)
			{
				pDC->SetPixel(i, j, RGB(255, 255, 0));
			}
		}
	}
}
void Path::DrawPath1(CDC*pDC)
{
		for (int i = postion.y; i < postion.y + RoadWith; i++)
		{
			for (int j = postion.x; j < postion.x + RoadWith; j++)
			{
				pDC->SetPixel(i, j, RGB(255, 255, 0));
			}
		}
}