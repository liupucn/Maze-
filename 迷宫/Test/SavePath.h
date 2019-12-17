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
	CPoint * base;//�C��
	CPoint * top;//�C��
	int stacksize;//�C���������
	bool Istick;
public:
	int InitStack(SavePath&S);//�C�ĳ�ʼ��
	int Push(SavePath&S, CPoint e);//��ջ
	int Pop(SavePath&S, CPoint&e);//��ջ
	CPoint GetTop(SavePath&S);//��ȡջ��Ԫ��
	int empty(SavePath&S);//�ж��Ƿ�Ϊ�՗C
};

