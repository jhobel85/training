#include "SablonyFunkci.h"

#include <set>
#include <vector>

using namespace std;

int setMultiset()
{
	multiset<int> a;
	set<int> b;
	Rand fn{ 10, 20 };

	for (size_t i = 0; i < 20; i++)
	{
		const int prvek = fn();
		a.insert(prvek);
		auto [pos, jeVlozeno] = b.insert(prvek);
		if (!jeVlozeno)
		{
			cout << *pos << " je duplicitni\n";
		}
	}

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	return 0;
}

int lookupSet()
{
	multiset<int> a;
	generate_n(inserter(a, a.end()), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane cislo (k - konec): ";
		int hodnota;
		cin >> hodnota;
		if (!cin)
		{
			break;
		}

		cout << "Prvek " << (a.contains(hodnota) ? "nalezen" : "nenalezen") << "!\n";
		cout << "pocet vyskytu je " << a.count(hodnota) << "\n";
		cout << "prvni vyskyt je " << distance(a.begin(), a.find(hodnota)) << "\n";
		auto [lb, ub] = a.equal_range(hodnota);
		cout << "lower_bound " << distance(a.begin(), lb) << "\n";
		cout << "upper_bound " << distance(a.begin(), ub) << "\n";
	}
	return 0;
}

int setrideneVkladani()
{
	vector<int> a;
	vector<int> b;
	Rand fn{ 10, 20 };

	for (size_t i = 0; i < 20; i++)
	{
		const int prvek = fn();
		insertMulti(a, prvek);
		bool jeVlozeno = insertUnique(b, prvek);
		if (!jeVlozeno)
		{
			cout << prvek << " je duplicitni\n";
		}
	}

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	return 0;
}

int lookupVector()
{
	vector<int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	greater<int> fn;
	ranges::sort(a, fn);
	CPP_ZOBRAZ(a);

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane cislo (k - konec): ";
		int hodnota;
		cin >> hodnota;
		if (!cin)
		{
			break;
		}

		cout << "Prvek " << (ranges::binary_search(a, hodnota, fn) ? "nalezen" : "nenalezen") << "!\n";
		cout << "prvni vyskyt je " <<
			distance(a.begin(), binaryFind(a, hodnota, fn))
			<< "\n";
	}
	return 0;
}

class PorovnejRetezce
{
public:
	bool operator() (const char* lhs, const char* rhs) const
	{
		return strcmp(lhs, rhs) < 0;
	}
};

int tridiciPredikaty()
{
	multiset<const char*> a{
		"skakal", "pes", "pres", "oves"
	};
	CPP_ZOBRAZ(a);

	multiset<const char*, PorovnejRetezce> b{
		"skakal", "pes", "pres", "oves"
	};
	CPP_ZOBRAZ(b);

	auto fn = [](const char* lhs, const char* rhs) {
		return strlen(lhs) < strlen(rhs);
	};

#if 0
	// C++ 98
	multiset<const char*, bool (*) (const char*, const char*)> c(
		{ "skakal", "pes", "pres", "oves" },
		fn
	);
#elif 0
	// C++ 11
	multiset<const char*, decltype(fn)> c(
		{ "skakal", "pes", "pres", "oves" },
		fn
	);
#else
	// C++ 14
	multiset c(
		{ "skakal", "pes", "pres", "oves" },
		fn
	);
#endif // 0

	CPP_ZOBRAZ(c);

	return 0;
}

struct Osoba
{
	int id;
	string jmeno;
	string prijmeni;
};

ostream& operator<<(ostream& os, const Osoba& osoba)
{
	os << osoba.prijmeni << " ";
	os << osoba.jmeno << " ";
	os << "(" << osoba.id << ")";
	return os;
}

class PorovnejOsoby
{
public:
	// Enable heterogenous lookup in std::set.
	using is_transparent = void;

