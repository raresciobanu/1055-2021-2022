#include<iostream>

using namespace std;

//mostenire/derivare

class Vehicul {
	string culoare;
protected:
	long nrKm;
	int an;
public:
	string marca;
	char* serie;

	Vehicul() {
		//cout << "Vehicul()\n\n\n";
	}

	Vehicul(string culoare, long nrKm) {
		this->culoare = culoare;
		this->nrKm = nrKm;
	}

	Vehicul(string culoare, long nrKm, int an, string marca, const char* serie) {
		//cout << "Constructor (....,....,....,....,....) Vehicul\n";

		this->culoare = culoare;
		this->nrKm = nrKm;
		this->an = an;
		this->marca = marca;

		this->serie = new char[strlen(serie) + 1];
		strcpy_s(this->serie, strlen(serie) + 1, serie);
	}

	Vehicul(const Vehicul& v) {
		//	cout << "Constructor copiere Vehicul\n";

		this->culoare = v.culoare;
		this->nrKm = v.nrKm;
		this->an = v.an;
		this->marca = v.marca;

		if (v.serie != nullptr) {
			this->serie = new char[strlen(v.serie) + 1];
			strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
		}
		else {
			this->serie = nullptr;//sau anonim
		}
	}

	~Vehicul() {
		//cout << "Destructor Vehicul!\n";

		if (this->serie != nullptr) {
			delete[] this->serie;
		}
	}

	Vehicul& operator=(const Vehicul& v) {
		//cout << "Op. = Vehicul\n";
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
				this->serie = nullptr;//sau anonim
			}
		}

		return *this;
	}

	Vehicul& operator+(int km) {
		this->nrKm += km;

		return *this;
	}

	bool operator==(Vehicul& v) {
		if (this == &v) {
			return true;
		}

		return this->culoare == v.culoare &&
			this->nrKm == v.nrKm &&
			this->an == v.an &&
			this->marca == v.marca &&
			strcmp(this->serie, v.serie) == 0;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v) {
		cout << "Vehiculul are culoarea " << v.culoare << " nr km " << v.nrKm
			<< " este fabricat in anul " << v.an << " marca fiind " << v.marca
			<< " seria " << v.serie << endl;

		return out;
	}
};

//Mostenire/derivare
//Motocicleta "is a" Vehicul
//Motocicleta = Vehicul + arecasca
class Motocicleta : public Vehicul {
public:
	bool areCasca;

	Motocicleta() :Vehicul("Verde", 123000, 2009, "BMW", "HLYHIKG2121") {
		//cout << "Constructor () Motocicleta\n";
		this->areCasca = false;
	}

	Motocicleta(
		string culoare,
		long nrKm,
		int an,
		string marca,
		const char* serie,
		bool areCasca) :Vehicul(culoare, nrKm, an, marca, serie) {
		//cout << "Constructor () Motocicleta\n";

		this->areCasca = areCasca;
	}

	Motocicleta(const Motocicleta& m) :Vehicul(m) {
		//cout << "Constructor copiere Motocicleta\n";
		this->areCasca = m.areCasca;
	}

	~Motocicleta() {
		//cout << "Destructor Motocicleta!\n";
	}

	Motocicleta& operator=(const Motocicleta& m) {
		//cout << "Op. = Vehicul\n";
		if (this != &m) {
			Vehicul::operator=(m);

			this->areCasca = m.areCasca;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Motocicleta& m) {

		//Poti transforma un copil in parinte (up-casting)
		out << (Vehicul)m;
		out << "Are casca: " << m.areCasca << endl;

		return out;
	}

	Motocicleta& operator+(int km) {
		Vehicul::operator+(km);

		return *this;
	}

	bool operator==(Motocicleta& m) {
		if (this == &m) {
			return true;
		}

		return this->areCasca == m.areCasca &&
			Vehicul::operator==(m);
	}
};

class TIR :private Vehicul {
public:
	int ceva;
};

class Masina :protected Vehicul {
public:
	int altceva;
};

//compunere "has a"
class ReprezentantaDeMotociclete {
private:
	string denumire;
	Motocicleta* motociclete;
	int nrMotociclete;
public:
	ReprezentantaDeMotociclete(string denumire, Motocicleta* motociclete, int nrMotociclete) {

		this->denumire = denumire;

		this->nrMotociclete = nrMotociclete;

		this->motociclete = new Motocicleta[nrMotociclete];
		for (int i = 0; i < nrMotociclete; i++) {
			this->motociclete[i] = motociclete[i];
		}
	}

