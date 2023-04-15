#include "Header.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
// ��������� ������ � ����� x,y
void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // �������� ���������
    structCursorInfo.dwSize = size; // �������� ������
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void BackAqua() {
    SetConsoleTextAttribute(hStdOut, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
}
void White() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void Grey() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
}
void BackBlack() {
    SetConsoleTextAttribute(hStdOut, 0);
}

