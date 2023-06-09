#include "file_manager.h"

file_manager::file_manager()
{
	sizeDIR = 0ll;
	sizeFILE = 0ll;
}

void file_manager::print_disk(string path)
{
	__finddata64_t* Info_dir = new __finddata64_t;
	_int64 done = _findfirst64(path.c_str(), Info_dir);
	int can = done;
	string tmp = path;
	while (can != -1)
	{
		if (strcmp(Info_dir->name, ".") != 0 || strcmp(Info_dir->name, "..") != 0)
		{			
			if (Info_dir->attrib == 16 || Info_dir->attrib == 18)
			{
				cout << Info_dir->name << endl;
				tmp.pop_back();
				for (int i = 0; i < strlen(Info_dir->name); i++)
				{
					tmp.push_back(Info_dir->name[i]);
				}
				tmp += "\\*";
				print_disk(tmp.c_str());
			}
			else
			{
				cout << "\t" << Info_dir->name << endl;
			}
			tmp.clear();
			tmp = path;
		}
		can = _findnext64(done, Info_dir);
	}
	_findclose(done);
	cout << endl;
}

void file_manager::create_file()
{
	char path[MAX_PATH];
	cout << "\nВведите путь, имя и тип файла: ";
	cin.getline(path, MAX_PATH);
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
		cout << "\nОшибка создание файла!\n";
	else
		cout << "\nФайл успешно создан!\n";
	fout.close();
}

void file_manager::create_dir()
{
	char path[MAX_PATH];
	cout << "\nВведите путь и имя директории: "; cin.getline(path, MAX_PATH);
	if (_mkdir(path) == -1)
		cout << "\nОшибка создание директории!\n";
	else
		cout << "\nДиректория успешно создана!\n";
}

void file_manager::rename_file()
{
	char old_name[MAX_PATH];
	char new_name[MAX_PATH];
	char tmp[MAX_PATH];
	int pos = -1;
	cout << "\nВведите старый путь и имя файла: "; cin.getline(old_name, MAX_PATH);
	cout << "\nВведите новое имя и тип файла: "; cin.getline(tmp, MAX_PATH);
	for (int i = strlen(old_name); i > 0; i--)
	{
		if (old_name[i] == '\\')
		{
			pos = i;
			break;
		}
	}
	for (int i = 0; i <= pos; i++)
	{
		new_name[i] = old_name[i];
	}
	new_name[pos + 1] = '\0';
	strcat_s(new_name, tmp);
	if (rename(old_name, new_name) == 0)
		cout << "\nФайл успешно переименнован!\n";
	else
		cout << "\nОшибка переименнования файла!\n";
}

void file_manager::rename_dir()
{
	char old_name[MAX_PATH];
	char new_name[MAX_PATH];
	char tmp[MAX_PATH];
	int pos = -1;
	cout << "\nВведите старый путь и имя директории: "; cin.getline(old_name, MAX_PATH);
	cout << "\nВведите новое имя директории: "; cin.getline(tmp, MAX_PATH);
	for (int i = strlen(old_name); i > 0; i--)
	{
		if (old_name[i] == '\\')
		{
			pos = i;
			break;
		}
	}
	for (int i = 0; i <= pos; i++)
	{
		new_name[i] = old_name[i];
	}
	new_name[pos + 1] = '\0';
	strcat_s(new_name, tmp);
	if (rename(old_name, new_name) == 0)
		cout << "\nДиректория успешно переименнован!\n";
	else
		cout << "\nОшибка переименнования директории!\n";
}

void file_manager::Del_file()
{
	char path[MAX_PATH];
	cout << "\nВведите путь, имя и тип файла, который хотите удалить: "; cin.getline(path, MAX_PATH);
	if (remove(path) == 0)
		cout << "\nФайл удалён!\n";
	else
		cout << "\nОшибка удаления файла!\n";
}

