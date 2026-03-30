/*#include <stdio.h>
#include <stdlib.h>

int arr[10] = {1, 3, 4, 5, 6, 7, 8, 9};
int count = 8;

//선형 탐색
	for (int i = 0; i < count; i++)
		if (arr[i] == x)
			return i;
	return -1; // NULL

	//이진 탐색
	int binary_search(int s, int e, int x)
	{
		if (s == e)
			return (arr[s] == x) ? s : -1;

		int mid = (s + e) / 2;
		if (x == arr[mid])
			return mid;
		else if (arr[mid] > x)
			return binary_search(s, mid - 1, x);
		else
			return binary_search(mid + 1, e, x);
	}

void main() {
	int x = 6;
	int idx = linear_search(x);
	printf("%d position: %d\n", x, idx);

	idx = linear_search(0, count-1, x);
	printf("%d position: %d\n", x, idx);
	}
	return 0;
}*/

/*#include <stdio.h>
#include <stdlib.h>

int arr[10] = { 1, 2, 4, 5, 6, 7 };
int count = 6;

void insert_by_value(int x)
{
	int i, j;
	int size = 10;
	// 0. 예외적인 경우는?
	if (count == 0) {
		arr[0] = x;
		count++;
		return;
	}
	if (count == size) {
		printf("Overflow\n");
		return;
	}
	// 1. x를 추가할 위치를 결정
	for (i = 0; i < count; i++) {
		if (arr[i] > x)
			break;
	}
	// 2. 추가할 위치의 원소를 옮겨서 공간을 확보(à)
	for (j = count - 1; j >= i; j--)
		arr[j + 1] = arr[j];
	// 3. 원소를 추가
	arr[i] = x;
	// 4. 배열의 크기 (count)를 증가
	count++;
	return arr;
}

void main() {
	int x = 3;
	printf("Before insertion: ");
	for (int i = 0; i < count; i++)
		printf("%d ", arr[i]);
	printf("\n");

	insert_by_value(x);

	printf("After insertion: ");
	for (int i = 0; i < count; i++)
		printf("%d ", arr[i]);
	printf("\n");
}*/

/*#include <stdio.h>
#include <stdlib.h>

char arrc[10][30] = { "BAT", "CAT", "EAT", "FAT", "JAT", "LAT" };
int count = 6;

void insert_by_valuec(char x[30])
{
	char i, j;
	// 0. 예외적인 경우는?
	if (count == 0) {
		strcpy(arrc[0], x);
		count++;
		return;
	}
	if (count == 10) {
		printf("Overflow\n");
		return;
	}
	// 1. x를 추가할 위치를 결정
	for (i = 0; i < count; i++) {
		if (strcmp(arrc[i], x) > 0)
			break;
	}
	// 2. 추가할 위치의 원소를 옮겨서 공간을 확보(à)
	for (j = count - 1; j >= i; j--)
		strcpy(arrc[j + 1], arrc[j]);
	// 3. 원소를 추가
	strcpy(arrc[i], x);
	// 4. 배열의 크기 (count)를 증가

	count++;
}

void main() {
	char x_string[3][30] = { "DAT" };
	printf("Before insertion: ");
	for (int i = 0; i < count; i++)
		printf("%s ", arrc[i]);
	printf("\n");

	insert_by_valuec(x_string);

	printf("After insertion: ");
	for (int i = 0; i < count; i++)
		printf("%s ", arrc[i]);
	printf("\n");
}*/
/*#include <stdio.h>
#include <stdlib.h>


char arrc[10][30] = {"BAT", "CAT", "EAT", "FAT", "JAT", "LAT"};
char** arrd;
int count = 6;

void print_arrd(char** arrc) {
	for (int i = 0; i < count; i++)
		printf("%s ", arrc[i]);
	printf("\n");
}

void insert_by_valuec(char** arr, char* x)
{
	int i, j;
	// 0. 예외적인 경우는?

	// 1. x를 추가할 위치를 결정
	for (i = 0; i < count; i++) {
		if (strcmp(arr[i], x) > 0)
			break;
	}
	// 2. 추가할 위치의 원소를 옮겨서 공간을 확보(à)
	for (j = count - 1; j >= i; j--)
		strcpy(arr[j + 1], arr[j]);
	// 3. 원소를 추가
	strcpy(arr[i], x);
	// 4. 배열의 크기 (count)를 증가
	count++;
}

int main() {
	int x = 3;
	char x_string[30] = "DAT";

	arrd = (char**)calloc(10, sizeof(char*));
	for (int i = 0; i < 10; i++) {
		arrd[i] = (char*)calloc(30, sizeof(char));
		strcpy(arrd[i], arrc[i]); // arrc -> arrd
	}

	print_arrd(arrd);
	insert_by_valuec(arrd, x_string);
	print_arrd(arrd);
}*/

#include <stdio.h>

int arr[10] = { 1, 2, 4, 5, 6, 7};
int count = 6;

void printarr() {
	for (int i = 0; i < count; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void insert_by_value(int* arr, int x)
{
	int i, j;
	int size = 10;
	if (count == 0) {
		arr[0] = x;
		count++;
		return;
	}
	if (count == size) {
		printf("Overflow\n");
		return;
	}
	for (i = 0; i < count; i++) {
		if (arr[i] > x)
			break;
	}
	for (j = count - 1; j >= i; j--)
		arr[j + 1] = arr[j];
	arr[i] = x;
	count++;
}

void delete_by_value(int* arr, int x)
{
	// 1. 제거할 x를 arr에서 탐색
	int i, j;
	for (i = 0; i < count; i++) {
		if (arr[i] == x)
			break;
	}
	if (i == count)
		return; // x가 arr에 없는 경우

	// 2. 제거할 위치 뒤의 원소를 앞으로 옮겨서 공간을 확보
	for (j = i; j < count - 1; j++)
		arr[j] = arr[j + 1];

	// 3. 배열의 크기 (count)를 감소
	count--;
}

int main() {
	int x = 3;
	printarr();
	insert_by_value(arr, x);
	printarr();

	delete_by_value(arr, x);
	printarr();

	return 0;
}