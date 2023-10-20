#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20
#define MAX_CONTACTS 100

typedef struct
{
	char name[MAX_NAME_LENGTH];
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
} PhoneBook;

int loadData(PhoneBook* phoneBook, int* numberOfContacts, const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "r");
	if (file == NULL)
	{
		return 404;
	}
	
	// ���������� ������ � ��������� phoneBook
	while (!feof(file) && *numberOfContacts < 100)
	{
		fscanf_s(file, "%[^ ]", phoneBook[*numberOfContacts].name, MAX_NAME_LENGTH);
		fscanf_s(file, "%s\n", phoneBook[*numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH);
		++*numberOfContacts;
	}

	// �������� ����� �� �������( �� ���������, ��� ����� ����� ��������� )
	if (strlen(phoneBook[0].name) == 7029 && strlen(phoneBook[0].phoneNumber) == 6979)
	{
		*numberOfContacts = 0;
	}

	fclose(file);
	return 0;
}

void addContact(PhoneBook* phoneBook, int* numberOfContacts)
{
	// ��������� ��� � ����� � ���������� ������
	char name[MAX_NAME_LENGTH + 1], phoneNumber[MAX_PHONE_NUMBER_LENGTH + 1];
	printf("������� ���: ");
	scanf_s("%s", name, MAX_NAME_LENGTH);
	printf("������� �����: ");
	scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

	strcpy_s(phoneBook[*numberOfContacts].name, sizeof(char) * MAX_NAME_LENGTH, name);
	strcpy_s(phoneBook[*numberOfContacts].phoneNumber, sizeof(char) * MAX_PHONE_NUMBER_LENGTH, phoneNumber);

	++*numberOfContacts;
	printf("\n");
}

void printContacts(PhoneBook* phoneBook, int numberOfContacts) {
	if (numberOfContacts == 0) {
		printf("���������� ����� �����.\n");
		printf("\n");
		return;
	}
	printf("������ ���������:\n");
	for (int i = 0; i < numberOfContacts; i++) {
		printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
	}
	printf("\n");
}

int* findPhoneNumber(PhoneBook* phoneBook, int numberOfContacts, const char* name)
{
	int* suitableNumbers = calloc(MAX_CONTACTS + 1, sizeof(int));
	int j = 0;

	if (numberOfContacts == 0)
	{
		return NULL;
	}

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].name, name) == 0) // ������� �������� �������� � ����� ������
		{
			suitableNumbers[j] = i;
			++j;
		}
	}
	suitableNumbers[j] = NULL;
	return suitableNumbers;
}

int* findName(PhoneBook* phoneBook, int numberOfContacts, const char* phoneNumber)
{
	int* suitableNumbers = calloc(MAX_CONTACTS + 1, sizeof(int));
	int j = 0;

	if (numberOfContacts == 0)
	{
		return NULL;
	}

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].phoneNumber, phoneNumber) == 0) // ������� �������� �������� � ����� �������
		{
			suitableNumbers[j] = i;
			++j;
		}
	}
	suitableNumbers[j] = NULL;
	return suitableNumbers;
}

void printSuitableNumbers(PhoneBook* phoneBook, int* suitableNumbers, const char* partOfContact)
{
	if (suitableNumbers[0] == 0)
	{
		printf("����� � ������ ������� � ���������� ������ ���\n");
		printf("\n");
	}
	else
	{
		printf(strcmp("name", partOfContact) ? "\n��������� � ����� ������� ��������:\n" : "\n��������� ������� ��������� � ����� ������:\n");
		for (int i = 0; suitableNumbers[i] != 0; ++i)
		{
			printf("%s: %s\n", phoneBook[suitableNumbers[i]].name, phoneBook[suitableNumbers[i]].phoneNumber);
		}
		printf("\n");
	}
}

int saveData(PhoneBook* phoneBook, int numberOfContacts, const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "w");
	if (file == NULL)
	{
		return 1;
	}

	for (int i = 0; i < numberOfContacts; ++i)
	{
		fprintf_s(file, "%s %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
	}

	fclose(file);
	return 0;
}

void printCommands(void)
{
	printf("���������� ����������\n");
	printf("�������� ���� �� ������:\n");
	printf("0 - �����\n");
	printf("1 - �������� ������ (��� � �������)\n");
	printf("2 - ����������� ��� ��������� ������\n");
	printf("3 - ����� ������� �� �����\n");
	printf("4 - ����� ��� �� ��������\n");
	printf("5 - ��������� ������� ������ � ����\n");

	printf("���� �������: ");
}

int testLoadFile(void)
{
	// ���� 1: �������� �� ������ �����
	PhoneBook testPhoneBook1[MAX_CONTACTS];
	int numberOfContacts1 = 0;
	loadData(testPhoneBook1, &numberOfContacts1, "EmptyTestFile.txt");

	if (numberOfContacts1 != 0 || strlen(testPhoneBook1[0].name) != 7028 || strlen(testPhoneBook1[0].phoneNumber) != 6978)
	{
		return 1;
	}

	// ���� 2: �������� �� �������� �����
	PhoneBook testPhoneBook2[MAX_CONTACTS];
	int numberOfContacts2 = 0;
	loadData(testPhoneBook2, &numberOfContacts2, "testFile.txt");
	PhoneBook expected[5] = { {"����", "8-800-555-35-35"},
							{"����", "8-888-888-88-88"},
							{"����", "8-902-136-12-65"},
							{"����", "8-903-157-36-74"},
							{"����", "8-911-157-36-74"} };

	for (int i = 0; i < 5; ++i)
	{
		if (strcmp(testPhoneBook2[i].name, expected[i].name) || strcmp(testPhoneBook2[i].phoneNumber, expected[i].phoneNumber))
		{
			return 2;
		}
	}

	return 0;
}

