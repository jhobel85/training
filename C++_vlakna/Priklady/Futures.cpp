#include <future>
#include <iostream>

using namespace std;

double odmocnina(double value) {
	if (value < 0.0) {
		throw invalid_argument("Nelze odmocnit zaporne cislo.");
	}
	return sqrt(value);
}

int synchronniVolani() {
	double a = 0, b = 0;
	cout << "zadej dve cisla: ";
	cin >> a >> b;
	double odmA = NAN;
	double odmB = NAN;

	try {	
		odmA = odmocnina(a);
		odmB = odmocnina(b);
	}
	catch (const std::exception& e) {
		cerr << "Chyba " << e.what() << "\\n";
	}
	cout << "odmocnina " << a << " je " << odmA << "\n";
	cout << "odmocnina " << b << " je " << odmB << "\n";
	return 0;
}

unsigned fibonacci(unsigned n)
{
	return n < 2 ? n : fibonacci(n - 1) + fibonacci(n-2); // exponencialni cas - "pomoci" rekurze
}

int asynchronniVolani() {
	double a = 0, b = 0;
	cout << "zadej dve cisla: ";
	cin >> a >> b;
	double odmA = NAN; //abych nemel sdilenou promennou.
	double odmB = NAN;

	try {
		auto fut = async(&odmocnina, a); // viz. thread s argumentem listu
		odmB = odmocnina(b);//odmA se vypocitava zaorven s odmB
		odmA = fut.get();
	}
	catch (const std::exception& e) {
		cerr << "Chyba " << e.what() << "\\n";
	}
	cout << "odmocnina " << a << " je " << odmA << "\n";
	cout << "odmocnina " << b << " je " << odmB << "\n";
	
	return 0;
}

int fibThread(){
	unsigned n;
	std::cout << "Zadej cele cislo: ";
	cin >> n;
	future<unsigned> vysledek;
	thread vlakno;
	{
		promise<unsigned> p;
		vysledek = p.get_future();
		//[tmp = move(p), n] //// staci mit move, nepotrebuji copy, ale problem je treba udelat mutable move
		vlakno = thread{ [n](promise<unsigned> tmp) { // jednodusi pres parameter list noveho funktoru
			tmp.set_value(fibonacci(n));
		}, move(p) }; // vrat vysledek pres move
	}
	//auto vysledek = fibonacci(n);
	//cout << "fibonacci " << n << " je " << vysledek << "\\n";
	vysledek = async(launch::async, &fibonacci, n);
	while (vysledek.wait_for(1s) == future_status::timeout) {
		cout << ".";
	}
	cout << "\n";
	cout << "fibonacci " << n << " je " << vysledek.get() << "\\n";	
	if (vlakno.joinable()) {
		vlakno.join();
	}
	return 0;
}