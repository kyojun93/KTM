#pragma once

struct INTERVAL
{
	int x, y;
};

typedef INTERVAL POS;
typedef INTERVAL BSIZE;

class Block
{
private:
	HPEN	m_pen;
	HBRUSH	m_brush;
	POS		m_pos;
	BSIZE    m_size;


public:
	Block();
	Block(DWORD brushColor, DWORD penColor);
	~Block();

public:

	HPEN CreateBlockPen(int iStyle, int cWidth, COLORREF color);
	HBRUSH CreateBlockBrush(COLORREF color);
	HPEN GetPen();
	HBRUSH GetBrush();
	void SetPos(int x, int y);
	POS GetPos();

	void SetSize(int x, int y);
	BSIZE GetSize();

	void Render(HDC hdc);



};

