#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <process.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
struct employee
{
	int num; // идентификационный номер сотрудника
	char name[10]; // имя сотрудника
	double hours; // количество отработанных часов
};
using namespace std;
int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	string fileName;
	cout << "Name of the file:" << endl;
	cin >> fileName;
	cout << "Num of notices:" << endl;
	int n;
	cin >> n;
	string fileName1 = fileName + " " + to_string(n);
	string sCreator = "Creator.exe";
	sCreator = sCreator + " " + fileName1;
	const char* Creator = sCreator.c_str();
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, Creator, -1, wString, 4096);
	CreateProcess(NULL, wString, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	ifstream in;
	in.open(fileName, fstream::binary);
	employee* arr = new employee[n];
	for (int i = 0; i < n; i++) {
		in.read((char*)&arr[i], sizeof(employee));
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i].num << " " << arr[i].name << " " << arr[i].hours << endl;
	}
	return 0;
}