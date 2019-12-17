#include "stdafx.h"
#include "SavePath.h"


SavePath::SavePath()
{
	Istick = false;
}


SavePath::~SavePath()
{
}
int SavePath::InitStack(SavePath&S)//桟的初始化
{
	S.base = new CPoint[MAXSIZE];
	Istick = true;
	if (!S.base) return 0;;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}
int SavePath::Push(SavePath&S, CPoint e)//入栈
{
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top++ = e;
	return OK;
}
int SavePath::Pop(SavePath&S, CPoint&e)//出栈
{
	if (S.top == S.base)return ERROR;
	e = *--S.top;
	return OK;
}
int SavePath::empty(SavePath&S)
{
	if (S.top == S.base)return 1;
	else return 0;
}
CPoint SavePath::GetTop(SavePath&S)
{
	return *(S.top-1);
}