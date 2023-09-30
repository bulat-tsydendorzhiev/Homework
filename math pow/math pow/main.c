#include <stdio.h>
#include <locale.h>
#include <time.h>

int writeData(double* number, int* power);
double pow(double number, int power);
double fastPow(double number, int power);
int testPower(void);
int testFastPower(void);
int tests(void);

int main(void)
{
	setlocale(0, "Rus");
	double number; // �����, ���������� � �������
	int power; // ������� �����
	const int errorCode = writeData(&number, &power); // �������� �� ���������� ���� ������

	// �������� �� ������
	if (!errorCode)
	{
		const int errorTest = tests();
		if (errorTest)
		{
			return errorTest;
		}
		const double result = pow(number, power);
		printf("%lf\n", result);
		return 0;
	}
	return errorCode;
}

int writeData(double* number, int* power)
{
	char check; // ���������� ��� �������� �� ���������� ��� ������ 
	printf("������� ����� ������ ����� � ����� �������, � ������� ����� �������� �����: ");
	const int amountOfElements = scanf_s("%lf %d%c", number, power, &check);

	if (amountOfElements != 3 || (*number == 0 && *power < 0) || check != '\n') // ������ �� ������
	{
		if (amountOfElements != 3 || check != '\n')
		{
			printf("������: ������������ ���� ������\n");
			return 1;
		}
		else if (*number == 0 && *power < 0)
		{
			printf("������: ������� ����� �� 0\n");
			return 2;
		}
	}
	return 0;
}

double pow(double number, int power)
{
	// ���������� � ������� �� O(n)
	double result = 1;
	if (power == 0 || number == 1)
	{
		return result;
	}
	else if (number == 0)
	{
		return 0;
	}
	else if (power > 0)
	{
		while (power > 0)
		{
			result *= number;
			power--;
		}
	}
	else
	{
		while (power < 0)
		{
			result /= number;
			power++;
		}
	}
	return result;
}

double fastPow(double number, int power)
{
	// ���������� � ������� �� O(logn)
	double result = 1;
	if (power == 0 || number == 1)
	{
		return result;
	}
	else if (number == 0)
	{
		return 0;
	}
	else if (power > 0)
	{
		while (power > 0)
		{
			if (power % 2 == 0)
			{
				number *= number;
				power /= 2;
			}
			else
			{
				result *= number;
				power--;
			}
		}
		number = result;
	}
	else
	{
		while (power < 0)
		{
			if (power % 2 == 0)
			{
				number *= number;
				power /= 2;
			}
			else
			{
				result /= number;
				power++;
			}
		}
	}
	return result;
}

int testPower(void)
{
	// ���� 1: ���������� � ������� 0
	if ((int)pow(5, 0) != 1)
	{
		return 1;
	}

	// ���� 2: ���������� � ������������� �������
	if ((int)pow(2, 4) != 16)
	{
		return 2;
	}

	// ���� 3: ���������� � ������������� �������
	if (pow(2, -2) != 0.250000)
	{
		return 3;
	}

	// ���� 4: ���������� � ������� 1
	if ((int)pow(7, 1) != 7)
	{
		return 4;
	}

	// ���� 5: ���������� � ������� ������ 1
	if ((int)pow(4, 3) != 64)
	{
		return 5;
	}

	return 0;
}

int testFastPower(void)
{
	// ���� 1: ���������� � ������� 0
	if ((int)fastPow(5, 0) != 1)
	{
		return 1;
	}

	// ���� 2: ���������� � ������������� �������
	if ((int)fastPow(2, 4) != 16)
	{
		return 2;
	}

	// ���� 3: ���������� � ������������� �������
	if (fastPow(2, -2) != 0.250000)
	{
		return 3;
	}

	// ���� 4: ���������� � ������� 1
	if ((int)fastPow(7, 1) != 7)
	{
		return 4;
	}

	// ���� 5: ���������� � ������� ������ 1
	if ((int)fastPow(4, 3) != 64)
	{
		return 5;
	}

	return 0;
}

int tests(void)
{
	const int errorPowTest = testPower();
	if (errorPowTest)
	{
		printf("���� ��� ���������� � ������� �� O(n) �� �������\n");
		return errorPowTest;
	}

	int errorFastPowTest = testFastPower();
	if (errorFastPowTest)
	{
		printf("���� ��� ���������� � ������� �� O(logn) �� �������\n");
		return errorFastPowTest;
	}
}