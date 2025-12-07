#include "SablonyFunkci.h"

#include <fstream>
#include <iterator>
#include <list>
#include <memory>
#include <ranges>

using namespace std;

int zpetneHledani()
{
	int pole[20] = {};
	cpp_generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);
	cout << "\n";

	const int prvek = 13;
	auto prvniPos = find(begin(pole), end(pole), prvek);
	cout << "prvni vyskyt prvku " << *prvniPos << " je na pozici ";
	cout << distance(begin(pole), prvniPos) << "\n";
	cout << "\n";

	auto posledniPos = find(rbegin(pole), rend(pole), prvek);
	auto base = prev(posledniPos.base());
	cout << "posledni vyskyt prvku " << *posledniPos << " base " << *base << " je na pozici ";
	cout << distance(begin(pole), base) << "\n";
	cout << "\n";

	cout << "posledni 13 = " << rfind(pole, end(pole), 13) - pole << "\n";
	cout << "posledni 17 = " << rfind(pole, end(pole), 17) - pole << "\n";
	cout << "posledni 0  = " << rfind(pole, end(pole), 0) - pole << "\n";
	return 0;
}

int moveIteratory()
{
	auto zobrazRange = [](auto zac, auto kon, const char* title) {
		cout << title;
		for_each(zac, kon, [](const auto& ptr) {
			if (ptr)
				cout << *ptr;
			else
				cout << "(null)";
			cout << " ";
			});
		cout << "\n";
	};

	auto zobraz = [zobrazRange](const auto& pole, const char* title) {
		zobrazRange(begin(pole), end(pole), title);
	};

	unique_ptr<int> a[5] = {
		make_unique<int>(5),
		make_unique<int>(7),
		make_unique<int>(4),
		make_unique<int>(2),
		make_unique<int>(1),
	};
	unique_ptr<int> b[5] = {};

	zobraz(a, "a = ");
	zobraz(b, "b = ");
	cout << "\n";

	cout << "Algoritmus move\n";
	move(begin(a), end(a), b);

	zobraz(a, "a = ");
	zobraz(b, "b = ");
	cout << "\n";

	cout << "Algoritmus copy + make_move_iterator\n";
	copy(make_move_iterator(begin(b)), make_move_iterator(end(b)), a);

	zobraz(a, "a = ");
	zobraz(b, "b = ");
	cout << "\n";

	auto kon = remove_if(
		make_move_iterator(begin(a)), make_move_iterator(end(a)),
		[](const auto& ptr) {
			return jeSude(*ptr);
		});
	zobrazRange(make_move_iterator(begin(a)), kon, "a = ");
	return 0;
}

int vystupniProudovyIterator()
{
	int pole[20] = {};
	generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);
	cout << "\n";

	cout << "ostream_iterator\n";
	ofstream os{ "CISLA.TXT" };
	ranges::copy(pole, ostream_iterator<int>{os, " "});

	return 0;
}

int composableViews()
{
	ranges::copy(
		ranges::iota_view{1, 20} | views::filter(jeSude),
		ostream_iterator<int>{cout, " "});
	cout << "\n";
	return 0;
}

int vstupniProudovyIterator()
{
	ifstream is{ "CISLA.TXT" };
	cout << "istream_iterator\n";
#if 0
	copy(
		istream_iterator<int>{is}, {},
		ostream_iterator<int>{cout, " "}
	);
#else
	ranges::copy(
		ranges::istream_view<int>{is},
		ostream_iterator<int>{cout, " "}
	);
#endif // 0

	cout << "\n";
	return 0;
}

int streamBufferIterator()
{
	ifstream is{ __FILE__ };
#if 0
	cout << is.rdbuf();
#elif 0
	is >> noskipws;
	// Formatovane cteni.
	copy(
		istream_iterator<char>{is}, {},
		ostream_iterator<char>{cout}
	);
#else
	// Neformatovane cteni.
	copy(
		istreambuf_iterator<char>{is}, {},
		ostream_iterator<char>{cout}
	);
#endif // 0

	return 0;
}

int vkladaciIteratory()
{
	auto prvky = [i = 0]() mutable {
		return i++;
	};

	list<int> a;

	cout << "back_inserter\n";
	generate_n(back_inserter(a), 5 , ref(prvky));
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "front_inserter\n";
	generate_n(front_inserter(a), 5, ref(prvky));
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "inserter\n";
	generate_n(inserter(a, next(begin(a), 5)), 5, ref(prvky));
	CPP_ZOBRAZ(a);
	cout << "\n";
	return 0;
}