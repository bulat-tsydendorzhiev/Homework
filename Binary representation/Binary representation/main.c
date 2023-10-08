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

    printf("����� %d �������� ���� �������� ��� ���: ", number);
    for (int i = 0; i < 32; ++i)
    {
        printf("%d", binary[i]);
    }
    printf("\n");
}

void convertBinaryToDecimal(int* binary) {
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

    printf("%d\n", decimal);
}

void addBinaryColumn(int* binary1, int* binary2)
{
    int carry = 0; // �������
    int result[32]; // ���������

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

    // ������� ��������� � �������� � ���������� �����
    printf("��������� �������� � �������� ����: ");
    for (int i = 0; i < 32; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    printf("��������� �������� � ���������� ����: ");
    convertBinaryToDecimal(result);
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int number1, number2;

    const int errorWirteData = writeData(&number1, &number2);
    if (!errorWirteData) // ������ �� ������
    {
        int binary1[32], binary2[32];
        convertDecimalToBinary(number1, binary1);
        convertDecimalToBinary(number2, binary2);

        addBinaryColumn(binary1, binary2);
        return 0;
    }
    return errorWirteData;
}