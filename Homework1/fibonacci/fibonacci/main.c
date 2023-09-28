#include <stdio.h>
#include <time.h>

int iterativeFibonacci(int number);
int recursiveFibonacci(int number);
int testForRecursiveFibonacci(void);
int testForIterativeFibonacci(void);
int tests(void);
void timeCompare(void);

int main(void)
{
	const int errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}
	printf("Tests passed successfully!\n");
	timeCompare();
	return 0;
}

int iterativeFibonacci(int number)
{
	if (number == 0)
	{
		return 0;
	}
	if (number <= 2)
	{
		return 1;
	}
	else
	{
		int firstPrevious = 1, secondPrevious = 1; // ��� ���������� ���� ���������� ����������� 
		int result;
		for (int i = 0; i < number - 2; ++i)
		{
			result = firstPrevious + secondPrevious;
			firstPrevious = secondPrevious;
			secondPrevious = result;
		}
		return result;
	}
}

int recursiveFibonacci(int number)
{
	if (number == 0)
	{
		return 0;
	}
	if (number <= 2)
	{
		return 1;
	}
	return recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2);
}

int testForRecursiveFibonacci(void)
{
	// ���� 1: �������� ������� ����� ���������
	if (recursiveFibonacci(0) != 0) {
		return 1;
	}

	// ���� 2: �������� ������� ����� ���������
	if (recursiveFibonacci(1) != 1) {
		return 2;
	}

	// ���� 3: �������� �������� ����� ���������
	if (recursiveFibonacci(2) != 1) {
		return 3;
	}

	// ���� 4: �������� ������ ����� ���������
	if (recursiveFibonacci(4) != 3) {
		return 4;
	}

	// ���� 5: �������� �������� ����� ���������
	if (recursiveFibonacci(9) != 34) {
		return 5;
	}

	return 0;
}

int testForIterativeFibonacci(void)
{
	// ���� 1: �������� ������� ����� ���������
	if (iterativeFibonacci(0) != 0) {
		return 1;
	}

	// ���� 2: �������� ������� ����� ���������
	if (iterativeFibonacci(1) != 1) {
		return 2;
	}

	// ���� 3: �������� �������� ����� ���������
	if (iterativeFibonacci(2) != 1) {
		return 3;
	}

	// ���� 4: �������� ������ ����� ���������
	if (iterativeFibonacci(4) != 3) {
		return 4;
	}

	// ���� 5: �������� �������� ����� ���������
	if (iterativeFibonacci(9) != 34) {
		return 5;
	}

	return 0;
}

int tests(void)
{
	// �������� �� ������ � ������������ ������
	const int errorRecursiveTest = testForRecursiveFibonacci();
	if (errorRecursiveTest)
	{
		printf("Error of recursive Fibonacci algorithm test\n");
		return errorRecursiveTest;
	}

	// �������� �� ������ � ������������ ������
	const int errorIterativeTest = testForRecursiveFibonacci();
	if (errorIterativeTest)
	{
		printf("Error of iterative Fibonacci algorithm test\n");
		return errorIterativeTest;
	}
}

void timeCompare(void)
{
	// ���������� ����� ������������ � ������������ ��������
	clock_t start, end;
	double timeForRecursive, timeForIterative;

	for (int i = 0; i < 50; ++i)
	{
		// ������� ����� ��� ������������ �������
		start = clock();
		recursiveFibonacci(i);
		end = clock();
		timeForRecursive = ((double)(end - start)) / CLOCKS_PER_SEC;

		// ������� ����� ��� ������������ �������
		start = clock();
		iterativeFibonacci(i);
		end = clock();
		timeForIterative = ((double)(end - start)) / CLOCKS_PER_SEC;

		//������� �� �����
		printf("%d Fibonacci number took for iterative took %lf and took for recursive \n", i, timeForRecursive, timeForIterative);
	}
}