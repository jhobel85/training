#include "SablonyFunkci.h"

#include <fstream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

void seriovaAlokaceNotExceptionSafe(size_t delka)
{
	int* p1 = new int[delka];
	int* p2 = new int[delka];

	generate(p1, p1 + delka, Rand{ 10, 20 });
	copy(p1, p1 + delka, p2);
	double soucet = accumulate(p2, p2 + delka, 0.0);

	if (soucet > 200)
	{
		throw out_of_range{ "Prekrocen maximalni povoleny rozsah." };
	}
	cout << "soucet = " << soucet << "\n";

	delete[] p2;
	delete[] p1;
}

void seriovaAlokaceNaivne(size_t delka)
{
	exception_ptr eptr;
	int* p1 = nullptr;
	int* p2 = nullptr;

	try
	{
		p1 = new int[delka];
		p2 = new int[delka];

		generate(p1, p1 + delka, Rand{ 10, 20 });
		copy(p1, p1 + delka, p2);
		double soucet = accumulate(p2, p2 + delka, 0.0);

		if (soucet > 200)
		{
			throw out_of_range{ "Prekrocen maximalni povoleny rozsah." };
		}
		cout << "soucet = " << soucet << "\n";
	}
	catch (...)
	{
		eptr = current_exception();
	}

	delete[] p2;
	delete[] p1;

	if (eptr)
	{
		rethrow_exception(eptr);
	}
	return;
}

void seriovaAlokace(size_t delka)
{
	vector<int> p1(delka);
	vector<int> p2(delka);

	generate(p1.begin(), p1.end(), Rand{10, 20});
	copy(p1.begin(), p1.end(), p2.begin());
	double soucet = accumulate(p2.begin(), p2.end(), 0.0);

	if (soucet > 200)
	{
		throw out_of_range{ "Prekrocen maximalni povoleny rozsah." };
	}
	cout << "soucet = " << soucet << "\n";
}

int exceptionSafeProgramming()
{
	try
	{
		cout << "Zadej delku: ";
		size_t delka = -1;
		cin >> delka;

		cout << "delka = " << delka << "\n";
		seriovaAlokace(delka);
	}
	catch (const exception& e)
	{
		cerr << "Chyba: " << e.what() << "\n";
	}
	return 0;
}

void zobraz(int)
{
	cout << "int" << "\n";
}

void zobraz(double)
{
	cout << "double" << "\n";
}

template <class T>
void test(vector<T> data)
{
	zobraz(typename vector<T>::value_type{});
}

int alokacniStrategieVektoru()
{
	alokacniStrategie<vector<char>>();

	vector<int> a;
	vector<double> b;

	test(a);
	test(b);

	return 0;
}

int konstruktoryVektoru()
{
	cout << "fill...\n";
	vector<int> a(3);
	CPP_ZOBRAZ(a);
	vector<string> b(3, "hura");
	CPP_ZOBRAZ(b);

	vector<int> x( 3, 42 );
	CPP_ZOBRAZ(x);
	cout << "\n";

	cout << "range...\n";
	ifstream is{ "CISLA.TXT" };
	vector<int> c{ istream_iterator<int>{is}, {} };
	CPP_ZOBRAZ(c);
	cout << "\n";

	cout << "copy...\n";
	vector<string> d = b;
	CPP_ZOBRAZ(b);
	CPP_ZOBRAZ(d);
	cout << "\n";

	cout << "move...\n";
	vector<string> e = move(b);
	CPP_ZOBRAZ(b);
	CPP_ZOBRAZ(e);
	cout << "\n";

	cout << "initializer_list...\n";
	vector f{1, 2, 3, 4};
	CPP_ZOBRAZ(f);
	return 0;
}

int assigmenty()
{
	vector<int> a;

	cout << "fill...\n";
	a.assign(3, 42);
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "range...\n";
	ifstream is{ "CISLA.TXT" };
	a.assign( istream_iterator<int>{is}, {} );
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "copy...\n";
	vector<int> b;
	b = a;
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	cout << "\n";

	cout << "move...\n";
	vector<int> c;
	c = move(a);
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(c);
	cout << "\n";

	cout << "initializer_list...\n";
	a = {1, 2, 3};
	CPP_ZOBRAZ(a);
	cout << "\n";
	return 0;
}

int vkladani()
{
	string text = "ahoj";
	vector<string> a;

	cout << "copy push_back\n";
	a.push_back(text);
	cout << "text = " << text << "\n";
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "move push_back\n";
	a.push_back(move(text));
	cout << "text = " << text << "\n";

	a.push_back("text"s);
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "emplace_back\n";
	a.emplace_back(5, '-');
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "single element insert\n";
	auto novyPrvek = a.insert(a.begin(), ""s);
	*novyPrvek = "prvni";
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "fill insert\n";
	a.insert(a.end(), 3, "hura"s);
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "range insert\n";
	ifstream is{ "CISLA.TXT" };
	a.insert(a.end(), istream_iterator<string>{is}, {});
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "initializer_list insert\n";
	a.insert(a.end(), {"raz"s, "dva"s});
	CPP_ZOBRAZ(a);
	cout << "\n";
	return 0;
}

int mazaniPrvku()
{
	vector<int> a;
	generate_n(back_inserter(a), 20, Rand{10, 20});
	CPP_ZOBRAZ(a);

	auto prvek = a.begin();
	cout << "Mazeme prvek " << *prvek << "\n";
	prvek = a.erase(prvek);
	cout << "Prvek = " << *prvek << "\n";
	CPP_ZOBRAZ(a);

	prvek = a.erase(prvek, next(prvek, 3));
	cout << "Prvek = " << *prvek << "\n";
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "pop_back\n";
	while (!a.empty())
	{
		cout << a.back() << " ";
		a.pop_back();
	}
	cout << "\n";
	CPP_ZOBRAZ(a);
	cout << "capacity = " << a.capacity() << "\n";
	cout << "\n";

	cout << "resize\n";
	a.resize(5, 42);
	CPP_ZOBRAZ(a);
	a.resize(3);
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "clear\n";
	a.clear();
	CPP_ZOBRAZ(a);
	cout << "capacity = " << a.capacity() << "\n";
	return 0;
}

int naivniMazani()
{
	vector<Int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "Smazte sude prvky pomoci cyklu:\n";

	Int::counter = 0;
	auto zac = a.begin();
	while (zac != a.end())
	{
		if (jeSude(*zac))
		{
			zac = a.erase(zac);
		}
		else
		{
			++zac;
		}
	}
	cout << "counter = " << Int::counter << "\n";
	CPP_ZOBRAZ(a);
	cout << "\n";
	return 0;
}

int removeErase()
{
	vector<Int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "remove-erase idiom:\n";
	Int::counter = 0;
	
#if 0
	auto pos = remove_if(a.begin(), a.end(), &jeSude);
	a.erase(pos, a.end());
#else
	erase_if(a, &jeSude);
#endif // 0

	cout << "counter = " << Int::counter << "\n";
	CPP_ZOBRAZ(a);
	cout << "\n";
	return 0;
}