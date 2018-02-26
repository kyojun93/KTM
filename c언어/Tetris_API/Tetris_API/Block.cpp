#include "stdafx.h"
#include "Block.h"


Block::Block()
{

}

Block::Block(DWORD brushColor, DWORD penColor)
{

}

Block::~Block()
{
}

HPEN Block::CreateBlockPen(int iStyle, int cWidth, COLORREF color)
{
	m_pen = CreatePen(iStyle, cWidth, color);

	return NULL;
}
HBRUSH Block::CreateBlockBrush(COLORREF color)
{
	m_brush = CreateSolidBrush(color);
	return NULL;
}
HPEN Block::GetPen()
{
	return NULL;
}
HBRUSH Block::GetBrush()
{
	return NULL;
}

void Block::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

POS Block::GetPos()
{
	return m_pos;
}

void Block::Render(HDC hdc)
{
	int sizeX = m_size.x / 2;
	int sizeY = m_size.y / 2;
	int left = m_pos.x - sizeX;
	int top = m_pos.y - sizeY;
	int right = m_pos.x + sizeX;
	int bottom = m_pos.y + sizeY;

	HPEN oldPen = (HPEN)SelectObject(hdc, m_pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, m_brush);

	Rectangle(hdc, left, top, right, bottom);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);

}

void Block::SetSize(int x, int y)
{
	m_size.x = x;
	m_size.y = y;
}
BSIZE Block::GetSize()
{
	return m_size;
}