#include "Person.h"

void BubbleSortArr(DymArr* Arr, SwapFuncBy predicate) {
	for (int i = 0; i < Arr->size - 1; i++) {
		for (int j = 0; j < Arr->size - 1 - i; j++) {
			if (predicate(Arr->Data[j], Arr->Data[j+1]) > 0) {
				SwapPerson(&(Arr->Data[j]), &(Arr->Data[j + 1]));
			}
		}
	}
}

void QuickSort(int* arr, int left, int right) {
	int middle = (right - left) / 2 + left;
	int border = arr[middle];

	int i = left, j = right;

	while (i <= j) {
		while (arr[i] < border)
			i++;
		while (arr[j] > border)
			j--;

		if (i <= j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	if (left < j)
		QuickSort(arr, left, j);
	if (right > i)
		QuickSort(arr, i, right);
}

void SwapPerson(Person* P1, Person* P2) {
	if (P1 == NULL || P2 == NULL)
		return;
	Person tmp = *P1;
	*P1 = *P2;
	*P2 = tmp;
}

void Print_Arr(DymArr* Arr) {
	if (Arr->check == 1)
		return;
	if (Arr == NULL || Arr->Data == NULL)
		return;
	for (int i = 0; i < Arr->size; i++) {
		Person Temp = GetElem(Arr, i);
		if (Arr->check == 1)
			return;
		printf("%d) Name: %s    Lastname: %s\n", i + 1, Temp.Name, Temp.LastName);
	}
}


DymArr* NewArray(size_t Size) {
	if (Size == 0)
		return NULL;
	DymArr* Result = (DymArr*)malloc(sizeof(DymArr));
	if (Result == NULL)
		return Result;
	Result->size = Size;
	Result->countElem = 0;
	Result->check = 0;
	Result->Data = (Person*)malloc(sizeof(Person)*Size);
	if (Result->Data == NULL)
		return NULL;
	for (int i = 0; i < Size; i++) {
		Result->Data[i].Name = malloc(20*sizeof(char*));
		Result->Data[i].LastName = malloc(20 * sizeof(char*));
		if (Result->Data[i].LastName == NULL || Result->Data[i].Name == NULL)
			return NULL;

	}
	return Result;
}

void InsertElements(DymArr* Arr, size_t Size) {
	if (Arr == NULL || Arr->Data == NULL || Size == 0) 
		return;
	if (Size < Arr->size)
		Arr->size = Size;
	char ArrOfName[][20] = { "Ilya\t\0", "Vladimir\0", "Dmitry\0", "Ivan\0", "Mikhail\0", "Alexander\0", "Roman\0", "Sergey\0", "Nikolai\0", "Boris\t\0" };
	char ArrOfLastName[][20] = { "Ivanov\0", "Smirnov\0", "Popov\0", "Federov\0", "Orlov\0", "Makarov\0", "Volkov\0", "Egorov\0", "Zaharov\0", "Andreev\0" };
	for (int i = 0; i < Size; i++) {
		if (Arr->countElem == Arr->size) {
			Person* NewData = (Person*)realloc(Arr->Data, (Arr->size + 1) * sizeof(Person));
			if (NewData == NULL) {
				Arr->check = 1;
				return;
			}
			Arr->Data = NewData;
			Arr->Data[Arr->countElem].Name = malloc(20*sizeof(char));
			Arr->Data[Arr->countElem].LastName = malloc(20 * sizeof(char));
			if (Arr->Data[Arr->countElem].LastName == NULL || Arr->Data[Arr->countElem].Name == NULL)
				return;
			memcpy(Arr->Data[Arr->countElem].Name, ArrOfName[rand() % 10], 20);
			memcpy(Arr->Data[Arr->countElem].LastName, ArrOfLastName[rand() % 10], 20);
			Arr->size += 1;
			Arr->countElem += 1;
		}
		else {
			memcpy(Arr->Data[Arr->countElem].Name, ArrOfName[rand() % 10], 20);
			memcpy(Arr->Data[Arr->countElem].LastName, ArrOfLastName[rand() % 10], 20);
			Arr->countElem += 1;
		}
	}

}

Person GetElem(DymArr* Arr, int index) {
	Person ErrorStruct = { 0, 0 };
	if (Arr == NULL || Arr->Data == NULL)
		return ErrorStruct;
	if (index > Arr->countElem-1) {
		Arr->check = 1;
		return ErrorStruct;
	}
	else {
		return Arr->Data[index];
	}
}

void FreeArray(DymArr* Arr) {
	if (Arr == NULL || Arr->Data == NULL)
		return;
	free(Arr->Data);
	free(Arr);
}