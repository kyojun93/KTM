#define PUZZLE_SIZE 3

namespace PuzzleHelper
{
	//�ʱ�ȭ �Լ�
	void Initialize();

	//���̺��� ���¸� �����ִ� �Լ�
	void ShowTable();

	//��ȯ����
	void Run();

	void ShuffleCards();

	void swap(int x, int y, int mx, int my);

	void FindZero();

	void InputDir();

	bool IsClear();
}