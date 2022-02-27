#include <iostream>
#include <fstream>
using namespace std;
struct employee
{
	int num; // ����������������� ����� ����������
	char name[10]; // ��� ����������
	double hours; // ���������� ������������ �����
};
int main(int argc, char** argv) {
	ofstream out;
	ifstream in;
	in.open(argv[1], fstream::binary);
	out.open(argv[2]);
	int sum = strtol(argv[3], nullptr, 10);	
	out << argv[1] << endl;
	int n = 0;
	while (!in.eof()) {
		employee temp;
		in.read((char*)&temp, sizeof(employee));
		n++;
	}
	n--;
	in.close();
	in.open(argv[1], fstream::binary);
	for (int i = 0; i < n; i++) {
		employee temp;
		in.read((char*)&temp, sizeof(employee));
		out << temp.num << " " << temp.name << " " << temp.hours << " " << sum * temp.hours << endl;
	}	
	return 0;
}