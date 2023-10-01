#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int writeData(int* arrayLength, int** arrayOfNumbers);
void swap(int* number1, int* number2);
void insertionSort(int* arrayOfNumbers, int low, int high);
void smartQuickSort(int* arrayOfNumbers, int left, int right);
void printArray(int* arrayOfNumbers, int length);
int arraysEqual(int* realArray, int* expectedArray, int length);
int smartQuickSortTests(void);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    const int errorTestOfSmartQuickSort = smartQuickSortTests();
    if (!errorTestOfSmartQuickSort)
    {
        int arrayLength;
        int *arrayOfNumbers;
        const int errorWriteData = writeData(&arrayLength, &arrayOfNumbers);
        
        if (!errorWriteData)
        {
            printf("������ ��: ");
            printArray(arrayOfNumbers, arrayLength);
            smartQuickSort(arrayOfNumbers, 0, arrayLength - 1);
            printf("������ ��: ");
            printArray(arrayOfNumbers, arrayLength);

            free(arrayOfNumbers);
            return 0;
        }
        return errorWriteData;
    }
    return errorTestOfSmartQuickSort;
}

int writeData(int* arrayLength, int** arrayOfNumbers)
{
    int amountOfValues;
    char check;

    printf("������� ����� ������������ �������: ");
    amountOfValues = scanf_s("%d%c", arrayLength, &check);
    if (*arrayLength <= 0 || amountOfValues != 2 || check != '\n')
    {
        printf("������������ ���� ������\n");
        if (*arrayLength <= 0)
        {
            printf("����� ������� ������ ���� ����������� ������\n");
        }
        return 1;
    }

    printf("������� ��� ������: ");
    *arrayOfNumbers = (int*)malloc(sizeof(int) * *arrayLength);
    for (int i = 0; i < *arrayLength; ++i)
    {
        scanf_s("%d", &(*arrayOfNumbers)[i]);
    }
    return 0;
}

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* arrayOfNumbers, int left, int right)
{
    int value, j;
    for (int i = left; i <= right; ++i)
    {
        value = arrayOfNumbers[i];
        j = i;
        while (j > left && arrayOfNumbers[j - 1] > value)
        {
            arrayOfNumbers[j] = arrayOfNumbers[j - 1];
            j--;
        }
        arrayOfNumbers[j] = value;
    }
}

void smartQuickSort(int* arrayOfNumbers, int left, int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(arrayOfNumbers, left, right);
        return;
    }
    int pivot = arrayOfNumbers[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (arrayOfNumbers[i] < pivot)
        {
            i++;
        }
		while (arrayOfNumbers[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			swap(&arrayOfNumbers[j], &arrayOfNumbers[i]);
			i++;
			j--;
		}
	}

    if (left < j)
    {
        smartQuickSort(arrayOfNumbers, left, j + 1);
    }
    if (i < right)
    {
        smartQuickSort(arrayOfNumbers, i, right);
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

int arraysEqual(int* realArray, int* expectedArray, int length)
{
    // ���������� 1, ���� ��� �������� �������� �����, � ��������� ������ - 0
    for (int i = 0; i < length; ++i)
    {
        if (realArray[i] != expectedArray[i])
        {
            return 0;
        }
    }
    return 1;
}

int smartQuickSortTests(void)
{
    // ���� 1: �������� ���������� ������� �� ������ ��������
    int array1[] = { 5 };
    int expected1[] = { 5 };
    smartQuickSort(&array1, 0, 0);
    if (!arraysEqual(&array1, &expected1, 1))
    {
        return 1;
    }

    // ���� 2: �������� ���������� ������� � �������������� ����������
    int array2[] = { 7, 3, 5, 3, 2 };
    int expected2[] = { 2, 3, 3, 5, 7 };
    smartQuickSort(&array2, 0, 4);
    if (!arraysEqual(&array2, &expected2, 5))
    {
        return 2;
    }

    // ���� 3: �������� ���������� �������������� �� ����������� �������
    int array3[] = { 1, 2, 3, 4, 5 };
    int expected3[] = { 1, 2, 3, 4, 5 };
    smartQuickSort(&array3, 0, 4);
    if (!arraysEqual(&array3, &expected3, 5))
    {
        return 3;
    }

    // ���� 4: �������� ���������� �������������� �� �������� �������
    int array4[] = { 5, 4, 3, 2, 1 };
    int expected4[] = { 1, 2, 3, 4, 5 };
    smartQuickSort(&array4, 0, 4);
    if (!arraysEqual(&array4, &expected4, 5))
    {
        return 4;
    }

    // ���� 5: �������� ���������� ������� � �������� ����������� ���������
    int array5[] = { 9, 4, 7, 2, 1 };
    int expected5[] = { 1,2,4,7,9 };
    smartQuickSort(&array5, 0, 4);
    if (!arraysEqual(&array5, &expected5, 5))
    {
        return 5;
    }

    // ���� 6: �������� ���������� ������� � ������ ����������� ���������
    int array6[] = { 6, 3, 8, 2 };
    int expected6[] = { 2,3,6,8 };
    smartQuickSort(&array6, 0, 3);
    if (!arraysEqual(&array6, &expected6, 4))
    {
        return 6;
    }

    return 0;
}