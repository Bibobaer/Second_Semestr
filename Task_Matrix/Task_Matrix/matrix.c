#include "matrix.h"

errno_t AllocMatrixOutConfig(Matrix* matrix, const char* filePath) {
	errno_t ResCode = 0;
	FILE* File = NULL;
	ResCode = fopen_s(&File, filePath, "r");
	if (ResCode != 0 || File == NULL) {
		printf("Error open config file with code: %d\n", ResCode);
		return ResCode;
	}
	uint HeightTMP;
	uint WidthTMP;

	int ret_h = fscanf_s(File, "height = %u\n", &HeightTMP);
	if (ret_h != 1) {
		printf("Error load config: read id\n");
		fclose(File);
		return ENODATA;
	}
	int ret_w = fscanf_s(File, "width = %u", &WidthTMP);
	if (ret_w != 1) {
		printf("Error load config: read id\n");
		fclose(File);
		return ENODATA;
	}

	AllocMatrix(matrix, HeightTMP, WidthTMP);
	for (uint i = 0; i < matrix->height; i++)
		for (uint j = 0; j < matrix->width; j++)
			matrix->ArrayOfNumbers[i][j] = rand() % 4;
	fclose(File);
	return ResCode;
}

void AllocMatrix(Matrix* matrix, uint rows, uint cols) {
	if (rows == 0 || cols == 0)
		return;
	matrix->height = rows;
	matrix->width = cols;

	matrix->ArrayOfNumbers = (int**)malloc(rows*sizeof(int*));
	if (matrix->ArrayOfNumbers == NULL) {
		printf("Matrix empty\n");
		return;
	}
	for (unsigned int i = 0; i < rows; i++) {
		matrix->ArrayOfNumbers[i] = (int*)malloc(cols*sizeof(int));
		if (matrix->ArrayOfNumbers[i] == NULL) {
			printf("Matrix empty\n");
			return;
		}
	}
}

Matrix SumMatrix(Matrix A, Matrix B) {
	Matrix Res = {0, 0, NULL};
	if (A.width == 0 || A.height == 0 || A.ArrayOfNumbers == NULL || B.width == 0 || B.height == 0 || B.ArrayOfNumbers == NULL) {
		printf("One of the matrix is empty\n");
		return Res;
	}
	if (A.height != B.height || A.width != B.width) {
		printf("Size of matrixs not equels\n");
		return Res;
	}
	AllocMatrix(&Res, A.height, A.width);
	for (uint i = 0; i < Res.height; i++)
		for (uint j = 0; j < Res.width; j++)
			Res.ArrayOfNumbers[i][j] = A.ArrayOfNumbers[i][j] + B.ArrayOfNumbers[i][j];
	return Res;
}

void PrintMatrix(Matrix mat) {
	if (mat.height == 0 || mat.width == 0 || mat.ArrayOfNumbers == NULL) {
		printf("Matrix is empty\n");
		return;
	}
	for (uint i = 0; i < mat.height; i++) {
		for (uint j = 0; j < mat.width; j++)
			printf("%d ", mat.ArrayOfNumbers[i][j]);
		printf("\n");
	}
	return;
}