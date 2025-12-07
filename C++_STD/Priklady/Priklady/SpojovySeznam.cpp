#include "SablonyFunkci.h"

#include <list>

using namespace std;

int mazaniSeznam()
{
	list<Int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "Smazte sude prvky pomoci cyklu:\n";

	Int::counter = 0;
#if 0
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
#elif 0
	a.remove_if(&jeSude);
#else
	erase_if(a, &jeSude);
#endif // 0

	cout << "counter = " << Int::counter << "\n";
	CPP_ZOBRAZ(a);
	cout << "\n";	return 0;
}

int sortUniqueReverse()
{
	list<int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "sort...\n";
	a.sort();
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "unique...\n";
	a.unique();
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "reverse...\n";
	a.reverse();
	CPP_ZOBRAZ(a);
	cout << "\n";

	return 0;
}

int spliceMerge()
{
	list<int> a, b;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);

	auto prvek = ranges::find(a, 20);
	cout << *prvek << " je na pozici " << distance(a.begin(), prvek) << " uvnitr instance a\n";
	cout << "\n";

	cout << "single element splice ...\n";
	b.splice(b.end(), a, prvek);
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	cout << *prvek << " je na pozici " << distance(b.begin(), prvek) << " uvnitr instance b\n";
	cout << "\n";

	cout << "range element splice ...\n";
	b.splice(b.begin(), a, a.begin(), next(a.begin(), 3));
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	cout << *prvek << " je na pozici " << distance(b.begin(), prvek) << " uvnitr instance b\n";
	cout << "\n";

	cout << "full container splice ...\n";
	a.splice(a.end(), b);
	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	cout << *prvek << " je na pozici " << distance(a.begin(), prvek) << " uvnitr instance a\n";
	cout << "\n";

	cout << "merge ...\n";

	a = { 1, 2, 3, 4 };
	b = { 3, 4, 5, 6 };

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);

	a.merge(b);

	CPP_ZOBRAZ(a);
	CPP_ZOBRAZ(b);
	return 0;
}