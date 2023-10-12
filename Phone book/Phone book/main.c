#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20
#define MAX_CONTACTS 100

typedef struct
{
	char name[MAX_NAME_LENGTH];
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
} PhoneBook;

int loadData(PhoneBook* phoneBook, int* numberOfContacts)
{
	FILE* file;
	fopen_s(&file, "PhoneBookFile.txt", "r");
	if (file == NULL)
	{
		return 1;
	}

	while (!feof(file) && *numberOfContacts < 100)
	{
		char name[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_NUMBER_LENGTH];
		fscanf_s(file, "%[^ ]", name, MAX_NAME_LENGTH);
		fscanf_s(file, "%s\n", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

		strncpy_s(phoneBook[*numberOfContacts].name, MAX_NAME_LENGTH + 1, name, MAX_NAME_LENGTH);
		strncpy_s(phoneBook[*numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH + 1, phoneNumber, MAX_PHONE_NUMBER_LENGTH);
		++*numberOfContacts;
	}

	fclose(file);
	return 0;
}

void addContact(PhoneBook* phoneBook, int* numberOfContacts)
{
	char name[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_NUMBER_LENGTH];
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
		return;
	}
	printf("������ ���������:\n");
	for (int i = 0; i < numberOfContacts; i++) {
		printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
	}
	printf("\n");
}

void findPhoneNumber(PhoneBook* phoneBook, int numberOfContacts)
{
	// ��������� ���������� ������ �� �������
	if (numberOfContacts == 0) {
		printf("���������� ����� �����.\n");
		return;
	}

	// ������ ��� ���������
	char name[MAX_NAME_LENGTH];
	printf("������� ��� ���������: ");
	scanf_s("%s", name, MAX_NAME_LENGTH);

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].name, name) == 0) // ������� �������� �������� � ����� ������
		{
			printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
		}
	}
	printf("\n");
}

void findName(PhoneBook* phoneBook, int numberOfContacts)
{
	// ��������� ���������� ������ �� �������
	if (numberOfContacts == 0) {
		printf("���������� ����� �����.\n");
		return;
	}

	// ������ ����� �������� ���������
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
	printf("������� ����� ��������: ");
	scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].phoneNumber, phoneNumber) == 0) // ������� �������� �������� � ����� �������
		{
			printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
		}
	}
	printf("\n");
}

int saveData(PhoneBook* phoneBook, int numberOfContacts)
{
	FILE* file;
	fopen_s(&file, "PhoneBookFile.txt", "w");
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

int tests()
{

}

int main()
{
	system("chcp 1251 > nul");
	PhoneBook phoneBook[MAX_CONTACTS];
	int numberOfContacts = 0;

	const int errorOpenFile = loadData(&phoneBook, &numberOfContacts);
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
				printf("%d\n", numberOfContacts);
				printContacts(phoneBook, numberOfContacts);
				break;
			case 3:
				findPhoneNumber(phoneBook, numberOfContacts);
				break;
			case 4:
				findName(phoneBook, numberOfContacts);
				break;
			case 5:
				saveData(phoneBook, numberOfContacts);
				printf("������ ������� ���������!\n");
				printf("\n");
				break;
			default:
				printf("������������ ���� ������, ���������� ��� ���");
				break;
			}
		}
		return 0;
	}
	return errorOpenFile;
}