#include "file_manager.h"

//Первое задание
// 
//Реализовать простейший файловый менеджер с использованием ООП(классы,
//наследование и так далее).
//Файловый менеджер должен иметь такие возможности :
// 
//■ показывать содержимое дисков;
// 
//■ создавать папки / файлы;
// 
//■ удалять папки / файлы;
// 
//■ переименовывать папки / файлы;
// 
//■ копировать / переносить папки / файлы;
// 
//■ вычислять размер папки / файла;
// 
//■ производить поиск по маске(с поиском по подпапкам) и так далее.

//Асташкин Денис Алексеевич

class Menu_file : public file_manager
{
public:
	Menu_file() : file_manager::file_manager()
	{

	}

	void menu()
	{
		int choose;
		while (true)
		{
			cout << "0.Выход\n1.Показать содержимое диска или папки\n2.Создать папку\n3.Создать файл\n4.Удалить папку\n5.Удалить файл\n6.Переименовать файл\n7.Переименовать папку\n8.Копировать папку\n9.Копировать файл\n10.Переместить папку\n11.Переместить файл\n12.Вычислить размер папки\n13.Вычислить размер файла\n14.Поиск файла по маске\n";
			cin >> choose;
			cin.ignore();
			switch (choose)
			{
			case 0:
				return;
			case 1:
			{
				string path;
				cout << "\nВведите путь и имя папки(E:\\tmp\\*) или букву диска(G:\\*): "; getline(cin, path);
				this->print_disk(path);
				system("pause");
				system("cls");
			}
			break;
			case 2:
				this->create_dir();
				system("pause");
				system("cls");
				break;
			case 3:
				this->create_file();
				system("pause");
				system("cls");
				break;
			case 4:
			{
				string path;
				cout << "\nВведите путь и имя папки, которую хотите удалить(E:\\tmp\\*): "; getline(cin, path);
				this->Del_dir(path);
				system("pause");
				system("cls");
			}
			break;
			case 5:
				this->Del_file();
				system("pause");
				system("cls");
				break;
			case 6:
				this->rename_file();
				system("pause");
				system("cls");
				break;
			case 7:
				this->rename_dir();
				system("pause");
				system("cls");
				break;
			case 8:
			{
				string old_path, new_path;
				cout << "\nВведите путь и имя папки, которую хотите копировать: "; getline(cin, old_path);
				cout << "Введите путь и имя(имя не обязательно должно существовать) папки куда хотите копировать: "; getline(cin, new_path);
				this->Copy_dir(old_path.c_str(), new_path.c_str());
				cout << "\nСодержимое папки скопировано\n";
				system("pause");
				system("cls");
			}
			break;
			case 9:
			{
				string old_path, new_path;
				cout << "\nВведите путь, имя и тип файла, который хотите копировать: "; getline(cin, old_path);
				cout << "Введите путь, имя и тип файла, куда хотите копировать: "; getline(cin, new_path);
				this->Copy_file(old_path, new_path);
				system("pause");
				system("cls");
			}
			break;
			case 10:
			{
				string old_path, new_path;
				cout << "\nВведите путь и имя папки, которую хотите переместить: "; getline(cin, old_path);
				cout << "Введите путь и имя(имя не обязательно должно существовать) папки куда хотите переместить: "; getline(cin, new_path);
				this->Move_dir_m(old_path.c_str(), new_path.c_str());
				system("pause");
				system("cls");
			}
			break;
			case 11:
			{
				string old_path, new_path;
				cout << "\nВведите путь, имя и тип файла, который хотите переместить: "; getline(cin, old_path);
				cout << "Введите путь куда хотите переместить: "; getline(cin, new_path);
				this->Move_file(old_path.c_str(), new_path.c_str());
				system("pause");
				system("cls");
			}
			break;
			case 12:
			{
				string path;
				cout << "\nВведите путь и имя папки размер, которой хотите узнать: "; getline(cin, path);
				long double res = (long double)this->GetDIRSize(path);
				cout << res << " Байт\n";
				cout << res / 1024 << " Кбайт\n";
				cout << res / 1048576 << " Мбайт\n";
				system("pause");
				system("cls");
			}
			break;
			case 13:
			{
				string path;
				cout << "\nВведите путь, имя и тип файла размер, которого хотите узнать: "; getline(cin, path);
				long double res = (long double)this->GetFILESize(path);
				cout << res << " Байт\n";
				cout << res / 1024 << " Кбайт\n";
				cout << res / 1048576 << " Мбайт\n";
				system("pause");
				system("cls");
			}
			break;
			case 14:
			{
				string path, mask;
				cout << "\nВведите путь бласти, в которой будет искаться информация(G:\\Temp\\*): "; getline(cin, path);
				cout << "Введите маску по которой будет искаться информация(.* .txt .png): "; getline(cin, mask);
				this->search(path, mask);
				system("pause");
				system("cls");
			}
			break;
			default:
				continue;
			}
		}
	}

	void Move_dir_m(string old_path, string new_path)
	{
		this->Move_dir(old_path.c_str(), new_path.c_str());
		this->Del_dir(old_path + "\\*");
	}

	~Menu_file()
	{
		file_manager::~file_manager();
	}
};