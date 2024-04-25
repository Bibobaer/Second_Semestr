#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

#include <limits.h>
#include <float.h>

#include "sput.h"

float Add(float a, float b);
float Sub(float a, float b);
float Multi(float a, float b);
float Div(float a, float b);
float Sqrt(float a);
float Cos(float a);
float Sin(float a);

void Calc_2_op(char op[], float a, float b);
void Calc_1_op(char op[], float a);

_Bool Check_big_op(char op[]);

void test_Op() {
	sput_fail_unless(Add(31.1, 42.9) == 74, "Test 1 norm\n");
	sput_fail_unless(Add(-12, 17) == 5, "Test 2 norm\n");
	sput_fail_unless(Add(INT_MAX, 1) == INT_MIN-1, "Test 3 norm\n");

	sput_fail_unless(Div(10, 0) == 0, "Test 4 norm\n");
	sput_fail_unless(Div(-100, -2) == 50, "Test 5 norm\n");
	sput_fail_unless(Div(FLT_MAX+1, FLT_MAX) == 1, "Test 6 norm\n");

}

void test_Func() {
	sput_fail_unless(Sqrt(4) == 2, "Test 1 norm");
	sput_fail_unless(Sqrt(-9) == 0, "Test 2 norm");
}

int main() {
	sput_start_testing();

	sput_enter_suite("Check Add and Div");
	sput_run_test(test_Op);
	sput_enter_suite("Check Sqrt");
	sput_run_test(test_Func);

	sput_finish_testing();

	/*char operation[5];
	float Num_1 = 0;
	float Num_2 = 0;
	test_Op();
	scanf_s("%s", operation, 5);
	if (Check_big_op(operation) == 0) {
		scanf_s("%f %f", &Num_1, &Num_2);
		Calc_2_op(operation, Num_1, Num_2);
	}
	else {
		scanf_s("%f", &Num_1);
		Calc_1_op(operation, Num_1);
	}*/

	return 0;
}

float Add(float a, float b) {
	return a + b;
}

float Sub(float a, float b) {
	return a - b;
}

float Multi(float a, float b) {
	return a * b;
}

float Div(float a, float b) {
	if (b == 0)
		return 0;
	return a / b;
}

float Sqrt(float a) {
	if (a < 0)
		return 0;
	return (float)sqrt((double)a);
}

float Cos(float a) {
	return cosf(a);
}

float Sin(float a) {
	return sinf(a);
}

void Calc_2_op(char op[], float a, float b) {
	if (strcmp(op, "+") == 0) {
		printf("%f", Add(a, b));
	}
	else if (strcmp(op, "-") == 0) {
		printf("%f", Sub(a, b));
	}
	else if (strcmp(op, "*") == 0) {
		printf("%f", Multi(a, b));
	}
	else if (strcmp(op, "/") == 0) {
		printf("%f", Div(a, b));
	}
	else {
		printf("Error");
	}
	return;
}

void Calc_1_op(char op[], float a) {
	if (strcmp(op, "sqrt") == 0) {
		printf("%f", Sqrt(a));
	}
	else if (strcmp(op, "cos") == 0) {
		printf("%f", Cos(a));
	}
	else if (strcmp(op, "sin") == 0) {
		printf("%f", Sin(a));
	}
	else {
		printf("Error");
	}
	return;
}

_Bool Check_big_op(char op[]) {
	if (strcmp(op, "sqrt") == 0 || strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0)
		return 1;
	else
		return 0;
}