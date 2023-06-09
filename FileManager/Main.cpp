#include <iostream>
#include <windows.h>
#include "File_Editor.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    auto FM = new Menu_file();
    FM->menu();
    system("pause");
    return 0;
}