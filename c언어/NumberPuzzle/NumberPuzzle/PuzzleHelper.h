#define PUZZLE_SIZE 3

namespace PuzzleHelper
{
	//초기화 함수
	void Initialize();

	//테이블의 상태를 보여주는 함수
	void ShowTable();

	//순환구조
	void Run();

	void ShuffleCards();

	void swap(int x, int y, int mx, int my);

	void FindZero();

	void InputDir();

	bool IsClear();
}