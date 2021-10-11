#include<iostream>

using namespace std;

void afisare(int x, int* y)
{
	cout << x << " ";
	if (y == nullptr) {
		cout << "nullptr" << endl;
	}
}

void main() {
	cout << "Sem 2\n";

	const int t = 100;

	int x = 10, y = 20, z = 30;

	//pointer constant la o zona de memorie
	int* const p1 = &x;
	*p1 = 200;
	//p1 = &z; //error

	//pointer la o zona de memorie constanta
	const int* p2 = &x;
	//*p2 = 300;//error
	p2 = &z;

	//pointer constant la o zona de memorie constanta
	const int* const p3 = &x;
	//*p3 = 1000;//error
	//p3 = &z;//error


	int *oo;
	
	int* px = NULL;
	int* py = nullptr;

	afisare(NULL, nullptr);
}