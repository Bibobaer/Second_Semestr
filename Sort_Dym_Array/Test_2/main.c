#include "Person.h"

int Name(Person P1, Person P2) {
	return strcmp(P1.Name, P2.Name);
}
int LastName(Person P1, Person P2) {
	return strcmp(P1.LastName, P2.LastName);
}

int main() {
	srand((unsigned int)time(NULL));
	SwapFuncBy Func = NULL;

	DymArr* Array = NewArray(10);
	InsertElements(Array, 16);
	printf("Array before sorting\n");
	Print_Arr(Array);

	char action = 0;
	printf("Select, the sorting will be by\n1)Name\n2)Lastname\n");
	action = _getch();
	if (action == '1')
		Func = Name;
	else if (action == '2')
		Func = LastName;
	else {
		printf("Wrong action");
		return 1;
	}
	BubbleSortArr(Array, Func);
	printf("Array after sorting\n");
	Print_Arr(Array);
	FreeArray(Array);
	return 0;
}