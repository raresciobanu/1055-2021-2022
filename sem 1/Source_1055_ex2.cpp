#include<iostream>
#include<conio.h>

using namespace std;


void sss(int N, int *pz) {

	int elementNou;
	cout << "Element nou = "; cin >> elementNou;


	int *aux = new int[N + 1];
	for (int i = 0; i < N; i++) {
		aux[i] = pz[i];
	}
	aux[N++] = elementNou;

	delete pz;
	pz = aux;
}
void main() {
	int x = 10;

	cout << "Adresa lui X este: " << &x << endl;
	int *px = &x;
	cout << "Adresa lui PX este: " << &px << endl;
	cout << "Valoarea lui PX este: " << px << endl;
	cout << "Ce se afla la adresa valorii lui PX este: " << *px << endl;

	//delete px; -> eroare fatala...incerci sa stergi ceva de pe stack

	int *py = new int(20);
	cout << "py = " << *py << endl;
	delete py;

	int N = 5;
	int *pz = new int[N];

	for (int i = 0; i < N; i++) {
		pz[i] = (i + 1) * 2;
	}


	for (int i = 0; i < N; i++) {
		cout << pz[i] << " ";
	}

	cout << endl;


	int elementNou;
	cout << "Element nou = "; cin >> elementNou;

	int *aux = new int[N + 1];
	for (int i = 0; i < N; i++) {
		aux[i] = pz[i];
	}
	aux[N++] = elementNou;

	delete pz;
	pz = aux;
	for (int i = 0; i < N; i++) {
		cout << pz[i] << " ";
	}

	delete pz;
	_getch();
}