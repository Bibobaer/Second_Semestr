#include "array.h"

int main() {
	DymArr* Array = NewArr(N);
	if (Array == NULL || (*Array).data == NULL) {
		printf("Array is empty");
		return 1;
	}
	for (int i = 0; i < 16; i++) {
		InsertElem(Array, i + 1);
	}
	Print_Arr(Array);
	FreeArr(Array);
	return 0;
}
