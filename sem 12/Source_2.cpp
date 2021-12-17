#include<iostream>
#include<list>
#include<fstream>

using namespace std;

class ISuma {
public:
	virtual double suma() = 0;
};

class Glovo : public ISuma {
private:
	int nrComenzi;
	double* valoriComenzi;
	string adresa;
	string telefon;
public:
	Glovo() {

	}

	Glovo(double* valoriComenzi, int nrComenzi) {
		this->nrComenzi = nrComenzi;
		this->valoriComenzi = new double[nrComenzi];
		for (int i = 0; i < nrComenzi; i++) {
			this->valoriComenzi[i] = valoriComenzi[i];
		}
	}

	Glovo(double* valoriComenzi, int nrComenzi, string telefon, string adresa) {
		this->telefon = telefon;
		this->adresa = adresa;

		this->nrComenzi = nrComenzi;
		this->valoriComenzi = new double[nrComenzi];
		for (int i = 0; i < nrComenzi; i++) {
			this->valoriComenzi[i] = valoriComenzi[i];
		}
	}

	Glovo(const Glovo& g) {
		this->adresa = g.adresa;
		this->telefon = g.telefon;
		this->nrComenzi = g.nrComenzi;
		this->valoriComenzi = new double[g.nrComenzi];
		for (int i = 0; i < g.nrComenzi; i++) {
			this->valoriComenzi[i] = g.valoriComenzi[i];
		}
	}

	Glovo& operator=(const Glovo& g) {
		if (this != &g) {
			if (this->valoriComenzi != nullptr) {
				delete[] this->valoriComenzi;
			}

			this->adresa = g.adresa;
			this->telefon = g.telefon;
			this->nrComenzi = g.nrComenzi;
			this->valoriComenzi = new double[g.nrComenzi];
			for (int i = 0; i < g.nrComenzi; i++) {
				this->valoriComenzi[i] = g.valoriComenzi[i];
			}
		}
		return *this;
	}


	~Glovo() {
		if (this->valoriComenzi != nullptr) {
			delete[] this->valoriComenzi;
		}
	}

	string getTelefon() {
		return telefon;
	}

	string getAdresa() {
		return adresa;
	}

	int getNrComenzi() {
		return nrComenzi;
	}

	double* getValoriComenzi() {
		return valoriComenzi;
	}

	//supraincarcare
	int getNrComenzi(int x) {
		return nrComenzi + x;
	}

	bool operator<(Glovo g) {
		return this->nrComenzi < g.nrComenzi;
	}

	void scrieGlovoInFisierBinar(ofstream& fisBinarOut, Glovo& g) {
		int dim = g.adresa.size() + 1;
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(g.adresa.c_str(), dim);

		dim = g.telefon.size() + 1;
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(g.telefon.c_str(), dim);

		fisBinarOut.write((char*)&g.nrComenzi, sizeof(int));

		for (int i = 0; i < g.nrComenzi; i++) {
			fisBinarOut.write((char*)&g.valoriComenzi[i], sizeof(double));
		}
	}

	void citireGlovoDinFisierBinar(ifstream& fisBinarIn, Glovo& g) {
		int dim = 0;
		char aux[100];

		fisBinarIn.read((char*)&dim, sizeof(dim));
		fisBinarIn.read(aux, dim);
		g.adresa = aux;


		fisBinarIn.read((char*)&dim, sizeof(dim));
		fisBinarIn.read(aux, dim);
		g.telefon = aux;


		fisBinarIn.read((char*)&g.nrComenzi, sizeof(int));

		g.valoriComenzi = new double[g.getNrComenzi()];
		for (int i = 0; i < g.nrComenzi; i++) {
			fisBinarIn.read((char*)&g.valoriComenzi[i], sizeof(double));
		}
	}

