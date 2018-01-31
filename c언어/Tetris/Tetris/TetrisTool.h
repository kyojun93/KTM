#pragma once

namespace TetrisTool {
	//커서 on/off
	void CursorVisible(bool blnCursorVisible);
	//커서 위치 변경
	void SetCursorPosition(int cursorLeft, int cursorTop);
	//게임 화면 출력
	void print();
	//초기화
	void init();
	//새로운 블럭 생성
	void newblock();
	//키보드 입력
	void InputDir();
	//블럭 이동
	void move(int dir);
	//블럭 충동 체크
	bool check(int bx,int by,int rotation);
	//블럭 밑으로 한칸씩 이동
	void dropblock();
	//움직이는 블록->굳은 블록 변환
	void changebolck();
	void initdraw();
	//블록이 다찼을때 제거
	void breakblock();
	//게임 끝
	void gameover();
	//순환
	void levelup();
	void run();
}