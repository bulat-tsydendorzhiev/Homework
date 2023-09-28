#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void swap(int* number1, int* number2);
void halfQsort(int* arrayOfNumbers, int left, int right);
void printArray(int* arrayOfNumbers, int length);
int writeAndCheckData(int* arrayLength);
void createArrayOfRandomNumbers(int* arrayOfNumbers, int length);
void printResult(int* arrayOfNumbers, int length);
int halfQsortTests(void);
int arraysEqual(int* arrayOfNumbers, int* expected, int length);

int main(void)
{
	setlocale(LC_ALL, "Rus");
	int arrayLength;
	const int errorCode = writeAndCheckData(&arrayLength);
	if (!errorCode)
	{
		const int errorHalfQsortTest = halfQsortTests();
		if (!errorHalfQsortTest)
		{
			int* arrayOfNumbers = malloc(sizeof(int) * arrayLength);
			createArrayOfRandomNumbers(arrayOfNumbers, arrayLength);
			printResult(arrayOfNumbers, arrayLength);
			free(arrayOfNumbers);
			return 0;
		}
		return errorHalfQsortTest;
	}
	return errorCode;
}

int writeAndCheckData(int* arrayLength)
{
	// ������� ����� � �������� ������
	printf("������� ����� �������: ");
	const int amountOfElements = scanf_s("%d", arrayLength);
	if (amountOfElements != 1 || *arrayLength < 0)
	{
		if (*arrayLength < 0)
		{
			printf("������: ����� ������� ������ ���� ��������������� ������ \n");
			return 2;
		}
		else
		{
			printf("������: ������� ������������ ������");
			return 1;
		}
	}
	return 0;
}

void createArrayOfRandomNumbers(int* arrayOfNumbers, int length)
{
	for (int i = 0; i < length; ++i)
	{
		arrayOfNumbers[i] = rand();
	}
}

void swap(int* number1, int* number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

void halfQsort(int* arrayOfNumbers, int left, int right)
{
	// ������� ��� ����������� ����� ������ �������� �������� � ������ �������,
	// � ������ - � �����
	int pivot = arrayOfNumbers[(int)((left + right) / 2)]; // ������� ������� ��� ���������
	printf("pivot = %d\n", pivot);
	while (left <= right)
	{
		while (arrayOfNumbers[left] < pivot)
		{
			left++; // �������� ������ ���������, ���� �� ������ ������ pivot
		}
		while (arrayOfNumbers[right] > pivot)
		{
			right--; // �������� ����� ���������, ���� �� ������ ������ pivot
		}

		if (left <= right)
		{
			// ������ ������� ������� ������� ������� � ������� � �������� ���������,
			// ����� �� �������� � ����������� �����
			swap(&arrayOfNumbers[left], &arrayOfNumbers[right]);
			left++;
			right--;
		}
	}
}

void printArray(int* arrayOfNumbers, int length)
{
	for (int i = 0; i < length; ++i)
	{
		printf("%d ", arrayOfNumbers[i]);
	}
	printf("\n");
}

void printResult(int* arrayOfNumbers, int length)
{
	// ������� ������ �� � ����� ���������� �������
	printf("������ ��: ");
	printArray(arrayOfNumbers, length);
	halfQsort(arrayOfNumbers, 0, length - 1);
	printf("������ �����: ");
	printArray(arrayOfNumbers, length);
}

int arraysEqual(int* arrayOfNumbers, int* expected, int length)
{
	// ���������� 1 ��� ������, � ��������� ������ - 0
	for (int i = 0; i < length; ++i)
	{
		if (arrayOfNumbers[i] != expected[i])
		{
			return 0;
		}
	}
	return 1;
}

int halfQsortTests(void)
{
	// ���� 1: �������� ���������� ������� �� ������ ��������
	int array1[] = { 5 };
	int expected1[] = { 5 };
	halfQsort(&array1, 0, 0);
	if (!arraysEqual(&array1, &expected1, 1)) {
		return 1;
	}

	// ���� 2: �������� ���������� ������� � �������������� ����������
	int array2[] = { 7,3,5,3,2 };
	int expected2[] = { 2,3,3,5,7 };
	halfQsort(&array2, 0, 4);
	if (!arraysEqual(&array2, &expected2, 5)) {
		return 2;
	}

	// ���� 3: �������� ���������� �������������� �� ����������� �������
	int array3[] = { 1,2,3,4,5 };
	int expected3[] = { 1,2,3,4,5 };
	halfQsort(&array3, 0, 4);
	if (!arraysEqual(&array3, &expected3, 5)) {
		return 3;
	}

	// ���� 4: �������� ���������� �������������� �� �������� �������
	int array4[] = { 5,4,3,2,1 };
	int expected4[] = { 1,2,3,4,5 };
	halfQsort(&array4, 0, 4);
	if (!arraysEqual(&array4, &expected4, 5)) {
		return 4;
	}

	// ���� 5: �������� ���������� ������� � �������� ����������� ���������
	int array5[] = { 9,4,7,2,1 };
	int expected5[] = { 1,4,2,7,9 };
	halfQsort(&array5, 0, 4);
	if (!arraysEqual(&array5, &expected5, 5)) {
		return 5;
	}

	// ���� 6: �������� ���������� ������� � ������ ����������� ���������
	int array6[] = { 6,3,8,2 };
	int expected6[] = { 2,3,8,6 };
	halfQsort(&array6, 0, 3);
	if (!arraysEqual(&array6, &expected6, 4)) {
		return 6;
	}

	return 0;
}
