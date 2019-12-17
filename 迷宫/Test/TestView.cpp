
// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SearchPath, &CTestView::OnSearchpath)
	ON_COMMAND(ID_CreateMap, &CTestView::OnCreatemap)
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO:  �ڴ˴���ӹ������
	P = new Path*[m];
	for (int i = 0; i < m; i++)
	{
		P[i] = new Path[m];
	}
	for (int i = 0; i < m; i++)//λ��
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestView ����

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	CBitmap NewBitmap, *pOldBitmap;
	memDC.CreateCompatibleDC(pDC);
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap = memDC.SelectObject(&NewBitmap);
	memDC.FillSolidRect(rect,pDC->GetBkColor());
	for (int i = 0; i < m; i++)//��ͼ
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
//�����ͼ
void CTestView::CreateMap(Path **P, int left, int right, int top, int bottom)
{
	int x = (top + bottom) % 4 == 0 ? (top + bottom) / 2 : (top + bottom) / 2 + 1;
	int y = (left + right) % 4 == 0 ? (left + right) / 2 : (left + right) / 2 + 1;

	for (int i = top + 1; i < bottom; ++i) P[i][y].IsPass = 0;
	for (int i = left + 1; i < right; ++i) P[x][i].IsPass = 0;

	int x1, x2, y1, y2;
	x1 = rand() % ((x - top) / 2) * 2 + 1 + top;//�Ϸ�
	x2 = rand() % ((bottom - x) / 2) * 2 + 1 + x;//�·�
	y1 = rand() % ((y - left) / 2) * 2 + 1 + left;
	y2 = rand() % ((right - y) / 2) * 2 + 1 + y;
		switch (rand() % 4)
		{
		case 0://�Ϸ�����ͨ
			P[x][y1].IsPass = P[x][y2].IsPass = P[x2][y].IsPass = 1;
			break;
		case 1://���
			P[x1][y].IsPass = P[x][y2].IsPass = P[x2][y].IsPass = 1;
			break;
		case 2://�ұ�
			P[x][y1].IsPass = P[x1][y].IsPass = P[x2][y].IsPass = 1;
			break;
		case 3://����
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
	if (P[X + 1][Y].IsPass && X + 1< m && P[X+1][Y].flag)//��
		{
		P[X][Y].flag = 0;
			SiveP.Push(SiveP, CPoint(X+1, Y));
			DS(X+1,Y);
		}
	if (SiveP.GetTop(SiveP) == CPoint(m - 1, m - 2))return;
	if (P[X][Y + 1].IsPass&& Y + 1 < m && P[X][Y + 1].flag)//��
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
// CTestView ��ӡ

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������


void CTestView::OnSearchpath()
{
	// TODO:  �ڴ���������������
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
		MessageBox(L"���������Թ�", L"��ʾ", IDOK);
}


void CTestView::OnCreatemap()
{
	// TODO:  �ڴ���������������
	for (int i = 0; i < m; i++)
	{
		P[0][i].IsPass = 0; P[m - 1][i].IsPass = 0;
		P[i][0].IsPass = 0; P[i][m - 1].IsPass = 0;
	}
	P[0][1].IsPass = P[m - 1][m - 2].IsPass = 1;

	srand(unsigned(time(NULL)));
	CreateMap(P, 0, m - 1, 0, m - 1);//�Ƿ�ͨ��
	Invalidate(false);
	Is = true;
}
