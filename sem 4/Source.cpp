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
		if (this->nume != nullptr) {
			delete[] this->nume;
		}

		if (this->note != nullptr) {
			delete[] this->note;
		}
	}

	//op egal
	Student& operator=(Student& stud) {//s1=s3....sssss(s1)
		if (this != &stud) {//s1=s1
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

	void setPrenume(string prenume) {
		if (prenume.empty()) {
			throw new exception("Prenume este empty");
		}
		this->prenume = prenume;
	}

	void setNume(const char* nume) {
		if (nume != nullptr) {
			delete[] this->nume; //evitare memory leaks;

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			throw new exception("Nume este null");
		}
	}

	void setNote(double* note, int nrNote) {
		if (note != nullptr && nrNote > 0) {
			this->nrNote = nrNote;

			delete[] this->note;

			this->note = new double[nrNote];
			for (int i = 0; i < nrNote; i++) {
				this->note[i] = note[i];
			}
		}
		else {
			throw new exception("Note este null sau nrNote este <=0.");
		}
	}

	void afisare() {
		cout << "Studentul are numele " << nume << " prenumele " << prenume << " varsta " << varsta << " ani "
			<< " genul " << getGenInCaractere() << " ID-ul matricol " << ID_Matricol << " si notele: ";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}
		cout << endl;
	}

	friend double calcMediePrietena(Student& s);


	//operatori
	//op. unari
	//op. ++ pre-incrementare (cout<<++s2;)
	const Student& operator++() {
		varsta++;

		return *this;
	}

	//op. ++ post-incrementare (cout<<s3++;)
	const Student operator++(int) {
		Student aux(*this);

		varsta++;

		return aux;
	}

	//op. binari
	//op. + (ex: cout<<s5+2;)
	int operator+(int x) {
		return varsta + x;
	}

	//op + (ex: cout<<s5+s1;)
	Student operator+(Student& student) {
		Student aux(*this);

		aux.prenume = aux.prenume + "-" + student.prenume;

		return aux;
	}

	//op. + (ex: cout<<10+s2;)
	friend int operator+(int x, Student& student);

	//op. += (s5+=2);
	void operator+=(int x) {
		varsta += x;
	}

	//op<< (cout<<s5;)
	friend ostream& operator<<(ostream& out, const Student& stud);

	//op>> (cin>>s2;)
	friend istream& operator>>(istream& in, Student& stud);

};

//op. + (ex: cout<<10+s2;)
int operator+(int x, Student& student) {
	return x + student.varsta;
}


ostream& operator<<(ostream& out, const Student& stud) {
	out << "Studentul are numele " << stud.nume << " prenumele " << stud.prenume << " varsta " << stud.varsta << " ani "
		<< " genul " << stud.gen << " ID-ul matricol " << stud.ID_Matricol << " si notele: ";
	for (int i = 0; i < stud.nrNote; i++) {
		out << stud.note[i] << " ";
	}
	out << endl;

	return out;
}

istream& operator>>(istream& in, Student& stud) {
	char aux[100];
	cout << "Nume"; in >> aux;

	//eviti memory leaks
	if (stud.nume != nullptr) {
		delete[] stud.nume;
	}

	stud.nume = new char[strlen(aux) + 1];
	strcpy_s(stud.nume, strlen(aux) + 1, aux);

	cout << "Prenume: "; in >> stud.prenume;
	cout << "Varsta: "; in >> stud.varsta;

	int auxGen;
	cout << "GEN: "; in >> auxGen;
	switch (auxGen)
	{
	case 0:
		stud.gen = FEMEIE;
		break;
	case 3:
		stud.gen = BARBAT;
		break;
	case 5:
		stud.gen = NECUNOSCUT;
		break;
	}

	cout << "Nr note: "; in >> stud.nrNote;
	//eviti memory leaks
	if (stud.note != nullptr) {
		delete[] stud.note;
	}

	stud.note = new double[stud.nrNote];
	for (int i = 0; i < stud.nrNote; i++) {
		in >> stud.note[i];
	}

	return in;
}


double calcMedie(Student& s) {
	double medie = 0;
	for (int i = 0; i < s.getNrNote(); i++) {
		medie += s.getNota(i);
	}

	return medie / s.getNrNote();
}

double calcMediePrietena(Student& s) {
	double medie = 0;
	for (int i = 0; i < s.nrNote; i++) {
		medie += s.note[i];
	}

	return medie / s.nrNote;
}


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
	Student s3(30, "", "Ionel", 20, 5, v, GEN::BARBAT);
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

	s6.setNume("Rares");
	s6.setPrenume("Ion");
	s6.setVarsta(25);
	double v2[] = { 10,8,5.5,6,7.6,10,9,8,7,6 };
	s6.setNote(v2, 10);
	cout << s6.getNume() << endl;

	cout << "op<<\n\n\n";
	//op<<
	cout << s6;
	//op++ pre
	cout << ++s6;

	//op++ post
	cout << s6++;
	cout << endl << endl;
	//op+
	cout << 5 + s6 << endl;
}