#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef unsigned int uint;

typedef struct Matrix {
	uint height;
	uint width;
	int** ArrayOfNumbers;
}Matrix;

errno_t AllocMatrixOutConfig(Matrix* matrix, const char* filePath);
void AllocMatrix(Matrix* matrix, uint rows, uint cols);
Matrix SumMatrix(Matrix A, Matrix B);
void PrintMatrix(Matrix mat);