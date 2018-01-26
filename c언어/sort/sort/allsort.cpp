#include "stdafx.h"
#include "allsort.h"
#include <time.h>
#include <Windows.h>

int number[sortlen];
namespace allsort {
	void simplesort() {
		int count = 1;
		input();
		for (int i = 0; i < sortlen - 1; i++) {
			for (int j = i+1; j < sortlen; j++) {
				if (number[i]> number[j]) {
					swap(i,j);
					printf("%d번째 [%d]and[%d] swap\n", count++, number[i], number[j]);
					print();
				}
			}
		}
		printf("정렬후 숫자: ");
		print();
		Sleep(2000);
	}

	void bubblesort() {
		int count = 1;
		input();
		for (int i = sortlen-1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (number[j] > number[j + 1]) {
					swap(j, j+1);
					printf("%d번째 [%d]and[%d] swap\n", count++, number[j],number[j+1]);
					print();
				}
			}
		}
		printf("정렬후 숫자: ");
		print();
		Sleep(2000);
	}

	void insertionsort() {
		int count = 1;
		int j;
		input();
		for (int i = 0; i < sortlen; i++) {
			int t = number[i];
			for (j = i-1; j >= 0; j--) {
				if (number[j] > t) 
					number[j + 1] = number[j];
				else 
					break;
			}
			number[j + 1] = t;
			printf("%d번째 [%d]위치에[%d] insert\n", count++, number[j], number[j+1]);
			print();
		}
		printf("정렬후 숫자: ");
		print();
		Sleep(2000);
	}

	void quicksort(int first, int last) {
		int First = first;
		int Last = last;
		int Average = (number[First]+ number[Last])/2;
		while (1) {
			while (number[First] < Average) {
				First++;
			}
			while (number[Last] > Average) {
				Last--;
			}
			if (First >= Last) {
				break;
			}
			swap(First, Last);
			printf("First:%d\tLast:%d\tAverage:%d\t\t [%d],[%d] swap\n",first, last, Average, number[First],number[Last]);
			print();
			First++;
			Last--;
		}
		if (first < First - 1)
			quicksort(first, First - 1);
		if (Last + 1 < last)
			quicksort(Last+1, last);
	}

	void shellsort() {
		int count = 1;
		int h, j;
		input();
		for (h = 1; h <= sortlen; h = 3*h + 1)
			;
		h /= 3;
		while (h >= 1) {
			for (int i = h; i < sortlen; i++) {
				int t = number[i];
				for (j = i - h; j >= 0; j-=h) {
					if (number[j] > t)
						number[j + h] = number[j];
					else
						break;
				}
				number[j + h] = t;
				if (j + h != i) {
					printf("%d번째 [%d]위치에[%d] insert\n", count++, number[j], number[j + 1]);
					print();
				}
			}
			h /= 3;
		}
		printf("정렬후 숫자: ");
		print();
		Sleep(2000);
	}
	
	void binarysearch() {
		
		int search;
		int low = 0;
		int high = sortlen - 1;
		int h = high / 2;
		printf("찾을 숫자를 입력하세요\n");
		scanf_s("%d", &search);
		while (low <= high) {
			if (number[h] == search) {
				break;
			}
			else if(number[h] > search) {
				high = h--;
			}
			else if (number[h] < search) {
				low = h++;
			}
			h = (low + high) / 2;
		}
		if (number[h] ==  search) {
			printf("%d의 위치는 [%d]입니다.\n", search, h);
		}
		else {
			printf("%d은 없습니다.\n", search);
		}
		Sleep(10000);
	}

	void input() {
		system("cls");
		srand(time(NULL));
		printf("\t정렬할 %d개의 숫자자동입력(1~%d범위)\n", sortlen, sortlen);
		for (int i = 0;i < sortlen; i++) {
			number[i] = rand() % sortlen + 1;
		}
		printf("정렬전 숫자: ");
		print();
	}

	void print() {
		for (int i = 0;i < sortlen; i++) {
			printf("%2d ", number[i]);
		}
		printf("\n");
		Sleep(500);
	}
	void selectsort() {
		int count = 1;
		input();
		int min;
		for (int i = 0; i < sortlen - 1; i++) {
			min = i;
			for (int j = i + 1; j < sortlen; j++)
			{
				if (number[j] < number[min])
				{
					min = j;
				}
			}
			swap(i, min);
			printf("%d번째 [%d]and[%d] swap\n", count++, number[i], number[min]);
			print();
		}
		printf("정렬후 숫자: ");
		print();
		Sleep(2000);
	}
	void swap(int x, int mx) {
		int temp = number[x];
		number[x] = number[mx];
		number[mx] = temp;
	}
}