void file_manager::Del_dir(string path)
{
	__finddata64_t* Info_dir = new __finddata64_t;
	_int64 done = _findfirst64(path.c_str(), Info_dir);
	int can = done;
	string tmp = path;
	while (can != -1)
	{
		if (strcmp(Info_dir->name, ".") != 0 || strcmp(Info_dir->name, "..") != 0)
		{
			if (Info_dir->attrib == 16 || Info_dir->attrib == 18)
			{
				tmp.pop_back();
				for (int i = 0; i < strlen(Info_dir->name); i++)
				{
					tmp.push_back(Info_dir->name[i]);
				}
				tmp += "\\*";
				Del_dir(tmp.c_str());
			}
			else
			{
				string del(path);
				del.pop_back();
				for (int i = 0; i < strlen(Info_dir->name); i++)
				{
					del += Info_dir->name[i];
				}
				remove(del.c_str());
				del.clear();
			}
			tmp.clear();
			tmp = path;
		}
		can = _findnext64(done, Info_dir);
	}
	_findclose(done);
	string del_all_path(path);
	del_all_path.pop_back();
	if (_rmdir(del_all_path.c_str()))
		cout << "\nДиректория удалена!\n";
}

void file_manager::Move_file(string old_path, string new_path)
{
	string str;
	if (new_path.back() == '\\')
	{
		int pos = 0;
		string name;
		for (int i = strlen(old_path.c_str()) - 1; i > 0; i--)
		{
			if (old_path.at(i) == '\\')
			{
				pos = i;
				break;
			}
		}
		for (int i = pos; i < old_path.size(); i++)
			name.push_back(old_path.at(i));
		
		new_path += name;
	}
	ifstream fin_old_path(old_path);
	ofstream fout_new_path(new_path);
	while (fin_old_path.good())
	{
		getline(fin_old_path, str);
		fout_new_path << str << "\n";
	}
	fin_old_path.close();
	fout_new_path.close();
	remove(old_path.c_str());
}

void file_manager::Move_dir(const char* Source, const char* Destination)
{
	char Path[MAX_PATH];
	strcpy_s(Path, Source);
	strcat_s(Path, "\\*.*");
	__finddata64_t Find;

	_int64 result = _findfirst64(Path, &Find);
	system("cls");
	int flag = result;
	if (flag == -1)
	{
		cout << "Такой директории нет!" << endl;
		return;
	}
	_mkdir(Destination);
	while (flag != -1)
	{
		if (strcmp(Find.name, ".") && strcmp(Find.name, ".."))
		{

			if (Find.attrib & _A_SUBDIR)
			{

				char DirSrc[MAX_PATH];

				strcpy_s(DirSrc, Source);
				strcat_s(DirSrc, "\\");
				strcat_s(DirSrc, Find.name);
				char DirDest[MAX_PATH];
				strcpy_s(DirDest, Destination);
				strcat_s(DirDest, "\\");
				strcat_s(DirDest, Find.name);
				Move_dir(DirSrc, DirDest);
			}
			else
			{
				char FileSrc[MAX_PATH];
				strcpy_s(FileSrc, Source);
				strcat_s(FileSrc, "\\");
				strcat_s(FileSrc, Find.name);
				char FileDest[MAX_PATH];
				strcpy_s(FileDest, Destination);
				strcat_s(FileDest, "\\");
				strcat_s(FileDest, Find.name);
				Move_file(FileSrc, FileDest);
			}
		}
		flag = _findnext64(result, &Find);
	}
	_findclose(result);
}

long long file_manager::GetDIRSize(string path)
{
	__finddata64_t* Info_dir = new __finddata64_t;
	long done = _findfirst64(path.c_str(), Info_dir);
	int can = done;
	string tmp = path;
	while (can != -1)
	{

		if (strcmp(Info_dir->name, ".") != 0 || strcmp(Info_dir->name, "..") != 0)
		{
			if (Info_dir->attrib == 16 || Info_dir->attrib == 18)
			{
				tmp.pop_back();
				for (int i = 0; i < strlen(Info_dir->name); i++)
				{
					tmp.push_back(Info_dir->name[i]);
				}
				tmp += "\\*";
				GetDIRSize(tmp.c_str());
			}
			else
				sizeDIR += Info_dir->size;
			tmp.clear();
			tmp = path;
		}		
		can = _findnext64(done, Info_dir);
	}
	_findclose(done);
	return sizeDIR;
}

