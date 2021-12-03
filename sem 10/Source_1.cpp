#include<iostream>

using namespace std;


class ExceptieCustomAnimal : public exception {
public:
	// virtual char const* what() const
	const char* what()const throw() {
		return "Varsta animalului trebuie sa fie >0 si <30\n";
	}
};

//O interfata este o clasa ce are doar fct. virtuale pure!
//Se comporta ca un set de reguli pentru clasele pe care o mostenesc;
class InterfataCalorii {
public:
	virtual string catTrebuieSaMananceZilnic() = 0;
};


//100obiecte tip animal, pisica, caine, pisica persana
//InterfataAnimal* vector = new InterfataAnimal[100];
//
//vector[i].ceva1(); todo next week

class Animal :public InterfataCalorii {
public:
	string nume;
	string culoare;
	int varsta;

	Animal(string nume, string culoare, int varsta) {
		this->nume = nume;
		this->culoare = culoare;
		this->varsta = varsta;
	}

	//clasa abstracta = o clasa ce contine cel putin o functie virtuala pura
	virtual void administrareVaccin() = 0;

	//supraincarcare
	void afisare() {
		cout << "Nume " << nume << " culoare " << culoare
			<< " varsta " << varsta << endl;
	}

	void afisare(bool areVaccin) {
		cout << "Nume " << nume << " culoare " << culoare
			<< " varsta " << varsta << " este vaccinat: " << areVaccin << endl;
	}

	//suprascriere
	virtual void scoateSunet() {
		cout << "Animalul a scos un sunet\n";
	}

	//implementare metoda din interfata
	string catTrebuieSaMananceZilnic() {
		return "Animalul trebuie sa manance zilnic 1kg carne";
	}

	//setteri si validari + exceptie custom
	void setCuloare(string culoare) {
		if (culoare.empty()) {
			throw exception("Culoare primita ca input este invalida.");
		}
		else {
			this->culoare = culoare;
		}
	}

	void setNume(string nume) {
		if (nume.empty()) {
			throw new exception("Numele primit ca input este invalid.");
		}
		else {
			this->nume = nume;
		}
	}

	void setVarsta(int varsta) {
		if (varsta < 0 || varsta>30) {
			throw ExceptieCustomAnimal();
		}
		else {
			this->varsta = varsta;
		}
	}

	friend ostream& operator<<(ostream& out, const Animal& a) {
		out << "nume: " << a.nume << " culoare: " << a.culoare << " varsta: " << a.varsta << endl;
		return out;
	}
};

class Pisica : public Animal, public InterfataCalorii {
public:

	Pisica(string nume, string culoare, int varsta)
		:Animal(nume, culoare, varsta) {
	}

	void scoateSunet() {
		cout << "Pisica a scos un sunet: miau-miau\n";
	}

	void administrareVaccin() {
		cout << "Pisica a primit 10ml de vaccin\n";
	}

	//implementare metoda din interfata
	string catTrebuieSaMananceZilnic() {
		return "Pisica trebuie sa manance zilnic 0.6kg carne";
	}

	void afisare(int x, double y) {
		cout << "Nume " << nume << " culoare " << culoare
			<< " varsta " << varsta << endl;
	}
};

class Caine : public Animal, public InterfataCalorii {
public:

	Caine(string nume, string culoare, int varsta)
		:Animal(nume, culoare, varsta) {
	}

	void administrareVaccin() {
		cout << "Cainele a primit 20ml de vaccin\n";
	}

	void scoateSunet() {
		cout << "Cainele a scos un sunet: ham-ham\n";
	}

	//implementare metoda din interfata
	string catTrebuieSaMananceZilnic() {
		return "Caine trebuie sa manance zilnic 2kg carne";
	}
};

class PisicaPersana : public Pisica, public InterfataCalorii {
public:

	PisicaPersana(string nume, string culoare, int varsta)
		:Pisica(nume, culoare, varsta) {
	}

	void scoateSunet() {
		cout << "PisicaPersana a scos un sunet: miau-miau-miau\n";
	}

	void administrareVaccin() {
		cout << "Pisica persana a primit 12ml de vaccin\n";
	}

	//implementare metoda din interfata
	string catTrebuieSaMananceZilnic() {
		return "PisicaPersana trebuie sa manance zilnic 0.2kg carne";
	}
};

int main() {
	//Animal a("Bobby", "alb", 5);
	Pisica pisicaAjutatoare("Rex", "negru", 2);
	Animal* a = &pisicaAjutatoare;

	Pisica p("Silvester", "negru cu alb", 3);
	Caine c("Azorel", "gri", 5);
	PisicaPersana pp("Suzy", "alb", 4);

	p.Animal::afisare();

	cout << "\n\n";
	cout << "===early-binding===" << endl << endl;
	//early-binding ->stii de la compilare ce se apeleaza
	a->scoateSunet();
	a->administrareVaccin();

	p.scoateSunet();
	p.administrareVaccin();

	c.scoateSunet();
	c.administrareVaccin();

	pp.scoateSunet();
	pp.administrareVaccin();

	cout << "===late-binding===" << endl << endl;
	//late-binding -> la runtime se stie ce se apeleaza

	//Animal* ap = &a;

	//ap->scoateSunet();

	Animal* ap = &p;
	ap->scoateSunet();
	ap->administrareVaccin();

	ap = &c;
	ap->scoateSunet();
	ap->administrareVaccin();

	ap = &pp;
	ap->scoateSunet();
	ap->administrareVaccin();

	Animal* a1 = &pp;//(up-casting)
	a1->scoateSunet();
	a1->administrareVaccin();

	cout << "\n\ntry catch\n\n";
	try {
		//	p.setCuloare("");

		//p.setNume(""); //comentati voi aici metodele pentru a testa try catch
		p.setVarsta(100);
	}
	catch (ExceptieCustomAnimal e) {
		cout << e.what() << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	catch (exception* e) {
		cout << e->what() << endl;
	}
	catch (...) { //pt toate cazurile...adica nu mai ai nevoie de catch urile de mai sus
		cout << "ai o eroare undeva" << endl;
	}

	InterfataCalorii** vectorDeInterfeteCalorii = new InterfataCalorii * [4]{ &p, &c, &pp, &pisicaAjutatoare };
	for (int i = 0; i < 4; i++) {
		cout << vectorDeInterfeteCalorii[i]->catTrebuieSaMananceZilnic() << endl;
	}

	cout << "\n\nvector de animale\n\n";
	Animal** vectorDeAnimale = new Animal * [4]{ &p, &c, &pp, &pisicaAjutatoare };
	for (int i = 0; i < 4; i++) {
		vectorDeAnimale[i]->administrareVaccin();
		vectorDeAnimale[i]->scoateSunet();

	}

	//cout << p;
}