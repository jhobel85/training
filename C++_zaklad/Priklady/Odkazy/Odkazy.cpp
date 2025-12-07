#include <iostream>
#include <vector>
#include <list>
using namespace std;

//Odkazy - souhrnne, reference, pointery
//Index (kukatko) = relativni adresa prvky v poli, zastupce prvku v poli
int reference()
{
	cout << "Hello World!\n";
	double cil = 100;
	double& ref = cil;

	cout << "ref = " << ref << "\n"; //100
	ref = 200;
	cout << "cil = " << cil << "\n";//200
	return 0;
}

#pragma warning (push) // uloz warning do stacku
#pragma warning (disable:4700) // modifikuj nastaveni warningu
int ukazatel()
{
	cout << "Ukazatel\n";
	double cil = 100;
	double* ptr; // nullptr;//inicializace v pripade, ze pointer neni pripraveny, layzy inicializace
	double* ptr2; // vlajici pointer - od Micorsoft: 0xCCCCCCCC -> vypisu adresu, ale nic na ni neni -> 
	cout << "ptr = " << ptr << "\n";
	//cout << "ptr2 = " << ptr2 << "\n"; // warning
	ptr = &cil;
	cout << "ptr = " << ptr << "\n";
	if (ptr != nullptr)
	{
		cout << "*ptr = " << *ptr << "\n";
	}
	cout << "cil = " << cil << "\n";
	return 0;
}
#pragma warning (pop) // obnovit puvodni warning

void cpp_swap(int a, int b) 
{
	int c = a;
	a = b;
	b = c;
	cout << "a = " << a << " b = " << b << "\n";
}

void cpp_swap2(int& a, int& b) //vystupni parametry - referencni - velmi pouzivane v C++ (neexistuji v C)
{
	int tmp = a;
	a = b;
	b = tmp;
	cout << "a = " << a << " b = " << b << "\n";
}

void cpp_swap3(int* a, int* b) //vystupni parametry - pointry - v C
{
	//int* tmp = a; // toto neni integer, jen ukazatel na integer - tim nic nezamennine
	int tmp = *a; // hodnotu z pointeru priradim do tmp
	*a = *b;
	*b = tmp;
	cout << "a = " << a << " b = " << b << "\n";
}

/*
void cpp_swap4(long long a, long long b) //vystupni parametry - referencni - velmi pouzivane v C++ (neexistuji v C)
{
	cout << "a = " << a << " b = " << b << "\n";
	int tmp = a;
	a = b;
	b = tmp;
	cout << "a = " << a << " b = " << b << "\n";
}
*/

int cviceniSwap() {

	int x = 100, y = 200;
	cout << "x = " << x << " y = " << y << "\n";
	//cpp_swap(x, y);
	cout << "x = " << x << " y = " << y << "\n";
	//cpp_swap2(x, y);
	cout << "x = " << x << " y = " << y << "\n";
	//cpp_swap3(&x, &y);
	cout << "x = " << x << " y = " << y << "\n";
	/*
	cpp_swap4((long long) &x, (long long) &y); // nejde nacastovat automaticky 64bit pointer na 16bit int -> kdyztak tedy long long
	//ale castovat pointery na cisla je velmi nebezpecne a zavadejici -> jednou udelam chybu a cela app. se zborti.
	cout << "x = " << x << " y = " << y << "\n";
	*/
	return 0;
}

//iterator - genericky
//void zobraz(const double* zac, const double* kon) {
// genericky - nerikam ktereho typu - tzn. libovlna dat. struktura
void zobraz(auto zac, auto kon) { //C++ V20
	for (; zac != kon; ++zac) {
		//tady jen 1 operace dereference
		cout << *zac << " "; // lepsi performance nez zobraz pole[i] --> *(pole+i)  - 2 operace
	}
}

int pointerovaAritmetika() {
	constexpr int n = 5;
	double pole[n] = { 4,1,7,3,6 }; 
	//double* zac = &pole[0];
	//double* kon = &pole[5];
	// nazev pole v C je odkaz na prvni bunku.
	double* zac = pole;
	double* kon = pole + n;

	cout << "kon - zac = " << kon - zac; //rozdil indexu
	cout << "pole[2] = " << pole[2] << "\n";
	cout << "*(pole+2) = " << *(pole+2) << "\n"; // pointerova aritmetika, tzn. [] jsou jen syntaticky cukr
	cout << "2[pole] = " << 2[pole] << "\n"; // take to stejne - sticani je komutativni

	cout << "iteratorvy pruchod polem:\n";

	for (;zac != kon;++zac) {
		cout << *zac << " ";
	}

	cout << "predani iteratoru funkce: \n";
	zobraz(begin(pole), end(pole)); // genericke funkce ktere vraci zacatek a konec nasi struktury
	cout << "\n\n";

	cout << "obsah vectoru" << "\n";
	vector<double> vec{ 4,1,7,3,5 };
	zobraz(pole, pole + n);
	cout << "\n";

	cout << "obsah zretezeneho seznamu" << "\n";
	list<double> seznam{ 44,111,777,333,555 };	
	zobraz(begin(seznam), end(seznam));
	cout << "\n";
	return 0;
}

int main() 
{
	int p1[] = {1,2}; 
	//zero terminated string - pole charu se zarazkou (take se tomu rika C pole)
	//char p2[] = { 'a','h','o','j'}; - pole bez zarazky prochazi jeste nejake random znaky
	//char p2[] = { 'a','h','o','j','\0' };//\0 nulovy znak 
	char p2[] = "ahoj"; //totozne jako predchozi, kompilator vytvori zero terminated string
	cout << "p1 = " << p1 << "\n";
	cout << "p2 = " << p2 << "\n";	
	char* observer = p2;
	cout << "observer = " << observer << "\n";
	
	//string a = "abcd";
	//cout << a;
	return 0;
}
