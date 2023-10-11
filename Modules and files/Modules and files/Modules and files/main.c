#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "QuickSort.h"

int writeData(char* filename, char** symbols, int* arrayLength)
{
    FILE* file;

    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        return 4040;
    }

    fseek(file, 0, SEEK_END);
    *arrayLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    *symbols = (char*)malloc(*arrayLength * sizeof(char));
    if (*symbols == NULL)
    {
        printf("������ ��� ��������� ������\n");
        return 4041;
    }

    for (int i = 0; i < *arrayLength; ++i)
    {
        fscanf_s(file, "%c", &(*symbols)[i]);
    }

    fclose(file);
    return 0;
}

char findMostFrequent(char* symbols, int arrayLength)
{
    quickSort(symbols, 0, arrayLength - 1);

    char answer = symbols[0];
    int count = 1, maxCount = 1;

    for (int i = 1; i < arrayLength; ++i)
    {
        if (symbols[i - 1] == symbols[i])
        {
            count++;
            if (count > maxCount)
            {
                maxCount = count;
                answer = symbols[i - 1];
            }
        }
        else
        {
            count = 1;
        }
    }
    return answer;
}

int tests()
{
    // ���� 1: ��������� ������������������ �������� "abcaaba"
    char* symbols1;
    int arrayLength1;
    writeData("test1.txt", &symbols1, &arrayLength1);
    if (findMostFrequent(symbols1, arrayLength1) != 'a')
    {
        return 1;
    }

    // ���� 2: ������������������ �� ���������� �������� "aaaaaaaaa"
    char* symbols2;
    int arrayLength2;
    writeData("test2.txt", &symbols2, &arrayLength2);
    if (findMostFrequent(symbols2, arrayLength2) != 'a')
    {
        return 2;
    }

    // ���� 3: ���������� ���������� �������� � ������������������ "abcde"
    char* symbols3;
    int arrayLength3;
    writeData("test3.txt", &symbols3, &arrayLength3);
    if (findMostFrequent(symbols3, arrayLength3) != 'a')
    {
        return 3;
    }

    // ���� 4: ������������������ �� ������ ������� "a"
    char* symbols4;
    int arrayLength4;
    writeData("test4.txt", &symbols4, &arrayLength4);
    if (findMostFrequent(symbols4, arrayLength4) != 'a')
    {
        return 4;
    }

    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");

    const int errorTest = tests();
    if (!errorTest)
    {
        char* symbols;
        int arrayLength;

        const int errorCode = writeData("File.txt", &symbols, &arrayLength);
        if (!errorCode)
        {
            printf("������� � �����: ");
            for (int i = 0; i < arrayLength; ++i)
            {
                printf("%c", symbols[i]);
            }
            printf("\n");

            const char mostFrequentElement = findMostFrequent(symbols, arrayLength);
            printf("����� ������ ������� � ����� = %c\n", mostFrequentElement);

            free(symbols);
            return 0;
        }
        return errorCode;
    }
    return errorTest;
}