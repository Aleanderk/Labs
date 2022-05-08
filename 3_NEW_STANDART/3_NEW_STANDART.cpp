#include <iostream>
#include <Windows.h> 
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using std::endl;
using std::cin;
using std::cout;
bool* checkArr;
int* arr;
int n;
int markerCount;
std::mutex signal;
std::condition_variable con;
int number = -1;

void marker(int num)
{
	
}
int main() {	
	cin >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	cin >> markerCount;
	std::vector<std::thread> hThreads;
	checkArr = new bool[markerCount];
	for (int i = 0; i < markerCount; i++) {
		hThreads.emplace_back(&marker, i);
		checkArr[i] = true;
	}
	for (int i = 0; i < markerCount; i++) {
		hThreads[i].detach();
	}
	return 0;
}