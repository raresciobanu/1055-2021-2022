#include<iostream>
#include<conio.h>

using namespace std;

typedef struct {
	int varsta;
	bool gen;//true M, else F
	double greutate;
	char nume[100];
}persoana;


void fct1(int a, int b) {

	cout << "a = " << a << " b = " << b << endl;

	a = 200;
	b = 300;
}

void fct2(int &c, int &d) {

	cout << "c = " << c << " d = " << d << endl;

	c = 900;
	d = 1100;
}

void main() {
	cout << "Salut.\n";


	persoana p;
	p.varsta = 20;
	p.gen = false;
	p.greutate = 65.5;
	strcpy_s(p.nume, "Popescu Ioana");

	cout << "Numele persoanei este: " << p.nume << " are varsta de " << p.varsta << " ani, greutatea de "
		<< p.greutate << " kg si este genul " << (p.gen == true ? "masculin" : "feminin") << endl;


	int vector[] = { 2,4,5,6 };
	for (int i = 0; i < 4; i++) {
		cout << "vector[" << i << "]=" << vector[i] << "  ";
	}
	cout << endl;

	int a = 4, b = 9;
	fct1(a, b);
	cout << "a = " << a << " b = " << b << endl;


	int c = 50, d = 60;
	fct2(c, d);
	cout << "c = " << c << " d = " << d << endl;

	cout << "&c = " << &c << " &d = " << &d << endl;

	_getch();
}