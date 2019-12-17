
// TestView.cpp : CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif
#include<iostream>
using namespace std;

#include "TestDoc.h"
#include "TestView.h"
#include<ctime>
#define m 67
#define W 10
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include<fstream>

// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SearchPath, &CTestView::OnSearchpath)
	ON_COMMAND(ID_CreateMap, &CTestView::OnCreatemap)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO:  在此处添加构造代码
	P = new Path*[m];
	for (int i = 0; i < m; i++)
	{
		P[i] = new Path[m];
	}
	for (int i = 0; i < m; i++)//位置
		for (int j = 0; j < m; j++)
			P[i][j] = Path(CPoint(i * W, j * W), W);
		SiveP.InitStack(SiveP);
		Is = false;
}

CTestView::~CTestView()
{
	for (int i = 0; i < m; i++)
	{
		delete[] P[i];
		P[i] = NULL;
	}
	delete[] P;
	P = NULL;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘制

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	CBitmap NewBitmap, *pOldBitmap;
	memDC.CreateCompatibleDC(pDC);
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap = memDC.SelectObject(&NewBitmap);
	memDC.FillSolidRect(rect,pDC->GetBkColor());
	for (int i = 0; i < m; i++)//画图
	{
		for (int j = 0; j < m; j++)
		{
			P[i][j].DrawPath(&memDC);
		}
	}
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	fstream file("test.txt", ios::out);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			file << P[i][j].IsPass << " ";
		}
		file << endl;		
	}
	file.close();
	fstream file1("Path.txt", ios::out);
	while (SiveP.top!=SiveP.base)
	{
		CPoint ps;
		ps = *++SiveP.base;
		file1 << "("<<ps.x<<","<<ps.y<<")"<<endl;
		Sleep(100);
		P[ps.x][ps.y].DrawPath1(pDC);
		
	}
	file1.close();
}
//随机地图
void CTestView::CreateMap(Path **P, int left, int right, int top, int bottom)
{
	int x = (top + bottom) % 4 == 0 ? (top + bottom) / 2 : (top + bottom) / 2 + 1;
	int y = (left + right) % 4 == 0 ? (left + right) / 2 : (left + right) / 2 + 1;

	for (int i = top + 1; i < bottom; ++i) P[i][y].IsPass = 0;
	for (int i = left + 1; i < right; ++i) P[x][i].IsPass = 0;

	int x1, x2, y1, y2;
	x1 = rand() % ((x - top) / 2) * 2 + 1 + top;//上方
	x2 = rand() % ((bottom - x) / 2) * 2 + 1 + x;//下方
	y1 = rand() % ((y - left) / 2) * 2 + 1 + left;
	y2 = rand() % ((right - y) / 2) * 2 + 1 + y;
		switch (rand() % 4)
		{
		case 0://上方不打通
			P[x][y1].IsPass = P[x][y2].IsPass = P[x2][y].IsPass = 1;
			break;
		case 1://左边
			P[x1][y].IsPass = P[x][y2].IsPass = P[x2][y].IsPass = 1;
			break;
		case 2://右边
			P[x][y1].IsPass = P[x1][y].IsPass = P[x2][y].IsPass = 1;
			break;
		case 3://下面
			P[x][y1].IsPass = P[x][y2].IsPass = P[x1][y].IsPass = 1;
			break;
		}
		if (y - left>2 && x - top>2) CreateMap(P, left, y, top, x);
		if (right - y>2 && x - top>2) CreateMap(P, y, right, top, x);
		if (y - left>2 && bottom - x>2) CreateMap(P, left, y, x, bottom);
		if (right - y>2 && bottom - x>2) CreateMap(P, y, right, x, bottom);
}
void CTestView::DS(int X,int Y)
{
	if (SiveP.GetTop(SiveP)==CPoint(m-1,m-2))return;
	if (P[X + 1][Y].IsPass && X + 1< m && P[X+1][Y].flag)//下
		{
		P[X][Y].flag = 0;
			SiveP.Push(SiveP, CPoint(X+1, Y));
			DS(X+1,Y);
		}
	if (SiveP.GetTop(SiveP) == CPoint(m - 1, m - 2))return;
	if (P[X][Y + 1].IsPass&& Y + 1 < m && P[X][Y + 1].flag)//右
	{
		P[X][Y].flag = 0;
		SiveP.Push(SiveP, CPoint(X, Y + 1));
		DS(X, Y + 1);
	}
	if (SiveP.GetTop(SiveP) == CPoint(m - 1, m - 2))return;
	if (X - 1 >0 && P[X - 1][Y].IsPass&&P[X - 1][Y].flag)
	{
		P[X][Y].flag = 0;
		SiveP.Push(SiveP, CPoint(X - 1, Y));
		DS(X - 1, Y);
	}
	if (SiveP.GetTop(SiveP) == CPoint(m - 1, m - 2))return;
	if (Y - 1> 0 && P[X][Y - 1].IsPass&&P[X][Y-1].flag)
	{
		P[X][Y].flag = 0;
		SiveP.Push(SiveP, CPoint(X, Y - 1));
		DS(X, Y - 1); 
	}
	if (SiveP.GetTop(SiveP) == CPoint(m - 1, m - 2))return;
		CPoint p3;
	    SiveP.Pop(SiveP, p3);
}
// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序


void CTestView::OnSearchpath()
{
	// TODO:  在此添加命令处理程序代码
	//SiveP.DeleteStack();
	if (Is)
	{
		SiveP.Push(SiveP, CPoint(0, 1));
		SiveP.Push(SiveP, CPoint(0, 1));
		SiveP.Push(SiveP, CPoint(1, 1));
		DS(0, 1);
		CPoint p3;
		SiveP.Pop(SiveP, p3);
		Invalidate(false);
	}
	else
		MessageBox(L"请先生成迷宫", L"提示", IDOK);
}


void CTestView::OnCreatemap()
{
	// TODO:  在此添加命令处理程序代码
	for (int i = 0; i < m; i++)
	{
		P[0][i].IsPass = 0; P[m - 1][i].IsPass = 0;
		P[i][0].IsPass = 0; P[i][m - 1].IsPass = 0;
	}
	P[0][1].IsPass = P[m - 1][m - 2].IsPass = 1;

	srand(unsigned(time(NULL)));
	CreateMap(P, 0, m - 1, 0, m - 1);//是否通过
	Invalidate(false);
	Is = true;
}
