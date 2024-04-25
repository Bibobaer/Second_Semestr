#include "DymArr.h"

void TestAdd() {
	DymArr* Array = CreateDymArray(1);
	if (Array == NULL || Array->Data == NULL) {
		printf("Error. Array not alloc");
		return -1;
	}
	AddElements(Array, 52);
	sput_fail_unless(Array->Data[0] == 52, "Test 1 norm");
	AddElements(Array, -1488);
	sput_fail_unless(Array->Data[1] == -1488, "Test 2 norm");
	AddElements(Array, INT_MAX+1);
	sput_fail_unless(Array->Data[2] == INT_MIN, "Test 3 norm");

}

void TestTimeSort() {
	DymArr* Array_1 = CreateDymArray(5);
	DymArr* Array_2 = CreateDymArray(5);
	if (Array_1 == NULL || Array_1->Data == NULL || Array_2 == NULL || Array_2->Data == NULL) {
		printf("Error. Array not alloc");
		return -1;
	}

	for (int i = 0; i < 20000; i++) {
		AddElements(Array_1, rand());
		AddElements(Array_2, rand());
	}

	clock_t start_1 = clock();
	BubbleSortArr(Array_1);
	clock_t diff_1 = clock() - start_1;

	clock_t start_2 = clock();
	QuickSort(Array_2, 0, Array_2->CountElements-1);
	clock_t diff_2 = clock() - start_2;
	
	sput_fail_unless(diff_1 >= diff_2, "Test norm");
}

void TestCorectSort() {
	DymArr* Array = CreateDymArray(4);
	if (Array == NULL || Array->Data == NULL) {
		printf("Error. Array not alloc");
		return -1;
	}

	AddElements(Array, 17);
	AddElements(Array, 1);
	AddElements(Array, 8);

	BubbleSortArr(Array);

	_Bool res = 0;
	if (Array->Data[0] == 1 && Array->Data[1] == 8 && Array->Data[2] == 17)
		res = 1;

	sput_fail_unless(res == 1, "Test 1 norm\n");

	Array->Data[0] = -16;
	Array->Data[1] = -54;
	Array->Data[2] = 41;

	QuickSort(Array, 0, Array->CountElements - 1);

	if (Array->Data[0] == -54 && Array->Data[1] == -16 && Array->Data[2] == 41)
		res = 1;
	else
		res = 0;

	sput_fail_unless(res == 1, "Test 2 norm\n");

	Array->Data[0] = INT_MAX;
	Array->Data[1] = INT_MAX + 1;
	Array->Data[2] = INT_MAX + 2;

	BubbleSortArr(Array);

	if (Array->Data[0] == INT_MAX+1 && Array->Data[1] == INT_MAX+2 && Array->Data[2] == INT_MAX)
		res = 1;
	else
		res = 0;

	sput_fail_unless(res == 1, "Test 3 norm\n");
}

int main() {
	
	sput_start_testing();

	sput_enter_suite("Check Add Elements\n");
	sput_run_test(TestAdd);

	sput_enter_suite("Check Correct Sort\n");
	sput_run_test(TestCorectSort);

	sput_enter_suite("Check Time Sort\n");
	sput_run_test(TestTimeSort);

	sput_finish_testing();
	return 0;
}