int testFindPhoneNumber(void)
{
	PhoneBook testPhoneBook[MAX_CONTACTS];
	int numberOfContacts = 0;
	loadData(testPhoneBook, &numberOfContacts, "testFile.txt");

	// ���� 1: �������� �� ������� ������������� ������ � �����
	char testName1[] = "����";
	int* suitableNumbers1 = findPhoneNumber(testPhoneBook, numberOfContacts, testName1);

	if (suitableNumbers1[0] == suitableNumbers1[1])
	{
		return 11;
	}

	// ���� 2: �������� �� ������� ��������������� ����� � �����
	char testName2[] = "����";
	int* suitableNumbers2 = findPhoneNumber(testPhoneBook, numberOfContacts, testName2);

	if (suitableNumbers2[0] != suitableNumbers2[1])
	{
		return 12;
	}

	free(suitableNumbers1);
	free(suitableNumbers2);
	return 0;
}

int testFindName(void)
{
	PhoneBook testPhoneBook[MAX_CONTACTS];
	int numberOfContacts = 0;
	loadData(testPhoneBook, &numberOfContacts, "testFile.txt");

	// ���� 1: �������� �� ������� ������������� ������ � �����
	char testNumber1[] = "8-888-888-88-88";
	int* suitableNumbers1 = findName(testPhoneBook, numberOfContacts, testNumber1);

	if (suitableNumbers1[0] == suitableNumbers1[1])
	{
		return 21;
	}

	// ���� 2: �������� �� ������� ��������������� ����� � �����
	char testNumber2[] = "8-123-456-78-90";
	int* suitableNumbers2 = findName(testPhoneBook, numberOfContacts, testNumber2);

	if (suitableNumbers2[0] != suitableNumbers2[1])
	{
		return 22;
	}

	free(suitableNumbers1);
	free(suitableNumbers2);
	return 0;
}

int testSaveData(void)
{
	// ����: �������� �� ���������� ������
	PhoneBook testPhoneBook1[6];
	int numberOfContacts1 = 0;
	loadData(testPhoneBook1, &numberOfContacts1, "testSaveDataFile1.txt");

	// ���������� �������������� ������� � ���� ��� ���������
	strcpy_s(testPhoneBook1[numberOfContacts1].name, sizeof(char) * MAX_NAME_LENGTH, "����");
	strcpy_s(testPhoneBook1[numberOfContacts1].phoneNumber, sizeof(char) * MAX_PHONE_NUMBER_LENGTH, "8-924-333-32-55");
	saveData(testPhoneBook1, numberOfContacts1 + 1, "testSaveDataFile2.txt");

	// ��������� ���� ��� ���������
	PhoneBook testPhoneBook2[6];
	int numberOfContacts2 = 0;
	loadData(testPhoneBook2, &numberOfContacts2, "testSaveDataFile2.txt");

	for (int i = 0; i < 5; ++i)
	{
		if (strcmp(testPhoneBook2[i].name, testPhoneBook2[i].name) || strcmp(testPhoneBook2[i].phoneNumber, testPhoneBook2[i].phoneNumber))
		{
			return 2;
		}
	}

	return 0;
}

int findErrorCode(int* errorCodes)
{
	for (int i = 0; i < 4; ++i)
	{
		if (errorCodes[i] > 0)
		{
			return errorCodes[i];
		}
	}
	return 0;
}

const int tests(void)
{
	const int errorCodes[] = { testLoadFile(), testFindPhoneNumber(), testFindName(), testSaveData(), testSaveData() };
	return findErrorCode(errorCodes);
}

int main()
{
	system("chcp 1251 > nul");
	
	// ��������� �����
	const int errorCode = tests();
	if (!errorCode)
	{
		// ������� ���������� ������, ���������� ���������� ���������, suitableNumbers, name � phoneNumber ����� ��� ��������� ���������� ��� ������� 3 � 4
		PhoneBook phoneBook[MAX_CONTACTS];
		int numberOfContacts = 0;
		char name[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_NUMBER_LENGTH];
		int* suitableNumbers = NULL;

		// ��������� ����������� ������
		const int errorOpenFile = loadData(phoneBook, &numberOfContacts, "PhoneBookFile.txt");
		if (!errorOpenFile)
		{
			while (1)
			{
				// ������� ������������ ������� � ���� �����
				printCommands();
				int choice;
				scanf_s("%d", &choice);
				printf("\n");

				switch (choice)
				{
					case 0:
						return 0;
					case 1:
						addContact(phoneBook, &numberOfContacts);
						break;
					case 2:
						printContacts(phoneBook, numberOfContacts);
						break;
					case 3:
						printf("������� ��� ���������: ");
						scanf_s("%s", name, MAX_NAME_LENGTH);
						suitableNumbers = findPhoneNumber(phoneBook, numberOfContacts, name);
						printSuitableNumbers(phoneBook, suitableNumbers, "name");
						free(suitableNumbers);
						break;
					case 4:
						printf("������� ����� ��������: ");
						scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH);
						suitableNumbers = findName(phoneBook, numberOfContacts, phoneNumber);
						printSuitableNumbers(phoneBook, suitableNumbers, "phoneNumber");
						free(suitableNumbers);
						break;
					case 5:
						saveData(phoneBook, numberOfContacts, "PhoneBookFile.txt");
						printf("������ ������� ���������!\n");
						printf("\n");
						break;
					default:
						printf("������������ ���� ������, ���������� ��� ���\n");
						printf("\n");
						break;
				}
			}
			return 0;
		}
		return errorOpenFile;
	}
	return errorCode;
}