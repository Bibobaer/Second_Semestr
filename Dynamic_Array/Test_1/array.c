#include "array.h"

DymArr* NewArr(int A) {
	if (A == 0)
		return NULL;
	DymArr* Result;
	Result = (DymArr*)malloc(sizeof(DymArr));
	if (!Result)
		return Result;

	(*Result).size = A;
	(*Result).countElem = 0;
	(*Result).check = 0;

	(*Result).data = (int*)malloc(sizeof(int)*A);
	if ((*Result).data == NULL) {
		free(Result);
		Result = NULL;
	}
	return Result;
}

void InsertElem(DymArr* Arr, int NewElem) {
	if ((*Arr).countElem == (*Arr).size) {
		int* NewArr = (int*)realloc((*Arr).data, sizeof(int) * ((*Arr).size + 1));
		if (NewArr == NULL)
			return;
		(*Arr).data = NewArr;
		*((*Arr).data + (*Arr).countElem) = NewElem;
		(*Arr).countElem += 1;
		(*Arr).size += 1;
		return;
	}
	else {
		*((*Arr).data + (*Arr).countElem) = NewElem;
		(*Arr).countElem += 1;
		return;
	}
}

int GetElem(DymArr* Arr, int index) {
	if (index > (*Arr).countElem - 1 || index < 0) {
		(*Arr).check = 1;
		return -1;
	}
	else
		return *((*Arr).data + index);
}

void FreeArr(DymArr* Arr) {
	if (Arr == NULL || (*Arr).data == NULL) {
		return;
	}
	else {
		free((*Arr).data);
		free(Arr);
		return;
	}
}

void Print_Arr(DymArr* Arr) {
	if (Check_Operation == 1)
		return;
	for (int i = 0; i < (*Arr).size; i++) {
		printf("%d ", GetElem(Arr, i));
	}
}

int Check_Operation(DymArr* Arr) {
	int Tmp = (*Arr).check == 0 ? 0 : 1;
	return Tmp;
}