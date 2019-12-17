#pragma once
#include"Path.h"
#define MAXSIZE 1000
#define OK 1
#define ERROR 0

class SavePath
{
public:
	SavePath();
	~SavePath();
	CPoint * base;//桟底
	CPoint * top;//桟顶
	int stacksize;//桟的最大容量
	bool Istick;
public:
	int InitStack(SavePath&S);//桟的初始化
	int Push(SavePath&S, CPoint e);//入栈
	int Pop(SavePath&S, CPoint&e);//出栈
	CPoint GetTop(SavePath&S);//获取栈顶元素
	int empty(SavePath&S);//判断是否为空桟
};

