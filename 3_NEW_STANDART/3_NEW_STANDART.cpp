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
srand(num);
	int count = 0;
	std::vector<int> mass;
	while (true) {
		std::unique_lock<std::mutex> ul(signal);
		if (number == num) {
			checkArr[num] = false;
			for (int i = 0; i < mass.size(); i++) {
				arr[mass[i]] = 0;
			}
			
			con.notify_all();
			ul.unlock();
			return;
		}
		int temp = rand() % n;
		if (arr[temp] == 0) {
			Sleep(5);
			arr[temp] = num + 1;
			if (!check(mass, temp)) {
				mass.push_back(temp);
			}
			Sleep(5);
		}
		else {
			checkArr[num] = false;
			cout << num << " " << mass.size() << " " << temp << endl;
			con.notify_all();
			con.wait(ul, [=]() {return checkArr[num]; });
		}
		ul.unlock();
	}	
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