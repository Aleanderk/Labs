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
void average(boost::container::small_vector<int, 10000> iArr)
{
	boost::container::small_vector<int, 10000> arr = iArr;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		boost::this_thread::sleep(boost::posix_time::milliseconds(12));
	}
	arithmeticMean = sum / n;
	cout << "Arithmetic mean: " << arithmeticMean << endl;	
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
	boost::thread Average(average, arr);	
	Min_Max.join();
	Average.join();

	return 0;
}