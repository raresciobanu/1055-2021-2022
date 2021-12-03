#include<iostream>
#include<fstream>


using namespace std;

class Vehicul {
	string culoare;
protected:
	long nrKm;
	int an;
public:
	string marca;
	char* serie;

	Vehicul() {
		this->serie = new char[strlen("HKGYHN6778") + 1];
		strcpy_s(this->serie, strlen("HKGYHN6778") + 1, "HKGYHN6778");
	}

	Vehicul(string culoare, long nrKm) {
		this->culoare = culoare;
		this->nrKm = nrKm;
	}

	Vehicul(string culoare, long nrKm, int an, string marca, const char* serie) {
		this->culoare = culoare;
		this->nrKm = nrKm;
		this->an = an;
		this->marca = marca;

		this->serie = new char[strlen(serie) + 1];
		strcpy_s(this->serie, strlen(serie) + 1, serie);
	}

	Vehicul(const Vehicul& v) {
		this->culoare = v.culoare;
		this->nrKm = v.nrKm;
		this->an = v.an;
		this->marca = v.marca;

		if (v.serie != nullptr) {
			this->serie = new char[strlen(v.serie) + 1];
			strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
		}
		else {
			this->serie = nullptr;//sau initializezi serie cu Anonim
		}
	}

	~Vehicul() {
		if (this->serie != nullptr) {
			delete[] this->serie;
		}
	}

	Vehicul& operator=(const Vehicul& v) {
		if (this != &v) {
			if (this->serie != nullptr) {
				delete[] this->serie;
			}

			this->culoare = v.culoare;
			this->nrKm = v.nrKm;
			this->an = v.an;
			this->marca = v.marca;

			if (v.serie != nullptr) {
				this->serie = new char[strlen(v.serie) + 1];
				strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
			}
			else {
				this->serie = nullptr;//sau initializezi serie cu Anonim
			}
		}

		return *this;
	}

	string getCuloare() {
		return culoare;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v) {
		out << "Vehiculul are culoarea " << v.culoare << " nr km " << v.nrKm <<
			" este fabricat in anul " << v.an << " marca fiind " << v.marca <<
			" seria " << v.serie << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Vehicul& v) {
		cout << "Culoare: "; in >> v.culoare;
		cout << "Nr km: "; in >> v.nrKm;
		cout << "An: "; in >> v.an;
		cout << "Marca: "; in >> v.marca;

		char aux[100];
		cout << "Serie: "; in >> aux;

		if (v.serie != nullptr) {
			delete[] v.serie;
		}

		v.serie = new char[strlen(aux) + 1];
		strcpy_s(v.serie, strlen(aux) + 1, aux);


		return in;
	}

	friend ofstream& operator<<(ofstream& out, const Vehicul& v) {
		out << v.culoare << endl << v.nrKm << endl << v.an << endl << v.marca << endl << v.serie << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Vehicul& v) {
		in >> v.culoare; //cititi despre in.getline (daca citesti mai multe cuvinte deodata) sau in.ignore (daca ti a ramas blocat ceva in buffer)
		in >> v.nrKm;
		in >> v.an;
		in >> v.marca;

		char aux[100];
		in >> aux;

		if (v.serie != nullptr) {
			delete[] v.serie;
		}

		v.serie = new char[strlen(aux) + 1];
		strcpy_s(v.serie, strlen(aux) + 1, aux);


		return in;
	}

	//cum ar arata in fisier binar un Vehicul:
		/*5
		rosu
		1000
		2020
		5
		Audi
		10
		JK5353JCE     totul in mod binar*/
	void scrieInFisierBinar(ofstream& fisBinarOut) {
		//string
		//pentru a scrie char* si string intr un fisier binar trebuie intai sa scriem ce dimensiune au pentru a sti la citire cand sa ne oprim
		int dim = culoare.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere

		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(this->culoare.c_str(), dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului


		fisBinarOut.write((char*)&this->nrKm, sizeof(this->nrKm));


		fisBinarOut.write((char*)&this->an, sizeof(this->an));

		//string
		dim = marca.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(this->marca.c_str(), dim);//aici nu mai e sizeof, pt ca ai calculat deja dimensiunea string-ului

		//char*
		dim = strlen(serie) + 1; //+1 - pt '\0' de la finalul unui sir de caractere
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(serie, dim);
	}


	void citireDinFisierBinar(ifstream& fisBinarIn) {
		//string
		int dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		char aux[100];
		fisBinarIn.read(aux, dim);
		culoare = aux;


		fisBinarIn.read((char*)&this->nrKm, sizeof(this->nrKm));


		fisBinarIn.read((char*)&this->an, sizeof(this->an));

		//string
		dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		fisBinarIn.read(aux, dim);
		marca = aux;


		//char*
		dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		fisBinarIn.read(aux, dim);
		if (serie != nullptr) {
			delete[] serie;
		}

		this->serie = new char[dim];
		strcpy_s(this->serie, dim, aux);
	}
};

int main() {

	Vehicul v1("rosu", 1000, 2020, "Audi", "JK5353JCE");

	ofstream fisTextOut("vehiculeOut.txt");
	if (fisTextOut.is_open()) {
		fisTextOut << v1; //op << pt scriere in fisier text

		fisTextOut.close();
	}
	else {
		cout << "Fisierul vehiculeOut.txt nu poate fi deschis pentru scriere\n";
	}


	Vehicul v2;
	ifstream fisTextIn("vehiculeOut.txt");
	if (fisTextIn.is_open()) {
		fisTextIn >> v2; //op >> pt citire din fisier text

		cout << "\n\n v2 \n\n" << v2 << endl; //op << pt scriere in consola

		fisTextIn.close();
	}
	else {
		cout << "Fisierul vehiculeOut.txt nu poate fi deschis pentru scriere\n";
	}


	//fisiere
	//flag-uri
	//ios::app - adauga informatii la un fisier existent sau il va crea daca nu exista
	//ios::nocreate - deschide fisierul daca exista deja.
	//ios::in - pt citire dintr-un fisier
	//ios::out - scriere intr-un fisier
	//ios::truc - sterge tot din fisier inainte sa scrii in el 
	//ios::noreplace - doar pt a crea un nou fisier
	//ios::ate - deschide fisierul si merge la sfarsitul lui - fol pt adaugare informatii la final
	//ios::binary - fisierul deschis va contine doar informatii binare

	Vehicul v3("albastru", 2200, 2021, "BMW", "AAAA3JCE");

	ofstream fisBinarOut("wwww.bin", ios::out | ios::binary | ios::app);
	if (fisBinarOut.is_open()) {
		v3.scrieInFisierBinar(fisBinarOut);

		fisBinarOut.close();
	}
	else {
		cout << "Fisierul wwww.dat nu poate fi deschis pentru scriere.\n";
	}

	Vehicul v4;
	ifstream fisBinarIn("wwww.bin", ios::in | ios::binary);
	if (fisBinarIn.is_open()) {
		v4.citireDinFisierBinar(fisBinarIn);
		cout << "v4 fisier binar:   " << v4 << " ";
		fisBinarIn.close();
	}
	else {
		cout << "Fisierul wwww.dat nu poate fi deschis pentru citire.\n";
	}


	Vehicul v5;
	cin >> v5;
	cout << v5;
}