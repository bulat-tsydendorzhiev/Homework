#pragma once

typedef enum
{
    successfullCommand,
    outOfMemoryCommands
} comandError;

// ���������� ���� ��� ������������
comandError commands(void);