	ReprezentantaDeMotociclete(const ReprezentantaDeMotociclete& reprezentanta) {
		this->denumire = reprezentanta.denumire;
		this->nrMotociclete = reprezentanta.nrMotociclete;
		this->motociclete = new Motocicleta[reprezentanta.nrMotociclete];
		for (int i = 0; i < nrMotociclete; i++) {
			this->motociclete[i] = reprezentanta.motociclete[i];
		}
	}

	~ReprezentantaDeMotociclete() {
		if (motociclete != nullptr) {
			delete[] motociclete;
		}
	}

	ReprezentantaDeMotociclete& operator=(const  ReprezentantaDeMotociclete& reprezentanta) {
		if (this != &reprezentanta) {
			if (this->motociclete != nullptr) {
				delete[] this->motociclete;
			}
			this->denumire = reprezentanta.denumire;
			this->nrMotociclete = reprezentanta.nrMotociclete;
			this->motociclete = new Motocicleta[reprezentanta.nrMotociclete];
			for (int i = 0; i < nrMotociclete; i++) {
				this->motociclete[i] = reprezentanta.motociclete[i];
			}
		}
		return *this;
	}

	int getNrMotociclete() {
		return nrMotociclete;
	}

	//ar fi mai safe uneori
	Motocicleta* getMotociclete() {
		Motocicleta* aux = new Motocicleta[nrMotociclete];

		for (int i = 0; i < nrMotociclete; i++) {
			aux[i] = this->motociclete[i];
		}

		return aux;

		//return this->motociclete;
	}

	Motocicleta& operator[](int index) {
		if (index >= 0 && index < nrMotociclete) {
			return motociclete[index];
		}
		else {
			throw new exception("eroare in [] ");
		}
	}

	void adaugaMotocicleta(Motocicleta m) {
		Motocicleta* aux = new Motocicleta[nrMotociclete + 1];
		for (int i = 0; i < nrMotociclete; i++) {
			aux[i] = motociclete[i];
		}

		aux[nrMotociclete++] = m;
		delete[] motociclete;
		motociclete = aux;
	}

	//sterge toate aparitiile
	void stergereMotocicleta(Motocicleta m) {
		int nrDuplicate = 0;
		for (int i = 0; i < nrMotociclete; i++) {
			if (this->motociclete[i] == m) {
				nrDuplicate++;
			}
		}

		if (nrDuplicate > 0) {
			for (int i = 0; i < nrMotociclete; i++) {
				if (this->motociclete[i] == m) {
					for (int j = i; j < nrMotociclete - 1; j++) {
						this->motociclete[j] = motociclete[j + 1];
					}
					nrMotociclete--;
				}
			}

			Motocicleta* aux = new Motocicleta[nrMotociclete];
			for (int i = 0; i < nrMotociclete; i++) {
				aux[i] = motociclete[i];
			}

			delete[] motociclete;
			motociclete = aux;
		}
	}

	friend ostream& operator<<(ostream& out, ReprezentantaDeMotociclete& r) {
		out << "Denumire reprezentanta: " << r.denumire << endl;
		out << "Numar de motociclete disponibile: " << r.nrMotociclete << endl;
		for (int i = 0; i < r.nrMotociclete; i++) {
			out << r.motociclete[i];
		}

		return out;
	}
};
void main() {
	Motocicleta m;
	cout << m << endl;

	Motocicleta m1("verde", 1000, 2021, "Suzuki", "JGUHGGTJ222", true);
	cout << m1 << endl;

	//mostenire publica/protected/private
	TIR t;
	Masina masina;
	m1.serie;//se poate accesa din main
	//t.serie;//mostenirea este privata => nu ai acces la zona publica din bunic si nici din clasa TIR
	//masina.serie;//mostenirea este protected => nu ai acces la zona publica din bunic, dar ai acces la ea din clasa MASINA


	//mostenire op
	cout << (m1 + 100) << endl << endl;

	Motocicleta m2("rosu", 11000, 2010, "Audi", "XXX#F#FD2", true);
	Motocicleta m3("negru", 2200, 2020, "BMW", "DWAFEWFW", true);

	ReprezentantaDeMotociclete reprezentanta("Moto SRL", new Motocicleta[]{ m1 }, 1);
	reprezentanta.adaugaMotocicleta(m2);
	reprezentanta.adaugaMotocicleta(m3);

	//op []
	cout << "reprezentanta[2]  " << reprezentanta[2] << endl << endl;

	cout << reprezentanta << endl << endl;

	reprezentanta.stergereMotocicleta(m2);

	cout << reprezentanta << endl << endl;

}