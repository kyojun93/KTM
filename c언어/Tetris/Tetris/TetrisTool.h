#pragma once

namespace TetrisTool {
	//Ŀ�� on/off
	void CursorVisible(bool blnCursorVisible);
	//Ŀ�� ��ġ ����
	void SetCursorPosition(int cursorLeft, int cursorTop);
	//���� ȭ�� ���
	void print();
	//�ʱ�ȭ
	void init();
	//���ο� �� ����
	void newblock();
	//Ű���� �Է�
	void InputDir();
	//�� �̵�
	void move(int dir);
	//�� �浿 üũ
	bool check(int bx,int by,int rotation);
	//�� ������ ��ĭ�� �̵�
	void dropblock();
	//�����̴� ���->���� ��� ��ȯ
	void changebolck();
	//����� ��á���� ����
	void breakblock();
	//���� ��
	void gameover();
	//��ȯ
	void levelup();
	void run();
}