#include <iostream>

using namespace std;

unsigned int soucetRady(unsigned n); // staci jen kladna cela cisla
unsigned int faktorial(unsigned n);
unsigned int fibonacci(unsigned n);
unsigned int pole[8] {0};
int i = 0;

int Rekurze()
{
	cout << "rekurze\n";
	cout << "soucetRady(0) = " << soucetRady(0) << "\n";//1
	cout << "soucetRady(1) = " << soucetRady(1) << "\n";//0
	cout << "soucetRady(100) = " << soucetRady(100) << "\n";//5050 
	//S(n) = (n+1) * n / 2 - vypocet pomoci Gausse
	//1 + 100 = 101
	//2 + 99 = 101
	//3 + 98 = 101 ...
	cout << "\n";
	cout << "faktorial(0) = " << faktorial(0) << "\n";
	cout << "faktorial(1) = " << faktorial(1) << "\n";
	cout << "faktorial(8) = " << faktorial(8) << "\n"; //40320
	cout << "\n";

	cout << "Fibbonacci\n";
	cout << "Fibbonacci(0) = " << fibonacci(0) << "\n";//0
	cout << "Fibbonacci(1) = " << fibonacci(1) << "\n";//1
	cout << "Fibbonacci(2) = " << fibonacci(1) << "\n";//1
	cout << "Fibbonacci(8) = " << fibonacci(8) << "\n"; //21
	//cout << "Fibbonacci(42) = " << fibonacci(42) << "\n";
	cout << "\n";

	return 0;
}

unsigned int soucetRady(unsigned n)
{
	return n < 2 ? n : soucetRady(n-1) + n;
}

unsigned int faktorial(unsigned n)
{
	return n < 2 ? 1 : faktorial(n-1) * n;
}

unsigned int fibonacci(unsigned n)
{
	int fibCur = 0;
	if (n >= 3) {
		fibCur = fibonacci(n - 1) + fibonacci(n - 2);
		//cout << " ;cur=" << fibCur << ", n=" << n;
	}			
	return n < 3 ? n == 0 ? 0: 1 : fibCur;
}