long long file_manager::GetFILESize(string path)
{
	__finddata64_t* Info = new __finddata64_t;
	_findfirst64(path.c_str(), Info);
	sizeFILE = Info->size;
	_findclose(_findfirst64(path.c_str(), Info));
	return sizeFILE;
}

void file_manager::Copy_file(string old_path, string new_path)
{
	string str;
	if (new_path.back() == '\\')
	{
		int pos = 0;
		string name;
		for (int i = strlen(old_path.c_str()) - 1; i > 0; i--)
		{
			if (old_path.at(i) == '\\')
			{
				pos = i;
				break;
			}
		}
		for (int i = pos; i < old_path.size(); i++)
		{
			name.push_back(old_path.at(i));
		}
		new_path += name;
	}
	ifstream fin_old_path(old_path);
	ofstream fout_new_path(new_path);
	while (fin_old_path.good())
	{
		getline(fin_old_path, str);
		fout_new_path << str << "\n";
	}
	fin_old_path.close();
	fout_new_path.close();
}

void file_manager::Copy_dir(const char* Source, const char* Destination)
{
	char Path[MAX_PATH];
	strcpy_s(Path, Source);
	strcat_s(Path, "\\*.*");
	__finddata64_t Find;

	int result = _findfirst64(Path, &Find);
	system("cls");
	int flag = result;
	if (flag == -1)
	{
		cout << "Такой директории нет!" << endl;
		return;
	}
	_mkdir(Destination);
	while (flag != -1)
	{
		if (strcmp(Find.name, ".") && strcmp(Find.name, ".."))
		{
			if (Find.attrib & _A_SUBDIR)
			{

				char DirSrc[MAX_PATH];

				strcpy_s(DirSrc, Source);
				strcat_s(DirSrc, "\\");
				strcat_s(DirSrc, Find.name);
				char DirDest[MAX_PATH];
				strcpy_s(DirDest, Destination);
				strcat_s(DirDest, "\\");
				strcat_s(DirDest, Find.name);
				Copy_dir(DirSrc, DirDest);
			}
			else
			{

				char FileSrc[MAX_PATH];
				strcpy_s(FileSrc, Source);
				strcat_s(FileSrc, "\\");
				strcat_s(FileSrc, Find.name);
				char FileDest[MAX_PATH];
				strcpy_s(FileDest, Destination);
				strcat_s(FileDest, "\\");
				strcat_s(FileDest, Find.name);
				Copy_file(FileSrc, FileDest);
			}
		}
		flag = _findnext64(result, &Find);
	}
	_findclose(result);
}

void file_manager::search(string path, string mask)
{
	__finddata64_t* Info = new __finddata64_t;
	_int64 done = _findfirst64(path.c_str(), Info);
	int can = done;
	string tmp = path;
	while (can != -1)
	{
		string InfoMask(Info->name);
		if (strcmp(Info->name, ".") != 0 || strcmp(Info->name, "..") != 0)
		{
			if (Info->attrib == 16 || Info->attrib == 18)
			{
				tmp.pop_back();
				for (int i = 0; i < strlen(Info->name); i++)
				{
					tmp.push_back(Info->name[i]);
				}
				tmp += "\\*";
				search(tmp, mask);
			}
			else if (InfoMask.find(mask) != -1)
			{
				int h = path.find(mask);
				cout << Info->name << endl;
			}
			tmp.clear();
			tmp = path;
		}		
		can = _findnext64(done, Info);
	}
	_findclose(done);
}

file_manager::~file_manager()
{

}