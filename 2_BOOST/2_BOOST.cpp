#include <iostream>
#include <boost/container/small_vector.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
using std::cout;
using std::endl;
using std::cin;
static int n;
volatile int min;
volatile int max;
volatile int arithmeticMean;
void min_max(boost::container::small_vector<int, 10000> iArr)
{
	boost::container::small_vector<int, 10000> arr = iArr;
	min = arr[0];
	max = arr[0];
	for (int i = 0; i < n; i++) {
		if (min > arr[i]) {
			min = arr[i];
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(7));
		if (max < arr[i]) {
			max = arr[i];
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(7));
	}
	cout << "Min: " << min << " Max: " << max << endl;
}

int main() {
	cout << "Input size of the array: " << endl;
	cin >> n;
	boost::container::small_vector<int, 10000> arr;
	cout << "Input the elements of the array:" << endl;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		arr.push_back(temp);
	}
	boost::thread Min_Max(min_max, arr);		
	Min_Max.join();

	return 0;
}