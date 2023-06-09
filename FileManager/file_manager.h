#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
class file_manager
{
private:
	long long sizeDIR;
	long long sizeFILE;
public:
	file_manager();
	void print_disk(string);
	void create_file();
	void create_dir();
	void rename_file();
	void rename_dir();
	void Del_file();
	void Del_dir(string);
	void Copy_dir(const char*, const char*);
	void Copy_file(string, string);
	void Move_file(string, string);
	void Move_dir(const char*, const char*);
	long long GetDIRSize(string);
	long long GetFILESize(string);
	void search(string, string);
	~file_manager();
};