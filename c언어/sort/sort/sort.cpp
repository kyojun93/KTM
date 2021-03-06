// sort.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "allsort.h"
#include <windows.h>

using namespace allsort;
int main()
{
	while (true) {
		int choice;
		system("cls");
		printf("\t ================\n");
		printf("\t| 단순 정렬: 1\t |\n");
		printf("\t| 버블 정렬: 2\t |\n");
		printf("\t| 삽입 정렬: 3\t |\n");
		printf("\t| 선택 정렬: 4\t |\n");
		printf("\t|   쉘 정렬: 5\t |\n");
		printf("\t|   퀵 정렬: 6\t |\n");
		printf("\t| 이진 탐색: 7\t |\n");
		printf("\t| 끝내기: -1\t |\n");
		printf("\t ================\n");
		scanf_s("%d", &choice);
		if (choice == 1) {
			simplesort();
		}
		else if (choice == 2) {
			bubblesort();
		}
		else if (choice == 3) {
			insertionsort();
		}
		else if (choice == 4) {
			selectsort();
		}
		else if (choice == 5) {
			shellsort();
		}
		else if (choice == 6) {
			input();
			quicksort(0, sortlen-1);
			printf("정렬후 숫자: ");
		print();
		Sleep(2000);
		}
		else if (choice == 7) {
			insertionsort();
			binarysearch();
		}
		else if (choice < 0) {
			break;
		}
		
	}
    return 0;
}

