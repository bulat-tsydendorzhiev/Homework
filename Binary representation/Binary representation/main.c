#include <stdio.h>
#include <locale.h>

int writeData(int* number1, int* number2)
{
    int amountOfValues;
    char check;

    printf("������� ������ ���������� �����: ");
    amountOfValues = scanf_s("%d%c", number1, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("������������ ���� ������\n");
        return 1;
    }

    printf("������� ������ ���������� �����: ");
    amountOfValues = scanf_s("%d%c", number2, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("������������ ���� ������\n");
        return 2;
    }
    printf("\n");
    return 0;
}

void convertDecimalToBinary(int number, int* binary)
{
    int i = 0;
    while (i < 32)
    {
        binary[31 - i] = (number >> i) & 1; // ��������� i-�� ���� �����
        i++;
    }
}

int convertBinaryToDecimal(int* binary) {
    int decimal = 0; // ������� �����
    int i = 32;
    int power = 1; // ������� ������

    // ���� ����� �������������, ������������� ������� ��� � 1
    if (binary[i] == 1) {
        decimal = -power;
    }

    i--;

    while (i >= 0) {
        decimal += binary[i] * power;
        power *= 2;
        i--;
    }

    return decimal;
}

void addBinaryColumn(int* binary1, int* binary2, int* result)
{
    int carry = 0; // �������

    // ���������� ����� �� ��������
    for (int i = 31; i >= 0; i--) {
        int bit1 = binary1[i]; // �������� ������� ��� ������� �����
        int bit2 = binary2[i]; // �������� ������� ��� ������� �����

        // ���������� ���� � ������ ��������
        int sum = bit1 ^ bit2 ^ carry;

        // ��������� �������
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);

        // ��������� ��������� � �������� �������
        result[i] = sum;
    }
}

void printBinary(int* binary)
{
    // ������� �������� ������
    for (int i = 0; i < 32; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

void printAnswer(int number1, int number2)
{
    // ������� 2 ������� ��� �������� �������� ������ � ���� ��� �������� ���������� �������� � �������
    int binary1[32], binary2[32], resultOfSumm[32];

    // ��������� ����� � �� �������� ������ ������� �� � �������
    printf("����� %d �������� ���� �������� ��� ���: ", number1);
    convertDecimalToBinary(number1, binary1);
    printBinary(binary1);

    printf("����� %d �������� ���� �������� ��� ���: ", number2);
    convertDecimalToBinary(number2, binary2);
    printBinary(binary2);

    // ��������� �������� � ������� � ������� �� ����� ��������� � �������� � ���������� �����
    addBinaryColumn(binary1, binary2, resultOfSumm);
    printf("��������� �������� � �������� ����: ");
    printBinary(resultOfSumm);

    const int decimalNotation = convertBinaryToDecimal(resultOfSumm);
    printf("��������� �������� � ���������� ������: %d\n", decimalNotation);
}

int tests(void)
{
    // ���� 1: ����� ������������� �����
    int number11 = 5, number12 = 7, binary11[32], binary12[32], resultOfSumm1[32];

    convertDecimalToBinary(number11, binary11);
    convertDecimalToBinary(number12, binary12);
    addBinaryColumn(binary11, binary12, resultOfSumm1);
    const int decimalNotation1 = convertBinaryToDecimal(resultOfSumm1);

    if (decimalNotation1 != 12)
    {
        return 21;
    }

    // ���� 2: ����� ������������� �����
    int number21 = -5, number22 = -7, binary21[32], binary22[32], resultOfSumm2[32];

    convertDecimalToBinary(number21, binary21);
    convertDecimalToBinary(number22, binary22);
    addBinaryColumn(binary21, binary22, resultOfSumm2);
    const int decimalNotation2 = convertBinaryToDecimal(resultOfSumm2);

    if (decimalNotation2 != -12)
    {
        return 22;
    }

    // ���� 3: ����� �������������� � �������������� �����
    int number31 = -5, number32 = 7, binary31[32], binary32[32], resultOfSumm3[32];

    convertDecimalToBinary(number31, binary31);
    convertDecimalToBinary(number32, binary32);
    addBinaryColumn(binary31, binary32, resultOfSumm3);
    const int decimalNotation3 = convertBinaryToDecimal(resultOfSumm3);

    if (decimalNotation3 != 2)
    {
        return 23;
    }

    // ���� 4: ����� c ������, ���������� �����
    int number41 = 0, number42 = 7, binary41[32], binary42[32], resultOfSumm4[32];

    convertDecimalToBinary(number41, binary41);
    convertDecimalToBinary(number42, binary42);
    addBinaryColumn(binary41, binary42, resultOfSumm4);
    const int decimalNotation4 = convertBinaryToDecimal(resultOfSumm4);

    if (decimalNotation4 != 7)
    {
        return 24;
    }
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int number1, number2;
    const int errorTest = tests();
    if (!errorTest)
    {
        const int errorWirteData = writeData(&number1, &number2);
        if (!errorWirteData) // ������ �� ������
        {
            printAnswer(number1, number2);
            return 0;
        }
        return errorWirteData;
    }
    return errorTest;
}