//15. Разработайте программу, реализующую работу с бинарными файлами.
//Необходимо хранить информацию об ассортименте обуви в магазине :
//Артикул(уникальный);
//-наименование;
//-количество;
//-стоимость одной пары.
//Реализовать следующие функции, вызываемые из меню :
//1. Ввод информации об обуви с клавиатуры и сохранение ее в бинарном
//файле с выбранным пользователем названием.
//2. Просмотр содержимого бинарного файла с выбранным пользователем
//названием.
//3. Вывод информации об обуви по введенной пользователем фамилии из
//выбранного пользователем файла.
//4. Вывод информации обо всей обуви с количеством ниже 5.
//5. Удаление информации из выбранного бинарного файла об обуви с
//выбранным артикулом.
//6. Изменение информации о цене для всей обуви из выбранного файла,
//количество которых меньше, чем вводит пользователь.
//7. Вывод наименований с максимальной стоимостью из выбранного
//файла.
//8. Изменение информации наименовании по введенному артикулу.Файл
//вводит пользователь.
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct obuv {
	char surname[10];
	int kol;
	int stoimost;
};

void create(int &size) {
	char name[10];
	cout << "Введите имя файла\n";
	cin >> name;
	
	fstream file(name, ios::binary | ios::app);
	if (file) {
		file.seekp(0, ios::end);
		obuv obuvs[5];
		cout << "Введите размер(до 5)\n"; 
		cin >> size;
		for (int i = 0; i < size; i++) {
			cout << "Наименование " <<i+1<< endl; 
			cin >> obuvs[i].surname;
			cout << "Количество: " <<i+1<< endl;
			cin >> obuvs[i].kol;
			cout << "Стоимость: " <<i+1<< endl;
			cin >> obuvs[i].stoimost;
			file.write(reinterpret_cast<char*>(&obuvs[i]), sizeof(obuvs[i]));
		}
		file.close();
	}
	else {
		file.seekp(0);
		obuv obuvs;
		int size; cout << "Введите размер\n"; cin >> size;
		for (int i = 0; i < size; i++) {
			cout << "Наименование " << i + 1; cin >> obuvs.surname;
			cout << "Количество: " << i + 1; cin >> obuvs.kol;
			cout << "Стоимость: " << i + 1; cin >> obuvs.stoimost;
			file.write(reinterpret_cast<char*>(&obuvs), sizeof(obuvs));
		}
		file.close();
	}
}
void info() {
	obuv s;
	char name[10];
	cout << "Введите название файла\n";
	cin >> name;
	ifstream file(name, ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	if (!file) {
		cout << " no file " << endl;
		return;
	}
	while (!file.eof()) {
		cout << "Наименование: " << s.surname << endl;
		cout << "Количество: " << s.kol << endl;
		cout << "Стоимость: " << s.stoimost << endl;
		file.read(reinterpret_cast<char*>(&s), sizeof(s));
	}

	file.close();
}
//3. Вывод информации об обуви по введенной пользователем Наименования из
//выбранного пользователем файла.
void search() {
	obuv s;
	char name[10];
	cout << "Введите название файла\n";
	cin >> name;
	string g;
	cout << "Введите наименование: ";
	cin >> g;
	ifstream file(name, ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	while (!file.eof()) {
		if (s.surname == g) {
			cout << "Наименование: " << s.surname << endl;
			cout << "Количество: " << s.kol << endl;
			cout << "Стоимость: " << s.stoimost << endl;
		}
		file.read(reinterpret_cast<char*>(&s), sizeof(s));
	}
}
//4. Вывод информации обо всей обуви с количеством ниже 5.
void Kol() {
	obuv s;
	char name[10];
	cout << "Введите название файла\n";
	cin >> name;
	int koli;
	cout << "Введите количество\n";
	cin >> koli;
	ifstream file(name, ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	while (!file.eof()) {
		if (s.kol > koli) {
			cout << "Наименование: " << s.surname << endl;
			cout << "Количество: " << s.kol << endl;
			cout << "Стоимость: " << s.stoimost << endl;
		}
		file.read(reinterpret_cast<char*>(&s), sizeof(s));
	}
}
//5. Удаление информации из выбранного бинарного файла об обуви с
//выбранным артикулом.
void Dell() {
	obuv s;
	char name[10];
	cout << "Введите название файла\n";
	cin >> name;
	string n;
	int c = 0;
	cout << "Введите наименование: ";
	cin >> n;
	ifstream file(name, ios::binary);
	ofstream tmp("tmp.bin", ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	while (!file.eof()) {
		if (s.surname != n) {
			tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
		}
		file.read(reinterpret_cast<char*>(&s), sizeof(s));
		c++;
	}
	file.close();
	tmp.close();
	remove(name);
	rename("tmp.bin", name);
}
//6. Изменение информации о цене для всей обуви из выбранного файла,
//количество которых меньше, чем вводит пользователь.
void Change() {
	obuv s;
	char name[10];
	cout << "Введите название файла\n";
	cin >> name;
	int n, mark1, c = 0;
	int koli4;
	cout << "Введите количество: ";
	cin >> koli4;
	cout << "Введите новую стоимость: ";
	cin >> mark1;
	ifstream file(name, ios::binary);
	ofstream tmp("tmp.bin", ios::binary);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	while (!file.eof()) {
		if (s.kol<koli4) {
			s.stoimost = mark1;
		}
		tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
		file.read(reinterpret_cast<char*>(&s), sizeof(s));
		c++;
	}
	file.close();
	tmp.close();
	remove(name);
	rename("tmp.bin", name);
}
//7. Вывод наименований с максимальной стоимостью из выбранного
//файла.
void Max(int size) {
	obuv s;
	char name[10];
	int max;
	cout << "Введите название файла\n";
	cin >> name;
	ifstream file(name, ios::binary);
	ofstream tmp("tmp.bin", ios::binary);
	file.seekg(0);
	tmp.seekp(0);
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	max = s.stoimost;
	while (!file.eof()) {
		if (s.stoimost > max) {
			cout << "Наименование: " << s.surname << endl;
			cout << "Количество: " << s.kol << endl;
			cout << "Стоимость: " << s.stoimost << endl;
		}

		file.read(reinterpret_cast<char*>(&s), sizeof(s));
	}
	file.close();
}
//8. Изменение информации наименовании по введенному артикулу.Файл
//вводит пользователь.
void Change2() {
	obuv s;
	char name[10];

	char newname[10];
	int counter = 0;
	cout << "Введите название файла\n";
	cin >> name;
	string naim;
	cout << "Введите наименование: ";
	cin >> naim;
	ifstream file(name, ios::binary);
	ofstream tmp("tmp.bin", ios::binary);
	
	file.read(reinterpret_cast<char*>(&s), sizeof(s));
	
	if (s.surname == naim) {
		while (!file.eof()) {
			cout << "\nВведите новое наименование: ";
			cin >> s.surname;
			tmp.write(reinterpret_cast<char*>(&s), sizeof(s));
			file.read(reinterpret_cast<char*>(&s), sizeof(s));
		}
	}
	file.close();
	tmp.close();
	remove(name);
	rename("tmp.bin", name);
}
int main() {
	int size;
	setlocale(LC_ALL, "RUS");
	int input = 1;
	while (input) {
		cout << "1. Ввод информации об обуви с клавиатуры и сохранение ее в бинарном файле с выбранным пользователем названием.\n2. Просмотр содержимого бинарного файла с выбранным пользователем названием.\n3. Вывод информации об обуви по введенной пользователем фамилии из выбранного пользователем файла.\n 4. Вывод информации обо всей обуви с количеством ниже\n5. Удаление информации из выбранного бинарного файла об обуви с выбранным артикулом.\n6. Изменение информации о цене для всей обуви из выбранного файла, количество которых меньше, чем вводит пользователь.\n7. Вывод наименований с максимальной стоимостью из выбранного файла.\n8. Изменение информации наименовании по введенному артикулу.Файл вводит пользователь.\n9.Выход\n";
		cin >> input;
		switch (input) {
		case 1:
			create(size);
			break;
		case 2:
			info();
			break;
		case 3:
			search();
			break;
		case 4:
			Kol();
			break;
		case 5:
			Dell();
			break;
		case 6:
			Change();
			break;
		case 7:
			Max(size);
			break;
		case 8:
			Change2();
			break;
		case 9:
		{
			exit(0);
			break;
		}
		default:
			break;
		}
	}
	}
