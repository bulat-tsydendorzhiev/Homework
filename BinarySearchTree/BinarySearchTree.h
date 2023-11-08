#pragma once

#include <stdbool.h>

typedef enum
{
	okBST,
	keyNotFoundBST,
	outOfMemoryBST
} BinarySearchTreeErrorCode;

typedef struct BinarySearchTree BinarySearchTree;

// �������� ��������� ������ ������
BinarySearchTree* createTree(void);

// ���������� ����� � �������� � �������� ������ ������
BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value);

// ��������� �������� �� ����� �� ��������� ������ ������
char* getValueByKey(const BinarySearchTree* const tree, const int key);

// ����� ����� � �������� ������ ������
bool findKey(const BinarySearchTree* const tree, const int key);

// �������� ���� �� ��������� ������ ������
BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key);

// ������� ��������� ������ ������
void clearTree(BinarySearchTree** tree);