	template <class LHS, class RHS>
	bool operator()(const LHS& lhs, const RHS& rhs) const
	{
		return getKey(lhs) < getKey(rhs);
	}
private:
	const string& getKey(const Osoba& osoba) const
	{
		return osoba.prijmeni;
	}
	const string& getKey(const string& prijmeni) const
	{
		return prijmeni;
	}
};

int heterogenniLookupVektor()
{
	vector<Osoba> a = {
		{1, "Jan", "Jara"},
		{2, "Karel", "Vojacek"},
		{3, "Pavel", "Kvaca"},
		{4, "Lukas", "Kunc"},
	};
	PorovnejOsoby fn;
	ranges::sort(a, fn);
	CPP_ZOBRAZ(a);

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane prijmeni (k - konec): ";
		string prijmeni;
		cin >> prijmeni;
		if (prijmeni == "k")
		{
			break;
		}

#if 0
		// Homogeni lookup
		Osoba tmp{ 0, "", prijmeni };
		cout << "Prvek " << (ranges::binary_search(a, tmp, fn) ? "nalezen" : "nenalezen") << "!\n";
		cout << "prvni vyskyt je " <<
			distance(a.begin(), binaryFind(a, tmp, fn))
			<< "\n";
#else
		// Heterogeni lookup
		cout << "Prvek " << (binary_search(a.begin(), a.end(), prijmeni, fn) ? "nalezen" : "nenalezen") << "!\n";
		cout << "prvni vyskyt je " <<
			distance(a.begin(), binaryFind(a, prijmeni, fn))
			<< "\n";

#endif // 0
	}
	return 0;
}

int heterogenniLookupSet()
{
	set<Osoba, PorovnejOsoby> a = {
		{1, "Jan", "Jara"},
		{2, "Karel", "Vojacek"},
		{3, "Pavel", "Kvaca"},
		{4, "Lukas", "Kunc"},
	};
	CPP_ZOBRAZ(a);

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane prijmeni (k - konec): ";
		string prijmeni;
		cin >> prijmeni;
		if (prijmeni == "k")
		{
			break;
		}

#if 0
		// Homogeni lookup
		Osoba tmp{ 0, "", prijmeni };
		cout << "Prvek " << (a.contains(tmp) ? "nalezen" : "nenalezen") << "!\n";
		cout << "prvni vyskyt je " <<
			distance(a.begin(), a.find(tmp))
			<< "\n";
#else
		// Heterogeni lookup
		cout << "Prvek " << (a.contains(prijmeni) ? "nalezen" : "nenalezen") << "!\n";
		cout << "prvni vyskyt je " <<
			distance(a.begin(), a.find(prijmeni))
			<< "\n";

#endif // 0
	}
	return 0;
}

int mnoziny()
{
	set A{ 0, 1, 2, 3, 4 };
	set B{ 3, 4, 5, 6, 7 };
	CPP_ZOBRAZ(A);
	CPP_ZOBRAZ(B);
	cout << "\n";

	cout << "sjednoceni ";
	ranges::set_union(A, B, ostream_iterator<int>{cout, " "});
	cout << "\n";

	cout << "slouceni   ";
	ranges::merge(A, B, ostream_iterator<int>{cout, " "});
	cout << "\n";

	cout << "prunik     ";
	ranges::set_intersection(A, B, ostream_iterator<int>{cout, " "});
	cout << "\n";

	cout << "rozdil     ";
	ranges::set_difference(A, B, ostream_iterator<int>{cout, " "});
	cout << "\n";

	cout << "sym.rozdil ";
	ranges::set_symmetric_difference(A, B, ostream_iterator<int>{cout, " "});
	cout << "\n";
	return 0;
}

int setSplice()
{
	set<string> a{ "skakal"s, "pes"s }, b;

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	cout << "\n";
	auto pos = a.find("pes"s);
	auto node = a.extract(pos);
	b.insert(move(node));

//	b.insert(move(*pos));
//	a.erase(pos);

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	return 0;
}