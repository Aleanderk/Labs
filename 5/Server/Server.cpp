#pragma warning(disable : 4996)
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
CRITICAL_SECTION cs;
struct employee
{
	int num = -1; // идентификационный номер сотрудника
	char name[10] = ""; // имя сотрудника
	double hours = 0; // количество отработанных часов
};
employee* arr;
bool* mod;
int numOfEntries;

int main() {
	char fileName[66];
	cout << "Input name of the file:" << endl;
	cin >> fileName;
	cout << "Input the number of entries: " << endl;
	cin >> numOfEntries;
	cout << "Input ID, name and number of hours worked:" << endl;
	arr = new employee[numOfEntries];
	for (int i = 0; i < numOfEntries; i++) {		
		cout << "Input the information of " << i + 1 << " worker:" << endl;
		cin >> arr[i].num >> arr[i].name >> arr[i].hours;
	}
	ifstream in;
	ofstream out;
	out.open(fileName, ofstream::binary);
	out.write((const char*)arr, sizeof(employee) * numOfEntries);
	out.close();
	cout << "Initial data:" << endl;
	for (int i = 0; i < numOfEntries; i++) {
		cout << arr[i].num << " " << arr[i].name << " " << arr[i].hours << endl;
	}
	cout << "Input number of processes: " << endl;
	int numOfProcesses;
	cin >> numOfProcesses;
	InitializeCriticalSection(&cs);
	HANDLE hStartALL = CreateEvent(NULL, TRUE, FALSE, "START_ALL");
	mod = new bool[numOfEntries];
	for (int i = 0; i < numOfEntries; i++) {
		mod[i] = false;
	}
	HANDLE* hEvents = new HANDLE[numOfProcesses];
	for (int i = 0; i < numOfProcesses; i++) {
		string processName = "Client.exe";
		string eventName = "EVENT_";
		eventName = eventName + std::to_string(i + 1);
		processName = processName + " " + eventName;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		char* _eventName = new char(eventName.size()+1); 
		_eventName = strcpy(_eventName, eventName.c_str());
		char* _processName = new char(processName.size() + 1);
		_processName = strcpy(_processName, processName.c_str());
		hEvents[i] = CreateEvent(NULL, TRUE, FALSE, _eventName);
		if (!CreateProcess(NULL, _processName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			GetLastError();
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}
	WaitForMultipleObjects(numOfProcesses, hEvents, TRUE, INFINITE);	
	SetEvent(hStartALL);
	HANDLE hPipe;
	HANDLE* hThreads = new HANDLE[numOfProcesses];
	
	return 0;
}