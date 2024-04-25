#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct Person {
	char* Name;
	char* LastName;
}Person;

typedef struct DymArr {
	size_t size;
	int countElem;
	Person* Data;
	_Bool check;
}DymArr;

typedef int(*SwapFuncBy)(Person, Person);

void BubbleSortArr(DymArr* Arr, SwapFuncBy predicate);
void SwapPerson(Person* P1, Person* P2);

void Print_Arr(DymArr* Arr);

DymArr* NewArray(size_t Size);
void InsertElements(DymArr* Arr, size_t Size);
Person GetElem(DymArr* Arr, int index);
void FreeArray(DymArr* Arr);