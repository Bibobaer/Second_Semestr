#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N	10

typedef struct DymArr {
	int countElem;
	int size;
	int* data;
	_Bool check;
}DymArr;

DymArr* NewArr(int A);
void InsertElem(DymArr* Arr, int NewElem);
int GetElem(DymArr* Arr, int index);
void FreeArr(DymArr* Arr);
void Print_Arr(DymArr* Arr);
int Check_Operation(DymArr* Arr);