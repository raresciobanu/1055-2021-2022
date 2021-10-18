#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 5 };

//private, protected, public
class Student {
	//private: by default daca nu este scris 
	const int ID_Matricol;
	GEN gen;
	char* nume;
	string prenume = "Florin";
	int varsta = 20;
	int nrNote;
	double* note;
public:
	static int anCurent;

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

	/*Student( const Student &stud1, const Student &stud2, int varsta) :ID_Matricol(stud1.ID_Matricol){
		this->nume = new char[strlen(stud1.nume) + 1];
		strcpy_s(this->nume, strlen(stud1.nume) + 1, stud1.nume);

		this->prenume = stud1.prenume;
		this->varsta = varsta;
		this->nrNote = stud2.nrNote;

		this->note = new double[stud2.nrNote];
		for (int i = 0; i < stud2.nrNote; i++) {
			this->note[i] = stud2.note[i];
		}

		this->gen = stud2.gen;
	}*/

	Student(const Student& stud) :ID_Matricol(stud.ID_Matricol) {
		cout << "constr de copiere\n";
		this->nume = new char[strlen(stud.nume) + 1];
		strcpy_s(this->nume, strlen(stud.nume) + 1, stud.nume);

		this->prenume = stud.prenume;
		this->varsta = stud.varsta;
		this->nrNote = stud.nrNote;

		this->note = new double[stud.nrNote];
		for (int i = 0; i < stud.nrNote; i++) {
			this->note[i] = stud.note[i];
		}

		this->gen = stud.gen;
	}

	~Student() {
		cout << "destructor" << endl;
		if (this->nume != nullptr) {
			delete[] this->nume;
		}

		if (this->note != nullptr) {
			delete[] this->note;
		}
	}

	//op egal
	Student& operator=(Student& stud) {//s1=s3....sssss(s1)
		if (this != &stud) {
			if (this->nume != nullptr) {
				delete[] this->nume;
			}

			if (this->note != nullptr) {
				delete[] this->note;
			}

			this->nume = new char[strlen(stud.nume) + 1];
			strcpy_s(this->nume, strlen(stud.nume) + 1, stud.nume);

			this->prenume = stud.prenume;
			this->varsta = stud.varsta;
			this->nrNote = stud.nrNote;

			this->note = new double[stud.nrNote];
			for (int i = 0; i < stud.nrNote; i++) {
				this->note[i] = stud.note[i];
			}

			this->gen = stud.gen;
		}

		return *this;
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

	char* getNume() {
		return nume;
	}

	int getVarsta() {
		return varsta;
	}

	int getIDMatricol() {
		return ID_Matricol;
	}

	string getPrenume() {
		return prenume;
	}

	int getNrNote() {
		return nrNote;
	}

	double* getNote() {
		return note;
	}

	double getNota(int index) {
		return this->note[index];
	}

	void setVarsta(int varsta) {
		this->varsta = varsta;
	}

	void setNrNote(int nrNote) {
		this->nrNote = nrNote;
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

int Student::anCurent = 2009;

void main() {
	Student s;
	s.afisare();
	s.anCurent = 2000;

	Student s1(20);
	s1.afisare();
	s1.anCurent = 2010;

	Student s2("Rares", 26);
	s2.afisare();
	s2.anCurent = 2020;

	double v[] = { 10,8,5.5,6,7.6 };
	Student s3(30, "Popescu", "Ionel", 20, 5, v, GEN::BARBAT);
	s3.afisare();

	cout << endl << endl;
	Student s4(s3);
	s4.afisare();

	Student s5 = s4;
	s5.afisare();

	cout << "op egal \n\n\n";
	Student s6;
	s6 = s3 = s1 = s2;
	s6.afisare();

	cout << endl << endl;
}