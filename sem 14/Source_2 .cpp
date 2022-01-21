#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


class ContBancar {
	string numar;
	string titular;
	string parola;
	double sold;
	string valuta;

public:
	ContBancar() {
		numar = "";
		titular = "";
		parola = "";
		sold = 0;
		valuta = "";
	}

	ContBancar(string numar, string titular, string parola, string valuta, double sold) {
		this->numar = numar;
		this->titular = titular;
		this->parola = parola;
		this->valuta = valuta;
		this->sold = sold;
	}

	ContBancar& operator=(ContBancar& cb) {
		if (this != &cb) {
			if (valuta == cb.valuta) {
				this->sold += cb.sold;
			}
			else {
				if (valuta == "RON" && cb.valuta == "DOL") {
					this->sold += cb.sold * 4.2;//curs 4.2 ron/dol
				}
				else {
					this->sold += cb.sold / 4.2;
				}
			}
			cb.sold = 0;
		}

		return *this;
	}

	//contbancar+STL
	//ContBancar operator+(vector<ContBancar>& conturi) {
	//	ContBancar cb(*this);
	//	for (int i = 0; i < conturi.size(); i++) {
	//		cb.sold += conturi[i].sold;
	//		conturi[i].sold = 0;
	//	}

	//	return cb;
	//}

	//void operator+=(ContBancar cont) {
	//	this->sold += cont.sold;
	//}

	friend ostream& operator<<(ostream& out, const ContBancar& cb) {
		cout << "numar = " << cb.numar << endl;
		cout << "titular = " << cb.titular << endl;
		cout << "parola = " << cb.parola << endl;
		cout << "sold = " << cb.sold << endl;
		cout << "valuta = " << cb.valuta << endl << endl;

		return out;
	}

	friend istream& operator>>(istream& in, ContBancar& cb) {
		char aux[200];
		cout << "numar = ";
		in.getline(aux, 200);
		cb.numar = aux;

		cout << "titular = ";
		in.getline(aux, 200);
		cb.titular = aux;

		//cout << "parola = "; //fara ecou pt parola
		in.getline(aux, 200);
		cb.parola = aux;

		cout << "sold = ";
		in >> cb.sold;

		in.ignore();
		cout << "valuta = ";
		in.getline(aux, 200);
		cb.valuta = aux;


		return in;
	}

	friend ofstream& operator<<(ofstream& out, const ContBancar& cb) {
		int dim = 0;

		dim = cb.numar.size() + 1;
		out.write((char*)&dim, sizeof(int));
		out.write(cb.numar.c_str(), dim);

		dim = cb.titular.size() + 1;
		out.write((char*)&dim, sizeof(int));
		out.write(cb.titular.c_str(), dim);

		dim = cb.parola.size() + 1;
		out.write((char*)&dim, sizeof(int));
		out.write(cb.parola.c_str(), dim);

		out.write((char*)&cb.sold, sizeof(double));

		dim = cb.valuta.size() + 1;
		out.write((char*)&dim, sizeof(int));
		out.write(cb.valuta.c_str(), dim);

		return out;
	}


	friend ifstream& operator>>(ifstream& in, ContBancar& cb) {
		int dim = 0;
		char aux[200];

		in.read((char*)&dim, sizeof(int));
		in.read(aux, dim);
		cb.numar = aux;

		in.read((char*)&dim, sizeof(int));
		in.read(aux, dim);
		cb.titular = aux;

		in.read((char*)&dim, sizeof(int));
		in.read(aux, dim);
		cb.parola = aux;

		in.read((char*)&cb.sold, sizeof(double));

		in.read((char*)&dim, sizeof(int));
		in.read(aux, dim);
		cb.valuta = aux;

		return in;
	}

	~ContBancar() {
		ofstream fout("banca.dat", ios::binary | ios::app);
		if (fout.is_open()) {
			fout << *this;
			fout.close();
		}
		else {
			cout << "Eroare banca.dat\n";
		}
	}
};

void main() {
	ContBancar cb1("RNCB03434 433 4343 4334", "Ion Popescu", "1224", "RON", 2000.59);
	ContBancar cb2;
	ContBancar cb3("RNCB04476 999 2223 3232", "George Popescu", "9999", "DOL", 12500.99);

	//	cin >> cb2;

	ofstream fout("banca.dat", ios::binary);
	if (fout.is_open()) {
		fout << cb1;
		fout << cb3;
		fout.close();
	}
	else {
		cout << "Eroare banca.dat\n";
	}


	ContBancar cb4;
	ContBancar cb5;
	ifstream fin("banca.dat", ios::binary);
	if (fin.is_open()) {
		fin >> cb4;
		fin >> cb5;
		fin.close();

		cout << cb4 << endl << endl << cb5 << endl << endl;
	}
	else {
		cout << "Eroare banca.dat\n";
	}

	cb1 = cb3;
	cout << cb1 << endl;
}