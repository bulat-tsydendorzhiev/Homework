#pragma once

typedef enum
{
    testsPassed,
    testFailed
} TestErrorCode;

// ����� ��� �������� ����������������� ������
TestErrorCode tests(void);