	void scrieListaDeGlovoInFisierBinar(list<Glovo> listaGlovo) {
		ofstream fisBinarOut("glovo.bin", ios::out | ios::binary | ios::app);

		if (fisBinarOut.is_open()) {
			list<Glovo>::iterator it1;


			//scrii cate glovo-uri ai in fisier
			int dim = listaGlovo.size();
			fisBinarOut.write((char*)&dim, sizeof(dim));

			for (it1 = listaGlovo.begin(); it1 != listaGlovo.end(); it1++) {
				scrieGlovoInFisierBinar(fisBinarOut, *it1);
			}

			fisBinarOut.close();
		}
		else {
			cout << "Fisierul wwww.dat nu poate fi deschis pentru scriere.\n";
		}
	}

	void citireListaDeGlovoDinFisierBinar(list<Glovo>& listaGlovo) {
		ifstream fisBinarIn("glovo.bin", ios::in | ios::binary);

		if (fisBinarIn.is_open()) {

			int dim = 0;
			fisBinarIn.read((char*)&dim, sizeof(dim));

			Glovo gg;
			for (int i = 0; i < dim; i++) {
				citireGlovoDinFisierBinar(fisBinarIn, gg);
				listaGlovo.push_back(gg);
			}

			fisBinarIn.close();
		}
		else {
			cout << "Fisierul wwww.dat nu poate fi deschis pentru scriere.\n";
		}
	}

	double suma() {
		double suma = 0;
		for (int i = 0; i < this->nrComenzi; i++) {
			suma += this->valoriComenzi[i];
		}

		return suma;
	}
};

ostream& operator<<(ostream& out, Glovo& g) {
	out << "telefon = " << g.getTelefon()
		<< " adresa = " << g.getAdresa()
		<< " nrComenzi = " << g.getNrComenzi() << endl;

	for (int i = 0; i < g.getNrComenzi(); i++) {
		out << g.getValoriComenzi()[i] << " ";
	}

	return out;
}

class Calcul : public ISuma {
	string nume;
	int valoare;

public:

	Calcul(string nume, int valoare) {
		this->nume = nume;
		this->valoare = valoare;
	}

	double suma() {
		return valoare + 100;
	}

	friend ostream& operator<<(ostream& out, Calcul& c) {
		out << "Nume " << c.nume << " valoare: " << c.valoare << endl;
		return out;
	}
};

template <typename T, typename W> void afisareTemplate(T ttt, W www) {
	cout << ttt << endl;
	cout << www << endl;
}

void main() {
	double* d1 = new double[3]{ 10.44, 200.33, 44.33 };
	double* d2 = new double[3]{ 110.44, 78.33, 74.33 };
	double* d3 = new double[3]{ 120.44, 33.44, 33.22 };

	Glovo g1(d1, 3, "07011179", "adresa1");
	Glovo g2(d2, 3, "07565729", "adresa2");
	Glovo g3(d3, 3, "07079464", "adresa3");

	list<Glovo> listaGlovo;
	listaGlovo.push_back(g1);
	listaGlovo.push_back(g2);
	listaGlovo.push_back(g3);

	cout << "LIST STL\n\n";
	for (Glovo g : listaGlovo) {
		cout << g << endl;
	}
	g1.scrieListaDeGlovoInFisierBinar(listaGlovo);


	cout << "\n\ncitire stl din fisier binar\n\n";
	list<Glovo> listaGlovo2;
	g1.citireListaDeGlovoDinFisierBinar(listaGlovo2);
	for (Glovo g : listaGlovo2) {
		cout << g << endl;
	}


	cout << "\n\n ex8 \n\n";
	Calcul* c1 = new Calcul("aa", 10);
	Calcul* c2 = new Calcul("aab", 20);
	Calcul* c3 = new Calcul("aacc", 30);

	Glovo* gg1 = &g1;
	Glovo* gg2 = &g2;
	Glovo* gg3 = &g3;

	ISuma** sume = new ISuma * [6]{ c1,c2,c3 , gg1, gg2, gg3 };

	for (int i = 0; i < 6; i++) {
		cout << sume[i]->suma() << " ";
	}

	cout << "\n\n ex de 10 \n\n";
	afisareTemplate(g1, *c1);

	delete[] d1;
	delete[] d2;
	delete[] d3;

	delete c1;
	delete c2;
	delete c3;
}