#include "matrix.h"

int main() {
	srand((uint)time(NULL));
	Matrix A;
	Matrix B;
	Matrix Res;
	errno_t code = AllocMatrixOutConfig(&A, "Config.txt");
	if (code != 0) {
		printf("Error load config. Exit...");
		return -1;
	}
	code = AllocMatrixOutConfig(&B, "Config.txt");
	if (code != 0) {
		printf("Error load config. Exit...");
		return -1;
	}
	Res = SumMatrix(A, B);
	printf("Matrix A\n");
	PrintMatrix(A);
	printf("\nMatrix B\n");
	PrintMatrix(B);
	printf("\nResult Matrix\n");
	PrintMatrix(Res);
	return 0;
}