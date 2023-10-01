#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void swap(int* number1, int* number2);
void insertionSort(int* arrayOfNumbers, int left, int right);
void quickSort(int* arrayOfNumbers, int left, int right);
int writeData(int* arrayLength, int* amountOfRandomNumber);
int binarySearch(int number, int* arrayOfNumbers, int length);
void createArrayOfNumbers(int* arrayOfNumbers, int arrayLength);
void check(int randomNumber, int* arrayOfNumbers, int arrayLength);
int binarySearchTest(void);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    const int errorBinarySearchTest = binarySearchTest();
    if (!errorBinarySearchTest)
    {
        const int arrayLength, amountOfRandomNumber;
        // �������� �� ���������� ���� ������
        if (!writeData(&arrayLength, &amountOfRandomNumber))
        {
            // ������� ������ �� n(arrayLength) ��������� ���������
            int* arrayOfNumbers = calloc(arrayLength, sizeof(int));
            int randomNumber;
            createArrayOfNumbers(arrayOfNumbers, arrayLength);

            // ��������� ������, ����� ������������ �������� �����
            quickSort(arrayOfNumbers, 0, arrayLength - 1);

            //��������� ��������� �� ����� � �������
            for (int i = 0; i < amountOfRandomNumber; ++i)
            {
                randomNumber = rand() % 1000;
                check(randomNumber, arrayOfNumbers, arrayLength);
            }
            return 0;
        }
        return 1;
    }
    return errorBinarySearchTest;
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

void quickSort(int* arrayOfNumbers, int left, int right)
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
        quickSort(arrayOfNumbers, left, j + 1);
    }
    if (i < right)
    {
        quickSort(arrayOfNumbers, i, right);
    }
}

int writeData(int* arrayLength, int* amountOfRandomNumber)
{
    char check;
    printf("������� ����� n � k: ");
    const int errorScanf = scanf_s("%d %d%c", arrayLength, amountOfRandomNumber, &check);
    if (errorScanf != 3 || check != '\n' || check == ',' || *arrayLength <= 0 || *amountOfRandomNumber <= 0)
    {
        printf("������: n � k ������ ���� ������������ �������\n");
        return 1;
    }
    return 0;
}

int binarySearch(int number, int* arrayOfNumbers, int length)
{
    int middleIndex, middleElement;
    int start = 0;
    int end = length - 1;

    while (start <= end)
    {
        // ����� ���������� ������� � ���������� ��� � ������� ������
        middleIndex = (start + end) / 2;
        middleElement = arrayOfNumbers[middleIndex];
        if (number == middleElement)
        {
            // ����� �������
            return 1;
        }
        else if (middleElement < number)
        {
            // ����������� ������ ��������� ������ ������ ����������� �����, ��� ��� ����� ����� ������ ��������
            start = middleIndex + 1;
        }
        else
        {
            // ����������� ����� ��������� ������ ������ ����������� �����, ��� ��� ����� ������ ������ ��������
            end = middleIndex - 1;
        }
    }
    // ����� �� �������
    return 0;
}

void createArrayOfNumbers(int* arrayOfNumbers, int arrayLength)
{
    srand(time(NULL));
    for (int i = 0; i < arrayLength; ++i)
    {
        arrayOfNumbers[i] = rand() % 1000;
    }
}

void check(int randomNumber, int* arrayOfNumbers, int arrayLength)
{
    // ���������, ��������� �� ����� � �������
    if (binarySearch(randomNumber, arrayOfNumbers, arrayLength))
    {
        printf("����� %d ��������� � �������, ��������� �� %d �����\n", randomNumber, arrayLength);
    }
    else
    {
        printf("����� %d �� ��������� � �������, ��������� �� %d �����\n", randomNumber, arrayLength);
    }
}

int binarySearchTest(void)
{
    // ���� 1: ����� ������������� ��������
    int array1[] = { 1, 3, 5, 7, 9 };
    int length1 = sizeof(array1) / sizeof(array1[0]);
    int target1 = 7;
    if (!binarySearch(target1, array1, length1))
    {
        return 1;
    }

    // ���� 2: ����� ��������������� ��������
    int array2[] = { 2, 4, 6, 8, 10 };
    int length2 = sizeof(array2) / sizeof(array2[0]);
    int target2 = 5;
    if (binarySearch(target2, array2, length2))
    {
        return 2;
    }

    // ���� 3: ����� � ������� � ����� ���������
    int array3[] = { 5 };
    int length3 = sizeof(array3) / sizeof(array3[0]);
    int target3 = 5;
    if (!binarySearch(target3, array3, length3))
    {
        return 3;
    }

    // ���� 4: ����� � ������� � �������������� ����������
    int array4[] = { 2, 2, 2, 2, 2 };
    int length4 = sizeof(array4) / sizeof(array4[0]);
    int target4 = 2;
    if (!binarySearch(target4, array4, length4))
    {
        return 3;
    }

    return 0;
}