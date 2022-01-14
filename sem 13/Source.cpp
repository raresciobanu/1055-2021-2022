#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class GestiuneExamene {
private:
	static int exameneActive;
protected:
	string disciplina;
	double nota;
	string dataExamen;
	const int ID;
public:
	GestiuneExamene() :ID(1002) {
		disciplina = "POO";
		nota = 4;
		dataExamen = "20.02.2022";
	}

	GestiuneExamene(string disciplina, double nota, string dataExamen, int ID) :ID(ID) {
		this->disciplina = disciplina;
		this->nota = nota;
		this->dataExamen = dataExamen;
		exameneActive++;
	}

	GestiuneExamene(const GestiuneExamene& g) :ID(g.ID) {
		this->disciplina = g.disciplina;
		this->nota = g.nota;
		this->dataExamen = g.dataExamen;
		exameneActive++;
	}

	~GestiuneExamene() {

	}

	GestiuneExamene& operator=(const GestiuneExamene& g) {
		if (this != &g) {
			this->disciplina = g.disciplina;
			this->nota = g.nota;
			this->dataExamen = g.dataExamen;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const GestiuneExamene& g) {
		out << "ID: " << g.ID << endl;
		out << "Disciplina: " << g.disciplina << endl;
		out << "Nota: " << g.nota << endl;
		out << "Data examen: " << g.dataExamen << endl;

		return out;
	}

	bool operator==(GestiuneExamene& g) {
		if (this == &g) {
			return true;
		}

		return this->nota == g.nota && disciplina == g.disciplina && dataExamen == g.dataExamen;
	}

	bool operator>=(GestiuneExamene& g) {
		return this->nota >= g.nota;
	}

	operator double() {
		return nota;
	}

	//pre ++
	GestiuneExamene& operator++() {
		if (nota > 0 && nota <= 9) {
			nota++;
		}

		return *this;
	}

	//post ++
	GestiuneExamene operator++(int) {
		GestiuneExamene aux(*this);

		if (nota > 0 && nota <= 9) {
			nota++;
		}

		return aux;
	}

	string getDisciplina() { return disciplina; }

	double getNota() { return nota; }

	string getDataExamen() { return dataExamen; }

	void platesteRestanta() {
		cout << "Restanta a fost platita\n";
	}

	double afiseazaNotaExamen() {
		return nota;
	}

	friend ofstream& operator<<(ofstream& out, const GestiuneExamene& g) {
		out.write((char*)&g.nota, sizeof(double));

		int dim = 0;
		dim = g.disciplina.size() + 1;

		out.write((char*)&dim, sizeof(int));
		out.write(g.disciplina.c_str(), dim);

		dim = g.dataExamen.size() + 1;
		out.write((char*)&dim, sizeof(int));
		out.write(g.dataExamen.c_str(), dim);

		return out;
	}

	friend ifstream& operator>>(ifstream& in, GestiuneExamene& g) {
		in.read((char*)&g.nota, sizeof(double));

		int dim = 0;
		in.read((char*)&dim, sizeof(int));

		char aux[100];
		in.read(aux, dim);
		g.disciplina = aux;

		dim = 0;
		in.read((char*)&dim, sizeof(int));
		in.read(aux, dim);
		g.dataExamen = aux;

		return in;
	}
};
int GestiuneExamene::exameneActive = 0;

class Catalog {
	GestiuneExamene* examene;
	int nrExamene;
public:

	Catalog(GestiuneExamene* examene, int nrExamene) {
		this->nrExamene = nrExamene;
		this->examene = new GestiuneExamene[nrExamene];
		for (int i = 0; i < nrExamene; i++) {
			this->examene[i] = examene[i];
		}
	}

	Catalog(const Catalog& c) {
		this->nrExamene = c.nrExamene;
		this->examene = new GestiuneExamene[c.nrExamene];
		for (int i = 0; i < c.nrExamene; i++) {
			this->examene[i] = c.examene[i];
		}
	}

	~Catalog() {
		if (examene != nullptr) {
			delete[] examene;
		}
	}

	void operator+=(GestiuneExamene g) {
		GestiuneExamene* aux = new GestiuneExamene[nrExamene + 1];
		for (int i = 0; i < nrExamene; i++) {
			aux[i] = examene[i];
		}

		aux[nrExamene] = g;
		delete[] examene;
		examene = aux;
	}

	void operator-=(GestiuneExamene examen) {
		int ok = 0;
		for (int i = 0; i < nrExamene; i++) {
			if (examene[i] == examen) {
				ok = 1;
			}
		}

		if (ok == 1) {
			GestiuneExamene* aux = new GestiuneExamene[nrExamene - 1];
			for (int i = 0; i < nrExamene; i++) {
				if (!(examene[i] == examen)) {
					aux[i] = examene[i];
				}
			}
			nrExamene--;
			delete[] examene;
			examene = aux;
		}
	}
};

void main() {
	GestiuneExamene g1;
	GestiuneExamene g2(g1);

	GestiuneExamene g3("MKT", 7.4, "10.02.2022", 1112);
	GestiuneExamene g4("MAN", 9.3, "10.02.2022", 1113);
	GestiuneExamene g5("CIBE", 9.9, "10.02.2022", 1114);
	//pre
	cout << ++g3 << endl;
	//post
	cout << g3++ << endl;
	cout << g3 << endl;
	//cast
	double dd = g3; //cast implicit
	cout << (double)g3 << endl;//cast explicit

	vector<GestiuneExamene> gestiuneExameneVector;
	gestiuneExameneVector.push_back(g1);
	gestiuneExameneVector.push_back(g2);
	gestiuneExameneVector.push_back(g3);
	gestiuneExameneVector.push_back(g4);
	gestiuneExameneVector.push_back(g5);

	ofstream fout("fout.bin", ios::binary | ios::out);
	if (fout.is_open()) {
		int dimVector = gestiuneExameneVector.size();
		fout.write((char*)&dimVector, sizeof(int));

		for (int i = 0; i < gestiuneExameneVector.size(); i++) {
			fout << gestiuneExameneVector[i];
		}

		fout.close();
	}
	else {
		cout << "Fisierul nu a putut fi deschis pt scriere. \n";
	}



	vector<GestiuneExamene> gestiuneExameneVectorDinFisier;
	ifstream fin("fout.bin", ios::binary | ios::in);
	if (fin.is_open()) {
		int dimVector = 0;
		fin.read((char*)&dimVector, sizeof(int));

		for (int i = 0; i < dimVector; i++) {
			GestiuneExamene uuu;
			fin >> uuu;


			gestiuneExameneVectorDinFisier.push_back(uuu);
		}

		fin.close();
	}
	else {
		cout << "Fisierul nu a putut fi deschis pt citire. \n";
	}

	cout << "\n\nafisare din fisier binar\n\n";
	for (int i = 0; i < gestiuneExameneVectorDinFisier.size(); i++) {
		cout << gestiuneExameneVectorDinFisier[i] << endl;
	}
}