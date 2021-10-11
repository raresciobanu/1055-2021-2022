#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 5 };

//private, protected, public
class Student {
	//private: by default daca nu este scris 
	const int ID_Matricol;
	GEN gen;
public:
	char* nume;
	string prenume = "Florin";
	int varsta = 20;
	int nrNote;
	double* note;

	//constructor default
	Student() :ID_Matricol(120) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id) :ID_Matricol(id) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(string prenume, int varsta) :ID_Matricol(20) {
		this->prenume = prenume;
		this->varsta = varsta;

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id, const char* nume, string prenume, int varsta, int nrNote, double* note, GEN gen) :ID_Matricol(id) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);

		this->prenume = prenume;
		this->varsta = varsta;
		this->nrNote = nrNote;

		this->note = new double[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}

		this->gen = gen;
	}

	const char* getGenInCaractere() {
		switch (gen)
		{
		case FEMEIE:
			return "femeie";
		case BARBAT:
			return "barbart";
		case NECUNOSCUT:
			return "necunoscut";
		}
	}

	GEN getGen() {
		return gen;
	}

	void afisare() {
		cout << "Studentul are numele " << nume << " prenumele " << prenume << " varsta " << varsta << " ani "
			<< " genul " << getGenInCaractere() << " ID-ul matricol " << ID_Matricol << " si notele: ";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}
		cout << endl;
	}
};


void main() {
	Student s;
	s.afisare();

	Student s1(20);
	s1.afisare();

	Student s2("Rares", 26);
	s2.afisare();

	double v[] = { 10,8,5.5,6,7.6 };
	Student s3(30, "Popescu", "Ionel", 20, 5, v, GEN::BARBAT);
	s3.afisare();
}